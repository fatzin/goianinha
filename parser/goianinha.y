%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "../semantic/semantic.h"
#include "../codegen/codegen.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern char* yytext;
extern int yylineno;

void yyerror(const char* s);

/* Raiz da AST */
ast_node* ast_root = NULL;
%}

%union {
    ast_node* node;
    char* str;
    int num;
}

/* Token declarations */
%token <str> ID INTCONST CARCONST STRING
%token <str> INT CAR PROGRAMA RETORNE LEIA ESCREVA NOVALINHA
%token <str> SE ENTAO SENAO ENQUANTO EXECUTE
%token <str> OU E
%token <str> ASSIGN PLUS MINUS MULT DIV NOT
%token <str> GT LT GE LE EQ NE
%token <str> LPAREN RPAREN LBRACE RBRACE COMMA SEMICOLON

/* Non-terminal types */
%type <node> Programa DeclFuncVar DeclProg DeclVar DeclFunc ListaParametros ListaParametrosCont
%type <node> Bloco ListaDeclVar Tipo ListaComando Comando Expr OrExpr AndExpr EqExpr
%type <node> DesigExpr AddExpr MulExpr UnExpr PrimExpr ListExpr

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
        {
            $$ = create_ast_node_with_children(AST_PROGRAMA, yylineno, NULL, $1, $2, NULL, NULL);
            ast_root = $$;
        }
        ;

DeclFuncVar: Tipo ID DeclVar SEMICOLON DeclFuncVar
          {
              ast_node* var_decl = create_ast_node_with_children(AST_DECL_VAR, yylineno, $2, $1, $3, NULL, NULL);
              $$ = create_ast_node_with_children(AST_LISTA_DECL_FUNC_VAR, yylineno, NULL, var_decl, $5, NULL, NULL);
          }
          | Tipo ID DeclFunc DeclFuncVar
          {
              ast_node* func_decl = create_ast_node_with_children(AST_DECL_FUNC, yylineno, $2, $1, $3, NULL, NULL);
              $$ = create_ast_node_with_children(AST_LISTA_DECL_FUNC_VAR, yylineno, NULL, func_decl, $4, NULL, NULL);
          }
          | /* empty */
          {
              $$ = NULL;
          }
          ;

DeclProg: PROGRAMA Bloco
        {
            $$ = $2;
        }
        ;

DeclVar: COMMA ID DeclVar
       {
           ast_node* id_node = create_ast_node(AST_EXPR_ID, yylineno, $2);
           $$ = create_ast_node_with_children(AST_LISTA_DECL_VAR, yylineno, NULL, id_node, $3, NULL, NULL);
       }
       | /* empty */
       {
           $$ = NULL;
       }
       ;

DeclFunc: LPAREN ListaParametros RPAREN Bloco
        {
            $$ = create_ast_node_with_children(AST_DECL_FUNC, yylineno, NULL, $2, $4, NULL, NULL);
        }
        ;

ListaParametros: /* empty */
               {
                   $$ = NULL;
               }
               | ListaParametrosCont
               {
                   $$ = $1;
               }
               ;

ListaParametrosCont: Tipo ID
                   {
                       ast_node* id_node = create_ast_node(AST_EXPR_ID, yylineno, $2);
                       $$ = create_ast_node_with_children(AST_PARAM, yylineno, NULL, $1, id_node, NULL, NULL);
                   }
                   | Tipo ID COMMA ListaParametrosCont
                   {
                       ast_node* id_node = create_ast_node(AST_EXPR_ID, yylineno, $2);
                       ast_node* param = create_ast_node_with_children(AST_PARAM, yylineno, NULL, $1, id_node, NULL, NULL);
                       $$ = create_ast_node_with_children(AST_LISTA_PARAM, yylineno, NULL, param, $4, NULL, NULL);
                   }
                   ;

Bloco: LBRACE ListaDeclVar ListaComando RBRACE
      {
          $$ = create_ast_node_with_children(AST_BLOCO, yylineno, NULL, $2, $3, NULL, NULL);
      }
      ;

ListaDeclVar: /* empty */
            {
                $$ = NULL;
            }
            | Tipo ID DeclVar SEMICOLON ListaDeclVar
            {
                ast_node* id_node = create_ast_node(AST_EXPR_ID, yylineno, $2);
                ast_node* var_decl = create_ast_node_with_children(AST_DECL_VAR, yylineno, NULL, $1, id_node, $3, NULL);
                $$ = create_ast_node_with_children(AST_LISTA_DECL_VAR, yylineno, NULL, var_decl, $5, NULL, NULL);
            }
            ;

