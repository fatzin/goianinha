/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser/goianinha.y"

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

#line 91 "parser/goianinha.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "goianinha.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_INTCONST = 4,                   /* INTCONST  */
  YYSYMBOL_CARCONST = 5,                   /* CARCONST  */
  YYSYMBOL_STRING = 6,                     /* STRING  */
  YYSYMBOL_INT = 7,                        /* INT  */
  YYSYMBOL_CAR = 8,                        /* CAR  */
  YYSYMBOL_PROGRAMA = 9,                   /* PROGRAMA  */
  YYSYMBOL_RETORNE = 10,                   /* RETORNE  */
  YYSYMBOL_LEIA = 11,                      /* LEIA  */
  YYSYMBOL_ESCREVA = 12,                   /* ESCREVA  */
  YYSYMBOL_NOVALINHA = 13,                 /* NOVALINHA  */
  YYSYMBOL_SE = 14,                        /* SE  */
  YYSYMBOL_ENTAO = 15,                     /* ENTAO  */
  YYSYMBOL_SENAO = 16,                     /* SENAO  */
  YYSYMBOL_ENQUANTO = 17,                  /* ENQUANTO  */
  YYSYMBOL_EXECUTE = 18,                   /* EXECUTE  */
  YYSYMBOL_OU = 19,                        /* OU  */
  YYSYMBOL_E = 20,                         /* E  */
  YYSYMBOL_ASSIGN = 21,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 22,                      /* PLUS  */
  YYSYMBOL_MINUS = 23,                     /* MINUS  */
  YYSYMBOL_MULT = 24,                      /* MULT  */
  YYSYMBOL_DIV = 25,                       /* DIV  */
  YYSYMBOL_NOT = 26,                       /* NOT  */
  YYSYMBOL_GT = 27,                        /* GT  */
  YYSYMBOL_LT = 28,                        /* LT  */
  YYSYMBOL_GE = 29,                        /* GE  */
  YYSYMBOL_LE = 30,                        /* LE  */
  YYSYMBOL_EQ = 31,                        /* EQ  */
  YYSYMBOL_NE = 32,                        /* NE  */
  YYSYMBOL_LPAREN = 33,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 34,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 35,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 36,                    /* RBRACE  */
  YYSYMBOL_COMMA = 37,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 38,                 /* SEMICOLON  */
  YYSYMBOL_UMINUS = 39,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_Programa = 41,                  /* Programa  */
  YYSYMBOL_DeclFuncVar = 42,               /* DeclFuncVar  */
  YYSYMBOL_DeclProg = 43,                  /* DeclProg  */
  YYSYMBOL_DeclVar = 44,                   /* DeclVar  */
  YYSYMBOL_DeclFunc = 45,                  /* DeclFunc  */
  YYSYMBOL_ListaParametros = 46,           /* ListaParametros  */
  YYSYMBOL_ListaParametrosCont = 47,       /* ListaParametrosCont  */
  YYSYMBOL_Bloco = 48,                     /* Bloco  */
  YYSYMBOL_ListaDeclVar = 49,              /* ListaDeclVar  */
  YYSYMBOL_Tipo = 50,                      /* Tipo  */
  YYSYMBOL_ListaComando = 51,              /* ListaComando  */
  YYSYMBOL_Comando = 52,                   /* Comando  */
  YYSYMBOL_Expr = 53,                      /* Expr  */
  YYSYMBOL_OrExpr = 54,                    /* OrExpr  */
  YYSYMBOL_AndExpr = 55,                   /* AndExpr  */
  YYSYMBOL_EqExpr = 56,                    /* EqExpr  */
  YYSYMBOL_DesigExpr = 57,                 /* DesigExpr  */
  YYSYMBOL_AddExpr = 58,                   /* AddExpr  */
  YYSYMBOL_MulExpr = 59,                   /* MulExpr  */
  YYSYMBOL_UnExpr = 60,                    /* UnExpr  */
  YYSYMBOL_PrimExpr = 61,                  /* PrimExpr  */
  YYSYMBOL_ListExpr = 62                   /* ListExpr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   131

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  122

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    52,    52,    59,    64,    70,    75,    81,    87,    92,
      99,   102,   108,   113,   121,   128,   131,   139,   143,   149,
     153,   159,   163,   167,   171,   176,   180,   185,   189,   193,
     197,   201,   207,   211,   218,   222,   228,   232,   238,   242,
     246,   252,   256,   260,   264,   268,   274,   278,   282,   288,
     292,   296,   302,   306,   310,   316,   321,   326,   330,   336,
     342,   348,   352
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "INTCONST",
  "CARCONST", "STRING", "INT", "CAR", "PROGRAMA", "RETORNE", "LEIA",
  "ESCREVA", "NOVALINHA", "SE", "ENTAO", "SENAO", "ENQUANTO", "EXECUTE",
  "OU", "E", "ASSIGN", "PLUS", "MINUS", "MULT", "DIV", "NOT", "GT", "LT",
  "GE", "LE", "EQ", "NE", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "COMMA",
  "SEMICOLON", "UMINUS", "$accept", "Programa", "DeclFuncVar", "DeclProg",
  "DeclVar", "DeclFunc", "ListaParametros", "ListaParametrosCont", "Bloco",
  "ListaDeclVar", "Tipo", "ListaComando", "Comando", "Expr", "OrExpr",
  "AndExpr", "EqExpr", "DesigExpr", "AddExpr", "MulExpr", "UnExpr",
  "PrimExpr", "ListExpr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-31)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      51,   -31,   -31,    27,    -2,    22,   -31,    -4,   -31,   -11,
      51,   -31,    51,    38,     8,    51,     7,    45,    32,   -31,
      77,    19,    51,   -31,    11,   -31,   -31,    50,    79,    46,
      37,    74,    75,    10,    10,    50,   -31,   -31,    73,     7,
      76,    91,    92,    33,    65,    48,    53,   -31,   -31,    19,
      -4,    78,   -31,   -31,    50,    34,    80,    81,    82,    83,
     -31,    50,    50,    84,   -31,   -31,    88,   -31,   -31,   -31,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    85,   -31,    51,   -31,   -31,   -31,   -29,   -31,
     -31,   -31,   -31,    90,    93,   -31,    92,    33,    65,    65,
      48,    48,    48,    48,    53,    53,   -31,   -31,    51,   -31,
     -31,    50,    96,    95,   -31,   -31,     7,     7,   100,   -31,
       7,   -31
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,    17,    18,     0,     0,     0,     1,     0,     2,     8,
      15,     6,    10,     0,     0,     5,     0,     0,     0,    11,
       0,     8,     5,     4,    57,    59,    58,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,    31,     0,    19,
       0,    32,    35,    37,    40,    45,    48,    51,    54,     8,
       0,    12,     7,     3,     0,     0,     0,     0,     0,     0,
      27,     0,     0,    57,    52,    53,     0,    14,    20,    22,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     9,     0,    33,    56,    61,     0,    23,
      24,    26,    25,     0,     0,    60,    34,    36,    38,    39,
      42,    41,    43,    44,    46,    47,    49,    50,    15,    13,
      55,     0,     0,     0,    16,    62,     0,     0,    28,    30,
       0,    29
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -31,   -31,     1,   -31,   -15,   -31,   -31,    41,    -3,    20,
     -10,    87,   -30,   -26,   -31,    59,    60,    16,    25,    18,
      23,    72,   -31
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     8,    14,    15,    18,    19,    37,    16,
       5,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    88
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      17,    56,    20,    59,    11,   110,    52,     7,   111,    66,
      24,    25,    26,    63,    25,    26,    23,    27,    28,    29,
      30,    31,    12,    53,    32,     9,    13,     6,    85,    87,
      33,    10,    54,    34,    82,    93,    94,    24,    25,    26,
      35,    21,    10,    35,    55,    36,    22,    83,    49,    24,
      25,    26,    58,    24,    25,    26,    13,    33,     1,     2,
      34,    63,    25,    26,    72,    73,    50,    35,    86,    33,
      78,    79,    34,    33,    20,    60,    34,    80,    81,    35,
      51,    33,    57,    35,    34,   115,   118,   119,    98,    99,
     121,    35,    74,    75,    76,    77,   104,   105,    17,   100,
     101,   102,   103,   106,   107,    64,    65,    61,    62,    67,
      70,   116,    71,   117,    69,    84,   120,    55,    89,    90,
      91,    92,    95,   108,   112,   109,    68,   113,   114,    96,
       0,    97
};

static const yytype_int8 yycheck[] =
{
      10,    27,    12,    29,     7,    34,    21,     9,    37,    35,
       3,     4,     5,     3,     4,     5,    15,    10,    11,    12,
      13,    14,    33,    22,    17,     3,    37,     0,    54,    55,
      23,    35,    21,    26,    49,    61,    62,     3,     4,     5,
      33,     3,    35,    33,    33,    38,    38,    50,     3,     3,
       4,     5,     6,     3,     4,     5,    37,    23,     7,     8,
      26,     3,     4,     5,    31,    32,    34,    33,    34,    23,
      22,    23,    26,    23,    84,    38,    26,    24,    25,    33,
       3,    23,     3,    33,    26,   111,   116,   117,    72,    73,
     120,    33,    27,    28,    29,    30,    78,    79,   108,    74,
      75,    76,    77,    80,    81,    33,    34,    33,    33,    36,
      19,    15,    20,    18,    38,    37,    16,    33,    38,    38,
      38,    38,    34,    38,    34,    84,    39,    34,   108,    70,
      -1,    71
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     8,    41,    42,    50,     0,     9,    43,     3,
      35,    48,    33,    37,    44,    45,    49,    50,    46,    47,
      50,     3,    38,    42,     3,     4,     5,    10,    11,    12,
      13,    14,    17,    23,    26,    33,    38,    48,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,     3,
      34,     3,    44,    42,    21,    33,    53,     3,     6,    53,
      38,    33,    33,     3,    61,    61,    53,    36,    51,    38,
      19,    20,    31,    32,    27,    28,    29,    30,    22,    23,
      24,    25,    44,    48,    37,    53,    34,    53,    62,    38,
      38,    38,    38,    53,    53,    34,    55,    56,    57,    57,
      58,    58,    58,    58,    59,    59,    60,    60,    38,    47,
      34,    37,    34,    34,    49,    53,    15,    18,    52,    52,
      16,    52
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    42,    43,    44,    44,    45,
      46,    46,    47,    47,    48,    49,    49,    50,    50,    51,
      51,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    53,    53,    54,    54,    55,    55,    56,    56,
      56,    57,    57,    57,    57,    57,    58,    58,    58,    59,
      59,    59,    60,    60,    60,    61,    61,    61,    61,    61,
      61,    62,    62
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     5,     4,     0,     2,     3,     0,     4,
       0,     1,     2,     4,     4,     0,     5,     1,     1,     1,
       2,     1,     2,     3,     3,     3,     3,     2,     6,     8,
       6,     1,     1,     3,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     2,     2,     1,     4,     3,     1,     1,     1,
       3,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Programa: DeclFuncVar DeclProg  */
