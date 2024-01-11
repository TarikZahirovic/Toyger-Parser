//Token definitions for Toyger
//Tarik Zahirovic
//G01285530

#ifndef TOKENS_H
#define TOKENS_H

//Keywords
#define LET 1
#define IN 2
#define END 3
#define VAR 4
#define FUNCTION 5
#define PRINT_INT 6
#define PRINT_STRING 7
#define GET_INT 8
#define RETURN 9
#define IF 10
#define THEN 11
#define ELSE 12
#define FOR 13
#define TO 14
#define DO 15
#define INT 16
#define STRING_K 17
#define VOID 18

//Punctuation Elements
#define OPEN_P 19
#define CLOSE_P 20
#define COLON 21
#define COMMA 22
#define EQUALS 23
#define SEMICOL 24

//Operators (arithmetic)
#define ASSIGN 25
#define ADD 26
#define SUB 27
#define MULT 28
#define DIV 29

//Operators (comparison)
#define COMP_EQ 30
#define LESS 31
#define LESS_EQ 32
#define GREATER 33
#define GREATER_EQ 34
#define NOT_EQ 35

//Identifiers, numbers, strings
#define ID 36
#define NUMBER 37
#define STRING 38

//Comments are not reported to parser

#endif /*TOKENS_H*/
