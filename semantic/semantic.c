#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Cria um novo analisador semântico */
semantic_analyzer *create_semantic_analyzer(void)
{
    semantic_analyzer *analyzer = (semantic_analyzer *)malloc(sizeof(semantic_analyzer));
    if (!analyzer)
    {
        fprintf(stderr, "ERRO: Falha na alocação de memória para analisador semântico\n");
        exit(1);
    }

    analyzer->global_table = create_symbol_table(NULL);
    analyzer->current_table = analyzer->global_table;
    analyzer->has_errors = 0;
    analyzer->in_function = 0;
    analyzer->current_function_return_type = TYPE_VOID;

    return analyzer;
}

/* Destrói o analisador semântico */
void destroy_semantic_analyzer(semantic_analyzer *analyzer)
{
    if (!analyzer)
        return;

    destroy_symbol_table(analyzer->global_table);
    free(analyzer);
}

/* Função principal de análise semântica */
int analyze_program(semantic_analyzer *analyzer, ast_node *root)
{
    if (!analyzer || !root)
        return -1;

    if (root->type != AST_PROGRAMA)
    {
        semantic_error(root->line_number, "Nó raiz deve ser um programa");
        return -1;
    }

    /* Analisa declarações de funções e variáveis globais */
    if (root->child1)
    {
        analyze_declarations(analyzer, root->child1);
    }

    /* Analisa o bloco principal */
    if (root->child2)
    {
        analyze_block(analyzer, root->child2);
    }

    return analyzer->has_errors ? -1 : 0;
}

/* Imprime erro semântico */
void semantic_error(int line, const char *message)
{
    fprintf(stderr, "ERRO SEMÂNTICO linha %d: %s\n", line, message);
}

/* Converte tipo AST para tipo de dados */
data_type ast_type_to_data_type(ast_node_type type)
{
    switch (type)
    {
    case AST_TIPO_INT:
        return TYPE_INT;
    case AST_TIPO_CAR:
        return TYPE_CAR;
    default:
        return TYPE_VOID;
    }
}

/* Verifica se dois tipos são compatíveis */
int types_compatible(data_type type1, data_type type2)
{
    return type1 == type2;
}

/* Analisa declarações de funções e variáveis */
void analyze_declarations(semantic_analyzer *analyzer, ast_node *node)
{
    if (!node)
        return;

    switch (node->type)
    {
    case AST_LISTA_DECL_FUNC_VAR:
        if (node->child1)
            analyze_declarations(analyzer, node->child1);
        if (node->child2)
            analyze_declarations(analyzer, node->child2);
        break;

    case AST_DECL_VAR:
        analyze_variable_declaration(analyzer, node);
        break;

    case AST_DECL_FUNC:
        analyze_function_declaration(analyzer, node);
        break;

    default:
        break;
    }
}

/* Analisa declaração de variável */
void analyze_variable_declaration(semantic_analyzer *analyzer, ast_node *node)
{
    if (!node || !node->child1)
        return;

    data_type var_type = ast_type_to_data_type(node->child1->type);

    /* Declara a variável principal - o nome está em node->child2 se for estrutura tipo-id */
    if (node->child2 && node->child2->lexeme)
    {
        symbol_entry *entry = insert_symbol(analyzer->current_table, node->child2->lexeme,
                                            SYMBOL_VAR, var_type, node->child2->line_number);
        if (!entry)
        {
            semantic_error(node->child2->line_number, "Variável já foi declarada neste escopo");
            analyzer->has_errors = 1;
        }

        /* Se estiver numa função, também insere na tabela global para o gerador de código */
        if (analyzer->in_function && analyzer->current_table != analyzer->global_table)
        {
            insert_symbol(analyzer->global_table, node->child2->lexeme,
                          SYMBOL_VAR, var_type, node->child2->line_number);
        }
    }
    else if (node->lexeme)
    {
        /* Para declarações globais onde o nome está no próprio nó */
        symbol_entry *entry = insert_symbol(analyzer->current_table, node->lexeme,
                                            SYMBOL_VAR, var_type, node->line_number);
        if (!entry)
        {
            semantic_error(node->line_number, "Variável já foi declarada neste escopo");
            analyzer->has_errors = 1;
        }

        /* Se estiver numa função, também insere na tabela global para o gerador de código */
        if (analyzer->in_function && analyzer->current_table != analyzer->global_table)
        {
            insert_symbol(analyzer->global_table, node->lexeme,
                          SYMBOL_VAR, var_type, node->line_number);
        }
    }

    /* Declara variáveis adicionais na lista - verifica child2 para declarações globais */
    ast_node *var_list = node->child2 ? node->child2 : node->child3;
    while (var_list)
    {
        if (var_list->type == AST_LISTA_DECL_VAR && var_list->child1)
        {
            ast_node *var_id = var_list->child1;
            if (var_id->lexeme)
            {
                symbol_entry *entry = insert_symbol(analyzer->current_table, var_id->lexeme,
                                                    SYMBOL_VAR, var_type, var_id->line_number);
                if (!entry)
                {
                    semantic_error(var_id->line_number, "Variável já foi declarada neste escopo");
                    analyzer->has_errors = 1;
                }

                /* Se estiver numa função, também insere na tabela global para o gerador de código */
                if (analyzer->in_function && analyzer->current_table != analyzer->global_table)
                {
                    insert_symbol(analyzer->global_table, var_id->lexeme,
                                  SYMBOL_VAR, var_type, var_id->line_number);
                }
            }
            var_list = var_list->child2;
        }
        else
        {
            break;
        }
    }
}

