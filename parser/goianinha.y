%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern char* yytext;
extern int yylineno;

void yyerror(const char* s);
%}

/* Token declarations */
%token ID INTCONST CARCONST STRING
%token INT CAR PROGRAMA RETORNE LEIA ESCREVA NOVALINHA
%token SE ENTAO SENAO ENQUANTO EXECUTE
%token OU E
%token ASSIGN PLUS MINUS MULT DIV NOT
%token GT LT GE LE EQ NE
%token LPAREN RPAREN LBRACE RBRACE COMMA SEMICOLON

/* Operator precedence */
%left OU
%left E
%left EQ NE
%left LT GT LE GE
%left PLUS MINUS
%left MULT DIV
%right NOT UMINUS

%%

Programa: DeclFuncVar DeclProg
        ;

DeclFuncVar: Tipo ID DeclVar SEMICOLON DeclFuncVar
          | Tipo ID DeclFunc DeclFuncVar
          | /* empty */
          ;

DeclProg: PROGRAMA Bloco
        ;

DeclVar: COMMA ID DeclVar
       | /* empty */
       ;

DeclFunc: LPAREN ListaParametros RPAREN Bloco
        ;

ListaParametros: /* empty */
               | ListaParametrosCont
               ;

ListaParametrosCont: Tipo ID
                   | Tipo ID COMMA ListaParametrosCont
                   ;

Bloco: LBRACE ListaDeclVar ListaComando RBRACE
      ;

ListaDeclVar: /* empty */
            | Tipo ID DeclVar SEMICOLON ListaDeclVar
            ;

Tipo: INT
    | CAR
    ;

ListaComando: Comando
            | Comando ListaComando
            ;

Comando: SEMICOLON
       | Expr SEMICOLON
       | RETORNE Expr SEMICOLON
       | LEIA ID SEMICOLON
       | ESCREVA Expr SEMICOLON
       | ESCREVA STRING SEMICOLON
       | NOVALINHA SEMICOLON
       | SE LPAREN Expr RPAREN ENTAO Comando
       | SE LPAREN Expr RPAREN ENTAO Comando SENAO Comando
       | ENQUANTO LPAREN Expr RPAREN EXECUTE Comando
       | Bloco
       ;

Expr: OrExpr
    | ID ASSIGN Expr
    ;

OrExpr: OrExpr OU AndExpr
      | AndExpr
      ;

AndExpr: AndExpr E EqExpr
       | EqExpr
       ;

EqExpr: EqExpr EQ DesigExpr
      | EqExpr NE DesigExpr
      | DesigExpr
      ;

DesigExpr: DesigExpr LT AddExpr
         | DesigExpr GT AddExpr
         | DesigExpr GE AddExpr
         | DesigExpr LE AddExpr
         | AddExpr
         ;

AddExpr: AddExpr PLUS MulExpr
       | AddExpr MINUS MulExpr
       | MulExpr
       ;

MulExpr: MulExpr MULT UnExpr
       | MulExpr DIV UnExpr
       | UnExpr
       ;

UnExpr: MINUS PrimExpr %prec UMINUS
      | NOT PrimExpr
      | PrimExpr
      ;

PrimExpr: ID LPAREN ListExpr RPAREN
        | ID LPAREN RPAREN
        | ID
        | CARCONST
        | INTCONST
        | LPAREN Expr RPAREN
        ;

ListExpr: Expr
        | ListExpr COMMA Expr
        ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "ERRO: %s na linha %d\n", s, yylineno);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <arquivo.gyn>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "ERRO: Não foi possível abrir o arquivo %s\n", argv[1]);
        return 1;
    }

    int result = yyparse();
    fclose(yyin);
    return result;
} 