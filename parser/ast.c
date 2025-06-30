#include "ast.h"

/* Cria um novo nó da AST */
ast_node *create_ast_node(ast_node_type type, int line, const char *lexeme)
{
    ast_node *node = (ast_node *)malloc(sizeof(ast_node));
    if (!node)
    {
        fprintf(stderr, "ERRO: Falha na alocação de memória para nó da AST\n");
        exit(1);
    }

    node->type = type;
    node->line_number = line;
    node->lexeme = lexeme ? strdup(lexeme) : NULL;
    node->child1 = NULL;
    node->child2 = NULL;
    node->child3 = NULL;
    node->child4 = NULL;
    node->next = NULL;
    node->data_type = -1; /* Não definido inicialmente */
    node->value = 0;
    node->char_value = '\0';

    return node;
}

/* Cria um novo nó da AST com filhos */
ast_node *create_ast_node_with_children(ast_node_type type, int line, const char *lexeme,
                                        ast_node *child1, ast_node *child2, ast_node *child3, ast_node *child4)
{
    ast_node *node = create_ast_node(type, line, lexeme);
    node->child1 = child1;
    node->child2 = child2;
    node->child3 = child3;
    node->child4 = child4;
    return node;
}

/* Imprime a AST (para debug) */
void print_ast(ast_node *node, int depth)
{
    if (!node)
        return;

    /* Indentação */
    for (int i = 0; i < depth; i++)
    {
        printf("  ");
    }

    printf("%s", ast_type_to_string(node->type));
    if (node->lexeme)
    {
        printf(" (%s)", node->lexeme);
    }
    printf(" [linha %d]\n", node->line_number);

    /* Imprime os filhos */
    if (node->child1)
        print_ast(node->child1, depth + 1);
    if (node->child2)
        print_ast(node->child2, depth + 1);
    if (node->child3)
        print_ast(node->child3, depth + 1);
    if (node->child4)
        print_ast(node->child4, depth + 1);

    /* Imprime próximo nó (para listas) */
    if (node->next)
        print_ast(node->next, depth);
}

/* Libera memória da AST */
void free_ast(ast_node *node)
{
    if (!node)
        return;

    free_ast(node->child1);
    free_ast(node->child2);
    free_ast(node->child3);
    free_ast(node->child4);
    free_ast(node->next);

    if (node->lexeme)
    {
        free(node->lexeme);
    }
    free(node);
}

/* Converte tipo do nó para string */
const char *ast_type_to_string(ast_node_type type)
{
    switch (type)
    {
    case AST_PROGRAMA:
        return "PROGRAMA";
    case AST_DECL_VAR:
        return "DECL_VAR";
    case AST_DECL_FUNC:
        return "DECL_FUNC";
    case AST_LISTA_DECL_VAR:
        return "LISTA_DECL_VAR";
    case AST_LISTA_DECL_FUNC_VAR:
        return "LISTA_DECL_FUNC_VAR";
    case AST_TIPO_INT:
        return "TIPO_INT";
    case AST_TIPO_CAR:
        return "TIPO_CAR";
    case AST_PARAM:
        return "PARAM";
    case AST_LISTA_PARAM:
        return "LISTA_PARAM";
    case AST_BLOCO:
        return "BLOCO";
    case AST_LISTA_CMD:
        return "LISTA_CMD";
    case AST_CMD_EXPR:
        return "CMD_EXPR";
    case AST_CMD_RETORNE:
        return "CMD_RETORNE";
    case AST_CMD_LEIA:
        return "CMD_LEIA";
    case AST_CMD_ESCREVA:
        return "CMD_ESCREVA";
    case AST_CMD_NOVALINHA:
        return "CMD_NOVALINHA";
    case AST_CMD_SE:
        return "CMD_SE";
    case AST_CMD_ENQUANTO:
        return "CMD_ENQUANTO";
    case AST_CMD_VAZIO:
        return "CMD_VAZIO";
    case AST_EXPR_ASSIGN:
        return "EXPR_ASSIGN";
    case AST_EXPR_OR:
        return "EXPR_OR";
    case AST_EXPR_AND:
        return "EXPR_AND";
    case AST_EXPR_EQ:
        return "EXPR_EQ";
    case AST_EXPR_NE:
        return "EXPR_NE";
    case AST_EXPR_LT:
        return "EXPR_LT";
    case AST_EXPR_GT:
        return "EXPR_GT";
    case AST_EXPR_LE:
        return "EXPR_LE";
    case AST_EXPR_GE:
        return "EXPR_GE";
    case AST_EXPR_PLUS:
        return "EXPR_PLUS";
    case AST_EXPR_MINUS:
        return "EXPR_MINUS";
    case AST_EXPR_MULT:
        return "EXPR_MULT";
    case AST_EXPR_DIV:
        return "EXPR_DIV";
    case AST_EXPR_UNARY_MINUS:
        return "EXPR_UNARY_MINUS";
    case AST_EXPR_NOT:
        return "EXPR_NOT";
    case AST_EXPR_CALL:
        return "EXPR_CALL";
    case AST_EXPR_ID:
        return "EXPR_ID";
    case AST_EXPR_INTCONST:
        return "EXPR_INTCONST";
    case AST_EXPR_CARCONST:
        return "EXPR_CARCONST";
    case AST_LISTA_EXPR:
        return "LISTA_EXPR";
    case AST_STRING:
        return "STRING";
    default:
        return "UNKNOWN";
    }
}