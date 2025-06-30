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
    gen->in_multi_call_operation = 0;
    gen->saved_args_base_offset = 0;
    gen->strings = NULL;
    gen->string_counter = 0;
    gen->current_function_params = NULL;

    return gen;
}

/* Destrói o gerador de código */
void destroy_code_generator(code_generator *gen)
{
    if (!gen)
        return;

    /* Libera strings literais */
    string_literal *current = gen->strings;
    while (current)
    {
        string_literal *next = current->next;
        free(current->content);
        free(current->label);
        free(current);
        current = next;
    }

    free(gen);
}

/* Adiciona uma string literal e retorna seu label */
char *add_string_literal(code_generator *gen, const char *content)
{
    /* Verifica se a string já existe */
    string_literal *current = gen->strings;
    while (current)
    {
        if (strcmp(current->content, content) == 0)
        {
            return current->label;
        }
        current = current->next;
    }

    /* Cria nova string literal */
    string_literal *new_string = (string_literal *)malloc(sizeof(string_literal));
    new_string->content = strdup(content);

    /* Gera label único */
    char label_buffer[64];
    snprintf(label_buffer, sizeof(label_buffer), "str_%d", gen->string_counter++);
    new_string->label = strdup(label_buffer);

    /* Adiciona à lista */
    new_string->next = gen->strings;
    gen->strings = new_string;

    return new_string->label;
}