/* Analisa declaração de função */
void analyze_function_declaration(semantic_analyzer *analyzer, ast_node *node)
{
    if (!node || !node->child1)
        return;

    data_type func_type = ast_type_to_data_type(node->child1->type);

    /* Insere a função na tabela de símbolos global */
    symbol_entry *func_entry = insert_symbol(analyzer->global_table, node->lexeme,
                                             SYMBOL_FUNC, func_type, node->line_number);
    if (!func_entry)
    {
        semantic_error(node->line_number, "Função já foi declarada");
        analyzer->has_errors = 1;
        return;
    }

    /* Cria novo escopo para a função */
    symbol_table *func_table = create_symbol_table(analyzer->global_table);
    symbol_table *old_table = analyzer->current_table;
    analyzer->current_table = func_table;
    analyzer->in_function = 1;
    analyzer->current_function_return_type = func_type;

    /* Analisa parâmetros da função */
    if (node->child2 && node->child2->child1)
    {
        ast_node *params = node->child2->child1;
        analyze_function_parameters(analyzer, params, func_entry);
    }

    /* Analisa corpo da função */
    if (node->child2 && node->child2->child2)
    {
        analyze_block(analyzer, node->child2->child2);
    }

    /* Restaura escopo anterior */
    analyzer->current_table = old_table;
    analyzer->in_function = 0;
    analyzer->current_function_return_type = TYPE_VOID;
    destroy_symbol_table(func_table);
}

/* Analisa parâmetros de função */
void analyze_function_parameters(semantic_analyzer *analyzer, ast_node *params, symbol_entry *func_entry)
{
    if (!params)
        return;

    switch (params->type)
    {
    case AST_LISTA_PARAM:
        if (params->child1)
            analyze_function_parameters(analyzer, params->child1, func_entry);
        if (params->child2)
            analyze_function_parameters(analyzer, params->child2, func_entry);
        break;

    case AST_PARAM:
        if (params->child1 && params->child2)
        {
            data_type param_type = ast_type_to_data_type(params->child1->type);
            const char *param_name = params->child2->lexeme;

            /* Adiciona parâmetro à função */
            add_function_param(func_entry, param_type, param_name);

            /* Insere parâmetro no escopo local da função */
            symbol_entry *param_entry = insert_symbol(analyzer->current_table, param_name,
                                                      SYMBOL_PARAM, param_type, params->child2->line_number);
            if (!param_entry)
            {
                semantic_error(params->child2->line_number, "Parâmetro já foi declarado");
                analyzer->has_errors = 1;
            }
        }
        break;

    default:
        break;
    }
}

/* Analisa bloco de comandos */
void analyze_block(semantic_analyzer *analyzer, ast_node *node)
{
    if (!node)
        return;

    /* Para o bloco principal, não cria novo escopo */
    /* Para blocos dentro de funções, mantém o escopo da função */

    /* Analisa declarações locais */
    if (node->child1)
    {
        analyze_local_declarations(analyzer, node->child1);
    }

    /* Analisa comandos */
    if (node->child2)
    {
        analyze_commands(analyzer, node->child2);
    }
}

/* Analisa declarações locais */
void analyze_local_declarations(semantic_analyzer *analyzer, ast_node *node)
{
    if (!node)
        return;

    if (node->type == AST_LISTA_DECL_VAR)
    {
        if (node->child1)
        {
            analyze_variable_declaration(analyzer, node->child1);
        }
        if (node->child2)
        {
            analyze_local_declarations(analyzer, node->child2);
        }
    }
    else if (node->type == AST_DECL_VAR)
    {
        analyze_variable_declaration(analyzer, node);
    }
}

