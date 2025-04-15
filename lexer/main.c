#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *yyin;
extern char *yytext;
extern int yylineno;
extern int yylex(void);

const char* token_name(int token_code) {
    switch (token_code) {
        // Identificadores e constantes
        case 1: return "ID";
        case 2: return "INTCONST";
        case 3: return "CARCONST";
        case 4: return "STRING";
        
        // Palavras-chave
        case 10: return "INT";
        case 11: return "CAR";
        case 12: return "PROGRAMA";
        case 13: return "RETORNE";
        case 14: return "LEIA";
        case 15: return "ESCREVA";
        case 16: return "NOVALINHA";
        case 17: return "SE";
        case 18: return "ENTAO";
        case 19: return "SENAO";
        case 20: return "ENQUANTO";
        case 21: return "EXECUTE";
        case 22: return "OU";
        case 23: return "E";
        
        // Operadores e símbolos
        case 30: return "=";
        case 31: return "+";
        case 32: return "-";
        case 33: return "*";
        case 34: return "/";
        case 35: return "!";
        case 36: return ">";
        case 37: return "<";
        case 38: return ">=";
        case 39: return "<=";
        case 40: return "==";
        case 41: return "!=";
        case 42: return "(";
        case 43: return ")";
        case 44: return "{";
        case 45: return "}";
        case 46: return ",";
        case 47: return ";";
        
        default: return "UNKNOWN";
    }
}

int main(int argc, char *argv[]) {
    int token;
    
    if (argc != 2) {
        fprintf(stderr, "Uso: %s arquivo_fonte\n", argv[0]);
        return 1;
    }
    
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", argv[1]);
        return 1;
    }
    
    printf("Análise léxica do arquivo: %s\n\n", argv[1]);
    printf("%-20s %-20s %-10s\n", "TOKEN", "LEXEMA", "LINHA");
    printf("-------------------------------------------------------\n");

    while ((token = yylex()) != 0) {
        printf("%-20s %-20s %-10d\n", token_name(token), yytext, yylineno);
    }
    
    printf("-------------------------------------------------------\n");
    printf("Análise léxica concluída.\n");
    
    fclose(yyin);
    return 0;
}
