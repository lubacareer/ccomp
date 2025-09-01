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
void yyerror(const char *s);
extern char *yytext;
extern int yylineno;
ASTNode *root;

#line 85 "parser.c"

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
  YYSYMBOL_T_SEMICOLON = 40,               /* T_SEMICOLON  */
  YYSYMBOL_T_LPAREN = 41,                  /* T_LPAREN  */
  YYSYMBOL_T_RPAREN = 42,                  /* T_RPAREN  */
  YYSYMBOL_T_LBRACE = 43,                  /* T_LBRACE  */
  YYSYMBOL_T_RBRACE = 44,                  /* T_RBRACE  */
  YYSYMBOL_T_COMMA = 45,                   /* T_COMMA  */
  YYSYMBOL_T_LBRACKET = 46,                /* T_LBRACKET  */
  YYSYMBOL_T_RBRACKET = 47,                /* T_RBRACKET  */
  YYSYMBOL_T_DOT = 48,                     /* T_DOT  */
  YYSYMBOL_T_ARROW = 49,                   /* T_ARROW  */
  YYSYMBOL_T_INC = 50,                     /* T_INC  */
  YYSYMBOL_T_DEC = 51,                     /* T_DEC  */
  YYSYMBOL_T_LOGICAL_NOT = 52,             /* T_LOGICAL_NOT  */
  YYSYMBOL_T_BITWISE_NOT = 53,             /* T_BITWISE_NOT  */
  YYSYMBOL_T_LOGICAL_AND = 54,             /* T_LOGICAL_AND  */
  YYSYMBOL_T_LOGICAL_OR = 55,              /* T_LOGICAL_OR  */
  YYSYMBOL_T_BITWISE_AND = 56,             /* T_BITWISE_AND  */
  YYSYMBOL_T_BITWISE_OR = 57,              /* T_BITWISE_OR  */
  YYSYMBOL_T_BITWISE_XOR = 58,             /* T_BITWISE_XOR  */
  YYSYMBOL_T_LSHIFT = 59,                  /* T_LSHIFT  */
  YYSYMBOL_T_RSHIFT = 60,                  /* T_RSHIFT  */
  YYSYMBOL_T_ASSIGN = 61,                  /* T_ASSIGN  */
  YYSYMBOL_T_ADD_ASSIGN = 62,              /* T_ADD_ASSIGN  */
  YYSYMBOL_T_SUB_ASSIGN = 63,              /* T_SUB_ASSIGN  */
  YYSYMBOL_T_MUL_ASSIGN = 64,              /* T_MUL_ASSIGN  */
  YYSYMBOL_T_DIV_ASSIGN = 65,              /* T_DIV_ASSIGN  */
  YYSYMBOL_T_MOD_ASSIGN = 66,              /* T_MOD_ASSIGN  */
  YYSYMBOL_T_EQ = 67,                      /* T_EQ  */
  YYSYMBOL_T_NE = 68,                      /* T_NE  */
  YYSYMBOL_T_GT = 69,                      /* T_GT  */
  YYSYMBOL_T_GE = 70,                      /* T_GE  */
  YYSYMBOL_T_LT = 71,                      /* T_LT  */
  YYSYMBOL_T_LE = 72,                      /* T_LE  */
  YYSYMBOL_T_ADD = 73,                     /* T_ADD  */
  YYSYMBOL_T_SUB = 74,                     /* T_SUB  */
  YYSYMBOL_T_MUL = 75,                     /* T_MUL  */
  YYSYMBOL_T_DIV = 76,                     /* T_DIV  */
  YYSYMBOL_T_MOD = 77,                     /* T_MOD  */
  YYSYMBOL_T_QUESTION = 78,                /* T_QUESTION  */
  YYSYMBOL_T_COLON = 79,                   /* T_COLON  */
  YYSYMBOL_T_IFX = 80,                     /* T_IFX  */
  YYSYMBOL_81_ = 81,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 82,                  /* $accept  */
  YYSYMBOL_program = 83,                   /* program  */
  YYSYMBOL_translation_unit = 84,          /* translation_unit  */
  YYSYMBOL_external_declaration = 85,      /* external_declaration  */
  YYSYMBOL_function_definition = 86,       /* function_definition  */
  YYSYMBOL_declaration = 87,               /* declaration  */
  YYSYMBOL_declaration_specifiers = 88,    /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 89,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 90,           /* init_declarator  */
  YYSYMBOL_declarator = 91,                /* declarator  */
  YYSYMBOL_direct_declarator = 92,         /* direct_declarator  */
  YYSYMBOL_pointer = 93,                   /* pointer  */
  YYSYMBOL_param_list = 94,                /* param_list  */
  YYSYMBOL_parameter_declaration = 95,     /* parameter_declaration  */
  YYSYMBOL_type_name = 96,                 /* type_name  */
  YYSYMBOL_abstract_declarator = 97,       /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 98, /* direct_abstract_declarator  */
  YYSYMBOL_statement = 99,                 /* statement  */
  YYSYMBOL_compound_statement = 100,       /* compound_statement  */
  YYSYMBOL_block_item_list = 101,          /* block_item_list  */
  YYSYMBOL_block_item = 102,               /* block_item  */
  YYSYMBOL_labeled_statement = 103,        /* labeled_statement  */
  YYSYMBOL_selection_statement = 104,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 105,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 106,           /* jump_statement  */
  YYSYMBOL_expression = 107,               /* expression  */
  YYSYMBOL_assignment_expression = 108,    /* assignment_expression  */
  YYSYMBOL_conditional_expression = 109,   /* conditional_expression  */
  YYSYMBOL_logical_or_expression = 110,    /* logical_or_expression  */
  YYSYMBOL_logical_and_expression = 111,   /* logical_and_expression  */
  YYSYMBOL_inclusive_or_expression = 112,  /* inclusive_or_expression  */
  YYSYMBOL_exclusive_or_expression = 113,  /* exclusive_or_expression  */
  YYSYMBOL_and_expression = 114,           /* and_expression  */
  YYSYMBOL_equality_expression = 115,      /* equality_expression  */
  YYSYMBOL_relational_expression = 116,    /* relational_expression  */
  YYSYMBOL_shift_expression = 117,         /* shift_expression  */
  YYSYMBOL_additive_expression = 118,      /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 119, /* multiplicative_expression  */
  YYSYMBOL_cast_expression = 120,          /* cast_expression  */
  YYSYMBOL_unary_expression = 121,         /* unary_expression  */
  YYSYMBOL_postfix_expression = 122,       /* postfix_expression  */
  YYSYMBOL_primary_expression = 123,       /* primary_expression  */
  YYSYMBOL_argument_expression_list = 124, /* argument_expression_list  */
  YYSYMBOL_initializer = 125,              /* initializer  */
  YYSYMBOL_initializer_list = 126,         /* initializer_list  */
  YYSYMBOL_type_specifier = 127,           /* type_specifier  */
  YYSYMBOL_struct_specifier = 128,         /* struct_specifier  */
  YYSYMBOL_union_specifier = 129,          /* union_specifier  */
  YYSYMBOL_enum_specifier = 130,           /* enum_specifier  */
  YYSYMBOL_enumerator_list = 131,          /* enumerator_list  */
  YYSYMBOL_enumerator = 132,               /* enumerator  */
  YYSYMBOL_struct_declaration_list = 133,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 134,       /* struct_declaration  */
  YYSYMBOL_declarator_list = 135           /* declarator_list  */
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
#define YYFINAL  42
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1437

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  183
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  343

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   335


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
       2,     2,     2,     2,     2,     2,     2,     2,    81,     2,
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
      75,    76,    77,    78,    79,    80
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    68,    68,    72,    73,    77,    78,    82,    86,    87,
      88,    97,    98,    99,   100,   101,   102,   106,   107,   111,
     112,   116,   117,   121,   122,   123,   124,   125,   135,   148,
     149,   153,   154,   158,   168,   169,   173,   174,   178,   179,
     180,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     196,   197,   198,   199,   200,   201,   205,   206,   210,   211,
     215,   216,   220,   221,   222,   223,   227,   228,   229,   233,
     234,   235,   236,   237,   238,   242,   243,   244,   245,   246,
     250,   251,   255,   256,   257,   258,   259,   260,   261,   265,
     266,   270,   271,   275,   276,   280,   281,   285,   286,   290,
     291,   295,   296,   297,   301,   302,   303,   304,   305,   309,
     310,   311,   315,   316,   317,   321,   322,   323,   324,   328,
     329,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   347,   348,   349,   350,   351,   352,   353,   354,
     358,   359,   360,   361,   362,   363,   367,   368,   372,   373,
     374,   378,   379,   383,   384,   385,   386,   387,   388,   389,
     390,   391,   392,   393,   394,   395,   399,   400,   401,   405,
     406,   407,   411,   412,   413,   417,   418,   422,   423,   427,
     428,   432,   436,   437
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
  "T_VOLATILE", "T_INLINE", "T_SEMICOLON", "T_LPAREN", "T_RPAREN",
  "T_LBRACE", "T_RBRACE", "T_COMMA", "T_LBRACKET", "T_RBRACKET", "T_DOT",
  "T_ARROW", "T_INC", "T_DEC", "T_LOGICAL_NOT", "T_BITWISE_NOT",
  "T_LOGICAL_AND", "T_LOGICAL_OR", "T_BITWISE_AND", "T_BITWISE_OR",
  "T_BITWISE_XOR", "T_LSHIFT", "T_RSHIFT", "T_ASSIGN", "T_ADD_ASSIGN",
  "T_SUB_ASSIGN", "T_MUL_ASSIGN", "T_DIV_ASSIGN", "T_MOD_ASSIGN", "T_EQ",
  "T_NE", "T_GT", "T_GE", "T_LT", "T_LE", "T_ADD", "T_SUB", "T_MUL",
  "T_DIV", "T_MOD", "T_QUESTION", "T_COLON", "T_IFX", "':'", "$accept",
  "program", "translation_unit", "external_declaration",
  "function_definition", "declaration", "declaration_specifiers",
  "init_declarator_list", "init_declarator", "declarator",
  "direct_declarator", "pointer", "param_list", "parameter_declaration",
  "type_name", "abstract_declarator", "direct_abstract_declarator",
  "statement", "compound_statement", "block_item_list", "block_item",
  "labeled_statement", "selection_statement", "iteration_statement",
  "jump_statement", "expression", "assignment_expression",
  "conditional_expression", "logical_or_expression",
  "logical_and_expression", "inclusive_or_expression",
  "exclusive_or_expression", "and_expression", "equality_expression",
  "relational_expression", "shift_expression", "additive_expression",
  "multiplicative_expression", "cast_expression", "unary_expression",
  "postfix_expression", "primary_expression", "argument_expression_list",
  "initializer", "initializer_list", "type_specifier", "struct_specifier",
  "union_specifier", "enum_specifier", "enumerator_list", "enumerator",
  "struct_declaration_list", "struct_declaration", "declarator_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-200)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1362,  -200,  -200,    24,    28,    33,  -200,  -200,  -200,  -200,
    -200,  -200,  -200,  -200,  1398,  1398,  1398,  1398,  1398,  1398,
      89,  1362,  -200,  -200,  -200,     4,  -200,  -200,  -200,  -200,
      88,  1398,    96,  1398,   109,   108,    17,  -200,  -200,  -200,
    -200,  -200,  -200,  -200,  -200,  -200,    17,    58,    -2,  -200,
      41,    45,    32,  1398,    17,  1146,  -200,  1398,  1182,   108,
      97,    53,  -200,    48,   116,   144,  -200,  -200,    17,   309,
     751,  -200,  1290,   781,    45,  1218,  -200,    56,  -200,  -200,
    1254,  -200,   168,   991,  -200,   108,  -200,  -200,  -200,   133,
    -200,  -200,  -200,  -200,   811,   178,   183,   190,   192,   991,
     145,   169,   636,   199,   242,  1021,   490,  -200,  1051,  1051,
     991,   991,   991,   991,   991,   991,  -200,     4,  -200,  -200,
     382,  -200,  -200,  -200,  -200,  -200,    60,  -200,  -200,   -31,
     197,   189,   194,   198,   105,    93,   157,   148,   -35,  -200,
     128,    66,  -200,  -200,   751,  -200,  -200,  -200,    29,    87,
    -200,  -200,   206,  -200,  -200,  -200,    17,  -200,  -200,  -200,
    -200,   563,  -200,    68,   991,   991,   436,   991,   175,   636,
    -200,   244,  -200,   218,   490,  -200,   -16,   217,    95,   991,
    -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,   991,   991,   991,   991,   991,   991,   991,   991,   991,
     991,   991,   991,   991,   991,   991,   991,   991,   991,   991,
     991,   991,   991,   991,   991,   991,   991,   841,   991,   257,
     258,  -200,  -200,  -200,   185,   690,   871,  -200,     5,  -200,
      77,  -200,  1398,  -200,  -200,  -200,  -200,  -200,    99,   112,
     991,    79,   125,   636,  -200,   222,  -200,   239,  1105,    80,
    -200,   991,  -200,  -200,   197,   -42,   189,   194,   198,   105,
      93,    93,   157,   157,   157,   157,   148,   148,   -35,   -35,
    -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,   126,    40,  -200,  -200,  -200,   699,  -200,   155,   240,
    -200,   236,    77,  1326,   901,  -200,   636,   636,    82,   991,
     636,  -200,   991,  -200,  -200,   991,  -200,   991,  -200,  -200,
    -200,  -200,  -200,  -200,  -200,   156,  -200,   237,   273,  -200,
     931,    90,  -200,   161,  -200,  -200,  -200,  -200,   636,   636,
     162,   961,   246,  -200,  -200,   636,   636,   166,  -200,  -200,
    -200,   636,  -200
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   165,   156,     0,     0,     0,   154,   158,   159,   153,
     155,   157,   160,   161,     0,     0,     0,     0,     0,     0,
       0,     2,     3,     5,     6,     0,    11,   162,   163,   164,
     168,     0,   171,     0,   174,     0,     0,    12,    13,    14,
      15,    16,     1,     4,    23,     9,     0,    29,     0,    17,
      19,    22,     0,     0,     0,     0,   179,     0,     0,     0,
     177,     0,   175,     0,    19,     0,    30,     8,     0,     0,
       0,     7,     0,     0,    21,     0,   182,     0,   167,   180,
       0,   170,     0,     0,   173,     0,    10,    24,    18,   140,
     141,   142,   143,   144,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    56,     0,     0,
       0,     0,     0,     0,     0,     0,    60,     0,    61,    51,
       0,    58,    50,    53,    54,    55,     0,    80,    82,    89,
      91,    93,    95,    97,    99,   101,   104,   109,   112,   115,
     119,   121,   132,   140,     0,   148,    20,    28,    35,     0,
      31,    26,     0,   119,   166,   181,     0,   169,   172,   178,
     176,     0,    78,     0,     0,     0,     0,     0,     0,     0,
      77,     0,    76,     0,     0,   130,    36,     0,     0,     0,
     122,   123,   129,   128,   124,   126,   127,   125,    57,    59,
      52,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   138,   139,   151,     0,     0,     0,    33,    38,    34,
      39,    27,     0,    25,   183,    65,    62,    79,     0,     0,
       0,     0,     0,     0,    64,     0,    75,     0,     0,    38,
      37,     0,   145,    81,    92,     0,    94,    96,    98,   100,
     102,   103,   106,   108,   105,   107,   110,   111,   113,   114,
     116,   117,   118,    83,    84,    85,    86,    87,    88,   134,
     146,     0,     0,   136,   137,   149,     0,    46,     0,     0,
      42,     0,    40,     0,     0,    32,     0,     0,     0,     0,
       0,    63,     0,   131,   120,     0,   135,     0,   133,   150,
     152,    47,    41,    43,    48,     0,    44,     0,    66,    69,
       0,     0,    68,     0,    90,   147,    49,    45,     0,     0,
       0,     0,     0,    67,    73,     0,     0,     0,    70,    74,
      71,     0,    72
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -200,  -200,  -200,   266,  -200,   -63,     0,   252,   221,   -20,
     -40,   -38,   -70,    59,   118,  -137,  -199,  -101,   245,  -200,
     170,  -200,  -200,  -200,  -200,   -84,   -66,   -50,  -200,   102,
     103,   104,   106,   101,    39,  -147,    38,    43,   -49,    70,
    -200,  -200,  -200,  -131,  -200,  -200,  -200,  -200,  -200,   241,
     216,    -5,    19,  -200
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    20,    21,    22,    23,    24,    54,    48,    49,    64,
      51,    52,   288,   150,   177,   289,   230,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   281,   146,   224,    26,    27,    28,    29,    61,
      62,    55,    56,    77
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      25,   171,   149,   191,   145,    50,   116,    44,    44,    66,
     163,   229,    74,   223,    36,    37,    38,    39,    40,    41,
      44,    25,   178,   152,   192,   248,    65,    30,    58,   292,
     226,    32,    44,   159,    76,    44,    34,   305,    67,   250,
     208,   209,   210,    68,    45,    46,   225,   193,    75,   168,
     292,   226,    80,   262,   263,   264,   265,   116,    46,    47,
     236,   182,   183,   184,   185,   186,   187,    31,   244,   117,
     225,    33,   148,    46,    79,   226,    35,    79,   145,    47,
     238,   239,   241,   242,    69,   191,    72,   308,    86,    42,
     178,    73,    47,    68,    79,   178,   155,    84,    85,    79,
     190,   156,    70,   240,    47,   191,   176,   217,   237,   255,
     228,    60,   218,   191,   219,   220,   221,   222,   293,   299,
     117,   248,   320,   294,   191,   253,   226,   191,   227,   231,
     331,    53,   232,    47,   282,   191,   234,   252,   249,    57,
     191,   296,   301,   153,   191,   273,   274,   275,   276,   277,
     278,   280,    59,   153,   297,   310,   298,   191,    83,   270,
     271,   272,   200,   201,   202,   203,   117,   300,   306,   153,
     191,   307,   198,   199,   176,   175,   291,    70,   180,   181,
     153,   153,   153,   153,   153,   153,    87,   228,    74,   211,
     212,   213,   214,   215,   216,   318,   319,   311,   326,   322,
     232,   232,   304,   332,   335,    65,   191,   191,   341,   170,
     249,   191,   158,    85,   161,   321,   204,   205,   323,   164,
     145,   206,   207,   315,   165,   148,   169,   333,   334,   285,
     286,   166,   148,   167,   339,   340,   330,   260,   261,   172,
     342,   325,   266,   267,   317,   173,   195,   337,   148,   268,
     269,   194,   196,   233,   197,   324,   243,   245,   246,   251,
     283,   284,   153,   302,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   303,   312,   313,   327,   328,   338,    43,    63,    88,
     189,   295,   247,   148,   254,    71,   153,   256,   259,   257,
      82,   160,   258,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,     1,    90,    91,    92,    93,     2,    94,
      95,   153,    96,    97,    98,    99,   100,   101,   102,   103,
     104,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,   105,    15,    16,    17,    18,    19,     0,
     106,     0,    69,   107,     0,     0,     0,     0,     0,   108,
     109,   110,   111,     0,   153,   112,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   153,     0,     0,     0,     0,
       0,     0,   113,   114,   115,    89,     1,    90,    91,    92,
      93,     2,    94,    95,     0,    96,    97,    98,    99,   100,
     101,   102,   103,   104,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,   105,    15,    16,    17,
      18,    19,     0,   106,     0,    69,   188,     0,     0,     0,
       0,     0,   108,   109,   110,   111,     0,     0,   112,   143,
       1,    90,    91,    92,    93,     2,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   113,   114,   115,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
     105,    15,    16,    17,    18,    19,     0,   106,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   109,   110,   111,
       0,     0,   112,   143,     1,    90,    91,    92,    93,     2,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   113,
     114,   115,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     0,   105,    15,    16,    17,    18,    19,
       0,   106,     0,     0,     0,     0,     0,     0,     0,     0,
     108,   109,   110,   111,     0,     0,   112,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   113,   114,   115,    89,     0,    90,    91,
      92,    93,     0,    94,    95,     0,    96,    97,    98,    99,
     100,   101,   102,   103,   104,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   105,     0,     0,
       0,     0,     0,   235,   106,     0,    69,     0,     0,     0,
       0,     0,     0,   108,   109,   110,   111,     0,     0,   112,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   113,   114,   115,    89,
       0,    90,    91,    92,    93,     0,    94,    95,     0,    96,
      97,    98,    99,   100,   101,   102,   103,   104,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     105,     0,     0,     0,     0,     0,     0,   106,     0,    69,
       0,     0,     0,     0,     0,     0,   108,   109,   110,   111,
       0,     0,   112,    44,     1,     0,     0,     0,     0,     2,
       0,     0,   143,     0,    90,    91,    92,    93,     0,   113,
     114,   115,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     0,     0,    15,    16,    17,    18,    19,
       0,   225,   287,   105,     0,     0,   226,     0,     0,     0,
     106,     0,   144,   309,     0,     0,     0,     0,     0,   108,
     109,   110,   111,     0,   143,   112,    90,    91,    92,    93,
       0,     0,     0,     0,     0,    47,     0,     0,     0,     0,
       0,     0,   113,   114,   115,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   143,   105,    90,    91,    92,    93,
       0,     0,   106,     0,   144,     0,     0,     0,     0,     0,
       0,   108,   109,   110,   111,     0,     0,   112,     0,     0,
       0,     0,     0,     0,   143,   105,    90,    91,    92,    93,
       0,     0,   106,     0,   113,   114,   115,     0,   151,     0,
       0,   108,   109,   110,   111,     0,     0,   112,     0,     0,
       0,     0,     0,     0,   143,   105,    90,    91,    92,    93,
       0,   162,   106,     0,   113,   114,   115,     0,     0,     0,
       0,   108,   109,   110,   111,     0,     0,   112,     0,     0,
       0,     0,     0,     0,   143,   105,    90,    91,    92,    93,
       0,     0,   106,   279,   113,   114,   115,     0,     0,     0,
       0,   108,   109,   110,   111,     0,     0,   112,     0,     0,
       0,     0,     0,     0,   143,   105,    90,    91,    92,    93,
       0,     0,   106,     0,   113,   114,   115,     0,   290,     0,
       0,   108,   109,   110,   111,     0,     0,   112,     0,     0,
       0,     0,     0,     0,   143,   105,    90,    91,    92,    93,
       0,     0,   106,     0,   113,   114,   115,     0,   316,     0,
       0,   108,   109,   110,   111,     0,     0,   112,     0,     0,
       0,     0,     0,     0,   143,   105,    90,    91,    92,    93,
       0,     0,   106,   329,   113,   114,   115,     0,     0,     0,
       0,   108,   109,   110,   111,     0,     0,   112,     0,     0,
       0,     0,     0,     0,   143,   105,    90,    91,    92,    93,
       0,     0,   106,   336,   113,   114,   115,     0,     0,     0,
       0,   108,   109,   110,   111,     0,     0,   112,     0,     0,
       0,     0,     0,     0,   143,   105,    90,    91,    92,    93,
       0,     0,   106,     0,   113,   114,   115,     0,     0,     0,
       0,   108,   109,   110,   111,     0,     0,   112,     0,     0,
       0,     0,     0,     0,   143,   105,    90,    91,    92,    93,
       0,     0,   174,     0,   113,   114,   115,     0,     0,     0,
       0,   108,   109,   110,   111,     0,     0,   112,     0,     0,
       0,     0,     0,     0,     0,   105,     0,     0,     0,     0,
       0,     0,   179,     0,   113,   114,   115,     0,     0,     0,
       0,   108,   109,   110,   111,     0,     0,   112,     0,     1,
       0,     0,     0,     0,     2,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   113,   114,   115,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     0,     0,
      15,    16,    17,    18,    19,     0,   248,   287,     0,     0,
       1,   226,     0,     0,     0,     2,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,     0,
      47,    15,    16,    17,    18,    19,     1,     0,     0,     0,
      78,     2,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,    15,    16,    17,
      18,    19,     1,     0,     0,     0,    81,     2,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,     0,     0,    15,    16,    17,    18,    19,     1,     0,
       0,     0,   154,     2,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,     0,     0,    15,
      16,    17,    18,    19,     1,     0,     0,     0,   157,     2,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     0,     0,    15,    16,    17,    18,    19,
       1,     0,   147,     0,     0,     2,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,     0,
       0,    15,    16,    17,    18,    19,     1,     0,   314,     0,
       0,     2,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,     0,    15,    16,    17,
      18,    19,     1,     0,     0,     0,     0,     2,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,     0,     0,    15,    16,    17,    18,    19
};