#line 53 "parser/goianinha.y"
        {
            (yyval.node) = create_ast_node_with_children(AST_PROGRAMA, yylineno, NULL, (yyvsp[-1].node), (yyvsp[0].node), NULL, NULL);
            ast_root = (yyval.node);
        }
#line 1225 "parser/goianinha.tab.c"
    break;

  case 3: /* DeclFuncVar: Tipo ID DeclVar SEMICOLON DeclFuncVar  */
#line 60 "parser/goianinha.y"
          {
              ast_node* var_decl = create_ast_node_with_children(AST_DECL_VAR, yylineno, (yyvsp[-3].str), (yyvsp[-4].node), (yyvsp[-2].node), NULL, NULL);
              (yyval.node) = create_ast_node_with_children(AST_LISTA_DECL_FUNC_VAR, yylineno, NULL, var_decl, (yyvsp[0].node), NULL, NULL);
          }
#line 1234 "parser/goianinha.tab.c"
    break;

  case 4: /* DeclFuncVar: Tipo ID DeclFunc DeclFuncVar  */
#line 65 "parser/goianinha.y"
          {
              ast_node* func_decl = create_ast_node_with_children(AST_DECL_FUNC, yylineno, (yyvsp[-2].str), (yyvsp[-3].node), (yyvsp[-1].node), NULL, NULL);
              (yyval.node) = create_ast_node_with_children(AST_LISTA_DECL_FUNC_VAR, yylineno, NULL, func_decl, (yyvsp[0].node), NULL, NULL);
          }
