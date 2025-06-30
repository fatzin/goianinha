#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Tipos de nós da AST */
typedef enum
{
    /* Programa */
    AST_PROGRAMA,

    /* Declarações */
    AST_DECL_VAR,
    AST_DECL_FUNC,
    AST_LISTA_DECL_VAR,
    AST_LISTA_DECL_FUNC_VAR,

    /* Tipos */
    AST_TIPO_INT,
    AST_TIPO_CAR,

    /* Parâmetros */
    AST_PARAM,
    AST_LISTA_PARAM,

    /* Comandos */
    AST_BLOCO,
    AST_LISTA_CMD,
    AST_CMD_EXPR,
    AST_CMD_RETORNE,
    AST_CMD_LEIA,
    AST_CMD_ESCREVA,
    AST_CMD_NOVALINHA,
    AST_CMD_SE,
    AST_CMD_ENQUANTO,
    AST_CMD_VAZIO,

    /* Expressões */
    AST_EXPR_ASSIGN,
    AST_EXPR_OR,
    AST_EXPR_AND,
    AST_EXPR_EQ,
    AST_EXPR_NE,
    AST_EXPR_LT,
    AST_EXPR_GT,
    AST_EXPR_LE,
    AST_EXPR_GE,
    AST_EXPR_PLUS,
    AST_EXPR_MINUS,
    AST_EXPR_MULT,
    AST_EXPR_DIV,
    AST_EXPR_UNARY_MINUS,
    AST_EXPR_NOT,
    AST_EXPR_CALL,
    AST_EXPR_ID,
    AST_EXPR_INTCONST,
    AST_EXPR_CARCONST,
    AST_LISTA_EXPR,

    /* String */
    AST_STRING
} ast_node_type;

/* Estrutura do nó da AST */
typedef struct ast_node
{
    ast_node_type type;
    int line_number;
    char *lexeme;

    /* Filhos do nó */
    struct ast_node *child1;
    struct ast_node *child2;
    struct ast_node *child3;
    struct ast_node *child4;

    /* Próximo nó (para listas) */
    struct ast_node *next;

    /* Informações semânticas (serão usadas na análise semântica) */
    int data_type;   /* 0 = int, 1 = car */
    int value;       /* Para constantes inteiras */
    char char_value; /* Para constantes de caractere */
} ast_node;

/* Funções para criação e manipulação da AST */
ast_node *create_ast_node(ast_node_type type, int line, const char *lexeme);
ast_node *create_ast_node_with_children(ast_node_type type, int line, const char *lexeme,
                                        ast_node *child1, ast_node *child2, ast_node *child3, ast_node *child4);
void print_ast(ast_node *node, int depth);
void free_ast(ast_node *node);

/* Funções auxiliares */
const char *ast_type_to_string(ast_node_type type);

#endif