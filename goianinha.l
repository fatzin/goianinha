%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Forward declaration */
typedef struct ast_node ast_node;

#include "parser/goianinha.tab.h"

extern YYSTYPE yylval;

// Definição dos códigos para tokens
#define T_ID 1
#define T_INTCONST 2
#define T_CARCONST 3
#define T_STRING 4

// Palavras-chave
#define T_INT 10
#define T_CAR 11
#define T_PROGRAMA 12
#define T_RETORNE 13
#define T_LEIA 14
#define T_ESCREVA 15
#define T_NOVALINHA 16
#define T_SE 17
#define T_ENTAO 18
#define T_SENAO 19
#define T_ENQUANTO 20
#define T_EXECUTE 21
#define T_OU 22
#define T_E 23

// Operadores e símbolos
#define T_IGUAL 30
#define T_MAIS 31
#define T_MENOS 32
#define T_MULT 33
#define T_DIV 34
#define T_NAO 35
#define T_MAIOR 36
#define T_MENOR 37
#define T_MAIORIGUAL 38
#define T_MENORIGUAL 39
#define T_IGUALIGUAL 40
#define T_DIFERENTE 41
#define T_ABREPAR 42
#define T_FECHAPAR 43
#define T_ABRECH 44
#define T_FECHACH 45
#define T_VIRGULA 46
#define T_PONTOVIR 47

int comment_start_line = 0;  // Para rastrear onde um comentário começa
char string_buf[1000];       // Buffer para armazenar strings
char *string_buf_ptr;        // Ponteiro para o buffer
%}

%option noyywrap
%option yylineno
%option noinput
%option nounput

/* Estados para processamento de comentários e strings */
%x COMENTARIO
%x CADEIA

/* Definições de padrões */
DIGITO      [0-9]
LETRA       [a-zA-Z]
UNDERSCORE  _
ID          ({LETRA}|{UNDERSCORE})({LETRA}|{DIGITO}|{UNDERSCORE})*
INTCONST    {DIGITO}+
CARCONST    '.'
ESPACO      [ \t\r\n]+

%%

 /* Palavras reservadas */
"int"         { yylval.str = strdup(yytext); return INT; }
"car"         { yylval.str = strdup(yytext); return CAR; }
"programa"    { yylval.str = strdup(yytext); return PROGRAMA; }
"retorne"     { yylval.str = strdup(yytext); return RETORNE; }
"leia"        { yylval.str = strdup(yytext); return LEIA; }
"escreva"     { yylval.str = strdup(yytext); return ESCREVA; }
"novalinha"   { yylval.str = strdup(yytext); return NOVALINHA; }
"se"          { yylval.str = strdup(yytext); return SE; }
"entao"       { yylval.str = strdup(yytext); return ENTAO; }
"senao"       { yylval.str = strdup(yytext); return SENAO; }
"enquanto"    { yylval.str = strdup(yytext); return ENQUANTO; }
"execute"     { yylval.str = strdup(yytext); return EXECUTE; }
"ou"          { yylval.str = strdup(yytext); return OU; }
"e"           { yylval.str = strdup(yytext); return E; }

 /* Operadores e símbolos */
"="           { yylval.str = strdup(yytext); return ASSIGN; }
"+"           { yylval.str = strdup(yytext); return PLUS; }
"-"           { yylval.str = strdup(yytext); return MINUS; }
"*"           { yylval.str = strdup(yytext); return MULT; }
"/"           { yylval.str = strdup(yytext); return DIV; }
"!"           { yylval.str = strdup(yytext); return NOT; }
">"           { yylval.str = strdup(yytext); return GT; }
"<"           { yylval.str = strdup(yytext); return LT; }
">="          { yylval.str = strdup(yytext); return GE; }
"<="          { yylval.str = strdup(yytext); return LE; }
"=="          { yylval.str = strdup(yytext); return EQ; }
"!="          { yylval.str = strdup(yytext); return NE; }
"("           { yylval.str = strdup(yytext); return LPAREN; }
")"           { yylval.str = strdup(yytext); return RPAREN; }
"{"           { yylval.str = strdup(yytext); return LBRACE; }
"}"           { yylval.str = strdup(yytext); return RBRACE; }
","           { yylval.str = strdup(yytext); return COMMA; }
";"           { yylval.str = strdup(yytext); return SEMICOLON; }

 /* Identificadores e constantes */
{ID}          { yylval.str = strdup(yytext); return ID; }
{INTCONST}    { yylval.str = strdup(yytext); return INTCONST; }
{CARCONST}    { yylval.str = strdup(yytext); return CARCONST; }

 /* Cadeias de caracteres */
\"            { string_buf_ptr = string_buf; BEGIN(CADEIA); }
<CADEIA>\n    { fprintf(stderr, "ERRO: Quebra de linha não permitida dentro de string na linha %d\n", yylineno-1); BEGIN(INITIAL); }
<CADEIA>\"    { 
                *string_buf_ptr = '\0'; 
                yylval.str = strdup(string_buf); 
                BEGIN(INITIAL); 
                return STRING; 
              }
<CADEIA>.     { *string_buf_ptr++ = *yytext; }
<CADEIA><<EOF>> { fprintf(stderr, "ERRO: Cadeia de caracteres não fechada na linha %d\n", yylineno); BEGIN(INITIAL); }

 /* Comentários */
"/*"          { comment_start_line = yylineno; BEGIN(COMENTARIO); }
<COMENTARIO>"*/" { BEGIN(INITIAL); }
<COMENTARIO>.|\n {  }
<COMENTARIO><<EOF>> { fprintf(stderr, "ERRO: Comentário não fechado iniciado na linha %d\n", comment_start_line); BEGIN(INITIAL); }

 /* Espaços em branco */
{ESPACO}      {  }

 /* Qualquer outro caractere é um erro */
.             { fprintf(stderr, "ERRO: Caractere inválido '%s' na linha %d\n", yytext, yylineno); }

%%