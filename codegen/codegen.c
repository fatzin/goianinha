#include "codegen.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/* Cria um novo gerador de código */
code_generator *create_code_generator(FILE *output, symbol_table *symtab)
{
    code_generator *gen = (code_generator *)malloc(sizeof(code_generator));
    if (!gen)
    {
        fprintf(stderr, "ERRO: Falha na alocação de memória para gerador de código\n");
        exit(1);
    }

    gen->output_file = output;
    gen->symtab = symtab;
    gen->label_counter = 0;
    gen->current_offset = 0;
    gen->in_function = 0;

    return gen;
}

/* Destrói o gerador de código */
void destroy_code_generator(code_generator *gen)
{
    if (gen)
    {
        free(gen);
    }
}

/* Emite código MIPS */
void emit_code(code_generator *gen, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(gen->output_file, format, args);
    va_end(args);
    fprintf(gen->output_file, "\n");
}

/* Emite um rótulo */
void emit_label(code_generator *gen, const char *label)
{
    fprintf(gen->output_file, "%s:\n", label);
}

/* Gera um rótulo único */
char *generate_label(code_generator *gen, const char *prefix)
{
    char *label = (char *)malloc(50);
    sprintf(label, "%s%d", prefix, gen->label_counter++);
    return label;
}

/* Função principal de geração de código */
void generate_code(code_generator *gen, ast_node *root)
{
    if (!gen || !root)
        return;

    /* Cabeçalho do arquivo MIPS para SPIM */
    emit_code(gen, "# Código MIPS gerado pelo compilador Goianinha");
    emit_code(gen, "# Compatível com SPIM");
    emit_code(gen, "");
    emit_code(gen, ".data");
    emit_code(gen, "newline: .asciiz \"\\n\"");

    /* Aloca espaço para variáveis globais */
    generate_global_variables(gen, gen->symtab);

    emit_code(gen, "");
    emit_code(gen, ".text");
    emit_code(gen, ".globl main");
    emit_code(gen, "");

    /* Gera código para o programa */
    generate_program(gen, root);

    /* Finalização do programa */
    emit_code(gen, "");
    emit_code(gen, "# Finalização do programa");
    emit_code(gen, "li $v0, 10          # syscall para exit");
    emit_code(gen, "syscall");
}

/* Gera declarações de variáveis globais */
void generate_global_variables(code_generator *gen, symbol_table *table)
{
    if (!table)
        return;

    symbol_entry *current = table->head;
    while (current)
    {
        if (current->sym_type == SYMBOL_VAR && current->scope == SCOPE_GLOBAL)
        {
            emit_code(gen, "%s: .word 0         # variável %s",
                      current->name, current->name);
        }
        current = current->next;
    }
}

/* Gera código para o programa principal */
void generate_program(code_generator *gen, ast_node *node)
{
    if (!node || node->type != AST_PROGRAMA)
        return;

    /* Gera declarações de funções */
    if (node->child1)
    {
        generate_declarations(gen, node->child1);
    }

    /* Gera bloco principal */
    emit_label(gen, "main");
    if (node->child2)
    {
        generate_main_block(gen, node->child2);
    }
}

/* Gera código para declarações */
void generate_declarations(code_generator *gen, ast_node *node)
{
    if (!node)
        return;

    switch (node->type)
    {
    case AST_LISTA_DECL_FUNC_VAR:
        if (node->child1)
            generate_declarations(gen, node->child1);
        if (node->child2)
            generate_declarations(gen, node->child2);
        break;

    case AST_DECL_FUNC:
        generate_function(gen, node);
        break;

    case AST_DECL_VAR:
        /* Variáveis globais são alocadas na seção .data (implementação simplificada) */
        break;

    default:
        break;
    }
}

/* Gera código para função */
void generate_function(code_generator *gen, ast_node *node)
{
    if (!node || !node->lexeme)
        return;

    gen->in_function = 1;

    /* Label da função */
    emit_label(gen, node->lexeme);

    /* Prólogo da função */
    generate_prologue(gen);

    /* Corpo da função */
    if (node->child2 && node->child2->child2)
    {
        generate_commands(gen, node->child2->child2->child2); /* Comandos do bloco */
    }

    /* Epílogo da função */
    generate_epilogue(gen);

    gen->in_function = 0;
}

/* Gera código para bloco principal */
void generate_main_block(code_generator *gen, ast_node *node)
{
    if (!node)
        return;

    /* Prólogo simplificado para main */
    emit_code(gen, "# Início do programa principal");

    /* Gera comandos */
    if (node->child2)
    {
        generate_commands(gen, node->child2);
    }
}

