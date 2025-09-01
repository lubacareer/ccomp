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
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symtab.h"

extern int yylex(void);
extern SymbolTable *symbol_table;
void yyerror(const char *s);
extern char *yytext;
extern int yylineno;
ASTNode *root;
int main_function_defined = 0;

void check_function_call(char *name, ASTNode *args);
int compare_types(Type *a, Type *b);
Symbol *get_current_function();
DataType get_expression_type(ASTNode *expr);

#line 92 "parser.c"

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

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_IDENTIFIER = 3,               /* T_IDENTIFIER  */
  YYSYMBOL_T_TYPENAME = 4,                 /* T_TYPENAME  */
  YYSYMBOL_T_INTEGER = 5,                  /* T_INTEGER  */
  YYSYMBOL_T_FLOAT_LITERAL = 6,            /* T_FLOAT_LITERAL  */
  YYSYMBOL_T_CHAR_LITERAL = 7,             /* T_CHAR_LITERAL  */
  YYSYMBOL_T_STRING_LITERAL = 8,           /* T_STRING_LITERAL  */
  YYSYMBOL_T_INT = 9,                      /* T_INT  */
  YYSYMBOL_T_RETURN = 10,                  /* T_RETURN  */
  YYSYMBOL_T_IF = 11,                      /* T_IF  */
  YYSYMBOL_T_ELSE = 12,                    /* T_ELSE  */
  YYSYMBOL_T_WHILE = 13,                   /* T_WHILE  */
  YYSYMBOL_T_FOR = 14,                     /* T_FOR  */
  YYSYMBOL_T_SWITCH = 15,                  /* T_SWITCH  */
  YYSYMBOL_T_CASE = 16,                    /* T_CASE  */
  YYSYMBOL_T_DEFAULT = 17,                 /* T_DEFAULT  */
  YYSYMBOL_T_BREAK = 18,                   /* T_BREAK  */
  YYSYMBOL_T_DO = 19,                      /* T_DO  */
  YYSYMBOL_T_CONTINUE = 20,                /* T_CONTINUE  */
  YYSYMBOL_T_GOTO = 21,                    /* T_GOTO  */
  YYSYMBOL_T_STRUCT = 22,                  /* T_STRUCT  */
  YYSYMBOL_T_UNION = 23,                   /* T_UNION  */
  YYSYMBOL_T_ENUM = 24,                    /* T_ENUM  */
  YYSYMBOL_T_CHAR = 25,                    /* T_CHAR  */
  YYSYMBOL_T_FLOAT = 26,                   /* T_FLOAT  */
  YYSYMBOL_T_DOUBLE = 27,                  /* T_DOUBLE  */
  YYSYMBOL_T_VOID = 28,                    /* T_VOID  */
  YYSYMBOL_T_SHORT = 29,                   /* T_SHORT  */
  YYSYMBOL_T_LONG = 30,                    /* T_LONG  */
  YYSYMBOL_T_SIGNED = 31,                  /* T_SIGNED  */
  YYSYMBOL_T_UNSIGNED = 32,                /* T_UNSIGNED  */
  YYSYMBOL_T_TYPEDEF = 33,                 /* T_TYPEDEF  */
  YYSYMBOL_T_SIZEOF = 34,                  /* T_SIZEOF  */
  YYSYMBOL_T_CONST = 35,                   /* T_CONST  */
  YYSYMBOL_T_STATIC = 36,                  /* T_STATIC  */
  YYSYMBOL_T_EXTERN = 37,                  /* T_EXTERN  */
  YYSYMBOL_T_VOLATILE = 38,                /* T_VOLATILE  */
  YYSYMBOL_T_INLINE = 39,                  /* T_INLINE  */
  YYSYMBOL_T_BOOL = 40,                    /* T_BOOL  */
  YYSYMBOL_T_SEMICOLON = 41,               /* T_SEMICOLON  */
  YYSYMBOL_T_LPAREN = 42,                  /* T_LPAREN  */
  YYSYMBOL_T_RPAREN = 43,                  /* T_RPAREN  */
  YYSYMBOL_T_LBRACE = 44,                  /* T_LBRACE  */
  YYSYMBOL_T_RBRACE = 45,                  /* T_RBRACE  */
  YYSYMBOL_T_COMMA = 46,                   /* T_COMMA  */
  YYSYMBOL_T_LBRACKET = 47,                /* T_LBRACKET  */
  YYSYMBOL_T_RBRACKET = 48,                /* T_RBRACKET  */
  YYSYMBOL_T_DOT = 49,                     /* T_DOT  */
  YYSYMBOL_T_ARROW = 50,                   /* T_ARROW  */
  YYSYMBOL_T_INC = 51,                     /* T_INC  */
  YYSYMBOL_T_DEC = 52,                     /* T_DEC  */
  YYSYMBOL_T_LOGICAL_NOT = 53,             /* T_LOGICAL_NOT  */
  YYSYMBOL_T_BITWISE_NOT = 54,             /* T_BITWISE_NOT  */
  YYSYMBOL_T_LOGICAL_AND = 55,             /* T_LOGICAL_AND  */
  YYSYMBOL_T_LOGICAL_OR = 56,              /* T_LOGICAL_OR  */
  YYSYMBOL_T_BITWISE_AND = 57,             /* T_BITWISE_AND  */
  YYSYMBOL_T_BITWISE_OR = 58,              /* T_BITWISE_OR  */
  YYSYMBOL_T_BITWISE_XOR = 59,             /* T_BITWISE_XOR  */
  YYSYMBOL_T_LSHIFT = 60,                  /* T_LSHIFT  */
  YYSYMBOL_T_RSHIFT = 61,                  /* T_RSHIFT  */
  YYSYMBOL_T_ASSIGN = 62,                  /* T_ASSIGN  */
  YYSYMBOL_T_ADD_ASSIGN = 63,              /* T_ADD_ASSIGN  */
  YYSYMBOL_T_SUB_ASSIGN = 64,              /* T_SUB_ASSIGN  */
  YYSYMBOL_T_MUL_ASSIGN = 65,              /* T_MUL_ASSIGN  */
  YYSYMBOL_T_DIV_ASSIGN = 66,              /* T_DIV_ASSIGN  */
  YYSYMBOL_T_MOD_ASSIGN = 67,              /* T_MOD_ASSIGN  */
  YYSYMBOL_T_EQ = 68,                      /* T_EQ  */
  YYSYMBOL_T_NE = 69,                      /* T_NE  */
  YYSYMBOL_T_GT = 70,                      /* T_GT  */
  YYSYMBOL_T_GE = 71,                      /* T_GE  */
  YYSYMBOL_T_LT = 72,                      /* T_LT  */
  YYSYMBOL_T_LE = 73,                      /* T_LE  */
  YYSYMBOL_T_ADD = 74,                     /* T_ADD  */
  YYSYMBOL_T_SUB = 75,                     /* T_SUB  */
  YYSYMBOL_T_MUL = 76,                     /* T_MUL  */
  YYSYMBOL_T_DIV = 77,                     /* T_DIV  */
  YYSYMBOL_T_MOD = 78,                     /* T_MOD  */
  YYSYMBOL_T_QUESTION = 79,                /* T_QUESTION  */
  YYSYMBOL_T_COLON = 80,                   /* T_COLON  */
  YYSYMBOL_T_IFX = 81,                     /* T_IFX  */
  YYSYMBOL_82_ = 82,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 83,                  /* $accept  */
  YYSYMBOL_program = 84,                   /* program  */
  YYSYMBOL_translation_unit = 85,          /* translation_unit  */
  YYSYMBOL_external_declaration = 86,      /* external_declaration  */
  YYSYMBOL_function_definition = 87,       /* function_definition  */
  YYSYMBOL_declaration = 88,               /* declaration  */
  YYSYMBOL_declaration_specifiers = 89,    /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 90,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 91,           /* init_declarator  */
  YYSYMBOL_declarator = 92,                /* declarator  */
  YYSYMBOL_direct_declarator = 93,         /* direct_declarator  */
  YYSYMBOL_pointer = 94,                   /* pointer  */
  YYSYMBOL_param_list = 95,                /* param_list  */
  YYSYMBOL_parameter_declaration = 96,     /* parameter_declaration  */
  YYSYMBOL_type_name = 97,                 /* type_name  */
  YYSYMBOL_abstract_declarator = 98,       /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 99, /* direct_abstract_declarator  */
  YYSYMBOL_statement = 100,                /* statement  */
  YYSYMBOL_compound_statement = 101,       /* compound_statement  */
  YYSYMBOL_102_1 = 102,                    /* $@1  */
  YYSYMBOL_103_2 = 103,                    /* $@2  */
  YYSYMBOL_block_item_list = 104,          /* block_item_list  */
  YYSYMBOL_block_item = 105,               /* block_item  */
  YYSYMBOL_labeled_statement = 106,        /* labeled_statement  */
  YYSYMBOL_selection_statement = 107,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 108,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 109,           /* jump_statement  */
  YYSYMBOL_expression = 110,               /* expression  */
  YYSYMBOL_assignment_expression = 111,    /* assignment_expression  */
  YYSYMBOL_conditional_expression = 112,   /* conditional_expression  */
  YYSYMBOL_logical_or_expression = 113,    /* logical_or_expression  */
  YYSYMBOL_logical_and_expression = 114,   /* logical_and_expression  */
  YYSYMBOL_inclusive_or_expression = 115,  /* inclusive_or_expression  */
  YYSYMBOL_exclusive_or_expression = 116,  /* exclusive_or_expression  */
  YYSYMBOL_and_expression = 117,           /* and_expression  */
  YYSYMBOL_equality_expression = 118,      /* equality_expression  */
  YYSYMBOL_relational_expression = 119,    /* relational_expression  */
  YYSYMBOL_shift_expression = 120,         /* shift_expression  */
  YYSYMBOL_additive_expression = 121,      /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 122, /* multiplicative_expression  */
  YYSYMBOL_cast_expression = 123,          /* cast_expression  */
  YYSYMBOL_unary_expression = 124,         /* unary_expression  */
  YYSYMBOL_postfix_expression = 125,       /* postfix_expression  */
  YYSYMBOL_primary_expression = 126,       /* primary_expression  */
  YYSYMBOL_argument_expression_list = 127, /* argument_expression_list  */
  YYSYMBOL_initializer = 128,              /* initializer  */
  YYSYMBOL_initializer_list = 129,         /* initializer_list  */
  YYSYMBOL_type_specifier = 130,           /* type_specifier  */
  YYSYMBOL_struct_specifier = 131,         /* struct_specifier  */
  YYSYMBOL_union_specifier = 132,          /* union_specifier  */
  YYSYMBOL_enum_specifier = 133,           /* enum_specifier  */
  YYSYMBOL_enumerator_list = 134,          /* enumerator_list  */
  YYSYMBOL_enumerator = 135,               /* enumerator  */
  YYSYMBOL_struct_declaration_list = 136,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 137,       /* struct_declaration  */
  YYSYMBOL_declarator_list = 138           /* declarator_list  */
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
typedef yytype_int16 yy_state_t;

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
#define YYFINAL  43
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1433

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  83
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  186
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  346

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   336


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
       2,     2,     2,     2,     2,     2,     2,     2,    82,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    75,    75,    84,    85,    89,    90,    94,   116,   125,
     126,   135,   136,   137,   138,   139,   140,   144,   145,   149,
     150,   154,   155,   159,   160,   161,   162,   163,   173,   186,
     187,   191,   192,   196,   209,   210,   214,   215,   219,   220,
     221,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     237,   238,   239,   240,   241,   242,   246,   246,   247,   247,
     251,   252,   256,   257,   261,   262,   263,   264,   268,   274,
     280,   284,   290,   291,   292,   293,   294,   298,   299,   300,
     301,   308,   321,   322,   326,   327,   335,   336,   337,   338,
     339,   343,   344,   348,   349,   358,   359,   368,   369,   373,
     374,   378,   379,   383,   384,   392,   403,   404,   412,   420,
     428,   439,   440,   441,   445,   446,   447,   451,   452,   453,
     454,   458,   459,   463,   464,   465,   466,   467,   473,   474,
     475,   476,   482,   483,   487,   488,   499,   503,   507,   508,
     509,   510,   514,   520,   521,   522,   523,   524,   528,   529,
     533,   534,   535,   539,   540,   544,   545,   546,   547,   548,
     549,   550,   551,   552,   553,   554,   555,   556,   557,   561,
     562,   563,   567,   568,   569,   573,   574,   575,   579,   580,
     584,   585,   589,   590,   594,   598,   599
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
  "\"end of file\"", "error", "\"invalid token\"", "T_IDENTIFIER",
  "T_TYPENAME", "T_INTEGER", "T_FLOAT_LITERAL", "T_CHAR_LITERAL",
  "T_STRING_LITERAL", "T_INT", "T_RETURN", "T_IF", "T_ELSE", "T_WHILE",
  "T_FOR", "T_SWITCH", "T_CASE", "T_DEFAULT", "T_BREAK", "T_DO",
  "T_CONTINUE", "T_GOTO", "T_STRUCT", "T_UNION", "T_ENUM", "T_CHAR",
  "T_FLOAT", "T_DOUBLE", "T_VOID", "T_SHORT", "T_LONG", "T_SIGNED",
  "T_UNSIGNED", "T_TYPEDEF", "T_SIZEOF", "T_CONST", "T_STATIC", "T_EXTERN",
  "T_VOLATILE", "T_INLINE", "T_BOOL", "T_SEMICOLON", "T_LPAREN",
  "T_RPAREN", "T_LBRACE", "T_RBRACE", "T_COMMA", "T_LBRACKET",
  "T_RBRACKET", "T_DOT", "T_ARROW", "T_INC", "T_DEC", "T_LOGICAL_NOT",
  "T_BITWISE_NOT", "T_LOGICAL_AND", "T_LOGICAL_OR", "T_BITWISE_AND",
  "T_BITWISE_OR", "T_BITWISE_XOR", "T_LSHIFT", "T_RSHIFT", "T_ASSIGN",
  "T_ADD_ASSIGN", "T_SUB_ASSIGN", "T_MUL_ASSIGN", "T_DIV_ASSIGN",
  "T_MOD_ASSIGN", "T_EQ", "T_NE", "T_GT", "T_GE", "T_LT", "T_LE", "T_ADD",
  "T_SUB", "T_MUL", "T_DIV", "T_MOD", "T_QUESTION", "T_COLON", "T_IFX",
  "':'", "$accept", "program", "translation_unit", "external_declaration",
  "function_definition", "declaration", "declaration_specifiers",
  "init_declarator_list", "init_declarator", "declarator",
  "direct_declarator", "pointer", "param_list", "parameter_declaration",
  "type_name", "abstract_declarator", "direct_abstract_declarator",
  "statement", "compound_statement", "$@1", "$@2", "block_item_list",
  "block_item", "labeled_statement", "selection_statement",
  "iteration_statement", "jump_statement", "expression",
  "assignment_expression", "conditional_expression",
  "logical_or_expression", "logical_and_expression",
  "inclusive_or_expression", "exclusive_or_expression", "and_expression",
  "equality_expression", "relational_expression", "shift_expression",
  "additive_expression", "multiplicative_expression", "cast_expression",
  "unary_expression", "postfix_expression", "primary_expression",
  "argument_expression_list", "initializer", "initializer_list",
  "type_specifier", "struct_specifier", "union_specifier",
  "enum_specifier", "enumerator_list", "enumerator",
  "struct_declaration_list", "struct_declaration", "declarator_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-184)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-57)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1356,  -184,  -184,    22,    26,    27,  -184,  -184,  -184,  -184,
    -184,  -184,  -184,  -184,  1393,  1393,  1393,  1393,  1393,  1393,
    -184,    58,  1356,  -184,  -184,  -184,     7,  -184,  -184,  -184,
    -184,   -10,  1393,    45,  1393,    53,   122,    18,  -184,  -184,
    -184,  -184,  -184,  -184,  -184,  -184,  -184,    18,   -11,    -4,
    -184,    -1,    34,    20,  1393,    18,  1134,  -184,  1393,  1171,
     122,    78,     1,  -184,    41,   100,   107,  -184,  -184,    18,
     128,   714,  -184,  1282,   767,    34,  1208,  -184,    49,  -184,
    -184,  1245,  -184,   188,   977,  -184,   122,  -184,  -184,  -184,
     142,   394,  -184,  -184,  -184,  -184,  -184,  1007,   504,   714,
    1037,  1037,   977,   977,   977,   977,   977,   977,  -184,  -184,
     -23,   136,   150,   151,   165,   -42,    88,   175,   167,    90,
    -184,    37,    72,  -184,  -184,  -184,    17,    -5,  -184,  -184,
     179,  -184,  -184,  -184,    18,  -184,  -184,  -184,  -184,  -184,
     147,   797,   206,   213,   216,   218,   977,   158,   238,   652,
     239,   278,  -184,     7,  -184,  -184,   320,  -184,  -184,  -184,
    -184,  -184,    65,  -184,   504,  -184,    -7,   241,    96,  -184,
     198,   977,  -184,  -184,  -184,  -184,  -184,  -184,  -184,  -184,
     977,   977,   977,   977,   977,   977,   977,   977,   977,   977,
     977,   977,   977,   977,   977,   977,   977,   977,   977,   977,
     977,   977,   977,   977,   977,   827,   977,   279,   282,  -184,
    -184,   707,   857,  -184,    21,  -184,    66,  -184,  1393,  -184,
    -184,   578,  -184,    71,   977,   977,   449,   977,   205,   652,
    -184,   277,  -184,   251,  -184,  -184,  -184,   977,   250,  1092,
      84,  -184,   977,  -184,  -184,   244,   136,   -35,   150,   151,
     165,   -42,    88,    88,   175,   175,   175,   175,   167,   167,
      90,    90,  -184,  -184,  -184,  -184,  -184,  -184,  -184,  -184,
    -184,  -184,  -184,   131,    70,  -184,  -184,  -184,   159,   256,
    -184,   246,    66,  1319,   887,  -184,  -184,  -184,  -184,   160,
     161,   977,   102,   166,   652,  -184,   258,  -184,  -184,  -184,
    -184,  -184,  -184,   977,  -184,   977,  -184,  -184,  -184,  -184,
    -184,   171,  -184,   254,   652,   652,   108,   977,   652,  -184,
     977,  -184,  -184,  -184,  -184,   291,  -184,   917,   111,  -184,
     173,   652,   652,   178,   947,   263,  -184,  -184,   652,   652,
     185,  -184,  -184,  -184,   652,  -184
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   168,   159,     0,     0,     0,   157,   161,   162,   156,
     158,   160,   163,   164,     0,     0,     0,     0,     0,     0,
     155,     0,     2,     3,     5,     6,     0,    11,   165,   166,
     167,   171,     0,   174,     0,   177,     0,     0,    12,    13,
      14,    15,    16,     1,     4,    23,     9,     0,    29,     0,
      17,    19,    22,     0,     0,     0,     0,   182,     0,     0,
       0,   180,     0,   178,     0,    19,     0,    30,     8,     0,
      58,     0,     7,     0,     0,    21,     0,   185,     0,   170,
     183,     0,   173,     0,     0,   176,     0,    10,    24,    18,
       0,     0,   142,   143,   144,   145,   146,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   150,    84,
      91,    93,    95,    97,    99,   101,   103,   106,   111,   114,
     117,   121,   123,   134,    20,    28,    35,     0,    31,    26,
       0,   121,   169,   184,     0,   172,   175,   181,   179,    57,
     142,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    62,     0,    63,    51,     0,    60,    50,    53,
      54,    55,     0,    82,     0,   132,    36,     0,     0,   153,
       0,     0,   124,   125,   131,   130,   126,   128,   129,   127,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   140,
     141,     0,     0,    33,    38,    34,    39,    27,     0,    25,
     186,     0,    80,     0,     0,     0,     0,     0,     0,     0,
      79,     0,    78,     0,    59,    61,    52,     0,     0,     0,
      38,    37,     0,   147,   151,     0,    94,     0,    96,    98,
     100,   102,   104,   105,   108,   110,   107,   109,   112,   113,
     115,   116,   118,   119,   120,    85,    86,    87,    88,    89,
      90,   136,   148,     0,     0,   138,   139,    46,     0,     0,
      42,     0,    40,     0,     0,    32,    67,    64,    81,     0,
       0,     0,     0,     0,     0,    66,     0,    77,    83,   133,
     122,   152,   154,     0,   137,     0,   135,    47,    41,    43,
      48,     0,    44,     0,     0,     0,     0,     0,     0,    65,
       0,    92,   149,    49,    45,    68,    71,     0,     0,    70,
       0,     0,     0,     0,     0,     0,    69,    75,     0,     0,
       0,    72,    76,    73,     0,    74
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -184,  -184,  -184,   283,  -184,   -79,     0,   269,   240,   -19,
     -45,   -46,   -68,    89,   144,   -87,  -183,  -143,   259,  -184,
    -184,  -184,   155,  -184,  -184,  -184,  -184,   -97,   -67,   -71,
    -184,   132,   133,   130,   138,   129,    59,     9,    61,    62,
     -52,    79,  -184,  -184,  -184,   -90,  -184,  -184,  -184,  -184,
    -184,   257,   230,    38,    29,  -184
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    21,    22,    23,    24,    25,    55,    49,    50,    65,
      52,    53,   278,   128,   167,   279,   216,   154,   155,    90,
      91,   156,   157,   158,   159,   160,   161,   162,   163,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   273,   124,   170,    27,    28,    29,
      30,    62,    63,    56,    57,    78
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      26,   168,    67,   130,   108,   127,   231,    51,    75,   169,
      45,   237,   152,   137,    37,    38,    39,    40,    41,    42,
      45,    45,    26,    45,    45,    31,   186,   187,    66,    33,
      35,   282,   108,   180,    54,   239,    77,    68,   217,   215,
     212,   218,    69,    70,   223,   303,    85,    86,    46,    47,
     174,   175,   176,   177,   178,   179,   181,   282,    43,   211,
      47,    71,    47,   211,   212,    48,    32,   168,   212,    48,
      34,    36,    59,   126,   168,   228,    73,   152,   287,   241,
     214,    74,    87,    48,   247,    80,   295,    69,    80,    58,
     133,   153,    76,    48,    48,   134,    81,    60,   166,   199,
     200,   201,   202,   203,   204,    80,   236,   213,   283,   274,
      80,   237,   288,   284,   205,   220,   237,   237,   306,   206,
     240,   207,   208,   209,   210,    61,   239,   289,   290,   292,
     293,   212,   265,   266,   267,   268,   269,   270,   272,   243,
      84,   281,   237,   317,   262,   263,   264,   291,   237,   327,
      88,   319,   334,   131,   237,   302,   153,   237,   188,   189,
     190,   191,    71,   131,   166,   214,   196,   197,   198,    75,
     298,   325,   326,   -56,   304,   329,   165,   305,   108,   172,
     173,   131,   131,   131,   131,   131,   131,   139,   336,   337,
     300,   182,    66,   240,   316,   342,   343,   254,   255,   256,
     257,   345,   307,   314,   315,   218,   237,   237,   183,   318,
     184,   126,   237,   313,   323,   311,   335,   218,   126,   237,
     328,   338,   185,   330,   237,   131,   153,   219,   344,   221,
     333,   237,   321,   136,    86,   192,   193,   340,   322,   126,
     229,   194,   195,   244,   245,   252,   253,    92,   224,    93,
      94,    95,    96,   258,   259,   225,   260,   261,   226,   131,
     227,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,    97,   230,
     232,   233,   275,   126,   242,   276,    98,   294,    99,   301,
     296,   131,   297,   299,   309,   100,   101,   102,   103,   308,
     320,   104,   324,   331,   341,    44,    64,   285,   238,    89,
      72,   235,   246,   249,   251,   248,   138,    83,   105,   106,
     107,   131,   250,   140,     1,    93,    94,    95,    96,     2,
     141,   142,     0,   143,   144,   145,   146,   147,   148,   149,
     150,   151,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    97,    15,    16,    17,    18,    19,
      20,     0,    98,   131,    70,   234,     0,     0,     0,     0,
       0,   100,   101,   102,   103,     0,     0,   104,     0,     0,
       0,     0,   131,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   105,   106,   107,   140,     1,    93,
      94,    95,    96,     2,   141,   142,     0,   143,   144,   145,
     146,   147,   148,   149,   150,   151,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    97,    15,
      16,    17,    18,    19,    20,     0,    98,     0,    70,     0,
       0,     0,     0,     0,     0,   100,   101,   102,   103,     0,
       0,   104,    92,     1,    93,    94,    95,    96,     2,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   105,   106,
     107,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    97,    15,    16,    17,    18,    19,    20,
       0,    98,     0,     0,     0,     0,     0,     0,     0,     0,
     100,   101,   102,   103,     0,     0,   104,    92,     1,    93,
      94,    95,    96,     2,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   105,   106,   107,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,     0,    97,    15,
      16,    17,    18,    19,    20,     0,    98,     0,     0,     0,
       0,     0,     0,     0,     0,   100,   101,   102,   103,     0,
       0,   104,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   105,   106,
     107,   140,     0,    93,    94,    95,    96,     0,   141,   142,
       0,   143,   144,   145,   146,   147,   148,   149,   150,   151,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    97,     0,     0,     0,     0,     0,     0,   286,
      98,     0,    70,     0,     0,     0,     0,     0,     0,   100,
     101,   102,   103,     0,     0,   104,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   105,   106,   107,   140,     0,    93,    94,    95,
      96,     0,   141,   142,     0,   143,   144,   145,   146,   147,
     148,   149,   150,   151,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    97,     0,     0,     0,
       0,     0,     0,     0,    98,     0,    70,     0,     0,     0,
       0,     0,     0,   100,   101,   102,   103,     0,     0,   104,
      45,     1,     0,     0,     0,     0,     2,    92,     0,    93,
      94,    95,    96,     0,     0,     0,   105,   106,   107,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
       0,     0,    15,    16,    17,    18,    19,    20,    97,   211,
     277,     0,     0,     0,   212,     0,    98,     0,    99,     0,
       0,     0,     0,     0,     0,   100,   101,   102,   103,     0,
      92,   104,    93,    94,    95,    96,     0,     0,     0,     0,
       0,     0,     0,    48,     0,     0,     0,     0,   105,   106,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      92,    97,    93,    94,    95,    96,     0,     0,     0,    98,
       0,     0,     0,     0,     0,   129,     0,     0,   100,   101,
     102,   103,     0,     0,   104,     0,     0,     0,     0,     0,
      92,    97,    93,    94,    95,    96,     0,     0,   222,    98,
       0,   105,   106,   107,     0,     0,     0,     0,   100,   101,
     102,   103,     0,     0,   104,     0,     0,     0,     0,     0,
      92,    97,    93,    94,    95,    96,     0,     0,     0,    98,
     271,   105,   106,   107,     0,     0,     0,     0,   100,   101,
     102,   103,     0,     0,   104,     0,     0,     0,     0,     0,
      92,    97,    93,    94,    95,    96,     0,     0,     0,    98,
       0,   105,   106,   107,     0,   280,     0,     0,   100,   101,
     102,   103,     0,     0,   104,     0,     0,     0,     0,     0,
      92,    97,    93,    94,    95,    96,     0,     0,     0,    98,
       0,   105,   106,   107,     0,   312,     0,     0,   100,   101,
     102,   103,     0,     0,   104,     0,     0,     0,     0,     0,
      92,    97,    93,    94,    95,    96,     0,     0,     0,    98,
     332,   105,   106,   107,     0,     0,     0,     0,   100,   101,
     102,   103,     0,     0,   104,     0,     0,     0,     0,     0,
      92,    97,    93,    94,    95,    96,     0,     0,     0,    98,
     339,   105,   106,   107,     0,     0,     0,     0,   100,   101,
     102,   103,     0,     0,   104,     0,     0,     0,     0,     0,
      92,    97,    93,    94,    95,    96,     0,     0,     0,    98,
       0,   105,   106,   107,     0,     0,     0,     0,   100,   101,
     102,   103,     0,     0,   104,     0,     0,     0,     0,     0,
      92,    97,    93,    94,    95,    96,     0,     0,     0,   164,
       0,   105,   106,   107,     0,     0,     0,     0,   100,   101,
     102,   103,     0,     0,   104,     0,     0,     0,     0,     0,
       0,    97,     0,     0,     0,     0,     0,     0,     0,   171,
       0,   105,   106,   107,     0,     0,     0,     0,   100,   101,
     102,   103,     0,     0,   104,     0,     1,     0,     0,     0,
       0,     2,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   105,   106,   107,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,    15,    16,    17,
      18,    19,    20,     0,   239,   277,     0,     0,     1,   212,
       0,     0,     0,     2,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,     0,    48,    15,
      16,    17,    18,    19,    20,     1,     0,     0,     0,    79,
       2,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,     0,    15,    16,    17,    18,
      19,    20,     1,     0,     0,     0,    82,     2,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,     0,     0,    15,    16,    17,    18,    19,    20,     1,
       0,     0,     0,   132,     2,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     0,     0,
      15,    16,    17,    18,    19,    20,     1,     0,     0,     0,
     135,     2,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,    15,    16,    17,
      18,    19,    20,     1,     0,   125,     0,     0,     2,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,    15,    16,    17,    18,    19,    20,
       1,     0,   310,     0,     0,     2,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
       0,    15,    16,    17,    18,    19,    20,     1,     0,     0,
       0,     0,     2,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,     0,     0,    15,    16,
      17,    18,    19,    20
};

