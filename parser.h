/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_IDENTIFIER = 258,            /* T_IDENTIFIER  */
    T_TYPENAME = 259,              /* T_TYPENAME  */
    T_INTEGER = 260,               /* T_INTEGER  */
    T_FLOAT_LITERAL = 261,         /* T_FLOAT_LITERAL  */
    T_CHAR_LITERAL = 262,          /* T_CHAR_LITERAL  */
    T_STRING_LITERAL = 263,        /* T_STRING_LITERAL  */
    T_INT = 264,                   /* T_INT  */
    T_RETURN = 265,                /* T_RETURN  */
    T_IF = 266,                    /* T_IF  */
    T_ELSE = 267,                  /* T_ELSE  */
    T_WHILE = 268,                 /* T_WHILE  */
    T_FOR = 269,                   /* T_FOR  */
    T_SWITCH = 270,                /* T_SWITCH  */
    T_CASE = 271,                  /* T_CASE  */
    T_DEFAULT = 272,               /* T_DEFAULT  */
    T_BREAK = 273,                 /* T_BREAK  */
    T_DO = 274,                    /* T_DO  */
    T_CONTINUE = 275,              /* T_CONTINUE  */
    T_GOTO = 276,                  /* T_GOTO  */
    T_STRUCT = 277,                /* T_STRUCT  */
    T_UNION = 278,                 /* T_UNION  */
    T_ENUM = 279,                  /* T_ENUM  */
    T_CHAR = 280,                  /* T_CHAR  */
    T_FLOAT = 281,                 /* T_FLOAT  */
    T_DOUBLE = 282,                /* T_DOUBLE  */
    T_VOID = 283,                  /* T_VOID  */
    T_SHORT = 284,                 /* T_SHORT  */
    T_LONG = 285,                  /* T_LONG  */
    T_SIGNED = 286,                /* T_SIGNED  */
    T_UNSIGNED = 287,              /* T_UNSIGNED  */
    T_TYPEDEF = 288,               /* T_TYPEDEF  */
    T_SIZEOF = 289,                /* T_SIZEOF  */
    T_CONST = 290,                 /* T_CONST  */
    T_STATIC = 291,                /* T_STATIC  */
    T_EXTERN = 292,                /* T_EXTERN  */
    T_VOLATILE = 293,              /* T_VOLATILE  */
    T_INLINE = 294,                /* T_INLINE  */
    T_SEMICOLON = 295,             /* T_SEMICOLON  */
    T_LPAREN = 296,                /* T_LPAREN  */
    T_RPAREN = 297,                /* T_RPAREN  */
    T_LBRACE = 298,                /* T_LBRACE  */
    T_RBRACE = 299,                /* T_RBRACE  */
    T_COMMA = 300,                 /* T_COMMA  */
    T_LBRACKET = 301,              /* T_LBRACKET  */
    T_RBRACKET = 302,              /* T_RBRACKET  */
    T_DOT = 303,                   /* T_DOT  */
    T_ARROW = 304,                 /* T_ARROW  */
    T_INC = 305,                   /* T_INC  */
    T_DEC = 306,                   /* T_DEC  */
    T_LOGICAL_NOT = 307,           /* T_LOGICAL_NOT  */
    T_BITWISE_NOT = 308,           /* T_BITWISE_NOT  */
    T_LOGICAL_AND = 309,           /* T_LOGICAL_AND  */
    T_LOGICAL_OR = 310,            /* T_LOGICAL_OR  */
    T_BITWISE_AND = 311,           /* T_BITWISE_AND  */
    T_BITWISE_OR = 312,            /* T_BITWISE_OR  */
    T_BITWISE_XOR = 313,           /* T_BITWISE_XOR  */
    T_LSHIFT = 314,                /* T_LSHIFT  */
    T_RSHIFT = 315,                /* T_RSHIFT  */
    T_ASSIGN = 316,                /* T_ASSIGN  */
    T_ADD_ASSIGN = 317,            /* T_ADD_ASSIGN  */
    T_SUB_ASSIGN = 318,            /* T_SUB_ASSIGN  */
    T_MUL_ASSIGN = 319,            /* T_MUL_ASSIGN  */
    T_DIV_ASSIGN = 320,            /* T_DIV_ASSIGN  */
    T_MOD_ASSIGN = 321,            /* T_MOD_ASSIGN  */
    T_EQ = 322,                    /* T_EQ  */
    T_NE = 323,                    /* T_NE  */
    T_GT = 324,                    /* T_GT  */
    T_GE = 325,                    /* T_GE  */
    T_LT = 326,                    /* T_LT  */
    T_LE = 327,                    /* T_LE  */
    T_ADD = 328,                   /* T_ADD  */
    T_SUB = 329,                   /* T_SUB  */
    T_MUL = 330,                   /* T_MUL  */
    T_DIV = 331,                   /* T_DIV  */
    T_MOD = 332,                   /* T_MOD  */
    T_QUESTION = 333,              /* T_QUESTION  */
    T_COLON = 334,                 /* T_COLON  */
    T_IFX = 335                    /* T_IFX  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 15 "parser.y"

    int integer_value;
    char *string_value;
    struct ASTNode *node;
    struct Type *type;

#line 151 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_H_INCLUDED  */