#line 1243 "parser/goianinha.tab.c"
    break;

  case 5: /* DeclFuncVar: %empty  */
#line 70 "parser/goianinha.y"
          {
              (yyval.node) = NULL;
          }
#line 1251 "parser/goianinha.tab.c"
    break;

  case 6: /* DeclProg: PROGRAMA Bloco  */
#line 76 "parser/goianinha.y"
        {
            (yyval.node) = (yyvsp[0].node);
        }
#line 1259 "parser/goianinha.tab.c"
    break;

  case 7: /* DeclVar: COMMA ID DeclVar  */
#line 82 "parser/goianinha.y"
       {
           ast_node* id_node = create_ast_node(AST_EXPR_ID, yylineno, (yyvsp[-1].str));
           (yyval.node) = create_ast_node_with_children(AST_LISTA_DECL_VAR, yylineno, NULL, id_node, (yyvsp[0].node), NULL, NULL);
       }
#line 1268 "parser/goianinha.tab.c"
    break;

  case 8: /* DeclVar: %empty  */
#line 87 "parser/goianinha.y"
       {
           (yyval.node) = NULL;
       }
#line 1276 "parser/goianinha.tab.c"
    break;

  case 9: /* DeclFunc: LPAREN ListaParametros RPAREN Bloco  */