static const yytype_int16 yycheck[] =
{
       0,    98,    48,    74,    71,    73,   149,    26,    53,    99,
       3,    46,    91,    84,    14,    15,    16,    17,    18,    19,
       3,     3,    22,     3,     3,     3,    68,    69,    47,     3,
       3,   214,    99,    56,    44,    42,    55,    41,    43,   126,
      47,    46,    46,    44,   141,    80,    45,    46,    41,    42,
     102,   103,   104,   105,   106,   107,    79,   240,     0,    42,
      42,    62,    42,    42,    47,    76,    44,   164,    47,    76,
      44,    44,    34,    73,   171,   146,    42,   156,   221,   166,
     126,    47,    41,    76,   181,    56,   229,    46,    59,    44,
      41,    91,    54,    76,    76,    46,    58,    44,    98,    62,
      63,    64,    65,    66,    67,    76,    41,   126,    42,   206,
      81,    46,    41,    47,    42,   134,    46,    46,    48,    47,
     166,    49,    50,    51,    52,     3,    42,   224,   225,   226,
     227,    47,   199,   200,   201,   202,   203,   204,   205,    43,
      62,   212,    46,    41,   196,   197,   198,   226,    46,    41,
      43,   294,    41,    74,    46,   245,   156,    46,    70,    71,
      72,    73,    62,    84,   164,   211,    76,    77,    78,   214,
     237,   314,   315,    45,    43,   318,    97,    46,   245,   100,
     101,   102,   103,   104,   105,   106,   107,    45,   331,   332,
     242,    55,   211,   239,   291,   338,   339,   188,   189,   190,
     191,   344,    43,    43,    43,    46,    46,    46,    58,    43,
      59,   211,    46,   284,    43,   283,    43,    46,   218,    46,
     317,    43,    57,   320,    46,   146,   226,    48,    43,    82,
     327,    46,   303,    45,    46,    60,    61,   334,   305,   239,
      82,    74,    75,    45,    46,   186,   187,     3,    42,     5,
       6,     7,     8,   192,   193,    42,   194,   195,    42,   180,
      42,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,    34,    41,
      41,     3,     3,   283,    43,     3,    42,    82,    44,    45,
      13,   212,    41,    43,    48,    51,    52,    53,    54,    43,
      42,    57,    48,    12,    41,    22,    37,   218,   164,    69,
      51,   156,   180,   183,   185,   182,    86,    60,    74,    75,
      76,   242,   184,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    -1,    42,   284,    44,    45,    -1,    -1,    -1,    -1,
      -1,    51,    52,    53,    54,    -1,    -1,    57,    -1,    -1,
      -1,    -1,   303,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    75,    76,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    -1,    42,    -1,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    52,    53,    54,    -1,
      -1,    57,     3,     4,     5,     6,     7,     8,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,
      76,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      -1,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      51,    52,    53,    54,    -1,    -1,    57,     3,     4,     5,
       6,     7,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    75,    76,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    37,    38,    39,    40,    -1,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    52,    53,    54,    -1,
      -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,
      76,     3,    -1,     5,     6,     7,     8,    -1,    10,    11,
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    51,
      52,    53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    75,    76,     3,    -1,     5,     6,     7,
       8,    -1,    10,    11,    -1,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    42,    -1,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    52,    53,    54,    -1,    -1,    57,
       3,     4,    -1,    -1,    -1,    -1,     9,     3,    -1,     5,
       6,     7,     8,    -1,    -1,    -1,    74,    75,    76,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    39,    40,    34,    42,
      43,    -1,    -1,    -1,    47,    -1,    42,    -1,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    52,    53,    54,    -1,
       3,    57,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    74,    75,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    34,     5,     6,     7,     8,    -1,    -1,    -1,    42,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    51,    52,
      53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
       3,    34,     5,     6,     7,     8,    -1,    -1,    41,    42,
      -1,    74,    75,    76,    -1,    -1,    -1,    -1,    51,    52,
      53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
       3,    34,     5,     6,     7,     8,    -1,    -1,    -1,    42,
      43,    74,    75,    76,    -1,    -1,    -1,    -1,    51,    52,
      53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
       3,    34,     5,     6,     7,     8,    -1,    -1,    -1,    42,
      -1,    74,    75,    76,    -1,    48,    -1,    -1,    51,    52,
      53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
       3,    34,     5,     6,     7,     8,    -1,    -1,    -1,    42,
      -1,    74,    75,    76,    -1,    48,    -1,    -1,    51,    52,
      53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
       3,    34,     5,     6,     7,     8,    -1,    -1,    -1,    42,
      43,    74,    75,    76,    -1,    -1,    -1,    -1,    51,    52,
      53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
       3,    34,     5,     6,     7,     8,    -1,    -1,    -1,    42,
      43,    74,    75,    76,    -1,    -1,    -1,    -1,    51,    52,
      53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
       3,    34,     5,     6,     7,     8,    -1,    -1,    -1,    42,
      -1,    74,    75,    76,    -1,    -1,    -1,    -1,    51,    52,
      53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
       3,    34,     5,     6,     7,     8,    -1,    -1,    -1,    42,
      -1,    74,    75,    76,    -1,    -1,    -1,    -1,    51,    52,
      53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,
      -1,    74,    75,    76,    -1,    -1,    -1,    -1,    51,    52,
      53,    54,    -1,    -1,    57,    -1,     4,    -1,    -1,    -1,
      -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    75,    76,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    -1,    35,    36,    37,
      38,    39,    40,    -1,    42,    43,    -1,    -1,     4,    47,
      -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    76,    35,
      36,    37,    38,    39,    40,     4,    -1,    -1,    -1,    45,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      39,    40,     4,    -1,    -1,    -1,    45,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    35,    36,    37,    38,    39,    40,     4,
      -1,    -1,    -1,    45,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    39,    40,     4,    -1,    -1,    -1,
      45,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    -1,    35,    36,    37,
      38,    39,    40,     4,    -1,    43,    -1,    -1,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,    39,    40,
       4,    -1,    43,    -1,    -1,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      -1,    35,    36,    37,    38,    39,    40,     4,    -1,    -1,
      -1,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,    39,    40
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     9,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    35,    36,    37,    38,    39,
      40,    84,    85,    86,    87,    88,    89,   130,   131,   132,
     133,     3,    44,     3,    44,     3,    44,    89,    89,    89,
      89,    89,    89,     0,    86,     3,    41,    42,    76,    90,
      91,    92,    93,    94,    44,    89,   136,   137,    44,   136,
      44,     3,   134,   135,    90,    92,    92,    94,    41,    46,
      44,    62,   101,    42,    47,    93,   136,    92,   138,    45,
     137,   136,    45,   134,    62,    45,    46,    41,    43,    91,
     102,   103,     3,     5,     6,     7,     8,    34,    42,    44,
      51,    52,    53,    54,    57,    74,    75,    76,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   128,    43,    89,    95,    96,    48,
     112,   124,    45,    41,    46,    45,    45,   112,   135,    45,
       3,    10,    11,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    88,    89,   100,   101,   104,   105,   106,   107,
     108,   109,   110,   111,    42,   124,    89,    97,   110,   128,
     129,    42,   124,   124,   123,   123,   123,   123,   123,   123,
      56,    79,    55,    58,    59,    57,    68,    69,    70,    71,
      72,    73,    60,    61,    74,    75,    76,    77,    78,    62,
      63,    64,    65,    66,    67,    42,    47,    49,    50,    51,
      52,    42,    47,    92,    94,    98,    99,    43,    46,    48,
      92,    82,    41,   110,    42,    42,    42,    42,   112,    82,
      41,   100,    41,     3,    45,   105,    41,    46,    97,    42,
      94,    98,    43,    43,    45,    46,   114,   110,   115,   116,
     117,   118,   119,   119,   120,   120,   120,   120,   121,   121,
     122,   122,   123,   123,   123,   111,   111,   111,   111,   111,
     111,    43,   111,   127,   110,     3,     3,    43,    95,    98,
      48,   112,    99,    42,    47,    96,    41,   100,    41,   110,
     110,    88,   110,   110,    82,   100,    13,    41,   111,    43,
     123,    45,   128,    80,    43,    46,    48,    43,    43,    48,
      43,    95,    48,   112,    43,    43,   110,    41,    43,   100,
      42,   112,   111,    43,    48,   100,   100,    41,   110,   100,
     110,    12,    43,   110,    41,    43,   100,   100,    43,    43,
     110,    41,   100,   100,    43,   100
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    83,    84,    85,    85,    86,    86,    87,    88,    88,
      88,    89,    89,    89,    89,    89,    89,    90,    90,    91,
      91,    92,    92,    93,    93,    93,    93,    93,    93,    94,
      94,    95,    95,    96,    96,    96,    97,    97,    98,    98,
      98,    99,    99,    99,    99,    99,    99,    99,    99,    99,
     100,   100,   100,   100,   100,   100,   102,   101,   103,   101,
     104,   104,   105,   105,   106,   106,   106,   106,   107,   107,
     107,   108,   108,   108,   108,   108,   108,   109,   109,   109,
     109,   109,   110,   110,   111,   111,   111,   111,   111,   111,
     111,   112,   112,   113,   113,   114,   114,   115,   115,   116,
     116,   117,   117,   118,   118,   118,   119,   119,   119,   119,
     119,   120,   120,   120,   121,   121,   121,   122,   122,   122,
     122,   123,   123,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   125,   125,   125,   125,   125,   125,
     125,   125,   126,   126,   126,   126,   126,   126,   127,   127,
     128,   128,   128,   129,   129,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   131,
     131,   131,   132,   132,   132,   133,   133,   133,   134,   134,
     135,   135,   136,   136,   137,   138,   138
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     3,     2,
       4,     1,     2,     2,     2,     2,     2,     1,     3,     1,
       3,     2,     1,     1,     3,     4,     3,     4,     3,     1,
       2,     1,     3,     2,     2,     1,     1,     2,     1,     1,
       2,     3,     2,     3,     3,     4,     2,     3,     3,     4,
       1,     1,     2,     1,     1,     1,     0,     3,     0,     4,
       1,     2,     1,     1,     3,     4,     3,     3,     5,     7,
       5,     5,     7,     8,     9,     7,     8,     3,     2,     2,
       2,     3,     1,     3,     1,     3,     3,     3,     3,     3,
       3,     1,     5,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     1,     4,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     4,     1,     4,     3,     4,     3,     3,
       2,     2,     1,     1,     1,     1,     1,     3,     1,     3,
       1,     3,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       4,     2,     5,     4,     2,     5,     4,     2,     1,     3,
       1,     3,     1,     2,     3,     1,     3
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
  case 2: /* program: translation_unit  */
#line 75 "parser.y"
                     {
        if (!main_function_defined) {
            yyerror("main function not defined");
        }
        root = (yyvsp[0].node);
    }
#line 1699 "parser.c"
    break;

  case 3: /* translation_unit: external_declaration  */
#line 84 "parser.y"
                         { (yyval.node) = create_program_node(); add_toplevel_statement_to_program((yyval.node), (yyvsp[0].node)); }
#line 1705 "parser.c"
    break;

  case 4: /* translation_unit: translation_unit external_declaration  */
#line 85 "parser.y"
                                            { add_toplevel_statement_to_program((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 1711 "parser.c"
    break;

  case 7: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 94 "parser.y"
                                                         {
        if (strcmp((yyvsp[-1].node)->var_decl.name, "main") == 0) {
            if (main_function_defined) {
                yyerror("main function already defined");
            }
            main_function_defined = 1;
            Type *func_type = (yyvsp[-1].node)->var_decl.var_type;
            while(func_type && func_type->base != TYPE_FUNCTION) func_type = func_type->ptr_to;
            if (func_type && func_type->members && func_type->members->param_list.count > 0) {
                yyerror("main function cannot have arguments");
            }
        }
        Type *func_type = (yyvsp[-1].node)->var_decl.var_type;
        while(func_type && func_type->base != TYPE_FUNCTION) func_type = func_type->ptr_to;
        if (!symtab_insert(symbol_table, (yyvsp[-1].node)->var_decl.name, SYMBOL_FUNCTION, DATA_TYPE_INT, (yyvsp[-2].type)->base, func_type ? func_type->members : NULL)) {
            yyerror("Symbol already defined in current scope");
        }
        (yyval.node) = create_function_definition_node((yyvsp[-2].type), (yyvsp[-1].node), NULL, (yyvsp[0].node));
    }
#line 1735 "parser.c"
    break;

  case 8: /* declaration: declaration_specifiers init_declarator_list T_SEMICOLON  */
#line 116 "parser.y"
                                                            {
        for (int i = 0; i < (yyvsp[-1].node)->statement_list.count; i++) {
            ASTNode *decl = (yyvsp[-1].node)->statement_list.statements[i];
            if (!symtab_insert(symbol_table, decl->var_decl.name, SYMBOL_VARIABLE, (yyvsp[-2].type)->base, DATA_TYPE_VOID, NULL)) {
                yyerror("Symbol already defined in current scope");
            }
        }
        (yyval.node) = create_decl_list_node((yyvsp[-2].type), (yyvsp[-1].node));
    }
#line 1749 "parser.c"
    break;

  case 9: /* declaration: declaration_specifiers T_SEMICOLON  */
#line 125 "parser.y"
                                         { (yyval.node) = create_type_decl_node((yyvsp[-1].type)); }
#line 1755 "parser.c"
    break;

  case 10: /* declaration: T_TYPEDEF declaration_specifiers init_declarator_list T_SEMICOLON  */
#line 126 "parser.y"
                                                                        {
        for (int i = 0; i < (yyvsp[-1].node)->statement_list.count; i++) {
            add_typedef_name(symbol_table, (yyvsp[-1].node)->statement_list.statements[i]->var_decl.name);
        }
        (yyval.node) = create_typedef_node(NULL, (yyvsp[-2].type));
    }
#line 1766 "parser.c"
    break;

  case 11: /* declaration_specifiers: type_specifier  */
#line 135 "parser.y"
                   { (yyval.type) = (yyvsp[0].type); }
#line 1772 "parser.c"
    break;

  case 12: /* declaration_specifiers: T_CONST declaration_specifiers  */
#line 136 "parser.y"
                                     { (yyval.type) = (yyvsp[0].type); (yyval.type)->is_const = 1; }
#line 1778 "parser.c"
    break;

  case 13: /* declaration_specifiers: T_STATIC declaration_specifiers  */
#line 137 "parser.y"
                                      { (yyval.type) = (yyvsp[0].type); (yyval.type)->is_static = 1; }
#line 1784 "parser.c"
    break;

  case 14: /* declaration_specifiers: T_EXTERN declaration_specifiers  */
#line 138 "parser.y"
                                      { (yyval.type) = (yyvsp[0].type); (yyval.type)->is_extern = 1; }
#line 1790 "parser.c"
    break;

  case 15: /* declaration_specifiers: T_VOLATILE declaration_specifiers  */
#line 139 "parser.y"
                                        { (yyval.type) = (yyvsp[0].type); (yyval.type)->is_volatile = 1; }
#line 1796 "parser.c"
    break;

  case 16: /* declaration_specifiers: T_INLINE declaration_specifiers  */
#line 140 "parser.y"
                                      { (yyval.type) = (yyvsp[0].type); (yyval.type)->is_inline = 1; }
#line 1802 "parser.c"
    break;

  case 17: /* init_declarator_list: init_declarator  */
#line 144 "parser.y"
                    { (yyval.node) = create_statement_list_node(); add_statement_to_list((yyval.node), (yyvsp[0].node)); }
#line 1808 "parser.c"
    break;

  case 18: /* init_declarator_list: init_declarator_list T_COMMA init_declarator  */
#line 145 "parser.y"
                                                   { add_statement_to_list((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1814 "parser.c"
    break;

  case 19: /* init_declarator: declarator  */
#line 149 "parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 1820 "parser.c"
    break;

  case 20: /* init_declarator: declarator T_ASSIGN initializer  */
#line 150 "parser.y"
                                      { (yyvsp[-2].node)->var_decl.init_expr = (yyvsp[0].node); (yyval.node) = (yyvsp[-2].node); }
#line 1826 "parser.c"
    break;

  case 21: /* declarator: pointer direct_declarator  */
#line 154 "parser.y"
                              { (yyval.node) = (yyvsp[0].node); Type *t = (yyvsp[-1].type); while(t->ptr_to) t = t->ptr_to; t->ptr_to = (yyvsp[0].node)->var_decl.var_type; (yyvsp[0].node)->var_decl.var_type = (yyvsp[-1].type); }
#line 1832 "parser.c"
    break;

  case 22: /* declarator: direct_declarator  */
#line 155 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1838 "parser.c"
    break;

  case 23: /* direct_declarator: T_IDENTIFIER  */
#line 159 "parser.y"
                 { (yyval.node) = create_var_decl_node((yyvsp[0].string_value), NULL, 0, 0, NULL); }
#line 1844 "parser.c"
    break;

  case 24: /* direct_declarator: T_LPAREN declarator T_RPAREN  */
#line 160 "parser.y"
                                   { (yyval.node) = (yyvsp[-1].node); }
#line 1850 "parser.c"
    break;

  case 25: /* direct_declarator: direct_declarator T_LBRACKET conditional_expression T_RBRACKET  */
#line 161 "parser.y"
                                                                     { (yyval.node) = (yyvsp[-3].node); (yyvsp[-3].node)->var_decl.var_type = create_array_type((yyvsp[-3].node)->var_decl.var_type, 0); }
#line 1856 "parser.c"
    break;

  case 26: /* direct_declarator: direct_declarator T_LBRACKET T_RBRACKET  */
#line 162 "parser.y"
                                              { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->var_decl.var_type = create_array_type((yyvsp[-2].node)->var_decl.var_type, 0); }
#line 1862 "parser.c"
    break;

  case 27: /* direct_declarator: direct_declarator T_LPAREN param_list T_RPAREN  */
#line 163 "parser.y"
                                                     {
        (yyval.node) = (yyvsp[-3].node);
        Type *t = (yyval.node)->var_decl.var_type;
        if (t) {
            while(t->ptr_to) t = t->ptr_to;
            t->ptr_to = create_function_type(NULL, (yyvsp[-1].node));
        } else {
            (yyval.node)->var_decl.var_type = create_function_type(NULL, (yyvsp[-1].node));
        }
    }
#line 1877 "parser.c"
    break;

  case 28: /* direct_declarator: direct_declarator T_LPAREN T_RPAREN  */
#line 173 "parser.y"
                                          {
        (yyval.node) = (yyvsp[-2].node);
        Type *t = (yyval.node)->var_decl.var_type;
        if (t) {
            while(t->ptr_to) t = t->ptr_to;
            t->ptr_to = create_function_type(NULL, NULL);
        } else {
            (yyval.node)->var_decl.var_type = create_function_type(NULL, NULL);
        }
    }
#line 1892 "parser.c"
    break;

  case 29: /* pointer: T_MUL  */
#line 186 "parser.y"
          { (yyval.type) = create_pointer_type(NULL); }
#line 1898 "parser.c"
    break;

  case 30: /* pointer: T_MUL pointer  */
#line 187 "parser.y"
                    { (yyval.type) = create_pointer_type((yyvsp[0].type)); }
#line 1904 "parser.c"
    break;

  case 31: /* param_list: parameter_declaration  */
#line 191 "parser.y"
                          { (yyval.node) = create_param_list_node(); add_param_to_list((yyval.node), (yyvsp[0].node)); }
#line 1910 "parser.c"
    break;

  case 32: /* param_list: param_list T_COMMA parameter_declaration  */
#line 192 "parser.y"
                                               { add_param_to_list((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1916 "parser.c"
    break;

  case 33: /* parameter_declaration: declaration_specifiers declarator  */
#line 196 "parser.y"
                                      {
        if (!symtab_insert(symbol_table, (yyvsp[0].node)->var_decl.name, SYMBOL_VARIABLE, (yyvsp[-1].type)->base, DATA_TYPE_VOID, NULL)) {
            yyerror("Symbol already defined in current scope");
        }
        (yyval.node) = (yyvsp[0].node);
        if ((yyval.node)->var_decl.var_type) {
            Type *t = (yyval.node)->var_decl.var_type;
            while(t->ptr_to) t = t->ptr_to;
            t->ptr_to = (yyvsp[-1].type);
        } else {
            (yyval.node)->var_decl.var_type = (yyvsp[-1].type);
        }
    }
#line 1934 "parser.c"
    break;

  case 34: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 209 "parser.y"
                                                 { (yyval.node) = create_var_decl_node(NULL, (yyvsp[-1].type), 0, 0, NULL); }
#line 1940 "parser.c"
    break;

  case 35: /* parameter_declaration: declaration_specifiers  */
#line 210 "parser.y"
                             { (yyval.node) = create_var_decl_node(NULL, (yyvsp[0].type), 0, 0, NULL); }
#line 1946 "parser.c"
    break;

  case 36: /* type_name: declaration_specifiers  */
#line 214 "parser.y"
                           { (yyval.type) = (yyvsp[0].type); }
#line 1952 "parser.c"
    break;

  case 37: /* type_name: declaration_specifiers abstract_declarator  */
#line 215 "parser.y"
                                                 { (yyval.type) = (yyvsp[-1].type); }
#line 1958 "parser.c"
    break;

  case 38: /* abstract_declarator: pointer  */
#line 219 "parser.y"
            { (yyval.type) = (yyvsp[0].type); }
#line 1964 "parser.c"
    break;

  case 39: /* abstract_declarator: direct_abstract_declarator  */
#line 220 "parser.y"
                                 { (yyval.type) = (yyvsp[0].type); }
#line 1970 "parser.c"
    break;

  case 40: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 221 "parser.y"
                                         { (yyval.type) = (yyvsp[-1].type); }
#line 1976 "parser.c"
    break;

  case 41: /* direct_abstract_declarator: T_LPAREN abstract_declarator T_RPAREN  */
#line 225 "parser.y"
                                          { (yyval.type) = (yyvsp[-1].type); }
#line 1982 "parser.c"
    break;

  case 42: /* direct_abstract_declarator: T_LBRACKET T_RBRACKET  */
#line 226 "parser.y"
                            { (yyval.type) = create_array_type(NULL, 0); }
#line 1988 "parser.c"
    break;

  case 43: /* direct_abstract_declarator: T_LBRACKET conditional_expression T_RBRACKET  */
#line 227 "parser.y"
                                                   { (yyval.type) = create_array_type(NULL, 0); }
#line 1994 "parser.c"
    break;

  case 44: /* direct_abstract_declarator: direct_abstract_declarator T_LBRACKET T_RBRACKET  */
#line 228 "parser.y"
                                                       { (yyval.type) = (yyvsp[-2].type); }
#line 2000 "parser.c"
    break;

  case 45: /* direct_abstract_declarator: direct_abstract_declarator T_LBRACKET conditional_expression T_RBRACKET  */
#line 229 "parser.y"
                                                                              { (yyval.type) = (yyvsp[-3].type); }
#line 2006 "parser.c"
    break;

  case 46: /* direct_abstract_declarator: T_LPAREN T_RPAREN  */
#line 230 "parser.y"
                        { (yyval.type) = create_function_type(NULL, NULL); }
#line 2012 "parser.c"
    break;

  case 47: /* direct_abstract_declarator: T_LPAREN param_list T_RPAREN  */
#line 231 "parser.y"
                                   { (yyval.type) = create_function_type(NULL, (yyvsp[-1].node)); }
#line 2018 "parser.c"
    break;

  case 48: /* direct_abstract_declarator: direct_abstract_declarator T_LPAREN T_RPAREN  */
#line 232 "parser.y"
                                                   { (yyval.type) = (yyvsp[-2].type); }
#line 2024 "parser.c"
    break;

  case 49: /* direct_abstract_declarator: direct_abstract_declarator T_LPAREN param_list T_RPAREN  */
#line 233 "parser.y"
                                                              { (yyval.type) = (yyvsp[-3].type); }
#line 2030 "parser.c"
    break;

  case 56: /* $@1: %empty  */
#line 246 "parser.y"
             { symtab_enter_scope(symbol_table); }
#line 2036 "parser.c"
    break;

  case 57: /* compound_statement: T_LBRACE $@1 T_RBRACE  */
#line 246 "parser.y"
                                                            { (yyval.node) = create_statement_list_node(); symtab_exit_scope(symbol_table); }
#line 2042 "parser.c"
    break;

  case 58: /* $@2: %empty  */
#line 247 "parser.y"
               { symtab_enter_scope(symbol_table); }
#line 2048 "parser.c"
    break;

  case 59: /* compound_statement: T_LBRACE $@2 block_item_list T_RBRACE  */
#line 247 "parser.y"
                                                                              { (yyval.node) = (yyvsp[-1].node); symtab_exit_scope(symbol_table); }
#line 2054 "parser.c"
    break;

  case 60: /* block_item_list: block_item  */
#line 251 "parser.y"
               { (yyval.node) = create_statement_list_node(); add_statement_to_list((yyval.node), (yyvsp[0].node)); }
#line 2060 "parser.c"
    break;

  case 61: /* block_item_list: block_item_list block_item  */
#line 252 "parser.y"
                                 { add_statement_to_list((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2066 "parser.c"
    break;

  case 64: /* labeled_statement: T_IDENTIFIER ':' statement  */
#line 261 "parser.y"
                               { (yyval.node) = create_label_node((yyvsp[-2].string_value), (yyvsp[0].node)); }
#line 2072 "parser.c"
    break;

  case 65: /* labeled_statement: T_CASE conditional_expression ':' statement  */
#line 262 "parser.y"
                                                  { (yyval.node) = create_case_node((yyvsp[-2].node)); add_statement_to_list((yyval.node), (yyvsp[0].node)); }
#line 2078 "parser.c"
    break;

  case 66: /* labeled_statement: T_DEFAULT ':' statement  */
#line 263 "parser.y"
                              { (yyval.node) = create_case_node(NULL); add_statement_to_list((yyval.node), (yyvsp[0].node)); }
#line 2084 "parser.c"
    break;

  case 67: /* labeled_statement: T_IDENTIFIER ':' T_SEMICOLON  */
#line 264 "parser.y"
                                   { (yyval.node) = create_label_node((yyvsp[-2].string_value), NULL); }
#line 2090 "parser.c"
    break;

  case 68: /* selection_statement: T_IF T_LPAREN expression T_RPAREN statement  */
#line 268 "parser.y"
                                                            {
        if (get_expression_type((yyvsp[-2].node)) != DATA_TYPE_INT) {
            yyerror("if condition must be an integer type");
        }
        (yyval.node) = create_if_node((yyvsp[-2].node), (yyvsp[0].node), NULL);
    }
#line 2101 "parser.c"
    break;

  case 69: /* selection_statement: T_IF T_LPAREN expression T_RPAREN statement T_ELSE statement  */
#line 274 "parser.y"
                                                                   {
        if (get_expression_type((yyvsp[-4].node)) != DATA_TYPE_INT) {
            yyerror("if condition must be an integer type");
        }
        (yyval.node) = create_if_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2112 "parser.c"
    break;

  case 70: /* selection_statement: T_SWITCH T_LPAREN expression T_RPAREN statement  */
#line 280 "parser.y"
                                                      { (yyval.node) = create_switch_node((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2118 "parser.c"
    break;

  case 71: /* iteration_statement: T_WHILE T_LPAREN expression T_RPAREN statement  */
#line 284 "parser.y"
                                                   {
        if (get_expression_type((yyvsp[-2].node)) != DATA_TYPE_INT) {
            yyerror("while condition must be an integer type");
        }
        (yyval.node) = create_while_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2129 "parser.c"
    break;

  case 72: /* iteration_statement: T_DO statement T_WHILE T_LPAREN expression T_RPAREN T_SEMICOLON  */
#line 290 "parser.y"
                                                                      { (yyval.node) = create_do_while_node((yyvsp[-5].node), (yyvsp[-2].node)); }
#line 2135 "parser.c"
    break;

  case 73: /* iteration_statement: T_FOR T_LPAREN expression T_SEMICOLON expression T_SEMICOLON T_RPAREN statement  */
#line 291 "parser.y"
                                                                                      { (yyval.node) = create_for_node((yyvsp[-5].node), (yyvsp[-3].node), NULL, (yyvsp[0].node)); }
#line 2141 "parser.c"
    break;

  case 74: /* iteration_statement: T_FOR T_LPAREN expression T_SEMICOLON expression T_SEMICOLON expression T_RPAREN statement  */
#line 292 "parser.y"
                                                                                                 { (yyval.node) = create_for_node((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2147 "parser.c"
    break;

  case 75: /* iteration_statement: T_FOR T_LPAREN declaration expression T_SEMICOLON T_RPAREN statement  */
#line 293 "parser.y"
                                                                           { (yyval.node) = create_for_node((yyvsp[-4].node), (yyvsp[-3].node), NULL, (yyvsp[0].node)); }
#line 2153 "parser.c"
    break;

  case 76: /* iteration_statement: T_FOR T_LPAREN declaration expression T_SEMICOLON expression T_RPAREN statement  */
#line 294 "parser.y"
                                                                                      { (yyval.node) = create_for_node((yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2159 "parser.c"
    break;

  case 77: /* jump_statement: T_GOTO T_IDENTIFIER T_SEMICOLON  */
#line 298 "parser.y"
                                    { (yyval.node) = create_goto_node((yyvsp[-1].string_value)); }
#line 2165 "parser.c"
    break;

  case 78: /* jump_statement: T_CONTINUE T_SEMICOLON  */
#line 299 "parser.y"
                             { (yyval.node) = create_continue_node(); }
#line 2171 "parser.c"
    break;

  case 79: /* jump_statement: T_BREAK T_SEMICOLON  */
#line 300 "parser.y"
                          { (yyval.node) = create_break_node(); }
#line 2177 "parser.c"
    break;

  case 80: /* jump_statement: T_RETURN T_SEMICOLON  */
#line 301 "parser.y"
                           {
        Symbol *func = get_current_function();
        if (func && func->return_type != DATA_TYPE_VOID) {
            yyerror("Non-void function must return a value");
        }
        (yyval.node) = create_return_node(NULL);
    }
#line 2189 "parser.c"
    break;

  case 81: /* jump_statement: T_RETURN expression T_SEMICOLON  */
#line 308 "parser.y"
                                      {
        Symbol *func = get_current_function();
        if (func) {
            DataType expr_type = get_expression_type((yyvsp[-1].node));
            if (expr_type != func->return_type) {
                yyerror("Incompatible return type");
            }
        }
        (yyval.node) = create_return_node((yyvsp[-1].node));
    }
#line 2204 "parser.c"
    break;

  case 82: /* expression: assignment_expression  */
#line 321 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2210 "parser.c"
    break;

  case 83: /* expression: expression T_COMMA assignment_expression  */
#line 322 "parser.y"
                                               { (yyval.node) = create_binary_op_node(T_COMMA, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2216 "parser.c"
    break;

  case 84: /* assignment_expression: conditional_expression  */
#line 326 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2222 "parser.c"
    break;

  case 85: /* assignment_expression: unary_expression T_ASSIGN assignment_expression  */
#line 327 "parser.y"
                                                      {
        DataType left_type = get_expression_type((yyvsp[-2].node));
        DataType right_type = get_expression_type((yyvsp[0].node));
        if (left_type != right_type) {
            yyerror("Incompatible types in assignment");
        }
        (yyval.node) = create_assign_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2235 "parser.c"
    break;

  case 86: /* assignment_expression: unary_expression T_ADD_ASSIGN assignment_expression  */
#line 335 "parser.y"
                                                          { (yyval.node) = create_assign_node((yyvsp[-2].node), create_binary_op_node(T_ADD, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 2241 "parser.c"
    break;

  case 87: /* assignment_expression: unary_expression T_SUB_ASSIGN assignment_expression  */
#line 336 "parser.y"
                                                          { (yyval.node) = create_assign_node((yyvsp[-2].node), create_binary_op_node(T_SUB, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 2247 "parser.c"
    break;

  case 88: /* assignment_expression: unary_expression T_MUL_ASSIGN assignment_expression  */
#line 337 "parser.y"
                                                          { (yyval.node) = create_assign_node((yyvsp[-2].node), create_binary_op_node(T_MUL, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 2253 "parser.c"
    break;

  case 89: /* assignment_expression: unary_expression T_DIV_ASSIGN assignment_expression  */
#line 338 "parser.y"
                                                          { (yyval.node) = create_assign_node((yyvsp[-2].node), create_binary_op_node(T_DIV, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 2259 "parser.c"
    break;

  case 90: /* assignment_expression: unary_expression T_MOD_ASSIGN assignment_expression  */
#line 339 "parser.y"
                                                          { (yyval.node) = create_assign_node((yyvsp[-2].node), create_binary_op_node(T_MOD, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 2265 "parser.c"
    break;

  case 91: /* conditional_expression: logical_or_expression  */
#line 343 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2271 "parser.c"
    break;

  case 92: /* conditional_expression: logical_or_expression T_QUESTION expression T_COLON conditional_expression  */
#line 344 "parser.y"
                                                                                 { (yyval.node) = create_ternary_op_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2277 "parser.c"
    break;

  case 93: /* logical_or_expression: logical_and_expression  */
#line 348 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2283 "parser.c"
    break;

  case 94: /* logical_or_expression: logical_or_expression T_LOGICAL_OR logical_and_expression  */
#line 349 "parser.y"
                                                                {
        if (get_expression_type((yyvsp[-2].node)) != DATA_TYPE_BOOL || get_expression_type((yyvsp[0].node)) != DATA_TYPE_BOOL) {
            yyerror("Logical operators require boolean operands");
        }
        (yyval.node) = create_binary_op_node(T_LOGICAL_OR, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2294 "parser.c"
    break;

  case 95: /* logical_and_expression: inclusive_or_expression  */
#line 358 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2300 "parser.c"
    break;

  case 96: /* logical_and_expression: logical_and_expression T_LOGICAL_AND inclusive_or_expression  */
#line 359 "parser.y"
                                                                   {
        if (get_expression_type((yyvsp[-2].node)) != DATA_TYPE_BOOL || get_expression_type((yyvsp[0].node)) != DATA_TYPE_BOOL) {
            yyerror("Logical operators require boolean operands");
        }
        (yyval.node) = create_binary_op_node(T_LOGICAL_AND, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2311 "parser.c"
    break;

  case 97: /* inclusive_or_expression: exclusive_or_expression  */
#line 368 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2317 "parser.c"
    break;

  case 98: /* inclusive_or_expression: inclusive_or_expression T_BITWISE_OR exclusive_or_expression  */
#line 369 "parser.y"
                                                                   { (yyval.node) = create_binary_op_node(T_BITWISE_OR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2323 "parser.c"
    break;

  case 99: /* exclusive_or_expression: and_expression  */
#line 373 "parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2329 "parser.c"
    break;

  case 100: /* exclusive_or_expression: exclusive_or_expression T_BITWISE_XOR and_expression  */
#line 374 "parser.y"
                                                           { (yyval.node) = create_binary_op_node(T_BITWISE_XOR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2335 "parser.c"
    break;

  case 101: /* and_expression: equality_expression  */
#line 378 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2341 "parser.c"
    break;

  case 102: /* and_expression: and_expression T_BITWISE_AND equality_expression  */
#line 379 "parser.y"
                                                       { (yyval.node) = create_binary_op_node(T_BITWISE_AND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2347 "parser.c"
    break;

  case 103: /* equality_expression: relational_expression  */
#line 383 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2353 "parser.c"
    break;

  case 104: /* equality_expression: equality_expression T_EQ relational_expression  */
#line 384 "parser.y"
                                                     {
        DataType left_type = get_expression_type((yyvsp[-2].node));
        DataType right_type = get_expression_type((yyvsp[0].node));
        if (left_type != right_type) {
            yyerror("Equality operators require operands of the same type");
        }
        (yyval.node) = create_binary_op_node(T_EQ, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2366 "parser.c"
    break;

  case 105: /* equality_expression: equality_expression T_NE relational_expression  */
#line 392 "parser.y"
                                                     {
        DataType left_type = get_expression_type((yyvsp[-2].node));
        DataType right_type = get_expression_type((yyvsp[0].node));
        if (left_type != right_type) {
            yyerror("Equality operators require operands of the same type");
        }
        (yyval.node) = create_binary_op_node(T_NE, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2379 "parser.c"
    break;

  case 106: /* relational_expression: shift_expression  */
#line 403 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2385 "parser.c"
    break;

  case 107: /* relational_expression: relational_expression T_LT shift_expression  */
#line 404 "parser.y"
                                                  {
        DataType left_type = get_expression_type((yyvsp[-2].node));
        DataType right_type = get_expression_type((yyvsp[0].node));
        if ((left_type != DATA_TYPE_INT && left_type != DATA_TYPE_FLOAT) || (right_type != DATA_TYPE_INT && right_type != DATA_TYPE_FLOAT)) {
            yyerror("Relational operators require integer or float operands");
        }
        (yyval.node) = create_binary_op_node(T_LT, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2398 "parser.c"
    break;

  case 108: /* relational_expression: relational_expression T_GT shift_expression  */
#line 412 "parser.y"
                                                  {
        DataType left_type = get_expression_type((yyvsp[-2].node));
        DataType right_type = get_expression_type((yyvsp[0].node));
        if ((left_type != DATA_TYPE_INT && left_type != DATA_TYPE_FLOAT) || (right_type != DATA_TYPE_INT && right_type != DATA_TYPE_FLOAT)) {
            yyerror("Relational operators require integer or float operands");
        }
        (yyval.node) = create_binary_op_node(T_GT, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2411 "parser.c"
    break;

  case 109: /* relational_expression: relational_expression T_LE shift_expression  */
#line 420 "parser.y"
                                                  {
        DataType left_type = get_expression_type((yyvsp[-2].node));
        DataType right_type = get_expression_type((yyvsp[0].node));
        if ((left_type != DATA_TYPE_INT && left_type != DATA_TYPE_FLOAT) || (right_type != DATA_TYPE_INT && right_type != DATA_TYPE_FLOAT)) {
            yyerror("Relational operators require integer or float operands");
        }
        (yyval.node) = create_binary_op_node(T_LE, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2424 "parser.c"
    break;

  case 110: /* relational_expression: relational_expression T_GE shift_expression  */
#line 428 "parser.y"
                                                  {
        DataType left_type = get_expression_type((yyvsp[-2].node));
        DataType right_type = get_expression_type((yyvsp[0].node));
        if ((left_type != DATA_TYPE_INT && left_type != DATA_TYPE_FLOAT) || (right_type != DATA_TYPE_INT && right_type != DATA_TYPE_FLOAT)) {
            yyerror("Relational operators require integer or float operands");
        }
        (yyval.node) = create_binary_op_node(T_GE, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2437 "parser.c"
    break;

  case 111: /* shift_expression: additive_expression  */
#line 439 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2443 "parser.c"
    break;

  case 112: /* shift_expression: shift_expression T_LSHIFT additive_expression  */
#line 440 "parser.y"
                                                    { (yyval.node) = create_binary_op_node(T_LSHIFT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2449 "parser.c"
    break;

  case 113: /* shift_expression: shift_expression T_RSHIFT additive_expression  */
#line 441 "parser.y"
                                                    { (yyval.node) = create_binary_op_node(T_RSHIFT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2455 "parser.c"
    break;

  case 114: /* additive_expression: multiplicative_expression  */
#line 445 "parser.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 2461 "parser.c"
    break;

  case 115: /* additive_expression: additive_expression T_ADD multiplicative_expression  */
#line 446 "parser.y"
                                                          { (yyval.node) = create_binary_op_node(T_ADD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2467 "parser.c"
    break;

  case 116: /* additive_expression: additive_expression T_SUB multiplicative_expression  */
#line 447 "parser.y"
                                                          { (yyval.node) = create_binary_op_node(T_SUB, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2473 "parser.c"
    break;

  case 117: /* multiplicative_expression: cast_expression  */
#line 451 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2479 "parser.c"
    break;

  case 118: /* multiplicative_expression: multiplicative_expression T_MUL cast_expression  */
#line 452 "parser.y"
                                                      { (yyval.node) = create_binary_op_node(T_MUL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2485 "parser.c"
    break;

  case 119: /* multiplicative_expression: multiplicative_expression T_DIV cast_expression  */
#line 453 "parser.y"
                                                      { (yyval.node) = create_binary_op_node(T_DIV, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2491 "parser.c"
    break;

  case 120: /* multiplicative_expression: multiplicative_expression T_MOD cast_expression  */
#line 454 "parser.y"
                                                      { (yyval.node) = create_binary_op_node(T_MOD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2497 "parser.c"
    break;

  case 121: /* cast_expression: unary_expression  */
#line 458 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2503 "parser.c"
    break;

  case 122: /* cast_expression: T_LPAREN type_name T_RPAREN cast_expression  */
#line 459 "parser.y"
                                                  { (yyval.node) = create_cast_node((yyvsp[-2].type), (yyvsp[0].node)); }
#line 2509 "parser.c"
    break;

  case 123: /* unary_expression: postfix_expression  */
#line 463 "parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2515 "parser.c"
    break;

  case 124: /* unary_expression: T_INC unary_expression  */
#line 464 "parser.y"
                             { (yyval.node) = create_unary_op_node(T_INC, (yyvsp[0].node)); }
#line 2521 "parser.c"
    break;

  case 125: /* unary_expression: T_DEC unary_expression  */
#line 465 "parser.y"
                             { (yyval.node) = create_unary_op_node(T_DEC, (yyvsp[0].node)); }
#line 2527 "parser.c"
    break;

  case 126: /* unary_expression: T_BITWISE_AND cast_expression  */
#line 466 "parser.y"
                                    { (yyval.node) = create_unary_op_node(T_BITWISE_AND, (yyvsp[0].node)); }
#line 2533 "parser.c"
    break;

  case 127: /* unary_expression: T_MUL cast_expression  */
#line 467 "parser.y"
                            {
        if (get_expression_type((yyvsp[0].node)) != DATA_TYPE_POINTER) {
            yyerror("Dereference operator can only be applied to pointers");
        }
        (yyval.node) = create_unary_op_node(T_MUL, (yyvsp[0].node));
    }
#line 2544 "parser.c"
    break;

  case 128: /* unary_expression: T_ADD cast_expression  */
#line 473 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2550 "parser.c"
    break;

  case 129: /* unary_expression: T_SUB cast_expression  */
#line 474 "parser.y"
                            { (yyval.node) = create_unary_op_node(T_SUB, (yyvsp[0].node)); }
#line 2556 "parser.c"
    break;

  case 130: /* unary_expression: T_BITWISE_NOT cast_expression  */
#line 475 "parser.y"
                                    { (yyval.node) = create_unary_op_node(T_BITWISE_NOT, (yyvsp[0].node)); }
#line 2562 "parser.c"
    break;

  case 131: /* unary_expression: T_LOGICAL_NOT cast_expression  */
#line 476 "parser.y"
                                    {
        if (get_expression_type((yyvsp[0].node)) != DATA_TYPE_BOOL) {
            yyerror("Logical NOT operator can only be applied to booleans");
        }
        (yyval.node) = create_unary_op_node(T_LOGICAL_NOT, (yyvsp[0].node));
    }
#line 2573 "parser.c"
    break;

  case 132: /* unary_expression: T_SIZEOF unary_expression  */
#line 482 "parser.y"
                                { (yyval.node) = create_sizeof_node(NULL); }
#line 2579 "parser.c"
    break;

  case 133: /* unary_expression: T_SIZEOF T_LPAREN type_name T_RPAREN  */
#line 483 "parser.y"
                                           { (yyval.node) = create_sizeof_node((yyvsp[-1].type)); }
#line 2585 "parser.c"
    break;

  case 134: /* postfix_expression: primary_expression  */
#line 487 "parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2591 "parser.c"
    break;

  case 135: /* postfix_expression: postfix_expression T_LBRACKET expression T_RBRACKET  */
#line 488 "parser.y"
                                                          {
        DataType array_type = get_expression_type((yyvsp[-3].node));
        if (array_type != DATA_TYPE_ARRAY) {
            yyerror("[] operator can only be used with arrays");
        }
        DataType index_type = get_expression_type((yyvsp[-1].node));
        if (index_type != DATA_TYPE_INT) {
            yyerror("Array index must be an integer");
        }
        (yyval.node) = create_array_access_node((yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 2607 "parser.c"
    break;

  case 136: /* postfix_expression: postfix_expression T_LPAREN T_RPAREN  */
#line 499 "parser.y"
                                           {
        check_function_call((yyvsp[-2].node)->variable.name, NULL);
        (yyval.node) = create_func_call_node((yyvsp[-2].node)->variable.name, NULL);
    }
#line 2616 "parser.c"
    break;

  case 137: /* postfix_expression: postfix_expression T_LPAREN argument_expression_list T_RPAREN  */
#line 503 "parser.y"
                                                                    {
        check_function_call((yyvsp[-3].node)->variable.name, (yyvsp[-1].node));
        (yyval.node) = create_func_call_node((yyvsp[-3].node)->variable.name, (yyvsp[-1].node));
    }
#line 2625 "parser.c"
    break;

  case 138: /* postfix_expression: postfix_expression T_DOT T_IDENTIFIER  */
#line 507 "parser.y"
                                            { (yyval.node) = create_member_access_node((yyvsp[-2].node), (yyvsp[0].string_value)); }
#line 2631 "parser.c"
    break;

  case 139: /* postfix_expression: postfix_expression T_ARROW T_IDENTIFIER  */
#line 508 "parser.y"
                                              { (yyval.node) = create_member_access_node((yyvsp[-2].node), (yyvsp[0].string_value)); }
#line 2637 "parser.c"
    break;

  case 140: /* postfix_expression: postfix_expression T_INC  */
#line 509 "parser.y"
                               { (yyval.node) = create_unary_op_node(T_INC, (yyvsp[-1].node)); }
#line 2643 "parser.c"
    break;

  case 141: /* postfix_expression: postfix_expression T_DEC  */
#line 510 "parser.y"
                               { (yyval.node) = create_unary_op_node(T_DEC, (yyvsp[-1].node)); }
#line 2649 "parser.c"
    break;

  case 142: /* primary_expression: T_IDENTIFIER  */
#line 514 "parser.y"
                 {
        if (symtab_lookup(symbol_table, (yyvsp[0].string_value)) == NULL) {
            yyerror("Symbol not defined");
        }
        (yyval.node) = create_variable_node((yyvsp[0].string_value));
    }
#line 2660 "parser.c"
    break;

  case 143: /* primary_expression: T_INTEGER  */
#line 520 "parser.y"
                { (yyval.node) = create_integer_node((yyvsp[0].integer_value)); }
#line 2666 "parser.c"
    break;

  case 144: /* primary_expression: T_FLOAT_LITERAL  */
#line 521 "parser.y"
                      { (yyval.node) = create_float_node((yyvsp[0].string_value)); }
#line 2672 "parser.c"
    break;

  case 145: /* primary_expression: T_CHAR_LITERAL  */
#line 522 "parser.y"
                     { (yyval.node) = create_char_node((yyvsp[0].string_value)); }
#line 2678 "parser.c"
    break;

  case 146: /* primary_expression: T_STRING_LITERAL  */
#line 523 "parser.y"
                       { (yyval.node) = create_string_literal_node((yyvsp[0].string_value)); }
#line 2684 "parser.c"
    break;

  case 147: /* primary_expression: T_LPAREN expression T_RPAREN  */
#line 524 "parser.y"
                                   { (yyval.node) = (yyvsp[-1].node); }
#line 2690 "parser.c"
    break;

  case 148: /* argument_expression_list: assignment_expression  */
#line 528 "parser.y"
                          { (yyval.node) = create_arg_list_node(); add_arg_to_list((yyval.node), (yyvsp[0].node)); }
#line 2696 "parser.c"
    break;

  case 149: /* argument_expression_list: argument_expression_list T_COMMA assignment_expression  */
#line 529 "parser.y"
                                                             { add_arg_to_list((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2702 "parser.c"
    break;

  case 150: /* initializer: assignment_expression  */
#line 533 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2708 "parser.c"
    break;

  case 151: /* initializer: T_LBRACE initializer_list T_RBRACE  */
#line 534 "parser.y"
                                         { (yyval.node) = (yyvsp[-1].node); }
#line 2714 "parser.c"
    break;

  case 152: /* initializer: T_LBRACE initializer_list T_COMMA T_RBRACE  */
#line 535 "parser.y"
                                                 { (yyval.node) = (yyvsp[-2].node); }
#line 2720 "parser.c"
    break;

  case 153: /* initializer_list: initializer  */
#line 539 "parser.y"
                { (yyval.node) = create_initializer_list_node(); add_initializer_to_list((yyval.node), (yyvsp[0].node)); }
#line 2726 "parser.c"
    break;

  case 154: /* initializer_list: initializer_list T_COMMA initializer  */
#line 540 "parser.y"
                                           { add_initializer_to_list((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2732 "parser.c"
    break;

  case 155: /* type_specifier: T_BOOL  */
#line 544 "parser.y"
           { (yyval.type) = create_type(TYPE_BOOL); }
#line 2738 "parser.c"
    break;

  case 156: /* type_specifier: T_VOID  */
#line 545 "parser.y"
             { (yyval.type) = create_type(TYPE_VOID); }
#line 2744 "parser.c"
    break;

  case 157: /* type_specifier: T_CHAR  */
#line 546 "parser.y"
             { (yyval.type) = create_type(TYPE_CHAR); }
#line 2750 "parser.c"
    break;

  case 158: /* type_specifier: T_SHORT  */
#line 547 "parser.y"
              { (yyval.type) = create_type(TYPE_SHORT); }
#line 2756 "parser.c"
    break;

  case 159: /* type_specifier: T_INT  */
#line 548 "parser.y"
            { (yyval.type) = create_type(TYPE_INT); }
#line 2762 "parser.c"
    break;

  case 160: /* type_specifier: T_LONG  */
#line 549 "parser.y"
             { (yyval.type) = create_type(TYPE_LONG); }
#line 2768 "parser.c"
    break;

  case 161: /* type_specifier: T_FLOAT  */
#line 550 "parser.y"
              { (yyval.type) = create_type(TYPE_FLOAT); }
#line 2774 "parser.c"
    break;

  case 162: /* type_specifier: T_DOUBLE  */
#line 551 "parser.y"
               { (yyval.type) = create_type(TYPE_DOUBLE); }
#line 2780 "parser.c"
    break;

  case 163: /* type_specifier: T_SIGNED  */
#line 552 "parser.y"
               { (yyval.type) = create_type(TYPE_INT); (yyval.type)->is_signed = 1; }
#line 2786 "parser.c"
    break;

  case 164: /* type_specifier: T_UNSIGNED  */
#line 553 "parser.y"
                 { (yyval.type) = create_type(TYPE_INT); (yyval.type)->is_unsigned = 1; }
#line 2792 "parser.c"
    break;

  case 165: /* type_specifier: struct_specifier  */
#line 554 "parser.y"
                       { (yyval.type) = create_type_from_specifier((yyvsp[0].node)); }
#line 2798 "parser.c"
    break;

  case 166: /* type_specifier: union_specifier  */
#line 555 "parser.y"
                      { (yyval.type) = create_type_from_union_specifier((yyvsp[0].node)); }
#line 2804 "parser.c"
    break;

  case 167: /* type_specifier: enum_specifier  */
#line 556 "parser.y"
                     { (yyval.type) = create_type_from_enum_specifier((yyvsp[0].node)); }
#line 2810 "parser.c"
    break;

  case 168: /* type_specifier: T_TYPENAME  */
#line 557 "parser.y"
                 { (yyval.type) = create_type(TYPE_TYPEDEF); (yyval.type)->name = (yyvsp[0].string_value); }
#line 2816 "parser.c"
    break;

  case 169: /* struct_specifier: T_STRUCT T_IDENTIFIER T_LBRACE struct_declaration_list T_RBRACE  */
#line 561 "parser.y"
                                                                    { (yyval.node) = create_struct_def_node((yyvsp[-3].string_value), (yyvsp[-1].node)); }
#line 2822 "parser.c"
    break;

  case 170: /* struct_specifier: T_STRUCT T_LBRACE struct_declaration_list T_RBRACE  */
#line 562 "parser.y"
                                                         { (yyval.node) = create_struct_def_node(NULL, (yyvsp[-1].node)); }
#line 2828 "parser.c"
    break;

  case 171: /* struct_specifier: T_STRUCT T_IDENTIFIER  */
#line 563 "parser.y"
                            { (yyval.node) = create_struct_ref_node((yyvsp[0].string_value)); }
#line 2834 "parser.c"
    break;

  case 172: /* union_specifier: T_UNION T_IDENTIFIER T_LBRACE struct_declaration_list T_RBRACE  */
#line 567 "parser.y"
                                                                   { (yyval.node) = create_union_def_node((yyvsp[-3].string_value), (yyvsp[-1].node)); }
#line 2840 "parser.c"
    break;

  case 173: /* union_specifier: T_UNION T_LBRACE struct_declaration_list T_RBRACE  */
#line 568 "parser.y"
                                                        { (yyval.node) = create_union_def_node(NULL, (yyvsp[-1].node)); }
#line 2846 "parser.c"
    break;

  case 174: /* union_specifier: T_UNION T_IDENTIFIER  */
#line 569 "parser.y"
                           { (yyval.node) = create_union_ref_node((yyvsp[0].string_value)); }
#line 2852 "parser.c"
    break;

  case 175: /* enum_specifier: T_ENUM T_IDENTIFIER T_LBRACE enumerator_list T_RBRACE  */
#line 573 "parser.y"
                                                          { (yyval.node) = create_enum_specifier_node((yyvsp[-3].string_value), (yyvsp[-1].node)); }
#line 2858 "parser.c"
    break;

  case 176: /* enum_specifier: T_ENUM T_LBRACE enumerator_list T_RBRACE  */
#line 574 "parser.y"
                                               { (yyval.node) = create_enum_specifier_node(NULL, (yyvsp[-1].node)); }
#line 2864 "parser.c"
    break;

  case 177: /* enum_specifier: T_ENUM T_IDENTIFIER  */
#line 575 "parser.y"
                          { (yyval.node) = create_enum_specifier_node((yyvsp[0].string_value), NULL); }
#line 2870 "parser.c"
    break;

  case 178: /* enumerator_list: enumerator  */
#line 579 "parser.y"
               { (yyval.node) = create_statement_list_node(); add_statement_to_list((yyval.node), (yyvsp[0].node)); }
#line 2876 "parser.c"
    break;

  case 179: /* enumerator_list: enumerator_list T_COMMA enumerator  */
#line 580 "parser.y"
                                         { add_statement_to_list((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2882 "parser.c"
    break;

  case 180: /* enumerator: T_IDENTIFIER  */
#line 584 "parser.y"
                 { (yyval.node) = create_enumerator_node((yyvsp[0].string_value), NULL); }
#line 2888 "parser.c"
    break;

  case 181: /* enumerator: T_IDENTIFIER T_ASSIGN conditional_expression  */
#line 585 "parser.y"
                                                   { (yyval.node) = create_enumerator_node((yyvsp[-2].string_value), (yyvsp[0].node)); }
#line 2894 "parser.c"
    break;

  case 182: /* struct_declaration_list: struct_declaration  */
#line 589 "parser.y"
                       { (yyval.node) = create_statement_list_node(); add_statement_to_list((yyval.node), (yyvsp[0].node)); }
#line 2900 "parser.c"
    break;

  case 183: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 590 "parser.y"
                                                 { add_statement_to_list((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2906 "parser.c"
    break;

  case 184: /* struct_declaration: declaration_specifiers declarator_list T_SEMICOLON  */
#line 594 "parser.y"
                                                       { (yyval.node) = create_decl_list_node((yyvsp[-2].type), (yyvsp[-1].node)); }
#line 2912 "parser.c"
    break;

  case 185: /* declarator_list: declarator  */
#line 598 "parser.y"
               { (yyval.node) = create_statement_list_node(); add_statement_to_list((yyval.node), (yyvsp[0].node)); }
#line 2918 "parser.c"
    break;

  case 186: /* declarator_list: declarator_list T_COMMA declarator  */
#line 599 "parser.y"
                                         { add_statement_to_list((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2924 "parser.c"
    break;


#line 2928 "parser.c"

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

#line 602 "parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Parse error on line %d: %s near '%s'\n", yylineno, s, yytext);
}

void check_function_call(char *name, ASTNode *args) {
    Symbol *s = symtab_lookup(symbol_table, name);
    if (s == NULL) {
        yyerror("Function not defined");
        return;
    }
    if (s->type != SYMBOL_FUNCTION) {
        yyerror("Identifier is not a function");
        return;
    }

    int num_args = args ? args->arg_list.count : 0;
    int num_params = s->params ? s->params->param_list.count : 0;

    if (num_args != num_params) {
        yyerror("Incorrect number of arguments in function call");
        return;
    }

    for (int i = 0; i < num_args; i++) {
        // This is a simplified type check. A real implementation would need to
        // traverse the expression tree to determine the type of the argument.
        // Here, we're just assuming that the argument is a variable and
        // looking up its type in the symbol table.
        ASTNode *arg = args->arg_list.args[i];
        if (arg->type == NODE_TYPE_VARIABLE) {
            Symbol *arg_s = symtab_lookup(symbol_table, arg->variable.name);
            if (arg_s) {
                Type *param_type = s->params->param_list.params[i]->var_decl.var_type;
                Type arg_type = { .base = arg_s->data_type };
                if (!compare_types(&arg_type, param_type)) {
                    yyerror("Incompatible argument type in function call");
                }
            }
        }
    }
}

int compare_types(Type *a, Type *b) {
    if (a == NULL || b == NULL) {
        return 0;
    }
    if (a->base != b->base) {
        return 0;
    }
    if (a->base == TYPE_POINTER) {
        return compare_types(a->ptr_to, b->ptr_to);
    }
    return 1;
}

Symbol *get_current_function() {
    Scope *scope = symbol_table->current_scope;
    while (scope) {
        for (int i = 0; i < TABLE_SIZE; i++) {
            Symbol *s = scope->table[i];
            while (s) {
                if (s->type == SYMBOL_FUNCTION) {
                    return s;
                }
                s = s->next;
            }
        }
        scope = scope->parent;
    }
    return NULL;
}

DataType get_expression_type(ASTNode *expr) {
    if (!expr) {
        return DATA_TYPE_VOID;
    }
    switch (expr->type) {
        case NODE_TYPE_VARIABLE: {
            Symbol *s = symtab_lookup(symbol_table, expr->variable.name);
            if (s) {
                if (s->type == SYMBOL_FUNCTION) return s->return_type;
                return s->data_type;
            }
            return DATA_TYPE_VOID;
        }
        case NODE_TYPE_INTEGER:
            return DATA_TYPE_INT;
        case NODE_TYPE_CHAR:
            return DATA_TYPE_CHAR;
        case NODE_TYPE_FLOAT:
            return DATA_TYPE_FLOAT;
        case NODE_TYPE_BINARY_OP:
            // This is a simplification. A real implementation would need to
            // consider the types of the operands and the operator.
            return get_expression_type(expr->binary_op.left);
        case NODE_TYPE_FUNC_CALL: {
            Symbol *s = symtab_lookup(symbol_table, expr->func_call.name);
            return s ? s->return_type : DATA_TYPE_VOID;
        }
        case NODE_TYPE_ARRAY_ACCESS: {
            // This is a simplification. A real implementation would need to
            // determine the element type of the array.
            return DATA_TYPE_CHAR; // Assuming array elements are chars for now
        }
        default:
            return DATA_TYPE_VOID;
    }
}
