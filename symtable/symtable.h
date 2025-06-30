#ifndef SYMTABLE_H
#define SYMTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Tipos de dados */
typedef enum
{
    TYPE_INT = 0,
    TYPE_CAR = 1,
    TYPE_VOID = 2
} data_type;

/* Tipos de símbolos */
typedef enum
{
    SYMBOL_VAR,
    SYMBOL_FUNC,
    SYMBOL_PARAM
} symbol_type;

/* Escopo */
typedef enum
{
    SCOPE_GLOBAL,
    SCOPE_LOCAL
} scope_type;

/* Entrada da tabela de símbolos */
typedef struct symbol_entry
{
    char *name;           /* Nome do símbolo */
    symbol_type sym_type; /* Tipo do símbolo (var, func, param) */
    data_type dtype;      /* Tipo de dados (int, car, void) */
    scope_type scope;     /* Escopo (global, local) */
    int line_declared;    /* Linha onde foi declarado */
    int line_used;        /* Linha onde foi usado */

    /* Para funções */
    int num_params;         /* Número de parâmetros */
    data_type *param_types; /* Tipos dos parâmetros */
    char **param_names;     /* Nomes dos parâmetros */

    /* Para variáveis */
    int is_initialized; /* Se a variável foi inicializada */

    struct symbol_entry *next; /* Próxima entrada (lista ligada) */
} symbol_entry;

/* Tabela de símbolos */
typedef struct symbol_table
{
    symbol_entry *head;          /* Primeira entrada */
    struct symbol_table *parent; /* Escopo pai */
    int scope_level;             /* Nível do escopo */
} symbol_table;

/* Funções da tabela de símbolos */
symbol_table *create_symbol_table(symbol_table *parent);
void destroy_symbol_table(symbol_table *table);

symbol_entry *insert_symbol(symbol_table *table, const char *name, symbol_type sym_type,
                            data_type dtype, int line);
symbol_entry *lookup_symbol(symbol_table *table, const char *name);
symbol_entry *lookup_symbol_local(symbol_table *table, const char *name);

void add_function_param(symbol_entry *func_entry, data_type param_type, const char *param_name);
void print_symbol_table(symbol_table *table);

/* Funções auxiliares */
const char *data_type_to_string(data_type type);
const char *symbol_type_to_string(symbol_type type);

#endif