/* Gera declarações de strings literais na seção .data */
void generate_string_literals(code_generator *gen)
{
    string_literal *current = gen->strings;
    while (current)
    {
        /* Verifica se a string já tem aspas */
        if (current->content[0] == '"')
        {
            emit_code(gen, "%s: .asciiz %s", current->label, current->content);
        }
        else
        {
            emit_code(gen, "%s: .asciiz \"%s\"", current->label, current->content);
        }
        current = current->next;
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

    /* Primeiro passo: coleta todas as strings literais */
    collect_string_literals(gen, root);

    /* Cabeçalho do arquivo MIPS para SPIM */
    emit_code(gen, "# Código MIPS gerado pelo compilador Goianinha");
    emit_code(gen, "# Compatível com SPIM");
    emit_code(gen, "");
    emit_code(gen, ".data");
    emit_code(gen, "newline: .asciiz \"\\n\"");

    /* Gera declarações de strings literais */
    generate_string_literals(gen);

    /* Aloca espaço para variáveis globais */
    generate_global_variables(gen, gen->symtab);

    emit_code(gen, "");
    emit_code(gen, ".text");
    emit_code(gen, ".globl main");
    emit_code(gen, "");

    /* Gera código para o programa */
    generate_program(gen, root);
}

/* Gera declarações de variáveis globais */
void generate_global_variables(code_generator *gen, symbol_table *table)
{
    if (!table)
        return;

    symbol_entry *current = table->head;
    while (current)
    {
        /* Inclui TODAS as variáveis (globais E locais) no segmento .data */
        if (current->sym_type == SYMBOL_VAR)
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

    /* Gera bloco principal PRIMEIRO */
    emit_label(gen, "main");
    if (node->child2)
    {
        generate_main_block(gen, node->child2);
    }

    /* Gera declarações de funções DEPOIS */
    if (node->child1)
    {
        generate_declarations(gen, node->child1);
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

    /* Extrai parâmetros da função */
    if (node->child2 && node->child2->child1)
    {
        extract_function_params(gen, node->child2->child1);
    }

    /* Label da função */
    emit_label(gen, node->lexeme);

    /* Prólogo da função */
    generate_prologue(gen);

    /* Verifica se precisa salvar registradores de argumentos */
    ast_node *function_body = node->child2 && node->child2->child2 ? node->child2->child2->child2 : NULL;
    int param_count = count_function_params(gen);
    int call_count = count_function_calls_in_body(function_body);

    int need_save_args_in_prologue = (param_count >= 2) && (call_count >= 2);

    if (need_save_args_in_prologue)
    {
        emit_code(gen, "# Salvando argumentos (função com múltiplos parâmetros e chamadas)");
        emit_code(gen, "addi $sp, $sp, -16  # aloca espaço para $a0-$a3");
        emit_code(gen, "sw $a0, 12($sp)     # salva $a0");
        emit_code(gen, "sw $a1, 8($sp)      # salva $a1");
        emit_code(gen, "sw $a2, 4($sp)      # salva $a2");
        emit_code(gen, "sw $a3, 0($sp)      # salva $a3");
        gen->in_multi_call_operation = 1; /* Toda a função usa valores salvos */
        gen->saved_args_base_offset = 0;
    }

    /* Corpo da função */
    if (function_body)
    {
        generate_commands(gen, function_body); /* Comandos do bloco */
    }

    /* Restaura registradores se foram salvos */
    if (need_save_args_in_prologue)
    {
        emit_code(gen, "# Função finalizada - registradores serão restaurados no epílogo");
        gen->in_multi_call_operation = 0;
    }

    /* Epílogo da função */
    generate_epilogue(gen);

    gen->in_function = 0;
    clear_function_params(gen);
}

/* Gera código para bloco principal */
void generate_main_block(code_generator *gen, ast_node *node)
{
    if (!node)
        return;

    /* Inicializa stack pointer para main */
    emit_code(gen, "# Início do programa principal");
    emit_code(gen, "li $sp, 0x7ffe0000    # inicializa stack pointer com mais espaço");

    /* Gera comandos */
    if (node->child2)
    {
        generate_commands(gen, node->child2);
    }

    /* Termina o programa principal explicitamente */
    emit_code(gen, "");
    emit_code(gen, "# Finalização do programa");
    emit_code(gen, "li $v0, 10          # syscall para exit");
    emit_code(gen, "syscall");
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
    {
        /* Verifica se é parâmetro da função atual */
        function_param *param = find_function_param(gen, node->lexeme);
        if (gen->in_function && param)
        {
            emit_code(gen, "# Usa parâmetro %s", node->lexeme);
            if (gen->in_multi_call_operation)
            {
                /* Usa valor salvo na pilha se estamos numa operação com múltiplas chamadas */
                load_saved_param(gen, param->register_index);
            }
            else
            {
                /* Usa valor do registrador normalmente */
                emit_code(gen, "move $t0, $a%d       # usa valor do parâmetro", param->register_index);
            }
        }
        else
        {
            emit_code(gen, "# Carrega variável %s", node->lexeme);
            emit_code(gen, "lw $t0, %s          # carrega valor da variável", node->lexeme);
        }
        break;
    }

    case AST_EXPR_ASSIGN:
        generate_assignment(gen, node);
        break;

    case AST_EXPR_PLUS:
    case AST_EXPR_MINUS:
    case AST_EXPR_MULT:
    case AST_EXPR_DIV:
        generate_binary_operation(gen, node);
        break;

    case AST_EXPR_EQ:
    case AST_EXPR_NE:
    case AST_EXPR_LT:
    case AST_EXPR_GT:
    case AST_EXPR_LE:
    case AST_EXPR_GE:
        generate_relational_operation(gen, node);
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

    /* Armazena o resultado na variável ou parâmetro */
    if (node->child1->lexeme)
    {
        /* Verifica se é um parâmetro da função atual */
        function_param *param = find_function_param(gen, node->child1->lexeme);
        if (gen->in_function && param)
        {
            /* Atribuição a parâmetro - modifica o registrador */
            emit_code(gen, "move $a%d, $t0       # atribui valor ao parâmetro %s",
                      param->register_index, node->child1->lexeme);
        }
        else
        {
            /* Atribuição a variável global */
            emit_code(gen, "sw $t0, %s          # armazena valor na variável %s",
                      node->child1->lexeme, node->child1->lexeme);
        }
    }
}

/* Gera código para chamada de função */
void generate_function_call(code_generator *gen, ast_node *node)
{
    if (!node || !node->child1)
        return;

    const char *func_name = node->child1->lexeme;

    /* Passagem de argumentos */
    if (node->child2)
    {
        emit_code(gen, "# Preparando argumentos para %s", func_name);
        generate_function_arguments(gen, node->child2, 0);
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
        const char *string_label = add_string_literal(gen, node->child1->lexeme);
        emit_code(gen, "# Escrita de string");
        emit_code(gen, "li $v0, 4           # syscall para print string");
        emit_code(gen, "la $a0, %s          # carrega endereço da string", string_label);
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

/* Verifica se há chamadas de função em uma expressão */
int has_function_call(ast_node *node)
{
    if (!node)
        return 0;

    if (node->type == AST_EXPR_CALL)
        return 1;

    return has_function_call(node->child1) ||
           has_function_call(node->child2) ||
           has_function_call(node->child3) ||
           has_function_call(node->child4);
}

/* Gera código para carregar parâmetro salvo na pilha */
void load_saved_param(code_generator *gen, int register_index)
{
    /* Calcula offset relativo à posição base onde os argumentos foram salvos */
    int base_offset = 12 - (register_index * 4);            /* $a0 em 12, $a1 em 8, etc. */
    int current_extra_offset = gen->saved_args_base_offset; /* Quantos bytes a pilha cresceu desde o salvamento */
    int final_offset = base_offset + current_extra_offset;
    emit_code(gen, "lw $t0, %d($sp)        # carrega parâmetro salvo (offset ajustado)", final_offset);
}

/* Conta chamadas de função no corpo de uma função */
int count_function_calls_in_body(ast_node *body)
{
    if (!body)
        return 0;

    int count = 0;

    if (body->type == AST_EXPR_CALL)
        count++;

    count += count_function_calls_in_body(body->child1);
    count += count_function_calls_in_body(body->child2);
    count += count_function_calls_in_body(body->child3);
    count += count_function_calls_in_body(body->child4);

    return count;
}

/* Conta número de parâmetros da função atual */
int count_function_params(code_generator *gen)
{
    int count = 0;
    function_param *current = gen->current_function_params;
    while (current)
    {
        count++;
        current = current->next;
    }
    return count;
}

/* Gera código para operação binária */
void generate_binary_operation(code_generator *gen, ast_node *node)
{
    if (!node || !node->child1 || !node->child2)
        return;

    /* Verifica se há chamadas de função nos operandos */
    int left_has_call = has_function_call(node->child1);
    int right_has_call = has_function_call(node->child2);
    int need_save_args = gen->in_function && left_has_call && right_has_call;

    /* Salva registradores de argumentos se necessário */
    if (need_save_args)
    {
        emit_code(gen, "# Salvando registradores $a0-$a3 (chamadas múltiplas)");
        emit_code(gen, "addi $sp, $sp, -16  # aloca espaço para $a0-$a3");
        emit_code(gen, "sw $a0, 12($sp)     # salva $a0");
        emit_code(gen, "sw $a1, 8($sp)      # salva $a1");
        emit_code(gen, "sw $a2, 4($sp)      # salva $a2");
        emit_code(gen, "sw $a3, 0($sp)      # salva $a3");
        gen->in_multi_call_operation = 1; /* Marca que estamos numa operação com múltiplas chamadas */
        gen->saved_args_base_offset = 0;  /* Reseta contador de mudanças na pilha */
    }

    /* Gera código para operando esquerdo */
    generate_expression(gen, node->child1);
    emit_code(gen, "addi $sp, $sp, -4   # aloca espaço na pilha");
    if (need_save_args)
        gen->saved_args_base_offset += 4; /* Rastreia mudança na pilha */
    emit_code(gen, "sw $t0, 0($sp)      # salva operando esquerdo na pilha");

    /* Gera código para operando direito */
    generate_expression(gen, node->child2);
    emit_code(gen, "move $t1, $t0       # move operando direito para $t1");
    emit_code(gen, "lw $t0, 0($sp)      # recupera operando esquerdo da pilha");
    emit_code(gen, "addi $sp, $sp, 4    # libera espaço da pilha");
    if (need_save_args)
        gen->saved_args_base_offset -= 4; /* Rastreia mudança na pilha */

    /* Restaura registradores de argumentos se salvou */
    if (need_save_args)
    {
        emit_code(gen, "# Restaurando registradores $a0-$a3");
        emit_code(gen, "lw $a3, 0($sp)      # restaura $a3");
        emit_code(gen, "lw $a2, 4($sp)      # restaura $a2");
        emit_code(gen, "lw $a1, 8($sp)      # restaura $a1");
        emit_code(gen, "lw $a0, 12($sp)     # restaura $a0");
        emit_code(gen, "addi $sp, $sp, 16   # libera espaço da pilha");
        gen->in_multi_call_operation = 0; /* Fim da operação com múltiplas chamadas */
    }

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

/* Gera código para operação relacional */
void generate_relational_operation(code_generator *gen, ast_node *node)
{
    if (!node || !node->child1 || !node->child2)
        return;

    /* Verifica se há chamadas de função nos operandos */
    int left_has_call = has_function_call(node->child1);
    int right_has_call = has_function_call(node->child2);
    int need_save_args = gen->in_function && left_has_call && right_has_call;

    /* Salva registradores de argumentos se necessário */
    if (need_save_args)
    {
        emit_code(gen, "# Salvando registradores $a0-$a3 (chamadas múltiplas)");
        emit_code(gen, "addi $sp, $sp, -16  # aloca espaço para $a0-$a3");
        emit_code(gen, "sw $a0, 12($sp)     # salva $a0");
        emit_code(gen, "sw $a1, 8($sp)      # salva $a1");
        emit_code(gen, "sw $a2, 4($sp)      # salva $a2");
        emit_code(gen, "sw $a3, 0($sp)      # salva $a3");
        gen->in_multi_call_operation = 1; /* Marca que estamos numa operação com múltiplas chamadas */
        gen->saved_args_base_offset = 0;  /* Reseta contador de mudanças na pilha */
    }

    /* Gera código para operando esquerdo */
    generate_expression(gen, node->child1);
    emit_code(gen, "addi $sp, $sp, -4   # aloca espaço na pilha");
    if (need_save_args)
        gen->saved_args_base_offset += 4; /* Rastreia mudança na pilha */
    emit_code(gen, "sw $t0, 0($sp)      # salva operando esquerdo na pilha");

    /* Gera código para operando direito */
    generate_expression(gen, node->child2);
    emit_code(gen, "move $t1, $t0       # move operando direito para $t1");
    emit_code(gen, "lw $t0, 0($sp)      # recupera operando esquerdo da pilha");
    emit_code(gen, "addi $sp, $sp, 4    # libera espaço da pilha");
    if (need_save_args)
        gen->saved_args_base_offset -= 4; /* Rastreia mudança na pilha */

    /* Restaura registradores de argumentos se salvou */
    if (need_save_args)
    {
        emit_code(gen, "# Restaurando registradores $a0-$a3");
        emit_code(gen, "lw $a3, 0($sp)      # restaura $a3");
        emit_code(gen, "lw $a2, 4($sp)      # restaura $a2");
        emit_code(gen, "lw $a1, 8($sp)      # restaura $a1");
        emit_code(gen, "lw $a0, 12($sp)     # restaura $a0");
        emit_code(gen, "addi $sp, $sp, 16   # libera espaço da pilha");
        gen->in_multi_call_operation = 0; /* Fim da operação com múltiplas chamadas */
    }

    /* Realiza comparação usando instruções básicas MIPS */
    switch (node->type)
    {
    case AST_EXPR_EQ:
        emit_code(gen, "sub $t0, $t0, $t1   # subtração");
        emit_code(gen, "sltiu $t0, $t0, 1   # 1 se resultado é 0 (iguais), 0 caso contrário");
        break;
    case AST_EXPR_NE:
        emit_code(gen, "sub $t0, $t0, $t1   # subtração");
        emit_code(gen, "sltu $t0, $zero, $t0 # 1 se resultado != 0 (diferentes), 0 caso contrário");
        break;
    case AST_EXPR_LT:
        emit_code(gen, "slt $t0, $t0, $t1   # menor que");
        break;
    case AST_EXPR_GT:
        emit_code(gen, "slt $t0, $t1, $t0   # maior que (inverte operandos)");
        break;
    case AST_EXPR_LE:
        emit_code(gen, "slt $t0, $t1, $t0   # inverte para maior que");
        emit_code(gen, "xori $t0, $t0, 1    # inverte resultado (NOT)");
        break;
    case AST_EXPR_GE:
        emit_code(gen, "slt $t0, $t0, $t1   # menor que");
        emit_code(gen, "xori $t0, $t0, 1    # inverte resultado (NOT)");
        break;
    default:
        break;
    }
}

/* Coleta todas as strings literais da AST */
void collect_string_literals(code_generator *gen, ast_node *node)
{
    if (!node)
        return;

    /* Se é uma string literal, adiciona à lista */
    if (node->type == AST_STRING && node->lexeme)
    {
        add_string_literal(gen, node->lexeme);
    }

    /* Recursivamente percorre os filhos */
    collect_string_literals(gen, node->child1);
    collect_string_literals(gen, node->child2);
    collect_string_literals(gen, node->child3);
    collect_string_literals(gen, node->child4);
}

/* Adiciona um parâmetro à lista da função atual */
void add_codegen_function_param(code_generator *gen, const char *param_name, int register_index)
{
    function_param *new_param = (function_param *)malloc(sizeof(function_param));
    new_param->name = strdup(param_name);
    new_param->register_index = register_index;
    new_param->next = gen->current_function_params;
    gen->current_function_params = new_param;
}

/* Limpa a lista de parâmetros da função atual */
void clear_function_params(code_generator *gen)
{
    function_param *current = gen->current_function_params;
    while (current)
    {
        function_param *next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
    gen->current_function_params = NULL;
}

/* Busca um parâmetro pelo nome */
function_param *find_function_param(code_generator *gen, const char *param_name)
{
    function_param *current = gen->current_function_params;
    while (current)
    {
        if (strcmp(current->name, param_name) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/* Extrai parâmetros da AST de uma função */
void extract_function_params(code_generator *gen, ast_node *params_node)
{
    if (!params_node)
        return;

    int param_index = 0;

    /* Se é uma lista de parâmetros */
    if (params_node->type == AST_LISTA_PARAM)
    {
        ast_node *current = params_node;
        while (current && current->type == AST_LISTA_PARAM)
        {
            /* Processa child1 se for um PARAM */
            if (current->child1 && current->child1->type == AST_PARAM)
            {
                ast_node *param = current->child1;
                if (param->child2 && param->child2->lexeme)
                {
                    add_codegen_function_param(gen, param->child2->lexeme, param_index++);
                }
            }

            /* Verifica se child2 é um PARAM (caso de múltiplos parâmetros) */
            if (current->child2 && current->child2->type == AST_PARAM)
            {
                ast_node *param = current->child2;
                if (param->child2 && param->child2->lexeme)
                {
                    add_codegen_function_param(gen, param->child2->lexeme, param_index++);
                }
                break; /* Processou os parâmetros desta lista */
            }

            current = current->child2;
        }
    }
    /* Se é um parâmetro único */
    else if (params_node->type == AST_PARAM)
    {
        if (params_node->child2 && params_node->child2->lexeme)
        {
            add_codegen_function_param(gen, params_node->child2->lexeme, param_index++);
        }
    }
}

/* Gera código para argumentos de função (recursivo para múltiplos argumentos) */
void generate_function_arguments(code_generator *gen, ast_node *args, int arg_index)
{
    if (!args)
        return;

    if (args->type == AST_LISTA_EXPR)
    {
        /* Processa argumentos recursivamente */
        if (args->child1)
        {
            if (args->child1->type == AST_LISTA_EXPR)
            {
                /* Se child1 é uma lista, processa recursivamente */
                generate_function_arguments(gen, args->child1, arg_index);
                /* Calcula quantos argumentos foram processados em child1 */
                int child1_count = count_codegen_arguments(args->child1);
                arg_index += child1_count;
            }
            else
            {
                /* Se child1 é um argumento simples, gera código */
                generate_expression(gen, args->child1);
                emit_code(gen, "move $a%d, $t0       # passa argumento %d", arg_index, arg_index);
                arg_index++;
            }
        }

        /* Processa argumentos restantes */
        if (args->child2)
        {
            generate_function_arguments(gen, args->child2, arg_index);
        }
    }
    else
    {
        /* Argumento único */
        generate_expression(gen, args);
        emit_code(gen, "move $a%d, $t0       # passa argumento %d", arg_index, arg_index);
    }
}

/* Conta recursivamente o número de argumentos (versão para gerador de código) */
int count_codegen_arguments(ast_node *args)
{
    if (!args)
        return 0;

    if (args->type == AST_LISTA_EXPR)
    {
        /* Conta argumentos recursivamente */
        int count = 0;
        if (args->child1)
        {
            if (args->child1->type == AST_LISTA_EXPR)
            {
                /* Se child1 é uma lista, conta recursivamente */
                count += count_codegen_arguments(args->child1);
            }
            else
            {
                /* Se child1 é um argumento, conta como 1 */
                count = 1;
            }
        }
        if (args->child2)
        {
            count += count_codegen_arguments(args->child2); /* Argumentos restantes */
        }
        return count;
    }
    else
    {
        /* Argumento único */
        return 1;
    }
}