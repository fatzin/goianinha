#include "symtable.h"

/* Cria uma nova tabela de símbolos */
symbol_table *create_symbol_table(symbol_table *parent)
{
    symbol_table *table = (symbol_table *)malloc(sizeof(symbol_table));
    if (!table)
    {
        fprintf(stderr, "ERRO: Falha na alocação de memória para tabela de símbolos\n");
        exit(1);
    }

    table->head = NULL;
    table->parent = parent;
    table->scope_level = parent ? parent->scope_level + 1 : 0;

    return table;
}

/* Destrói uma tabela de símbolos */
void destroy_symbol_table(symbol_table *table)
{
    if (!table)
        return;

    symbol_entry *current = table->head;
    while (current)
    {
        symbol_entry *next = current->next;

        if (current->name)
            free(current->name);
        if (current->param_types)
            free(current->param_types);
        if (current->param_names)
        {
            for (int i = 0; i < current->num_params; i++)
            {
                if (current->param_names[i])
                    free(current->param_names[i]);
            }
            free(current->param_names);
        }

        free(current);
        current = next;
    }

    free(table);
}

/* Insere um símbolo na tabela */
symbol_entry *insert_symbol(symbol_table *table, const char *name, symbol_type sym_type,
                            data_type dtype, int line)
{
    if (!table || !name)
        return NULL;

    /* Verifica se o símbolo já existe no escopo atual */
    symbol_entry *existing = lookup_symbol_local(table, name);
    if (existing)
    {
        return NULL; /* Símbolo já existe */
    }

    /* Cria nova entrada */
    symbol_entry *entry = (symbol_entry *)malloc(sizeof(symbol_entry));
    if (!entry)
    {
        fprintf(stderr, "ERRO: Falha na alocação de memória para entrada da tabela de símbolos\n");
        exit(1);
    }

    entry->name = strdup(name);
    entry->sym_type = sym_type;
    entry->dtype = dtype;
    entry->scope = (table->scope_level == 0) ? SCOPE_GLOBAL : SCOPE_LOCAL;
    entry->line_declared = line;
    entry->line_used = -1;
    entry->num_params = 0;
    entry->param_types = NULL;
    entry->param_names = NULL;
    entry->is_initialized = 0;
    entry->next = table->head;

    table->head = entry;
    return entry;
}

/* Procura um símbolo na tabela e em escopos pais */
symbol_entry *lookup_symbol(symbol_table *table, const char *name)
{
    if (!table || !name)
        return NULL;

    symbol_entry *current = table->head;
    while (current)
    {
        if (strcmp(current->name, name) == 0)
        {
            return current;
        }
        current = current->next;
    }

    /* Se não encontrou, procura no escopo pai */
    if (table->parent)
    {
        return lookup_symbol(table->parent, name);
    }

    return NULL;
}

/* Procura um símbolo apenas no escopo local */
symbol_entry *lookup_symbol_local(symbol_table *table, const char *name)
{
    if (!table || !name)
        return NULL;

    symbol_entry *current = table->head;
    while (current)
    {
        if (strcmp(current->name, name) == 0)
        {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

/* Adiciona um parâmetro a uma função */
void add_function_param(symbol_entry *func_entry, data_type param_type, const char *param_name)
{
    if (!func_entry || func_entry->sym_type != SYMBOL_FUNC)
        return;

    /* Realoca arrays para o novo parâmetro */
    func_entry->param_types = (data_type *)realloc(func_entry->param_types,
                                                   (func_entry->num_params + 1) * sizeof(data_type));
    func_entry->param_names = (char **)realloc(func_entry->param_names,
                                               (func_entry->num_params + 1) * sizeof(char *));

    if (!func_entry->param_types || !func_entry->param_names)
    {
        fprintf(stderr, "ERRO: Falha na alocação de memória para parâmetros da função\n");
        exit(1);
    }

    func_entry->param_types[func_entry->num_params] = param_type;
    func_entry->param_names[func_entry->num_params] = strdup(param_name);
    func_entry->num_params++;
}

/* Imprime a tabela de símbolos */
void print_symbol_table(symbol_table *table)
{
    if (!table)
        return;

    printf("=== Tabela de Símbolos (Nível %d) ===\n", table->scope_level);

    symbol_entry *current = table->head;
    while (current)
    {
        printf("Nome: %s, Tipo: %s, Dados: %s, Linha: %d",
               current->name,
               symbol_type_to_string(current->sym_type),
               data_type_to_string(current->dtype),
               current->line_declared);

        if (current->sym_type == SYMBOL_FUNC)
        {
            printf(", Parâmetros: %d", current->num_params);
            if (current->num_params > 0)
            {
                printf(" (");
                for (int i = 0; i < current->num_params; i++)
                {
                    if (i > 0)
                        printf(", ");
                    printf("%s %s",
                           data_type_to_string(current->param_types[i]),
                           current->param_names[i]);
                }
                printf(")");
            }
        }

        printf("\n");
        current = current->next;
    }

    printf("\n");
}

/* Converte tipo de dados para string */
const char *data_type_to_string(data_type type)
{
    switch (type)
    {
    case TYPE_INT:
        return "int";
    case TYPE_CAR:
        return "car";
    case TYPE_VOID:
        return "void";
    default:
        return "unknown";
    }
}

/* Converte tipo de símbolo para string */
const char *symbol_type_to_string(symbol_type type)
{
    switch (type)
    {
    case SYMBOL_VAR:
        return "variável";
    case SYMBOL_FUNC:
        return "função";
    case SYMBOL_PARAM:
        return "parâmetro";
    default:
        return "unknown";
    }
}