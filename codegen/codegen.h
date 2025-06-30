#ifndef CODEGEN_H
#define CODEGEN_H

#include "../parser/ast.h"
#include "../symtable/symtable.h"
#include <stdio.h>

/* Estrutura para armazenar strings literais */
typedef struct string_literal
{
    char *content;               /* Conteúdo da string */
    char *label;                 /* Label único para a string */
    struct string_literal *next; /* Próxima string na lista */
} string_literal;

/* Estrutura para parâmetros de função */
typedef struct function_param
{
    char *name;                  /* Nome do parâmetro */
    int register_index;          /* Índice do registrador ($a0=0, $a1=1, etc.) */
    struct function_param *next; /* Próximo parâmetro */
} function_param;

/* Estrutura para o gerador de código */
typedef struct code_generator
{
    FILE *output_file;                       /* Arquivo de saída */
    symbol_table *symtab;                    /* Tabela de símbolos */
    int label_counter;                       /* Contador para rótulos únicos */
    int current_offset;                      /* Offset atual na pilha */
    int in_function;                         /* Se está dentro de uma função */
    int in_multi_call_operation;             /* Se está numa operação com múltiplas chamadas */
    int saved_args_base_offset;              /* Offset base onde os argumentos foram salvos */
    string_literal *strings;                 /* Lista de strings literais */
    int string_counter;                      /* Contador para strings únicas */
    function_param *current_function_params; /* Lista de parâmetros da função atual */
} code_generator;

/* Funções principais */
code_generator *create_code_generator(FILE *output, symbol_table *symtab);
void destroy_code_generator(code_generator *gen);
void generate_code(code_generator *gen, ast_node *root);

/* Funções auxiliares para geração de código */
void emit_code(code_generator *gen, const char *format, ...);
void emit_label(code_generator *gen, const char *label);
char *generate_label(code_generator *gen, const char *prefix);

/* Funções para diferentes construções */
void generate_program(code_generator *gen, ast_node *node);
void generate_declarations(code_generator *gen, ast_node *node);
void generate_function(code_generator *gen, ast_node *node);
void generate_main_block(code_generator *gen, ast_node *node);
void generate_commands(code_generator *gen, ast_node *node);
void generate_expression(code_generator *gen, ast_node *node);

/* Funções específicas para comandos */
void generate_assignment(code_generator *gen, ast_node *node);
void generate_function_call(code_generator *gen, ast_node *node);
void generate_function_arguments(code_generator *gen, ast_node *args, int arg_index);
int count_codegen_arguments(ast_node *args);
void generate_if_statement(code_generator *gen, ast_node *node);
void generate_while_statement(code_generator *gen, ast_node *node);
void generate_read_statement(code_generator *gen, ast_node *node);
void generate_write_statement(code_generator *gen, ast_node *node);
void generate_return_statement(code_generator *gen, ast_node *node);

/* Funções para expressões aritméticas e lógicas */
void generate_binary_operation(code_generator *gen, ast_node *node);
void generate_relational_operation(code_generator *gen, ast_node *node);
void generate_unary_operation(code_generator *gen, ast_node *node);

/* Utilitários */
int get_variable_offset(code_generator *gen, const char *var_name);
void generate_prologue(code_generator *gen);
void generate_epilogue(code_generator *gen);
void generate_global_variables(code_generator *gen, symbol_table *table);

/* Funções para strings literais */
char *add_string_literal(code_generator *gen, const char *content);
void generate_string_literals(code_generator *gen);
void collect_string_literals(code_generator *gen, ast_node *node);

/* Funções para parâmetros de função */
void add_codegen_function_param(code_generator *gen, const char *param_name, int register_index);
void clear_function_params(code_generator *gen);
function_param *find_function_param(code_generator *gen, const char *param_name);
void extract_function_params(code_generator *gen, ast_node *params_node);
void load_saved_param(code_generator *gen, int register_index);
int count_function_calls_in_body(ast_node *body);
int count_function_params(code_generator *gen);

#endif