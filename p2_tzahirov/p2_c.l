/*CS440-P2: Toyger Scanner
Tarik Zahirovic
G01285530*/
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"

//Tracking variables
int declaring = 0; //Boolean whether in declarations stage
int declaring_global = 0; //Bool whether declaring a global variable
int declaring_func = 0; //Bool whether declaring a function

int globals_count = 0; //Number of global variables
int func_count = 0; //Number of functions
int comm_count = 0; //Number of comments
int lines = 1; //Line counter

//Global variable and function arrays
char *globals[64];
char *functions[64];
int globals_lines[64];
int func_lines[64];

%}

%option never-interactive

%%
	/*Keywords*/
"let" {declaring = 1; return(LET);}

"in" {return IN; declaring = 0;
	declaring_global = 0; declaring_func = 0;}

"end" {return END;}

"var" {	if (declaring) declaring_global = 1;
	return VAR; }

"function" {if (declaring) declaring_func = 1; 
	return FUNCTION;}

"printint" {return PRINT_INT;}

"printstring" {return PRINT_STRING;}

"getint" {return GET_INT;}

"return" {return RETURN;}

"if" {return IF;}

"then" {return THEN;}

"else" {return ELSE;}

"for" {return FOR;}

"to" {return TO;}

"do" {return DO;}

"int" {return INT;}

"string" {return STRING_K;}

"void" {return VOID;}

	/*Punctuation Elements*/

"(" {return OPEN_P;}

")" {return CLOSE_P;}

":" {return COLON;}

"," {return COMMA;}

"=" {return EQUALS;}

";" {return SEMICOL;}

	/*Operators (arithmetic)*/

":=" {return ASSIGN;}

"+" {return ADD;}

"-" {return SUB;}

"*" {return MULT;}

"/" {return DIV;}

	/*Operators (comparison)*/

"==" {return COMP_EQ;}

"<" {return LESS;}

"<=" {return LESS_EQ;}

">" {return GREATER;}

">=" {return GREATER_EQ;}

"<>" {return NOT_EQ;}

	/*Everything Else*/

[a-zA-Z][0-9a-zA-Z_]* { /*Identifiers - global variable and function names stored*/
	if (declaring_global) {
		globals[globals_count] = (char*)malloc((yyleng) * sizeof(char));
		strcpy(globals[globals_count], yytext);
		globals_lines[globals_count] = lines; 
		globals_count++;
		declaring_global = 0;
	}
	else if (declaring_func) {
		functions[func_count] = (char*)malloc((yyleng) * sizeof(char));
		strcpy(functions[func_count], yytext);
		func_lines[func_count] = lines;
		func_count++;
		declaring_func = 0;
	}
	return ID;}

[1-9][0-9]*|0 {return NUMBER;} /*Numbers (integers)*/

"\"".*"\"" {return STRING;} /*Strings*/

"//".*\n {comm_count++; lines++;} /*Comments (not reported, just counted)*/

" "|\t {;} /*Whitespace (ignored)*/

\n {lines++;} /*For line counting, otherwise ignored*/

. {fprintf(stderr, "Lexical Error: line %d\n", lines); exit(1);}

%%