/* Gera código para comandos */
void generate_commands(code_generator *gen, ast_node *node)
{
    if (!node)
        return;

    switch (node->type)
    {
    case AST_LISTA_CMD:
        if (node->child1)
            generate_commands(gen, node->child1);
        if (node->child2)
            generate_commands(gen, node->child2);
        break;

    case AST_CMD_EXPR:
        if (node->child1)
            generate_expression(gen, node->child1);
        break;

    case AST_CMD_LEIA:
        generate_read_statement(gen, node);
        break;

    case AST_CMD_ESCREVA:
        generate_write_statement(gen, node);
        break;

    case AST_CMD_NOVALINHA:
        emit_code(gen, "# Nova linha");
        emit_code(gen, "li $v0, 4           # syscall para print string");
        emit_code(gen, "la $a0, newline     # carrega endereço da nova linha");
        emit_code(gen, "syscall");
        break;

    case AST_CMD_SE:
        generate_if_statement(gen, node);
        break;

    case AST_CMD_ENQUANTO:
        generate_while_statement(gen, node);
        break;

    case AST_CMD_RETORNE:
        generate_return_statement(gen, node);
        break;

    case AST_BLOCO:
        if (node->child2)
            generate_commands(gen, node->child2);
        break;

    default:
        break;
    }
}

/* Gera código para expressão */
void generate_expression(code_generator *gen, ast_node *node)
{
    if (!node)
        return;

    switch (node->type)
    {
    case AST_EXPR_INTCONST:
        emit_code(gen, "li $t0, %d          # carrega constante %d", node->value, node->value);
        break;

    case AST_EXPR_ID:
        emit_code(gen, "# Carrega variável %s", node->lexeme);
        emit_code(gen, "lw $t0, %s          # carrega valor da variável", node->lexeme);
        break;

    case AST_EXPR_ASSIGN:
        generate_assignment(gen, node);
        break;

    case AST_EXPR_PLUS:
    case AST_EXPR_MINUS:
    case AST_EXPR_MULT:
    case AST_EXPR_DIV:
        generate_binary_operation(gen, node);
        break;

    case AST_EXPR_CALL:
        generate_function_call(gen, node);
        break;

    default:
        break;
    }
}

/* Gera código para atribuição */
void generate_assignment(code_generator *gen, ast_node *node)
{
    if (!node || !node->child1 || !node->child2)
        return;

    /* Gera código para expressão do lado direito */
    generate_expression(gen, node->child2);

    /* Armazena o resultado na variável */
    if (node->child1->lexeme)
    {
        emit_code(gen, "sw $t0, %s          # armazena valor na variável %s",
                  node->child1->lexeme, node->child1->lexeme);
    }
}

/* Gera código para chamada de função */
void generate_function_call(code_generator *gen, ast_node *node)
{
    if (!node || !node->child1)
        return;

    const char *func_name = node->child1->lexeme;

    /* Implementação simplificada - salva argumentos em registradores */
    if (node->child2)
    {
        emit_code(gen, "# Preparando argumentos para %s", func_name);
        /* TODO: Implementar passagem de argumentos */
    }

    /* Chama a função */
    emit_code(gen, "jal %s              # chama função %s", func_name, func_name);
    emit_code(gen, "move $t0, $v0       # move resultado para $t0");
}

/* Gera código para comando de leitura */
void generate_read_statement(code_generator *gen, ast_node *node)
{
    if (!node || !node->child1)
        return;

    const char *var_name = node->child1->lexeme;

    emit_code(gen, "# Leitura da variável %s", var_name);
    emit_code(gen, "li $v0, 5           # syscall para read integer");
    emit_code(gen, "syscall");
    emit_code(gen, "sw $v0, %s          # armazena valor lido na variável", var_name);
}

/* Gera código para comando de escrita */
void generate_write_statement(code_generator *gen, ast_node *node)
{
    if (!node || !node->child1)
        return;

    if (node->child1->type == AST_STRING)
    {
        /* Escrita de string */
        emit_code(gen, "# Escrita de string");
        emit_code(gen, "li $v0, 4           # syscall para print string");
        emit_code(gen, "la $a0, string_literal # carrega endereço da string");
        emit_code(gen, "syscall");
    }
    else
    {
        /* Escrita de expressão */
        generate_expression(gen, node->child1);
        emit_code(gen, "# Escrita de valor");
        emit_code(gen, "li $v0, 1           # syscall para print integer");
        emit_code(gen, "move $a0, $t0       # move valor para $a0");
        emit_code(gen, "syscall");
    }
}