#line 93 "parser/goianinha.y"
        {
            (yyval.node) = create_ast_node_with_children(AST_DECL_FUNC, yylineno, NULL, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL);
        }
#line 1284 "parser/goianinha.tab.c"
    break;

  case 10: /* ListaParametros: %empty  */
#line 99 "parser/goianinha.y"
               {
                   (yyval.node) = NULL;
               }
#line 1292 "parser/goianinha.tab.c"
    break;

  case 11: /* ListaParametros: ListaParametrosCont  */
#line 103 "parser/goianinha.y"
               {
                   (yyval.node) = (yyvsp[0].node);
               }
#line 1300 "parser/goianinha.tab.c"
    break;

  case 12: /* ListaParametrosCont: Tipo ID  */
#line 109 "parser/goianinha.y"
                   {
                       ast_node* id_node = create_ast_node(AST_EXPR_ID, yylineno, (yyvsp[0].str));
                       (yyval.node) = create_ast_node_with_children(AST_PARAM, yylineno, NULL, (yyvsp[-1].node), id_node, NULL, NULL);
                   }
#line 1309 "parser/goianinha.tab.c"
    break;

  case 13: /* ListaParametrosCont: Tipo ID COMMA ListaParametrosCont  */
#line 114 "parser/goianinha.y"
                   {
                       ast_node* id_node = create_ast_node(AST_EXPR_ID, yylineno, (yyvsp[-2].str));
                       ast_node* param = create_ast_node_with_children(AST_PARAM, yylineno, NULL, (yyvsp[-3].node), id_node, NULL, NULL);
                       (yyval.node) = create_ast_node_with_children(AST_LISTA_PARAM, yylineno, NULL, param, (yyvsp[0].node), NULL, NULL);
                   }
