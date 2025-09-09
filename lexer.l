%{
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "symtab.h"
extern SymbolTable *symbol_table;
int yylineno;
%}

%option yylineno

%x C_COMMENT

%%

"//".*      ; /* Ignore single-line comments */
"/*"        { BEGIN(C_COMMENT); }
<C_COMMENT>"*/" { BEGIN(INITIAL); }
<C_COMMENT>.    ;
<C_COMMENT>\n   ;

"switch"    { return T_SWITCH; }
"case"      { return T_CASE; }
"default"   { return T_DEFAULT; }
"break"     { return T_BREAK; }
"if"        { return T_IF; }
"else"      { return T_ELSE; }
"while"     { return T_WHILE; }
"do"        { return T_DO; }
"for"       { return T_FOR; }
"continue"  { return T_CONTINUE; }
"goto"      { return T_GOTO; }
"struct"    { return T_STRUCT; }
"union"     { return T_UNION; }
"enum"      { return T_ENUM; }
"char"      { return T_CHAR; }
"float"     { return T_FLOAT; }
"double"    { return T_DOUBLE; }
"void"      { return T_VOID; }
"short"     { return T_SHORT; }
"long"      { return T_LONG; }
"signed"    { return T_SIGNED; }
"unsigned"  { return T_UNSIGNED; }
"typedef"   { return T_TYPEDEF; }
"sizeof"    { return T_SIZEOF; }
"const"     { return T_CONST; }
"static"    { return T_STATIC; }
"extern"    { return T_EXTERN; }
"volatile"  { return T_VOLATILE; }
"inline"    { return T_INLINE; }
"int"       { return T_INT; }
"bool"      { return T_BOOL; }
"return"    { return T_RETURN; }
"=="        { return T_EQ; }
"!="        { return T_NE; }
">"         { return T_GT; }
"<"         { return T_LT; }
">="        { return T_GE; }
"<="        { return T_LE; }
"&&"        { return T_LOGICAL_AND; }
"||"        { return T_LOGICAL_OR; }
"!"         { return T_LOGICAL_NOT; }
"&"         { return T_BITWISE_AND; }
"|"         { return T_BITWISE_OR; }
"^"         { return T_BITWISE_XOR; }
"~"         { return T_BITWISE_NOT; }
"<<"        { return T_LSHIFT; }
">>"        { return T_RSHIFT; }
"+"         { return T_ADD; }
"-"         { return T_SUB; }
"*"         { return T_MUL; }
"/"         { return T_DIV; }
"%"         { return T_MOD; }
"++"        { return T_INC; }
"--"        { return T_DEC; }
"="         { return T_ASSIGN; }
"+="        { return T_ADD_ASSIGN; }
"-="        { return T_SUB_ASSIGN; }
"*="        { return T_MUL_ASSIGN; }
"/="        { return T_DIV_ASSIGN; }
"%="        { return T_MOD_ASSIGN; }
"->"        { return T_ARROW; }
":"         { return T_COLON; }
[0-9]+\.[0-9]+([fF])? { yylval.string_value = strdup(yytext); return T_FLOAT_LITERAL; }
\"[^"]*\"  { yylval.string_value = strdup(yytext); return T_STRING_LITERAL; }
'[^']'      { yylval.string_value = strdup(yytext); return T_CHAR_LITERAL; }
[0-9]+      { yylval.integer_value = atoi(yytext); return T_INTEGER; }
";"         { return T_SEMICOLON; }
"("         { return T_LPAREN; }
")"         { return T_RPAREN; }
"{"         { return T_LBRACE; }
"}"         { return T_RBRACE; }
","         { return T_COMMA; }
"["         { return T_LBRACKET; }
"]"         { return T_RBRACKET; }
"."         { return T_DOT; }
"?"         { return T_QUESTION; }
^#.*        ; /* ignore preprocessor directives */
[ \t\n]+    ; /* ignore whitespace */
[a-zA-Z_][a-zA-Z0-9_]* {
    if (is_typedef_name(symbol_table, yytext)) {
        yylval.string_value = strdup(yytext);
        return T_TYPENAME;
    }
    yylval.string_value = strdup(yytext);
    return T_IDENTIFIER;
}
.           { /* ignore other characters */ }


%%

int yywrap(void) {
    return 1;
}