static const yytype_int16 yycheck[] =
{
       0,   102,    72,    45,    70,    25,    69,     3,     3,    47,
      94,   148,    52,   144,    14,    15,    16,    17,    18,    19,
       3,    21,   106,    73,    55,    41,    46,     3,    33,   228,
      46,     3,     3,    83,    54,     3,     3,    79,    40,   176,
      75,    76,    77,    45,    40,    41,    41,    78,    53,    99,
     249,    46,    57,   200,   201,   202,   203,   120,    41,    75,
     161,   110,   111,   112,   113,   114,   115,    43,   169,    69,
      41,    43,    72,    41,    55,    46,    43,    58,   144,    75,
     164,   165,   166,   167,    43,    45,    41,    47,    40,     0,
     174,    46,    75,    45,    75,   179,    40,    44,    45,    80,
      40,    45,    61,   166,    75,    45,   106,    41,    40,   193,
     148,     3,    46,    45,    48,    49,    50,    51,    41,    40,
     120,    41,    40,    46,    45,   191,    46,    45,   148,    42,
      40,    43,    45,    75,   218,    45,   156,    42,   176,    43,
      45,    42,   243,    73,    45,   211,   212,   213,   214,   215,
     216,   217,    43,    83,    42,   286,   240,    45,    61,   208,
     209,   210,    69,    70,    71,    72,   166,    42,    42,    99,
      45,    45,    67,    68,   174,   105,   226,    61,   108,   109,
     110,   111,   112,   113,   114,   115,    42,   225,   228,    61,
      62,    63,    64,    65,    66,   296,   297,    42,    42,   300,
      45,    45,   251,    42,    42,   225,    45,    45,    42,    40,
     248,    45,    44,    45,    81,   299,    59,    60,   302,    41,
     286,    73,    74,   293,    41,   225,    81,   328,   329,    44,
      45,    41,   232,    41,   335,   336,   320,   198,   199,    40,
     341,   307,   204,   205,   294,     3,    57,   331,   248,   206,
     207,    54,    58,    47,    56,   305,    81,    13,    40,    42,
       3,     3,   192,    41,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,    42,    42,    47,    47,    12,    40,    21,    36,    68,
     120,   232,   174,   293,   192,    50,   226,   194,   197,   195,
      59,    85,   196,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,   251,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    -1,
      41,    -1,    43,    44,    -1,    -1,    -1,    -1,    -1,    50,
      51,    52,    53,    -1,   294,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   305,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    74,    75,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    -1,    41,    -1,    43,    44,    -1,    -1,    -1,
      -1,    -1,    50,    51,    52,    53,    -1,    -1,    56,     3,
       4,     5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    74,    75,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    -1,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      -1,    -1,    56,     3,     4,     5,     6,     7,     8,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,
      74,    75,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    34,    35,    36,    37,    38,    39,
      -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    51,    52,    53,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    75,     3,    -1,     5,     6,
       7,     8,    -1,    10,    11,    -1,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,
      -1,    -1,    -1,    40,    41,    -1,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    51,    52,    53,    -1,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,     3,
      -1,     5,     6,     7,     8,    -1,    10,    11,    -1,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      -1,    -1,    56,     3,     4,    -1,    -1,    -1,    -1,     9,
      -1,    -1,     3,    -1,     5,     6,     7,     8,    -1,    73,
      74,    75,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    -1,    35,    36,    37,    38,    39,
      -1,    41,    42,    34,    -1,    -1,    46,    -1,    -1,    -1,
      41,    -1,    43,    44,    -1,    -1,    -1,    -1,    -1,    50,
      51,    52,    53,    -1,     3,    56,     5,     6,     7,     8,
      -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    34,     5,     6,     7,     8,
      -1,    -1,    41,    -1,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    34,     5,     6,     7,     8,
      -1,    -1,    41,    -1,    73,    74,    75,    -1,    47,    -1,
      -1,    50,    51,    52,    53,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    34,     5,     6,     7,     8,
      -1,    40,    41,    -1,    73,    74,    75,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    34,     5,     6,     7,     8,
      -1,    -1,    41,    42,    73,    74,    75,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    34,     5,     6,     7,     8,
      -1,    -1,    41,    -1,    73,    74,    75,    -1,    47,    -1,
      -1,    50,    51,    52,    53,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    34,     5,     6,     7,     8,
      -1,    -1,    41,    -1,    73,    74,    75,    -1,    47,    -1,
      -1,    50,    51,    52,    53,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    34,     5,     6,     7,     8,
      -1,    -1,    41,    42,    73,    74,    75,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    34,     5,     6,     7,     8,
      -1,    -1,    41,    42,    73,    74,    75,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    34,     5,     6,     7,     8,
      -1,    -1,    41,    -1,    73,    74,    75,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    34,     5,     6,     7,     8,
      -1,    -1,    41,    -1,    73,    74,    75,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    -1,    73,    74,    75,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    -1,    -1,    56,    -1,     4,
      -1,    -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    74,    75,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    39,    -1,    41,    42,    -1,    -1,
       4,    46,    -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      75,    35,    36,    37,    38,    39,     4,    -1,    -1,    -1,
      44,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    -1,    35,    36,    37,
      38,    39,     4,    -1,    -1,    -1,    44,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    35,    36,    37,    38,    39,     4,    -1,
      -1,    -1,    44,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    -1,    35,
      36,    37,    38,    39,     4,    -1,    -1,    -1,    44,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    -1,    35,    36,    37,    38,    39,
       4,    -1,    42,    -1,    -1,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      -1,    35,    36,    37,    38,    39,     4,    -1,    42,    -1,
      -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    -1,    35,    36,    37,
      38,    39,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    35,    36,    37,    38,    39
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     9,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    35,    36,    37,    38,    39,
      83,    84,    85,    86,    87,    88,   127,   128,   129,   130,
       3,    43,     3,    43,     3,    43,    88,    88,    88,    88,
      88,    88,     0,    85,     3,    40,    41,    75,    89,    90,
      91,    92,    93,    43,    88,   133,   134,    43,   133,    43,
       3,   131,   132,    89,    91,    91,    93,    40,    45,    43,
      61,   100,    41,    46,    92,   133,    91,   135,    44,   134,
     133,    44,   131,    61,    44,    45,    40,    42,    90,     3,
       5,     6,     7,     8,    10,    11,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    34,    41,    44,    50,    51,
      52,    53,    56,    73,    74,    75,    87,    88,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,     3,    43,   108,   125,    42,    88,    94,
      95,    47,   109,   121,    44,    40,    45,    44,    44,   109,
     132,    81,    40,   107,    41,    41,    41,    41,   109,    81,
      40,    99,    40,     3,    41,   121,    88,    96,   107,    41,
     121,   121,   120,   120,   120,   120,   120,   120,    44,   102,
      40,    45,    55,    78,    54,    57,    58,    56,    67,    68,
      69,    70,    71,    72,    59,    60,    73,    74,    75,    76,
      77,    61,    62,    63,    64,    65,    66,    41,    46,    48,
      49,    50,    51,   125,   126,    41,    46,    91,    93,    97,
      98,    42,    45,    47,    91,    40,    99,    40,   107,   107,
      87,   107,   107,    81,    99,    13,    40,    96,    41,    93,
      97,    42,    42,   108,   111,   107,   112,   113,   114,   115,
     116,   116,   117,   117,   117,   117,   118,   118,   119,   119,
     120,   120,   120,   108,   108,   108,   108,   108,   108,    42,
     108,   124,   107,     3,     3,    44,    45,    42,    94,    97,
      47,   109,    98,    41,    46,    95,    42,    42,   107,    40,
      42,    99,    41,    42,   120,    79,    42,    45,    47,    44,
     125,    42,    42,    47,    42,    94,    47,   109,    99,    99,
      40,   107,    99,   107,   109,   108,    42,    47,    12,    42,
     107,    40,    42,    99,    99,    42,    42,   107,    40,    99,
      99,    42,    99
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    82,    83,    84,    84,    85,    85,    86,    87,    87,
      87,    88,    88,    88,    88,    88,    88,    89,    89,    90,
      90,    91,    91,    92,    92,    92,    92,    92,    92,    93,
      93,    94,    94,    95,    95,    95,    96,    96,    97,    97,
      97,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      99,    99,    99,    99,    99,    99,   100,   100,   101,   101,
     102,   102,   103,   103,   103,   103,   104,   104,   104,   105,
     105,   105,   105,   105,   105,   106,   106,   106,   106,   106,
     107,   107,   108,   108,   108,   108,   108,   108,   108,   109,
     109,   110,   110,   111,   111,   112,   112,   113,   113,   114,
     114,   115,   115,   115,   116,   116,   116,   116,   116,   117,
     117,   117,   118,   118,   118,   119,   119,   119,   119,   120,
     120,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   122,   122,   122,   122,   122,   122,   122,   122,
     123,   123,   123,   123,   123,   123,   124,   124,   125,   125,
     125,   126,   126,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   128,   128,   128,   129,
     129,   129,   130,   130,   130,   131,   131,   132,   132,   133,
     133,   134,   135,   135
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     3,     2,
       4,     1,     2,     2,     2,     2,     2,     1,     3,     1,
       3,     2,     1,     1,     3,     4,     3,     4,     3,     1,
       2,     1,     3,     2,     2,     1,     1,     2,     1,     1,
       2,     3,     2,     3,     3,     4,     2,     3,     3,     4,
       1,     1,     2,     1,     1,     1,     2,     3,     1,     2,
       1,     1,     3,     4,     3,     3,     5,     7,     5,     5,
       7,     8,     9,     7,     8,     3,     2,     2,     2,     3,
       1,     3,     1,     3,     3,     3,     3,     3,     3,     1,
       5,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       4,     1,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     4,     1,     4,     3,     4,     3,     3,     2,     2,
       1,     1,     1,     1,     1,     3,     1,     3,     1,     3,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     4,     2,     5,
       4,     2,     5,     4,     2,     1,     3,     1,     3,     1,
       2,     3,     1,     3
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
#line 68 "parser.y"
                     { root = (yyvsp[0].node); }
#line 1683 "parser.c"
    break;

  case 3: /* translation_unit: external_declaration  */
#line 72 "parser.y"
                         { (yyval.node) = create_program_node(); add_toplevel_statement_to_program((yyval.node), (yyvsp[0].node)); }
#line 1689 "parser.c"
    break;

  case 4: /* translation_unit: translation_unit external_declaration  */
#line 73 "parser.y"
                                            { add_toplevel_statement_to_program((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 1695 "parser.c"
    break;

  case 7: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 82 "parser.y"
                                                         { (yyval.node) = create_function_definition_node((yyvsp[-2].type), (yyvsp[-1].node), NULL, (yyvsp[0].node)); }
#line 1701 "parser.c"
    break;

  case 8: /* declaration: declaration_specifiers init_declarator_list T_SEMICOLON  */
#line 86 "parser.y"
                                                            { (yyval.node) = create_decl_list_node((yyvsp[-2].type), (yyvsp[-1].node)); }
#line 1707 "parser.c"
    break;

  case 9: /* declaration: declaration_specifiers T_SEMICOLON  */
#line 87 "parser.y"
                                         { (yyval.node) = create_type_decl_node((yyvsp[-1].type)); }
#line 1713 "parser.c"
    break;

  case 10: /* declaration: T_TYPEDEF declaration_specifiers init_declarator_list T_SEMICOLON  */
#line 88 "parser.y"
                                                                        {
        for (int i = 0; i < (yyvsp[-1].node)->statement_list.count; i++) {
            add_typedef_name((yyvsp[-1].node)->statement_list.statements[i]->var_decl.name);
        }
        (yyval.node) = create_typedef_node(NULL, (yyvsp[-2].type));
    }
#line 1724 "parser.c"
    break;

  case 11: /* declaration_specifiers: type_specifier  */
#line 97 "parser.y"
                   { (yyval.type) = (yyvsp[0].type); }
#line 1730 "parser.c"
    break;

  case 12: /* declaration_specifiers: T_CONST declaration_specifiers  */
#line 98 "parser.y"
                                     { (yyval.type) = (yyvsp[0].type); (yyval.type)->is_const = 1; }
#line 1736 "parser.c"
    break;

  case 13: /* declaration_specifiers: T_STATIC declaration_specifiers  */
#line 99 "parser.y"
                                      { (yyval.type) = (yyvsp[0].type); (yyval.type)->is_static = 1; }
#line 1742 "parser.c"
    break;

  case 14: /* declaration_specifiers: T_EXTERN declaration_specifiers  */
#line 100 "parser.y"
                                      { (yyval.type) = (yyvsp[0].type); (yyval.type)->is_extern = 1; }
#line 1748 "parser.c"
    break;

  case 15: /* declaration_specifiers: T_VOLATILE declaration_specifiers  */
#line 101 "parser.y"
                                        { (yyval.type) = (yyvsp[0].type); (yyval.type)->is_volatile = 1; }
#line 1754 "parser.c"
    break;

  case 16: /* declaration_specifiers: T_INLINE declaration_specifiers  */
#line 102 "parser.y"
                                      { (yyval.type) = (yyvsp[0].type); (yyval.type)->is_inline = 1; }
#line 1760 "parser.c"
    break;

  case 17: /* init_declarator_list: init_declarator  */
#line 106 "parser.y"
                    { (yyval.node) = create_statement_list_node(); add_statement_to_list((yyval.node), (yyvsp[0].node)); }
#line 1766 "parser.c"
    break;

  case 18: /* init_declarator_list: init_declarator_list T_COMMA init_declarator  */
#line 107 "parser.y"
                                                   { add_statement_to_list((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1772 "parser.c"
    break;

  case 19: /* init_declarator: declarator  */
#line 111 "parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 1778 "parser.c"
    break;

  case 20: /* init_declarator: declarator T_ASSIGN initializer  */
#line 112 "parser.y"
                                      { (yyvsp[-2].node)->var_decl.init_expr = (yyvsp[0].node); (yyval.node) = (yyvsp[-2].node); }
#line 1784 "parser.c"
    break;

  case 21: /* declarator: pointer direct_declarator  */
#line 116 "parser.y"
                              { (yyval.node) = (yyvsp[0].node); Type *t = (yyvsp[-1].type); while(t->ptr_to) t = t->ptr_to; t->ptr_to = (yyvsp[0].node)->var_decl.var_type; (yyvsp[0].node)->var_decl.var_type = (yyvsp[-1].type); }
#line 1790 "parser.c"
    break;

  case 22: /* declarator: direct_declarator  */
#line 117 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1796 "parser.c"
    break;

  case 23: /* direct_declarator: T_IDENTIFIER  */
#line 121 "parser.y"
                 { (yyval.node) = create_var_decl_node((yyvsp[0].string_value), NULL, 0, 0, NULL); }
#line 1802 "parser.c"
    break;

  case 24: /* direct_declarator: T_LPAREN declarator T_RPAREN  */
#line 122 "parser.y"
                                   { (yyval.node) = (yyvsp[-1].node); }
#line 1808 "parser.c"
    break;

  case 25: /* direct_declarator: direct_declarator T_LBRACKET conditional_expression T_RBRACKET  */
#line 123 "parser.y"
                                                                     { (yyval.node) = (yyvsp[-3].node); (yyvsp[-3].node)->var_decl.var_type = create_array_type((yyvsp[-3].node)->var_decl.var_type, 0); }
#line 1814 "parser.c"
    break;

  case 26: /* direct_declarator: direct_declarator T_LBRACKET T_RBRACKET  */
#line 124 "parser.y"
                                              { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->var_decl.var_type = create_array_type((yyvsp[-2].node)->var_decl.var_type, 0); }
#line 1820 "parser.c"
    break;

  case 27: /* direct_declarator: direct_declarator T_LPAREN param_list T_RPAREN  */
#line 125 "parser.y"
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
#line 1835 "parser.c"
    break;

  case 28: /* direct_declarator: direct_declarator T_LPAREN T_RPAREN  */
#line 135 "parser.y"
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
#line 1850 "parser.c"
    break;

  case 29: /* pointer: T_MUL  */
#line 148 "parser.y"
          { (yyval.type) = create_pointer_type(NULL); }
#line 1856 "parser.c"
    break;

  case 30: /* pointer: T_MUL pointer  */
#line 149 "parser.y"
                    { (yyval.type) = create_pointer_type((yyvsp[0].type)); }
#line 1862 "parser.c"
    break;

  case 31: /* param_list: parameter_declaration  */
#line 153 "parser.y"
                          { (yyval.node) = create_param_list_node(); add_param_to_list((yyval.node), (yyvsp[0].node)); }
#line 1868 "parser.c"
    break;

  case 32: /* param_list: param_list T_COMMA parameter_declaration  */
#line 154 "parser.y"
                                               { add_param_to_list((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1874 "parser.c"
    break;

  case 33: /* parameter_declaration: declaration_specifiers declarator  */
#line 158 "parser.y"
                                      {
        (yyval.node) = (yyvsp[0].node);
        if ((yyval.node)->var_decl.var_type) {
            Type *t = (yyval.node)->var_decl.var_type;
            while(t->ptr_to) t = t->ptr_to;
            t->ptr_to = (yyvsp[-1].type);
        } else {
            (yyval.node)->var_decl.var_type = (yyvsp[-1].type);
        }
    }
#line 1889 "parser.c"
    break;

  case 34: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 168 "parser.y"
                                                 { (yyval.node) = create_var_decl_node(NULL, (yyvsp[-1].type), 0, 0, NULL); }
#line 1895 "parser.c"
    break;

  case 35: /* parameter_declaration: declaration_specifiers  */
#line 169 "parser.y"
                             { (yyval.node) = create_var_decl_node(NULL, (yyvsp[0].type), 0, 0, NULL); }
#line 1901 "parser.c"
    break;

  case 36: /* type_name: declaration_specifiers  */
#line 173 "parser.y"
                           { (yyval.type) = (yyvsp[0].type); }
#line 1907 "parser.c"
    break;

  case 37: /* type_name: declaration_specifiers abstract_declarator  */
#line 174 "parser.y"
                                                 { (yyval.type) = (yyvsp[-1].type); }
#line 1913 "parser.c"
    break;

  case 38: /* abstract_declarator: pointer  */
#line 178 "parser.y"
            { (yyval.type) = (yyvsp[0].type); }
#line 1919 "parser.c"
    break;

  case 39: /* abstract_declarator: direct_abstract_declarator  */
#line 179 "parser.y"
                                 { (yyval.type) = (yyvsp[0].type); }
#line 1925 "parser.c"
    break;

  case 40: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 180 "parser.y"
                                         { (yyval.type) = (yyvsp[-1].type); }
#line 1931 "parser.c"
    break;

  case 41: /* direct_abstract_declarator: T_LPAREN abstract_declarator T_RPAREN  */
#line 184 "parser.y"
                                          { (yyval.type) = (yyvsp[-1].type); }
#line 1937 "parser.c"
    break;

  case 42: /* direct_abstract_declarator: T_LBRACKET T_RBRACKET  */
#line 185 "parser.y"
                            { (yyval.type) = create_array_type(NULL, 0); }
#line 1943 "parser.c"
    break;

  case 43: /* direct_abstract_declarator: T_LBRACKET conditional_expression T_RBRACKET  */
#line 186 "parser.y"
                                                   { (yyval.type) = create_array_type(NULL, 0); }
#line 1949 "parser.c"
    break;

  case 44: /* direct_abstract_declarator: direct_abstract_declarator T_LBRACKET T_RBRACKET  */
#line 187 "parser.y"
                                                       { (yyval.type) = (yyvsp[-2].type); }
#line 1955 "parser.c"
    break;

  case 45: /* direct_abstract_declarator: direct_abstract_declarator T_LBRACKET conditional_expression T_RBRACKET  */
#line 188 "parser.y"
                                                                              { (yyval.type) = (yyvsp[-3].type); }
#line 1961 "parser.c"
    break;

  case 46: /* direct_abstract_declarator: T_LPAREN T_RPAREN  */
#line 189 "parser.y"
                        { (yyval.type) = create_function_type(NULL, NULL); }
#line 1967 "parser.c"
    break;

  case 47: /* direct_abstract_declarator: T_LPAREN param_list T_RPAREN  */
#line 190 "parser.y"
                                   { (yyval.type) = create_function_type(NULL, (yyvsp[-1].node)); }
#line 1973 "parser.c"
    break;

  case 48: /* direct_abstract_declarator: direct_abstract_declarator T_LPAREN T_RPAREN  */
#line 191 "parser.y"
                                                   { (yyval.type) = (yyvsp[-2].type); }
#line 1979 "parser.c"
    break;

  case 49: /* direct_abstract_declarator: direct_abstract_declarator T_LPAREN param_list T_RPAREN  */
#line 192 "parser.y"
                                                              { (yyval.type) = (yyvsp[-3].type); }
#line 1985 "parser.c"
    break;

  case 56: /* compound_statement: T_LBRACE T_RBRACE  */
#line 205 "parser.y"
                      { (yyval.node) = create_statement_list_node(); }
#line 1991 "parser.c"
    break;

  case 57: /* compound_statement: T_LBRACE block_item_list T_RBRACE  */
#line 206 "parser.y"
                                        { (yyval.node) = (yyvsp[-1].node); }
#line 1997 "parser.c"
    break;

  case 58: /* block_item_list: block_item  */
#line 210 "parser.y"
               { (yyval.node) = create_statement_list_node(); add_statement_to_list((yyval.node), (yyvsp[0].node)); }
#line 2003 "parser.c"
    break;

  case 59: /* block_item_list: block_item_list block_item  */
#line 211 "parser.y"
                                 { add_statement_to_list((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2009 "parser.c"
    break;

  case 62: /* labeled_statement: T_IDENTIFIER ':' statement  */
#line 220 "parser.y"
                               { (yyval.node) = create_label_node((yyvsp[-2].string_value), (yyvsp[0].node)); }
#line 2015 "parser.c"
    break;

  case 63: /* labeled_statement: T_CASE conditional_expression ':' statement  */
#line 221 "parser.y"
                                                  { (yyval.node) = create_case_node((yyvsp[-2].node)); add_statement_to_list((yyval.node), (yyvsp[0].node)); }
#line 2021 "parser.c"
    break;

  case 64: /* labeled_statement: T_DEFAULT ':' statement  */
#line 222 "parser.y"
                              { (yyval.node) = create_case_node(NULL); add_statement_to_list((yyval.node), (yyvsp[0].node)); }
#line 2027 "parser.c"
    break;

  case 65: /* labeled_statement: T_IDENTIFIER ':' T_SEMICOLON  */
#line 223 "parser.y"
                                   { (yyval.node) = create_label_node((yyvsp[-2].string_value), NULL); }
#line 2033 "parser.c"
    break;

  case 66: /* selection_statement: T_IF T_LPAREN expression T_RPAREN statement  */
#line 227 "parser.y"
                                                            { (yyval.node) = create_if_node((yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2039 "parser.c"
    break;

  case 67: /* selection_statement: T_IF T_LPAREN expression T_RPAREN statement T_ELSE statement  */
#line 228 "parser.y"
                                                                   { (yyval.node) = create_if_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2045 "parser.c"
    break;

  case 68: /* selection_statement: T_SWITCH T_LPAREN expression T_RPAREN statement  */
#line 229 "parser.y"
                                                      { (yyval.node) = create_switch_node((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2051 "parser.c"
    break;

  case 69: /* iteration_statement: T_WHILE T_LPAREN expression T_RPAREN statement  */
#line 233 "parser.y"
                                                   { (yyval.node) = create_while_node((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2057 "parser.c"
    break;

  case 70: /* iteration_statement: T_DO statement T_WHILE T_LPAREN expression T_RPAREN T_SEMICOLON  */
#line 234 "parser.y"
                                                                      { (yyval.node) = create_do_while_node((yyvsp[-5].node), (yyvsp[-2].node)); }
#line 2063 "parser.c"
    break;

  case 71: /* iteration_statement: T_FOR T_LPAREN expression T_SEMICOLON expression T_SEMICOLON T_RPAREN statement  */
#line 235 "parser.y"
                                                                                      { (yyval.node) = create_for_node((yyvsp[-5].node), (yyvsp[-3].node), NULL, (yyvsp[0].node)); }
#line 2069 "parser.c"
    break;

  case 72: /* iteration_statement: T_FOR T_LPAREN expression T_SEMICOLON expression T_SEMICOLON expression T_RPAREN statement  */
#line 236 "parser.y"
                                                                                                 { (yyval.node) = create_for_node((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2075 "parser.c"
    break;

  case 73: /* iteration_statement: T_FOR T_LPAREN declaration expression T_SEMICOLON T_RPAREN statement  */
#line 237 "parser.y"
                                                                           { (yyval.node) = create_for_node((yyvsp[-4].node), (yyvsp[-3].node), NULL, (yyvsp[0].node)); }
#line 2081 "parser.c"
    break;

  case 74: /* iteration_statement: T_FOR T_LPAREN declaration expression T_SEMICOLON expression T_RPAREN statement  */
#line 238 "parser.y"
                                                                                      { (yyval.node) = create_for_node((yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2087 "parser.c"
    break;

  case 75: /* jump_statement: T_GOTO T_IDENTIFIER T_SEMICOLON  */
#line 242 "parser.y"
                                    { (yyval.node) = create_goto_node((yyvsp[-1].string_value)); }
#line 2093 "parser.c"
    break;

  case 76: /* jump_statement: T_CONTINUE T_SEMICOLON  */
#line 243 "parser.y"
                             { (yyval.node) = create_continue_node(); }
#line 2099 "parser.c"
    break;

  case 77: /* jump_statement: T_BREAK T_SEMICOLON  */
#line 244 "parser.y"
                          { (yyval.node) = create_break_node(); }
#line 2105 "parser.c"
    break;

  case 78: /* jump_statement: T_RETURN T_SEMICOLON  */
#line 245 "parser.y"
                           { (yyval.node) = create_return_node(NULL); }
#line 2111 "parser.c"
    break;

  case 79: /* jump_statement: T_RETURN expression T_SEMICOLON  */
#line 246 "parser.y"
                                      { (yyval.node) = create_return_node((yyvsp[-1].node)); }
#line 2117 "parser.c"
    break;

  case 80: /* expression: assignment_expression  */
#line 250 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2123 "parser.c"
    break;

  case 81: /* expression: expression T_COMMA assignment_expression  */
#line 251 "parser.y"
                                               { (yyval.node) = create_binary_op_node(T_COMMA, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2129 "parser.c"
    break;

  case 82: /* assignment_expression: conditional_expression  */
#line 255 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2135 "parser.c"
    break;

  case 83: /* assignment_expression: unary_expression T_ASSIGN assignment_expression  */
#line 256 "parser.y"
                                                      { (yyval.node) = create_assign_node((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2141 "parser.c"
    break;

  case 84: /* assignment_expression: unary_expression T_ADD_ASSIGN assignment_expression  */
#line 257 "parser.y"
                                                          { (yyval.node) = create_assign_node((yyvsp[-2].node), create_binary_op_node(T_ADD, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 2147 "parser.c"
    break;

  case 85: /* assignment_expression: unary_expression T_SUB_ASSIGN assignment_expression  */
#line 258 "parser.y"
                                                          { (yyval.node) = create_assign_node((yyvsp[-2].node), create_binary_op_node(T_SUB, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 2153 "parser.c"
    break;

  case 86: /* assignment_expression: unary_expression T_MUL_ASSIGN assignment_expression  */
#line 259 "parser.y"
                                                          { (yyval.node) = create_assign_node((yyvsp[-2].node), create_binary_op_node(T_MUL, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 2159 "parser.c"
    break;

  case 87: /* assignment_expression: unary_expression T_DIV_ASSIGN assignment_expression  */
#line 260 "parser.y"
                                                          { (yyval.node) = create_assign_node((yyvsp[-2].node), create_binary_op_node(T_DIV, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 2165 "parser.c"
    break;

  case 88: /* assignment_expression: unary_expression T_MOD_ASSIGN assignment_expression  */
#line 261 "parser.y"
                                                          { (yyval.node) = create_assign_node((yyvsp[-2].node), create_binary_op_node(T_MOD, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 2171 "parser.c"
    break;

  case 89: /* conditional_expression: logical_or_expression  */
#line 265 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2177 "parser.c"
    break;

  case 90: /* conditional_expression: logical_or_expression T_QUESTION expression T_COLON conditional_expression  */
#line 266 "parser.y"
                                                                                 { (yyval.node) = create_ternary_op_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2183 "parser.c"
    break;

  case 91: /* logical_or_expression: logical_and_expression  */
#line 270 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2189 "parser.c"
    break;

  case 92: /* logical_or_expression: logical_or_expression T_LOGICAL_OR logical_and_expression  */
#line 271 "parser.y"
                                                                { (yyval.node) = create_binary_op_node(T_LOGICAL_OR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2195 "parser.c"
    break;

  case 93: /* logical_and_expression: inclusive_or_expression  */
#line 275 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2201 "parser.c"
    break;

  case 94: /* logical_and_expression: logical_and_expression T_LOGICAL_AND inclusive_or_expression  */
#line 276 "parser.y"
                                                                   { (yyval.node) = create_binary_op_node(T_LOGICAL_AND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2207 "parser.c"
    break;

  case 95: /* inclusive_or_expression: exclusive_or_expression  */
#line 280 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2213 "parser.c"
    break;

  case 96: /* inclusive_or_expression: inclusive_or_expression T_BITWISE_OR exclusive_or_expression  */
#line 281 "parser.y"
                                                                   { (yyval.node) = create_binary_op_node(T_BITWISE_OR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2219 "parser.c"
    break;

  case 97: /* exclusive_or_expression: and_expression  */
#line 285 "parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2225 "parser.c"
    break;

  case 98: /* exclusive_or_expression: exclusive_or_expression T_BITWISE_XOR and_expression  */
#line 286 "parser.y"
                                                           { (yyval.node) = create_binary_op_node(T_BITWISE_XOR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2231 "parser.c"
    break;

  case 99: /* and_expression: equality_expression  */
#line 290 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2237 "parser.c"
    break;

  case 100: /* and_expression: and_expression T_BITWISE_AND equality_expression  */
#line 291 "parser.y"
                                                       { (yyval.node) = create_binary_op_node(T_BITWISE_AND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2243 "parser.c"
    break;

  case 101: /* equality_expression: relational_expression  */
#line 295 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2249 "parser.c"
    break;

  case 102: /* equality_expression: equality_expression T_EQ relational_expression  */
#line 296 "parser.y"
                                                     { (yyval.node) = create_binary_op_node(T_EQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2255 "parser.c"
    break;

  case 103: /* equality_expression: equality_expression T_NE relational_expression  */
#line 297 "parser.y"
                                                     { (yyval.node) = create_binary_op_node(T_NE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2261 "parser.c"
    break;

  case 104: /* relational_expression: shift_expression  */
#line 301 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2267 "parser.c"
    break;

  case 105: /* relational_expression: relational_expression T_LT shift_expression  */
#line 302 "parser.y"
                                                  { (yyval.node) = create_binary_op_node(T_LT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2273 "parser.c"
    break;

  case 106: /* relational_expression: relational_expression T_GT shift_expression  */
#line 303 "parser.y"
                                                  { (yyval.node) = create_binary_op_node(T_GT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2279 "parser.c"
    break;

  case 107: /* relational_expression: relational_expression T_LE shift_expression  */
#line 304 "parser.y"
                                                  { (yyval.node) = create_binary_op_node(T_LE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2285 "parser.c"
    break;

  case 108: /* relational_expression: relational_expression T_GE shift_expression  */
#line 305 "parser.y"
                                                  { (yyval.node) = create_binary_op_node(T_GE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2291 "parser.c"
    break;

  case 109: /* shift_expression: additive_expression  */
#line 309 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2297 "parser.c"
    break;

  case 110: /* shift_expression: shift_expression T_LSHIFT additive_expression  */
#line 310 "parser.y"
                                                    { (yyval.node) = create_binary_op_node(T_LSHIFT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2303 "parser.c"
    break;

  case 111: /* shift_expression: shift_expression T_RSHIFT additive_expression  */
#line 311 "parser.y"
                                                    { (yyval.node) = create_binary_op_node(T_RSHIFT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2309 "parser.c"
    break;

  case 112: /* additive_expression: multiplicative_expression  */
#line 315 "parser.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 2315 "parser.c"
    break;

  case 113: /* additive_expression: additive_expression T_ADD multiplicative_expression  */
#line 316 "parser.y"
                                                          { (yyval.node) = create_binary_op_node(T_ADD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2321 "parser.c"
    break;

  case 114: /* additive_expression: additive_expression T_SUB multiplicative_expression  */
#line 317 "parser.y"
                                                          { (yyval.node) = create_binary_op_node(T_SUB, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2327 "parser.c"
    break;

  case 115: /* multiplicative_expression: cast_expression  */
#line 321 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2333 "parser.c"
    break;

  case 116: /* multiplicative_expression: multiplicative_expression T_MUL cast_expression  */
#line 322 "parser.y"
                                                      { (yyval.node) = create_binary_op_node(T_MUL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2339 "parser.c"
    break;

  case 117: /* multiplicative_expression: multiplicative_expression T_DIV cast_expression  */
#line 323 "parser.y"
                                                      { (yyval.node) = create_binary_op_node(T_DIV, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2345 "parser.c"
    break;

  case 118: /* multiplicative_expression: multiplicative_expression T_MOD cast_expression  */
#line 324 "parser.y"
                                                      { (yyval.node) = create_binary_op_node(T_MOD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2351 "parser.c"
    break;

  case 119: /* cast_expression: unary_expression  */
#line 328 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2357 "parser.c"
    break;

  case 120: /* cast_expression: T_LPAREN type_name T_RPAREN cast_expression  */
#line 329 "parser.y"
                                                  { (yyval.node) = create_cast_node((yyvsp[-2].type), (yyvsp[0].node)); }
#line 2363 "parser.c"
    break;

  case 121: /* unary_expression: postfix_expression  */
#line 333 "parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2369 "parser.c"
    break;

  case 122: /* unary_expression: T_INC unary_expression  */
#line 334 "parser.y"
                             { (yyval.node) = create_unary_op_node(T_INC, (yyvsp[0].node)); }
#line 2375 "parser.c"
    break;

  case 123: /* unary_expression: T_DEC unary_expression  */
#line 335 "parser.y"
                             { (yyval.node) = create_unary_op_node(T_DEC, (yyvsp[0].node)); }
#line 2381 "parser.c"
    break;

  case 124: /* unary_expression: T_BITWISE_AND cast_expression  */
#line 336 "parser.y"
                                    { (yyval.node) = create_unary_op_node(T_BITWISE_AND, (yyvsp[0].node)); }
#line 2387 "parser.c"
    break;

  case 125: /* unary_expression: T_MUL cast_expression  */
#line 337 "parser.y"
                            { (yyval.node) = create_unary_op_node(T_MUL, (yyvsp[0].node)); }
#line 2393 "parser.c"
    break;

  case 126: /* unary_expression: T_ADD cast_expression  */
#line 338 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2399 "parser.c"
    break;

  case 127: /* unary_expression: T_SUB cast_expression  */
#line 339 "parser.y"
                            { (yyval.node) = create_unary_op_node(T_SUB, (yyvsp[0].node)); }
#line 2405 "parser.c"
    break;

  case 128: /* unary_expression: T_BITWISE_NOT cast_expression  */
#line 340 "parser.y"
                                    { (yyval.node) = create_unary_op_node(T_BITWISE_NOT, (yyvsp[0].node)); }
#line 2411 "parser.c"
    break;

  case 129: /* unary_expression: T_LOGICAL_NOT cast_expression  */
#line 341 "parser.y"
                                    { (yyval.node) = create_unary_op_node(T_LOGICAL_NOT, (yyvsp[0].node)); }
#line 2417 "parser.c"
    break;

  case 130: /* unary_expression: T_SIZEOF unary_expression  */
#line 342 "parser.y"
                                { (yyval.node) = create_sizeof_node(NULL); }
#line 2423 "parser.c"
    break;

  case 131: /* unary_expression: T_SIZEOF T_LPAREN type_name T_RPAREN  */
#line 343 "parser.y"
                                           { (yyval.node) = create_sizeof_node((yyvsp[-1].type)); }
#line 2429 "parser.c"
    break;

  case 132: /* postfix_expression: primary_expression  */
#line 347 "parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2435 "parser.c"
    break;

  case 133: /* postfix_expression: postfix_expression T_LBRACKET expression T_RBRACKET  */
#line 348 "parser.y"
                                                          { (yyval.node) = create_array_access_node((yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2441 "parser.c"
    break;

  case 134: /* postfix_expression: postfix_expression T_LPAREN T_RPAREN  */
#line 349 "parser.y"
                                           { (yyval.node) = create_func_call_node(NULL, NULL); }
#line 2447 "parser.c"
    break;

  case 135: /* postfix_expression: postfix_expression T_LPAREN argument_expression_list T_RPAREN  */
#line 350 "parser.y"
                                                                    { (yyval.node) = create_func_call_node(NULL, (yyvsp[-1].node)); }
#line 2453 "parser.c"
    break;

  case 136: /* postfix_expression: postfix_expression T_DOT T_IDENTIFIER  */
#line 351 "parser.y"
                                            { (yyval.node) = create_member_access_node((yyvsp[-2].node), (yyvsp[0].string_value)); }
#line 2459 "parser.c"
    break;

  case 137: /* postfix_expression: postfix_expression T_ARROW T_IDENTIFIER  */
#line 352 "parser.y"
                                              { (yyval.node) = create_member_access_node((yyvsp[-2].node), (yyvsp[0].string_value)); }
#line 2465 "parser.c"
    break;

  case 138: /* postfix_expression: postfix_expression T_INC  */
#line 353 "parser.y"
                               { (yyval.node) = create_unary_op_node(T_INC, (yyvsp[-1].node)); }
#line 2471 "parser.c"
    break;

  case 139: /* postfix_expression: postfix_expression T_DEC  */
#line 354 "parser.y"
                               { (yyval.node) = create_unary_op_node(T_DEC, (yyvsp[-1].node)); }
#line 2477 "parser.c"
    break;

  case 140: /* primary_expression: T_IDENTIFIER  */
#line 358 "parser.y"
                 { (yyval.node) = create_variable_node((yyvsp[0].string_value)); }
#line 2483 "parser.c"
    break;

  case 141: /* primary_expression: T_INTEGER  */
#line 359 "parser.y"
                { (yyval.node) = create_integer_node((yyvsp[0].integer_value)); }
#line 2489 "parser.c"
    break;

  case 142: /* primary_expression: T_FLOAT_LITERAL  */
#line 360 "parser.y"
                      { (yyval.node) = create_float_node((yyvsp[0].string_value)); }
#line 2495 "parser.c"
    break;

  case 143: /* primary_expression: T_CHAR_LITERAL  */
#line 361 "parser.y"
                     { (yyval.node) = create_char_node((yyvsp[0].string_value)); }
#line 2501 "parser.c"
    break;

  case 144: /* primary_expression: T_STRING_LITERAL  */
#line 362 "parser.y"
                       { (yyval.node) = create_string_literal_node((yyvsp[0].string_value)); }
#line 2507 "parser.c"
    break;

  case 145: /* primary_expression: T_LPAREN expression T_RPAREN  */
#line 363 "parser.y"
                                   { (yyval.node) = (yyvsp[-1].node); }
#line 2513 "parser.c"
    break;

  case 146: /* argument_expression_list: assignment_expression  */
#line 367 "parser.y"
                          { (yyval.node) = create_arg_list_node(); add_arg_to_list((yyval.node), (yyvsp[0].node)); }
#line 2519 "parser.c"
    break;

  case 147: /* argument_expression_list: argument_expression_list T_COMMA assignment_expression  */
#line 368 "parser.y"
                                                             { add_arg_to_list((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2525 "parser.c"
    break;

  case 148: /* initializer: assignment_expression  */
#line 372 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2531 "parser.c"
    break;

  case 149: /* initializer: T_LBRACE initializer_list T_RBRACE  */
#line 373 "parser.y"
                                         { (yyval.node) = (yyvsp[-1].node); }
#line 2537 "parser.c"
    break;

  case 150: /* initializer: T_LBRACE initializer_list T_COMMA T_RBRACE  */
#line 374 "parser.y"
                                                 { (yyval.node) = (yyvsp[-2].node); }
#line 2543 "parser.c"
    break;

  case 151: /* initializer_list: initializer  */
#line 378 "parser.y"
                { (yyval.node) = create_initializer_list_node(); add_initializer_to_list((yyval.node), (yyvsp[0].node)); }
#line 2549 "parser.c"
    break;

  case 152: /* initializer_list: initializer_list T_COMMA initializer  */
#line 379 "parser.y"
                                           { add_initializer_to_list((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2555 "parser.c"
    break;

  case 153: /* type_specifier: T_VOID  */
#line 383 "parser.y"
           { (yyval.type) = create_type(TYPE_VOID); }
#line 2561 "parser.c"
    break;

  case 154: /* type_specifier: T_CHAR  */
#line 384 "parser.y"
             { (yyval.type) = create_type(TYPE_CHAR); }
#line 2567 "parser.c"
    break;

  case 155: /* type_specifier: T_SHORT  */
#line 385 "parser.y"
              { (yyval.type) = create_type(TYPE_SHORT); }
#line 2573 "parser.c"
    break;

  case 156: /* type_specifier: T_INT  */
#line 386 "parser.y"
            { (yyval.type) = create_type(TYPE_INT); }
#line 2579 "parser.c"
    break;

  case 157: /* type_specifier: T_LONG  */
#line 387 "parser.y"
             { (yyval.type) = create_type(TYPE_LONG); }
#line 2585 "parser.c"
    break;

  case 158: /* type_specifier: T_FLOAT  */
#line 388 "parser.y"
              { (yyval.type) = create_type(TYPE_FLOAT); }
#line 2591 "parser.c"
    break;

  case 159: /* type_specifier: T_DOUBLE  */
#line 389 "parser.y"
               { (yyval.type) = create_type(TYPE_DOUBLE); }
#line 2597 "parser.c"
    break;

  case 160: /* type_specifier: T_SIGNED  */
#line 390 "parser.y"
               { (yyval.type) = create_type(TYPE_INT); (yyval.type)->is_signed = 1; }
#line 2603 "parser.c"
    break;

  case 161: /* type_specifier: T_UNSIGNED  */
#line 391 "parser.y"
                 { (yyval.type) = create_type(TYPE_INT); (yyval.type)->is_unsigned = 1; }
#line 2609 "parser.c"
    break;

  case 162: /* type_specifier: struct_specifier  */
#line 392 "parser.y"
                       { (yyval.type) = create_type_from_specifier((yyvsp[0].node)); }
#line 2615 "parser.c"
    break;

  case 163: /* type_specifier: union_specifier  */
#line 393 "parser.y"
                      { (yyval.type) = create_type_from_union_specifier((yyvsp[0].node)); }
#line 2621 "parser.c"
    break;

  case 164: /* type_specifier: enum_specifier  */
#line 394 "parser.y"
                     { (yyval.type) = create_type_from_enum_specifier((yyvsp[0].node)); }
#line 2627 "parser.c"
    break;

  case 165: /* type_specifier: T_TYPENAME  */
#line 395 "parser.y"
                 { (yyval.type) = create_type(TYPE_TYPEDEF); (yyval.type)->name = (yyvsp[0].string_value); }
#line 2633 "parser.c"
    break;

  case 166: /* struct_specifier: T_STRUCT T_IDENTIFIER T_LBRACE struct_declaration_list T_RBRACE  */
#line 399 "parser.y"
                                                                    { (yyval.node) = create_struct_def_node((yyvsp[-3].string_value), (yyvsp[-1].node)); }
#line 2639 "parser.c"
    break;

  case 167: /* struct_specifier: T_STRUCT T_LBRACE struct_declaration_list T_RBRACE  */
#line 400 "parser.y"
                                                         { (yyval.node) = create_struct_def_node(NULL, (yyvsp[-1].node)); }
#line 2645 "parser.c"
    break;

  case 168: /* struct_specifier: T_STRUCT T_IDENTIFIER  */
#line 401 "parser.y"
                            { (yyval.node) = create_struct_ref_node((yyvsp[0].string_value)); }
#line 2651 "parser.c"
    break;

  case 169: /* union_specifier: T_UNION T_IDENTIFIER T_LBRACE struct_declaration_list T_RBRACE  */
#line 405 "parser.y"
                                                                   { (yyval.node) = create_union_def_node((yyvsp[-3].string_value), (yyvsp[-1].node)); }
#line 2657 "parser.c"
    break;

  case 170: /* union_specifier: T_UNION T_LBRACE struct_declaration_list T_RBRACE  */
#line 406 "parser.y"
                                                        { (yyval.node) = create_union_def_node(NULL, (yyvsp[-1].node)); }
#line 2663 "parser.c"
    break;

  case 171: /* union_specifier: T_UNION T_IDENTIFIER  */
#line 407 "parser.y"
                           { (yyval.node) = create_union_ref_node((yyvsp[0].string_value)); }
#line 2669 "parser.c"
    break;

  case 172: /* enum_specifier: T_ENUM T_IDENTIFIER T_LBRACE enumerator_list T_RBRACE  */
#line 411 "parser.y"
                                                          { (yyval.node) = create_enum_specifier_node((yyvsp[-3].string_value), (yyvsp[-1].node)); }
#line 2675 "parser.c"
    break;

  case 173: /* enum_specifier: T_ENUM T_LBRACE enumerator_list T_RBRACE  */
#line 412 "parser.y"
                                               { (yyval.node) = create_enum_specifier_node(NULL, (yyvsp[-1].node)); }
#line 2681 "parser.c"
    break;

  case 174: /* enum_specifier: T_ENUM T_IDENTIFIER  */
#line 413 "parser.y"
                          { (yyval.node) = create_enum_specifier_node((yyvsp[0].string_value), NULL); }
#line 2687 "parser.c"
    break;

  case 175: /* enumerator_list: enumerator  */
#line 417 "parser.y"
               { (yyval.node) = create_statement_list_node(); add_statement_to_list((yyval.node), (yyvsp[0].node)); }
#line 2693 "parser.c"
    break;

  case 176: /* enumerator_list: enumerator_list T_COMMA enumerator  */
#line 418 "parser.y"
                                         { add_statement_to_list((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2699 "parser.c"
    break;

  case 177: /* enumerator: T_IDENTIFIER  */
#line 422 "parser.y"
                 { (yyval.node) = create_enumerator_node((yyvsp[0].string_value), NULL); }
#line 2705 "parser.c"
    break;

  case 178: /* enumerator: T_IDENTIFIER T_ASSIGN conditional_expression  */
#line 423 "parser.y"
                                                   { (yyval.node) = create_enumerator_node((yyvsp[-2].string_value), (yyvsp[0].node)); }
#line 2711 "parser.c"
    break;

  case 179: /* struct_declaration_list: struct_declaration  */
#line 427 "parser.y"
                       { (yyval.node) = create_statement_list_node(); add_statement_to_list((yyval.node), (yyvsp[0].node)); }
#line 2717 "parser.c"
    break;

  case 180: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 428 "parser.y"
                                                 { add_statement_to_list((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2723 "parser.c"
    break;

  case 181: /* struct_declaration: declaration_specifiers declarator_list T_SEMICOLON  */
#line 432 "parser.y"
                                                       { (yyval.node) = create_decl_list_node((yyvsp[-2].type), (yyvsp[-1].node)); }
#line 2729 "parser.c"
    break;

  case 182: /* declarator_list: declarator  */
#line 436 "parser.y"
               { (yyval.node) = create_statement_list_node(); add_statement_to_list((yyval.node), (yyvsp[0].node)); }
#line 2735 "parser.c"
    break;

  case 183: /* declarator_list: declarator_list T_COMMA declarator  */
#line 437 "parser.y"
                                         { add_statement_to_list((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2741 "parser.c"
    break;


#line 2745 "parser.c"

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

#line 440 "parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Parse error on line %d: %s near '%s'\n", yylineno, s, yytext);
}