/* Analisa comandos */
void analyze_commands(semantic_analyzer *analyzer, ast_node *node)
{
    if (!node)
        return;

    switch (node->type)
    {
    case AST_LISTA_CMD:
        if (node->child1)
            analyze_commands(analyzer, node->child1);
        if (node->child2)
            analyze_commands(analyzer, node->child2);
        break;

    case AST_CMD_EXPR:
        if (node->child1)
            analyze_expression(analyzer, node->child1);
        break;

    case AST_CMD_RETORNE:
        if (!analyzer->in_function)
        {
            semantic_error(node->line_number, "Comando 'retorne' só pode ser usado dentro de funções");
            analyzer->has_errors = 1;
        }
        else if (node->child1)
        {
            data_type expr_type = get_expression_type(analyzer, node->child1);
            if (!types_compatible(expr_type, analyzer->current_function_return_type))
            {
                semantic_error(node->line_number, "Tipo de retorno incompatível com tipo da função");
                analyzer->has_errors = 1;
            }
        }
        break;

    case AST_CMD_LEIA:
        if (node->child1 && node->child1->lexeme)
        {
            symbol_entry *var = lookup_symbol(analyzer->current_table, node->child1->lexeme);
            if (!var)
            {
                semantic_error(node->child1->line_number, "Variável não foi declarada");
                analyzer->has_errors = 1;
            }
            else if (var->sym_type != SYMBOL_VAR && var->sym_type != SYMBOL_PARAM)
            {
                semantic_error(node->child1->line_number, "Só é possível ler valores para variáveis");
                analyzer->has_errors = 1;
            }
        }
        break;

    case AST_CMD_ESCREVA:
        if (node->child1)
        {
            if (node->child1->type != AST_STRING)
            {
                get_expression_type(analyzer, node->child1);
            }
        }
        break;

    case AST_CMD_SE:
        if (node->child1)
        {
            data_type cond_type = get_expression_type(analyzer, node->child1);
            if (cond_type != TYPE_INT)
            {
                semantic_error(node->child1->line_number, "Condição deve ser do tipo int");
                analyzer->has_errors = 1;
            }
        }
        if (node->child2)
            analyze_commands(analyzer, node->child2);
        if (node->child3)
            analyze_commands(analyzer, node->child3);
        break;

    case AST_CMD_ENQUANTO:
        if (node->child1)
        {
            data_type cond_type = get_expression_type(analyzer, node->child1);
            if (cond_type != TYPE_INT)
            {
                semantic_error(node->child1->line_number, "Condição deve ser do tipo int");
                analyzer->has_errors = 1;
            }
        }
        if (node->child2)
            analyze_commands(analyzer, node->child2);
        break;

    case AST_BLOCO:
        analyze_block(analyzer, node);
        break;

    default:
        break;
    }
}

/* Obtém o tipo de uma expressão */
data_type get_expression_type(semantic_analyzer *analyzer, ast_node *expr)
{
    if (!expr)
        return TYPE_VOID;

    switch (expr->type)
    {
    case AST_EXPR_INTCONST:
        return TYPE_INT;

    case AST_EXPR_CARCONST:
        return TYPE_CAR;

    case AST_EXPR_ID:
        if (expr->lexeme)
        {
            symbol_entry *var = lookup_symbol(analyzer->current_table, expr->lexeme);
            if (!var)
            {
                semantic_error(expr->line_number, "Identificador não foi declarado");
                analyzer->has_errors = 1;
                return TYPE_VOID;
            }
            return var->dtype;
        }
        return TYPE_VOID;

    case AST_EXPR_ASSIGN:
        if (expr->child1 && expr->child2)
        {
            data_type left_type = get_expression_type(analyzer, expr->child1);
            data_type right_type = get_expression_type(analyzer, expr->child2);
            if (!types_compatible(left_type, right_type))
            {
                semantic_error(expr->line_number, "Tipos incompatíveis na atribuição");
                analyzer->has_errors = 1;
            }
            return left_type;
        }
        break;

    case AST_EXPR_PLUS:
    case AST_EXPR_MINUS:
    case AST_EXPR_MULT:
    case AST_EXPR_DIV:
        if (expr->child1 && expr->child2)
        {
            data_type left_type = get_expression_type(analyzer, expr->child1);
            data_type right_type = get_expression_type(analyzer, expr->child2);
            if (left_type != TYPE_INT || right_type != TYPE_INT)
            {
                semantic_error(expr->line_number, "Operadores aritméticos só podem ser aplicados a tipos int");
                analyzer->has_errors = 1;
            }
            return TYPE_INT;
        }
        break;

    case AST_EXPR_LT:
    case AST_EXPR_GT:
    case AST_EXPR_LE:
    case AST_EXPR_GE:
    case AST_EXPR_EQ:
    case AST_EXPR_NE:
        if (expr->child1 && expr->child2)
        {
            data_type left_type = get_expression_type(analyzer, expr->child1);
            data_type right_type = get_expression_type(analyzer, expr->child2);
            if (!types_compatible(left_type, right_type))
            {
                semantic_error(expr->line_number, "Operadores relacionais devem ser aplicados a operandos de mesmo tipo");
                analyzer->has_errors = 1;
            }
            return TYPE_INT;
        }
        break;

    case AST_EXPR_OR:
    case AST_EXPR_AND:
        if (expr->child1 && expr->child2)
        {
            data_type left_type = get_expression_type(analyzer, expr->child1);
            data_type right_type = get_expression_type(analyzer, expr->child2);
            if (left_type != TYPE_INT || right_type != TYPE_INT)
            {
                semantic_error(expr->line_number, "Operadores lógicos só podem ser aplicados a tipos int");
                analyzer->has_errors = 1;
            }
            return TYPE_INT;
        }
        break;

    case AST_EXPR_UNARY_MINUS:
        if (expr->child1)
        {
            data_type operand_type = get_expression_type(analyzer, expr->child1);
            if (operand_type != TYPE_INT)
            {
                semantic_error(expr->line_number, "Operador unário '-' só pode ser aplicado a tipo int");
                analyzer->has_errors = 1;
            }
            return TYPE_INT;
        }
        break;

    case AST_EXPR_NOT:
        if (expr->child1)
        {
            data_type operand_type = get_expression_type(analyzer, expr->child1);
            if (operand_type != TYPE_INT)
            {
                semantic_error(expr->line_number, "Operador '!' só pode ser aplicado a tipo int");
                analyzer->has_errors = 1;
            }
            return TYPE_INT;
        }
        break;

    case AST_EXPR_CALL:
        return analyze_function_call(analyzer, expr);

    default:
        break;
    }

    return TYPE_VOID;
}

