#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "../parser/ast.h"
#include "../symtable/symtable.h"

/* Estrutura para o analisador semântico */
typedef struct semantic_analyzer
{
    symbol_table *global_table;
    symbol_table *current_table;
    int has_errors;
    int in_function;
    data_type current_function_return_type;
} semantic_analyzer;

/* Funções principais do analisador semântico */
semantic_analyzer *create_semantic_analyzer(void);
void destroy_semantic_analyzer(semantic_analyzer *analyzer);
int analyze_program(semantic_analyzer *analyzer, ast_node *root);

/* Funções auxiliares */
void semantic_error(int line, const char *message);
data_type ast_type_to_data_type(ast_node_type type);
data_type get_expression_type(semantic_analyzer *analyzer, ast_node *expr);
int types_compatible(data_type type1, data_type type2);

/* Funções de análise por tipo de nó */
void analyze_declarations(semantic_analyzer *analyzer, ast_node *node);
void analyze_function_declaration(semantic_analyzer *analyzer, ast_node *node);
void analyze_variable_declaration(semantic_analyzer *analyzer, ast_node *node);
void analyze_function_parameters(semantic_analyzer *analyzer, ast_node *params, symbol_entry *func_entry);
void analyze_block(semantic_analyzer *analyzer, ast_node *node);
void analyze_local_declarations(semantic_analyzer *analyzer, ast_node *node);
void analyze_commands(semantic_analyzer *analyzer, ast_node *node);
void analyze_expression(semantic_analyzer *analyzer, ast_node *node);
data_type analyze_function_call(semantic_analyzer *analyzer, ast_node *node);

#endif