#line 1319 "parser/goianinha.tab.c"
    break;

  case 14: /* Bloco: LBRACE ListaDeclVar ListaComando RBRACE  */
#line 122 "parser/goianinha.y"
      {
          (yyval.node) = create_ast_node_with_children(AST_BLOCO, yylineno, NULL, (yyvsp[-2].node), (yyvsp[-1].node), NULL, NULL);
      }
#line 1327 "parser/goianinha.tab.c"
    break;

  case 15: /* ListaDeclVar: %empty  */
#line 128 "parser/goianinha.y"
            {
                (yyval.node) = NULL;
            }
#line 1335 "parser/goianinha.tab.c"
    break;

  case 16: /* ListaDeclVar: Tipo ID DeclVar SEMICOLON ListaDeclVar  */
#line 132 "parser/goianinha.y"
            {
                ast_node* id_node = create_ast_node(AST_EXPR_ID, yylineno, (yyvsp[-3].str));
                ast_node* var_decl = create_ast_node_with_children(AST_DECL_VAR, yylineno, NULL, (yyvsp[-4].node), id_node, (yyvsp[-2].node), NULL);
                (yyval.node) = create_ast_node_with_children(AST_LISTA_DECL_VAR, yylineno, NULL, var_decl, (yyvsp[0].node), NULL, NULL);
            }
#line 1345 "parser/goianinha.tab.c"
    break;

  case 17: /* Tipo: INT  */
#line 140 "parser/goianinha.y"
    {
        (yyval.node) = create_ast_node(AST_TIPO_INT, yylineno, (yyvsp[0].str));
    }
#line 1353 "parser/goianinha.tab.c"
    break;

  case 18: /* Tipo: CAR  */
#line 144 "parser/goianinha.y"
    {
        (yyval.node) = create_ast_node(AST_TIPO_CAR, yylineno, (yyvsp[0].str));
    }
#line 1361 "parser/goianinha.tab.c"
    break;

  case 19: /* ListaComando: Comando  */
#line 150 "parser/goianinha.y"
            {
                (yyval.node) = (yyvsp[0].node);
            }
#line 1369 "parser/goianinha.tab.c"
    break;

  case 20: /* ListaComando: Comando ListaComando  */
#line 154 "parser/goianinha.y"
            {
                (yyval.node) = create_ast_node_with_children(AST_LISTA_CMD, yylineno, NULL, (yyvsp[-1].node), (yyvsp[0].node), NULL, NULL);
            }
#line 1377 "parser/goianinha.tab.c"
    break;

  case 21: /* Comando: SEMICOLON  */
#line 160 "parser/goianinha.y"
       {
           (yyval.node) = create_ast_node(AST_CMD_VAZIO, yylineno, NULL);
       }
#line 1385 "parser/goianinha.tab.c"
    break;

  case 22: /* Comando: Expr SEMICOLON  */
#line 164 "parser/goianinha.y"
       {
           (yyval.node) = create_ast_node_with_children(AST_CMD_EXPR, yylineno, NULL, (yyvsp[-1].node), NULL, NULL, NULL);
       }
#line 1393 "parser/goianinha.tab.c"
    break;

  case 23: /* Comando: RETORNE Expr SEMICOLON  */
#line 168 "parser/goianinha.y"
       {
           (yyval.node) = create_ast_node_with_children(AST_CMD_RETORNE, yylineno, NULL, (yyvsp[-1].node), NULL, NULL, NULL);
       }
#line 1401 "parser/goianinha.tab.c"
    break;

  case 24: /* Comando: LEIA ID SEMICOLON  */
#line 172 "parser/goianinha.y"
       {
           ast_node* id_node = create_ast_node(AST_EXPR_ID, yylineno, (yyvsp[-1].str));
           (yyval.node) = create_ast_node_with_children(AST_CMD_LEIA, yylineno, NULL, id_node, NULL, NULL, NULL);
       }