/* Analisa chamada de função */
data_type analyze_function_call(semantic_analyzer *analyzer, ast_node *call)
{
    if (!call || !call->child1 || !call->child1->lexeme)
    {
        return TYPE_VOID;
    }

    const char *func_name = call->child1->lexeme;
    symbol_entry *func = lookup_symbol(analyzer->global_table, func_name);

    if (!func)
    {
        semantic_error(call->line_number, "Função não foi declarada");
        analyzer->has_errors = 1;
        return TYPE_VOID;
    }

    if (func->sym_type != SYMBOL_FUNC)
    {
        semantic_error(call->line_number, "Identificador não é uma função");
        analyzer->has_errors = 1;
        return TYPE_VOID;
    }

    /* Verifica parâmetros */
    int param_count = count_arguments(call->child2);

    if (param_count != func->num_params)
    {
        semantic_error(call->line_number, "Número incorreto de argumentos na chamada de função");
        analyzer->has_errors = 1;
        return func->dtype;
    }

    /* Verifica tipos dos argumentos */
    check_argument_types(analyzer, call->child2, func, call->line_number, 0);

    return func->dtype;
}

/* Analisa expressão */
void analyze_expression(semantic_analyzer *analyzer, ast_node *node)
{
    if (!node)
        return;
    get_expression_type(analyzer, node);
}

/* Conta recursivamente o número de argumentos em uma lista de expressões */
int count_arguments(ast_node *args)
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
                count += count_arguments(args->child1);
            }
            else
            {
                /* Se child1 é um argumento, conta como 1 */
                count = 1;
            }
        }
        if (args->child2)
        {

            count += count_arguments(args->child2); /* Argumentos restantes */
        }

        return count;
    }
    else
    {
        /* Argumento único */

        return 1;
    }
}

/* Verifica recursivamente os tipos dos argumentos */
void check_argument_types(semantic_analyzer *analyzer, ast_node *args, symbol_entry *func, int line_number, int arg_index)
{
    if (!args || arg_index >= func->num_params)
        return;

    if (args->type == AST_LISTA_EXPR)
    {
        /* Verifica argumentos recursivamente */
        if (args->child1)
        {
            if (args->child1->type == AST_LISTA_EXPR)
            {
                /* Se child1 é uma lista, verifica recursivamente */
                check_argument_types(analyzer, args->child1, func, line_number, arg_index);
                /* Calcula quantos argumentos foram processados em child1 */
                int child1_count = count_arguments(args->child1);
                arg_index += child1_count;
            }
            else
            {
                /* Se child1 é um argumento simples, verifica tipo */
                data_type arg_type = get_expression_type(analyzer, args->child1);
                if (!types_compatible(arg_type, func->param_types[arg_index]))
                {
                    semantic_error(line_number, "Tipo de argumento incompatível com parâmetro da função");
                    analyzer->has_errors = 1;
                }
                arg_index++;
            }
        }

        /* Verifica argumentos restantes */
        if (args->child2)
        {
            check_argument_types(analyzer, args->child2, func, line_number, arg_index);
        }
    }
    else
    {
        /* Argumento único */
        data_type arg_type = get_expression_type(analyzer, args);
        if (!types_compatible(arg_type, func->param_types[arg_index]))
        {
            semantic_error(line_number, "Tipo de argumento incompatível com parâmetro da função");
            analyzer->has_errors = 1;
        }
    }
}