Tipo: INT
    {
        $$ = create_ast_node(AST_TIPO_INT, yylineno, $1);
    }
    | CAR
    {
        $$ = create_ast_node(AST_TIPO_CAR, yylineno, $1);
    }
    ;

ListaComando: Comando
            {
                $$ = $1;
            }
            | Comando ListaComando
            {
                $$ = create_ast_node_with_children(AST_LISTA_CMD, yylineno, NULL, $1, $2, NULL, NULL);
            }
            ;

Comando: SEMICOLON
       {
           $$ = create_ast_node(AST_CMD_VAZIO, yylineno, NULL);
       }
       | Expr SEMICOLON
       {
           $$ = create_ast_node_with_children(AST_CMD_EXPR, yylineno, NULL, $1, NULL, NULL, NULL);
       }
       | RETORNE Expr SEMICOLON
       {
           $$ = create_ast_node_with_children(AST_CMD_RETORNE, yylineno, NULL, $2, NULL, NULL, NULL);
       }
       | LEIA ID SEMICOLON
       {
           ast_node* id_node = create_ast_node(AST_EXPR_ID, yylineno, $2);
           $$ = create_ast_node_with_children(AST_CMD_LEIA, yylineno, NULL, id_node, NULL, NULL, NULL);
       }
       | ESCREVA Expr SEMICOLON
       {
           $$ = create_ast_node_with_children(AST_CMD_ESCREVA, yylineno, NULL, $2, NULL, NULL, NULL);
       }
       | ESCREVA STRING SEMICOLON
       {
           ast_node* string_node = create_ast_node(AST_STRING, yylineno, $2);
           $$ = create_ast_node_with_children(AST_CMD_ESCREVA, yylineno, NULL, string_node, NULL, NULL, NULL);
       }
       | NOVALINHA SEMICOLON
       {
           $$ = create_ast_node(AST_CMD_NOVALINHA, yylineno, NULL);
       }
       | SE LPAREN Expr RPAREN ENTAO Comando
       {
           $$ = create_ast_node_with_children(AST_CMD_SE, yylineno, NULL, $3, $6, NULL, NULL);
       }
       | SE LPAREN Expr RPAREN ENTAO Comando SENAO Comando
       {
           $$ = create_ast_node_with_children(AST_CMD_SE, yylineno, NULL, $3, $6, $8, NULL);
       }
       | ENQUANTO LPAREN Expr RPAREN EXECUTE Comando
       {
           $$ = create_ast_node_with_children(AST_CMD_ENQUANTO, yylineno, NULL, $3, $6, NULL, NULL);
       }
       | Bloco
       {
           $$ = $1;
       }
       ;

Expr: OrExpr
    {
        $$ = $1;
    }
    | ID ASSIGN Expr
    {
        ast_node* id_node = create_ast_node(AST_EXPR_ID, yylineno, $1);
        $$ = create_ast_node_with_children(AST_EXPR_ASSIGN, yylineno, NULL, id_node, $3, NULL, NULL);
    }
    ;

OrExpr: OrExpr OU AndExpr
      {
          $$ = create_ast_node_with_children(AST_EXPR_OR, yylineno, NULL, $1, $3, NULL, NULL);
      }
      | AndExpr
      {
          $$ = $1;
      }
      ;

AndExpr: AndExpr E EqExpr
       {
           $$ = create_ast_node_with_children(AST_EXPR_AND, yylineno, NULL, $1, $3, NULL, NULL);
       }
       | EqExpr
       {
           $$ = $1;
       }
       ;

EqExpr: EqExpr EQ DesigExpr
      {
          $$ = create_ast_node_with_children(AST_EXPR_EQ, yylineno, NULL, $1, $3, NULL, NULL);
      }
      | EqExpr NE DesigExpr
      {
          $$ = create_ast_node_with_children(AST_EXPR_NE, yylineno, NULL, $1, $3, NULL, NULL);
      }
      | DesigExpr
      {
          $$ = $1;
      }
      ;

DesigExpr: DesigExpr LT AddExpr
         {
             $$ = create_ast_node_with_children(AST_EXPR_LT, yylineno, NULL, $1, $3, NULL, NULL);
         }
         | DesigExpr GT AddExpr
         {
             $$ = create_ast_node_with_children(AST_EXPR_GT, yylineno, NULL, $1, $3, NULL, NULL);
         }
         | DesigExpr GE AddExpr
         {
             $$ = create_ast_node_with_children(AST_EXPR_GE, yylineno, NULL, $1, $3, NULL, NULL);
         }
         | DesigExpr LE AddExpr
         {
             $$ = create_ast_node_with_children(AST_EXPR_LE, yylineno, NULL, $1, $3, NULL, NULL);
         }
         | AddExpr
         {
             $$ = $1;
         }
         ;