#line 1410 "parser/goianinha.tab.c"
    break;

  case 25: /* Comando: ESCREVA Expr SEMICOLON  */
#line 177 "parser/goianinha.y"
       {
           (yyval.node) = create_ast_node_with_children(AST_CMD_ESCREVA, yylineno, NULL, (yyvsp[-1].node), NULL, NULL, NULL);
       }
#line 1418 "parser/goianinha.tab.c"
    break;

  case 26: /* Comando: ESCREVA STRING SEMICOLON  */
#line 181 "parser/goianinha.y"
       {
           ast_node* string_node = create_ast_node(AST_STRING, yylineno, (yyvsp[-1].str));
           (yyval.node) = create_ast_node_with_children(AST_CMD_ESCREVA, yylineno, NULL, string_node, NULL, NULL, NULL);
       }
#line 1427 "parser/goianinha.tab.c"
    break;

  case 27: /* Comando: NOVALINHA SEMICOLON  */
#line 186 "parser/goianinha.y"
       {
           (yyval.node) = create_ast_node(AST_CMD_NOVALINHA, yylineno, NULL);
       }
#line 1435 "parser/goianinha.tab.c"
    break;

  case 28: /* Comando: SE LPAREN Expr RPAREN ENTAO Comando  */
#line 190 "parser/goianinha.y"
       {
           (yyval.node) = create_ast_node_with_children(AST_CMD_SE, yylineno, NULL, (yyvsp[-3].node), (yyvsp[0].node), NULL, NULL);
       }
#line 1443 "parser/goianinha.tab.c"
    break;

  case 29: /* Comando: SE LPAREN Expr RPAREN ENTAO Comando SENAO Comando  */
#line 194 "parser/goianinha.y"
       {
           (yyval.node) = create_ast_node_with_children(AST_CMD_SE, yylineno, NULL, (yyvsp[-5].node), (yyvsp[-2].node), (yyvsp[0].node), NULL);
       }
#line 1451 "parser/goianinha.tab.c"
    break;

  case 30: /* Comando: ENQUANTO LPAREN Expr RPAREN EXECUTE Comando  */
#line 198 "parser/goianinha.y"
       {
           (yyval.node) = create_ast_node_with_children(AST_CMD_ENQUANTO, yylineno, NULL, (yyvsp[-3].node), (yyvsp[0].node), NULL, NULL);
       }
#line 1459 "parser/goianinha.tab.c"
    break;

  case 31: /* Comando: Bloco  */
#line 202 "parser/goianinha.y"
       {
           (yyval.node) = (yyvsp[0].node);
       }
#line 1467 "parser/goianinha.tab.c"
    break;

  case 32: /* Expr: OrExpr  */
#line 208 "parser/goianinha.y"
    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1475 "parser/goianinha.tab.c"
    break;

  case 33: /* Expr: ID ASSIGN Expr  */
#line 212 "parser/goianinha.y"
    {
        ast_node* id_node = create_ast_node(AST_EXPR_ID, yylineno, (yyvsp[-2].str));
        (yyval.node) = create_ast_node_with_children(AST_EXPR_ASSIGN, yylineno, NULL, id_node, (yyvsp[0].node), NULL, NULL);
    }
#line 1484 "parser/goianinha.tab.c"
    break;

  case 34: /* OrExpr: OrExpr OU AndExpr  */
#line 219 "parser/goianinha.y"
      {
          (yyval.node) = create_ast_node_with_children(AST_EXPR_OR, yylineno, NULL, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL);
      }
#line 1492 "parser/goianinha.tab.c"
    break;

  case 35: /* OrExpr: AndExpr  */
#line 223 "parser/goianinha.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1500 "parser/goianinha.tab.c"
    break;

  case 36: /* AndExpr: AndExpr E EqExpr  */
#line 229 "parser/goianinha.y"
       {
           (yyval.node) = create_ast_node_with_children(AST_EXPR_AND, yylineno, NULL, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL);
       }
