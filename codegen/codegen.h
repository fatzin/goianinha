#ifndef CODEGEN_H
#define CODEGEN_H

#include "../parser/ast.h"
#include "../symtable/symtable.h"
#include <stdio.h>

/* Estrutura para o gerador de código */
typedef struct code_generator
{
    FILE *output_file;    /* Arquivo de saída */
    symbol_table *symtab; /* Tabela de símbolos */
    int label_counter;    /* Contador para rótulos únicos */
    int current_offset;   /* Offset atual na pilha */
    int in_function;      /* Se está dentro de uma função */
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
void generate_if_statement(code_generator *gen, ast_node *node);
void generate_while_statement(code_generator *gen, ast_node *node);
void generate_read_statement(code_generator *gen, ast_node *node);
void generate_write_statement(code_generator *gen, ast_node *node);
void generate_return_statement(code_generator *gen, ast_node *node);

/* Funções para expressões aritméticas e lógicas */
void generate_binary_operation(code_generator *gen, ast_node *node);
void generate_unary_operation(code_generator *gen, ast_node *node);

/* Utilitários */
int get_variable_offset(code_generator *gen, const char *var_name);
void generate_prologue(code_generator *gen);
void generate_epilogue(code_generator *gen);
void generate_global_variables(code_generator *gen, symbol_table *table);

#endif