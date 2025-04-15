%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
"int"         { return T_INT; }
"car"         { return T_CAR; }
"programa"    { return T_PROGRAMA; }
"retorne"     { return T_RETORNE; }
"leia"        { return T_LEIA; }
"escreva"     { return T_ESCREVA; }
"novalinha"   { return T_NOVALINHA; }
"se"          { return T_SE; }
"entao"       { return T_ENTAO; }
"senao"       { return T_SENAO; }
"enquanto"    { return T_ENQUANTO; }
"execute"     { return T_EXECUTE; }
"ou"          { return T_OU; }
"e"           { return T_E; }

 /* Operadores e símbolos */
"="           { return T_IGUAL; }
"+"           { return T_MAIS; }
"-"           { return T_MENOS; }
"*"           { return T_MULT; }
"/"           { return T_DIV; }
"!"           { return T_NAO; }
">"           { return T_MAIOR; }
"<"           { return T_MENOR; }
">="          { return T_MAIORIGUAL; }
"<="          { return T_MENORIGUAL; }
"=="          { return T_IGUALIGUAL; }
"!="          { return T_DIFERENTE; }
"("           { return T_ABREPAR; }
")"           { return T_FECHAPAR; }
"{"           { return T_ABRECH; }
"}"           { return T_FECHACH; }
","           { return T_VIRGULA; }
";"           { return T_PONTOVIR; }

 /* Identificadores e constantes */
{ID}          { return T_ID; }
{INTCONST}    { return T_INTCONST; }
{CARCONST}    { return T_CARCONST; }

 /* Cadeias de caracteres */
\"            { BEGIN(CADEIA); }
<CADEIA>\n    { fprintf(stderr, "ERRO: Quebra de linha não permitida dentro de string na linha %d\n", yylineno-1); BEGIN(INITIAL); }
<CADEIA>\"    { BEGIN(INITIAL); return T_STRING; }
<CADEIA>.     {  }
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