#line 1508 "parser/goianinha.tab.c"
    break;

  case 37: /* AndExpr: EqExpr  */
#line 233 "parser/goianinha.y"
       {
           (yyval.node) = (yyvsp[0].node);
       }
#line 1516 "parser/goianinha.tab.c"
    break;

  case 38: /* EqExpr: EqExpr EQ DesigExpr  */
#line 239 "parser/goianinha.y"
      {
          (yyval.node) = create_ast_node_with_children(AST_EXPR_EQ, yylineno, NULL, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL);
      }
#line 1524 "parser/goianinha.tab.c"
    break;

  case 39: /* EqExpr: EqExpr NE DesigExpr  */
#line 243 "parser/goianinha.y"
      {
          (yyval.node) = create_ast_node_with_children(AST_EXPR_NE, yylineno, NULL, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL);
      }
#line 1532 "parser/goianinha.tab.c"
    break;

  case 40: /* EqExpr: DesigExpr  */
#line 247 "parser/goianinha.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1540 "parser/goianinha.tab.c"
    break;

  case 41: /* DesigExpr: DesigExpr LT AddExpr  */
#line 253 "parser/goianinha.y"
         {
             (yyval.node) = create_ast_node_with_children(AST_EXPR_LT, yylineno, NULL, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL);
         }
#line 1548 "parser/goianinha.tab.c"
    break;

  case 42: /* DesigExpr: DesigExpr GT AddExpr  */
#line 257 "parser/goianinha.y"
         {
             (yyval.node) = create_ast_node_with_children(AST_EXPR_GT, yylineno, NULL, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL);
         }
#line 1556 "parser/goianinha.tab.c"
    break;

  case 43: /* DesigExpr: DesigExpr GE AddExpr  */
#line 261 "parser/goianinha.y"
         {
             (yyval.node) = create_ast_node_with_children(AST_EXPR_GE, yylineno, NULL, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL);
         }
#line 1564 "parser/goianinha.tab.c"
    break;

  case 44: /* DesigExpr: DesigExpr LE AddExpr  */
#line 265 "parser/goianinha.y"
         {
             (yyval.node) = create_ast_node_with_children(AST_EXPR_LE, yylineno, NULL, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL);
         }
#line 1572 "parser/goianinha.tab.c"
    break;

  case 45: /* DesigExpr: AddExpr  */
#line 269 "parser/goianinha.y"
         {
             (yyval.node) = (yyvsp[0].node);
         }
#line 1580 "parser/goianinha.tab.c"
    break;

  case 46: /* AddExpr: AddExpr PLUS MulExpr  */
#line 275 "parser/goianinha.y"
       {
           (yyval.node) = create_ast_node_with_children(AST_EXPR_PLUS, yylineno, NULL, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL);
       }
#line 1588 "parser/goianinha.tab.c"
    break;

  case 47: /* AddExpr: AddExpr MINUS MulExpr  */
#line 279 "parser/goianinha.y"
       {
           (yyval.node) = create_ast_node_with_children(AST_EXPR_MINUS, yylineno, NULL, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL);
       }
#line 1596 "parser/goianinha.tab.c"
    break;

  case 48: /* AddExpr: MulExpr  */
#line 283 "parser/goianinha.y"
       {
           (yyval.node) = (yyvsp[0].node);
       }
#line 1604 "parser/goianinha.tab.c"
    break;

  case 49: /* MulExpr: MulExpr MULT UnExpr  */
#line 289 "parser/goianinha.y"
       {
           (yyval.node) = create_ast_node_with_children(AST_EXPR_MULT, yylineno, NULL, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL);
       }
#line 1612 "parser/goianinha.tab.c"
    break;

  case 50: /* MulExpr: MulExpr DIV UnExpr  */
#line 293 "parser/goianinha.y"
       {
           (yyval.node) = create_ast_node_with_children(AST_EXPR_DIV, yylineno, NULL, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL);
       }
#line 1620 "parser/goianinha.tab.c"
    break;

  case 51: /* MulExpr: UnExpr  */