AddExpr: AddExpr PLUS MulExpr
       {
           $$ = create_ast_node_with_children(AST_EXPR_PLUS, yylineno, NULL, $1, $3, NULL, NULL);
       }
       | AddExpr MINUS MulExpr
       {
           $$ = create_ast_node_with_children(AST_EXPR_MINUS, yylineno, NULL, $1, $3, NULL, NULL);
       }
       | MulExpr
       {
           $$ = $1;
       }
       ;

MulExpr: MulExpr MULT UnExpr
       {
           $$ = create_ast_node_with_children(AST_EXPR_MULT, yylineno, NULL, $1, $3, NULL, NULL);
       }
       | MulExpr DIV UnExpr
       {
           $$ = create_ast_node_with_children(AST_EXPR_DIV, yylineno, NULL, $1, $3, NULL, NULL);
       }
       | UnExpr
       {
           $$ = $1;
       }
       ;

UnExpr: MINUS PrimExpr %prec UMINUS
      {
          $$ = create_ast_node_with_children(AST_EXPR_UNARY_MINUS, yylineno, NULL, $2, NULL, NULL, NULL);
      }
      | NOT PrimExpr
      {
          $$ = create_ast_node_with_children(AST_EXPR_NOT, yylineno, NULL, $2, NULL, NULL, NULL);
      }
      | PrimExpr
      {
          $$ = $1;
      }
      ;

PrimExpr: ID LPAREN ListExpr RPAREN
        {
            ast_node* id_node = create_ast_node(AST_EXPR_ID, yylineno, $1);
            $$ = create_ast_node_with_children(AST_EXPR_CALL, yylineno, NULL, id_node, $3, NULL, NULL);
        }
        | ID LPAREN RPAREN
        {
            ast_node* id_node = create_ast_node(AST_EXPR_ID, yylineno, $1);
            $$ = create_ast_node_with_children(AST_EXPR_CALL, yylineno, NULL, id_node, NULL, NULL, NULL);
        }
        | ID
        {
            $$ = create_ast_node(AST_EXPR_ID, yylineno, $1);
        }
        | CARCONST
        {
            ast_node* node = create_ast_node(AST_EXPR_CARCONST, yylineno, $1);
            node->char_value = $1[1]; /* Pega o caractere entre aspas simples */
            $$ = node;
        }
        | INTCONST
        {
            ast_node* node = create_ast_node(AST_EXPR_INTCONST, yylineno, $1);
            node->value = atoi($1);
            $$ = node;
        }
        | LPAREN Expr RPAREN
        {
            $$ = $2;
        }
        ;

ListExpr: Expr
        {
            $$ = $1;
        }
        | ListExpr COMMA Expr
        {
            $$ = create_ast_node_with_children(AST_LISTA_EXPR, yylineno, NULL, $1, $3, NULL, NULL);
        }
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
    
    if (result == 0 && ast_root) {
        printf("=== Análise Sintática Concluída ===\n");
        printf("Árvore Sintática Abstrata:\n");
        print_ast(ast_root, 0);
        printf("\n");
        
        /* Análise Semântica */
        printf("=== Iniciando Análise Semântica ===\n");
        semantic_analyzer* analyzer = create_semantic_analyzer();
        int semantic_result = analyze_program(analyzer, ast_root);
        
        if (semantic_result == 0) {
            printf("=== Análise Semântica Concluída com Sucesso ===\n");
            printf("Tabela de Símbolos:\n");
            print_symbol_table(analyzer->global_table);
            printf("\n");
            
            /* Geração de Código MIPS */
            printf("=== Iniciando Geração de Código MIPS ===\n");
            
            /* Cria arquivo de saída */
            char output_filename[256];
            strcpy(output_filename, argv[1]);
            char* dot = strrchr(output_filename, '.');
            if (dot) *dot = '\0';
            strcat(output_filename, ".s");
            
            FILE* output_file = fopen(output_filename, "w");
            if (!output_file) {
                fprintf(stderr, "ERRO: Não foi possível criar arquivo de saída %s\n", output_filename);
                result = 1;
            } else {
                code_generator* codegen = create_code_generator(output_file, analyzer->global_table);
                generate_code(codegen, ast_root);
                
                printf("=== Código MIPS gerado em %s ===\n", output_filename);
                
                destroy_code_generator(codegen);
                fclose(output_file);
            }
        } else {
            printf("=== Análise Semântica Falhou ===\n");
            result = 1;
        }
        
        destroy_semantic_analyzer(analyzer);
        free_ast(ast_root);
    }
    
    fclose(yyin);
    return result;
} 