/* Gera código para comando if */
void generate_if_statement(code_generator *gen, ast_node *node)
{
    if (!node)
        return;

    char *else_label = generate_label(gen, "else_");
    char *end_label = generate_label(gen, "end_if_");

    /* Avalia condição */
    if (node->child1)
    {
        generate_expression(gen, node->child1);
        emit_code(gen, "beqz $t0, %s        # se falso, pula para else", else_label);
    }

    /* Comando then */
    if (node->child2)
    {
        generate_commands(gen, node->child2);
    }

    emit_code(gen, "j %s                # pula para fim do if", end_label);

    /* Comando else (se existir) */
    emit_label(gen, else_label);
    if (node->child3)
    {
        generate_commands(gen, node->child3);
    }

    emit_label(gen, end_label);

    free(else_label);
    free(end_label);
}

/* Gera código para comando while */
void generate_while_statement(code_generator *gen, ast_node *node)
{
    if (!node)
        return;

    char *loop_label = generate_label(gen, "loop_");
    char *end_label = generate_label(gen, "end_loop_");

    emit_label(gen, loop_label);

    /* Avalia condição */
    if (node->child1)
    {
        generate_expression(gen, node->child1);
        emit_code(gen, "beqz $t0, %s        # se falso, sai do loop", end_label);
    }

    /* Corpo do loop */
    if (node->child2)
    {
        generate_commands(gen, node->child2);
    }

    emit_code(gen, "j %s                # volta para início do loop", loop_label);
    emit_label(gen, end_label);

    free(loop_label);
    free(end_label);
}

/* Gera código para comando return */
void generate_return_statement(code_generator *gen, ast_node *node)
{
    if (!node)
        return;

    if (node->child1)
    {
        generate_expression(gen, node->child1);
        emit_code(gen, "move $v0, $t0       # move resultado para $v0");
    }

    if (gen->in_function)
    {
        generate_epilogue(gen);
    }
}

/* Gera código para operação binária */
void generate_binary_operation(code_generator *gen, ast_node *node)
{
    if (!node || !node->child1 || !node->child2)
        return;

    /* Gera código para operando esquerdo */
    generate_expression(gen, node->child1);
    emit_code(gen, "addi $sp, $sp, -4   # aloca espaço na pilha");
    emit_code(gen, "sw $t0, 0($sp)      # salva operando esquerdo na pilha");

    /* Gera código para operando direito */
    generate_expression(gen, node->child2);
    emit_code(gen, "move $t1, $t0       # move operando direito para $t1");
    emit_code(gen, "lw $t0, 0($sp)      # recupera operando esquerdo da pilha");
    emit_code(gen, "addi $sp, $sp, 4    # libera espaço da pilha");

    /* Realiza operação */
    switch (node->type)
    {
    case AST_EXPR_PLUS:
        emit_code(gen, "add $t0, $t0, $t1   # soma");
        break;
    case AST_EXPR_MINUS:
        emit_code(gen, "sub $t0, $t0, $t1   # subtração");
        break;
    case AST_EXPR_MULT:
        emit_code(gen, "mul $t0, $t0, $t1   # multiplicação");
        break;
    case AST_EXPR_DIV:
        emit_code(gen, "div $t0, $t1        # divisão");
        emit_code(gen, "mflo $t0            # move resultado da divisão");
        break;
    default:
        break;
    }
}

/* Gera prólogo da função */
void generate_prologue(code_generator *gen)
{
    emit_code(gen, "# Prólogo da função");
    emit_code(gen, "addi $sp, $sp, -8   # aloca espaço na pilha");
    emit_code(gen, "sw $ra, 4($sp)      # salva endereço de retorno");
    emit_code(gen, "sw $fp, 0($sp)      # salva frame pointer");
    emit_code(gen, "move $fp, $sp       # configura novo frame pointer");
}

/* Gera epílogo da função */
void generate_epilogue(code_generator *gen)
{
    emit_code(gen, "# Epílogo da função");
    emit_code(gen, "move $sp, $fp       # restaura stack pointer");
    emit_code(gen, "lw $fp, 0($sp)      # restaura frame pointer");
    emit_code(gen, "lw $ra, 4($sp)      # restaura endereço de retorno");
    emit_code(gen, "addi $sp, $sp, 8    # libera espaço da pilha");
    emit_code(gen, "jr $ra              # retorna");
}