#line 297 "parser/goianinha.y"
       {
           (yyval.node) = (yyvsp[0].node);
       }
#line 1628 "parser/goianinha.tab.c"
    break;

  case 52: /* UnExpr: MINUS PrimExpr  */
#line 303 "parser/goianinha.y"
      {
          (yyval.node) = create_ast_node_with_children(AST_EXPR_UNARY_MINUS, yylineno, NULL, (yyvsp[0].node), NULL, NULL, NULL);
      }
#line 1636 "parser/goianinha.tab.c"
    break;

  case 53: /* UnExpr: NOT PrimExpr  */
#line 307 "parser/goianinha.y"
      {
          (yyval.node) = create_ast_node_with_children(AST_EXPR_NOT, yylineno, NULL, (yyvsp[0].node), NULL, NULL, NULL);
      }
#line 1644 "parser/goianinha.tab.c"
    break;

  case 54: /* UnExpr: PrimExpr  */
#line 311 "parser/goianinha.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1652 "parser/goianinha.tab.c"
    break;

  case 55: /* PrimExpr: ID LPAREN ListExpr RPAREN  */
#line 317 "parser/goianinha.y"
        {
            ast_node* id_node = create_ast_node(AST_EXPR_ID, yylineno, (yyvsp[-3].str));
            (yyval.node) = create_ast_node_with_children(AST_EXPR_CALL, yylineno, NULL, id_node, (yyvsp[-1].node), NULL, NULL);
        }
#line 1661 "parser/goianinha.tab.c"
    break;

  case 56: /* PrimExpr: ID LPAREN RPAREN  */
#line 322 "parser/goianinha.y"
        {
            ast_node* id_node = create_ast_node(AST_EXPR_ID, yylineno, (yyvsp[-2].str));
            (yyval.node) = create_ast_node_with_children(AST_EXPR_CALL, yylineno, NULL, id_node, NULL, NULL, NULL);
        }
#line 1670 "parser/goianinha.tab.c"
    break;

  case 57: /* PrimExpr: ID  */
#line 327 "parser/goianinha.y"
        {
            (yyval.node) = create_ast_node(AST_EXPR_ID, yylineno, (yyvsp[0].str));
        }
#line 1678 "parser/goianinha.tab.c"
    break;

  case 58: /* PrimExpr: CARCONST  */
#line 331 "parser/goianinha.y"
        {
            ast_node* node = create_ast_node(AST_EXPR_CARCONST, yylineno, (yyvsp[0].str));
            node->char_value = (yyvsp[0].str)[1]; /* Pega o caractere entre aspas simples */
            (yyval.node) = node;
        }
#line 1688 "parser/goianinha.tab.c"
    break;

  case 59: /* PrimExpr: INTCONST  */
#line 337 "parser/goianinha.y"
        {
            ast_node* node = create_ast_node(AST_EXPR_INTCONST, yylineno, (yyvsp[0].str));
            node->value = atoi((yyvsp[0].str));
            (yyval.node) = node;
        }
#line 1698 "parser/goianinha.tab.c"
    break;

  case 60: /* PrimExpr: LPAREN Expr RPAREN  */
#line 343 "parser/goianinha.y"
        {
            (yyval.node) = (yyvsp[-1].node);
        }
#line 1706 "parser/goianinha.tab.c"
    break;

  case 61: /* ListExpr: Expr  */
#line 349 "parser/goianinha.y"
        {
            (yyval.node) = (yyvsp[0].node);
        }
#line 1714 "parser/goianinha.tab.c"
    break;

  case 62: /* ListExpr: ListExpr COMMA Expr  */
#line 353 "parser/goianinha.y"
        {
            (yyval.node) = create_ast_node_with_children(AST_LISTA_EXPR, yylineno, NULL, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL);
        }
#line 1722 "parser/goianinha.tab.c"
    break;


#line 1726 "parser/goianinha.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 358 "parser/goianinha.y"


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
