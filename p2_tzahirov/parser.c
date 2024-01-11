//CS440-P2: Recursive Descent Parser
//Tarik Zahirovic
//G01285530
#include "lex.yy.c"

//Lookahead variable
int lookahead = 0;

//Print Strings
const char *accept_msg = "Input Accepted\n";

//Function declarations
void decs(); void dec(); void var_dec(); void type(); void func_dec();
void func_params_branch(); void func_tail(); void params();
void param_loop(); void param(); void statements();
void statement_loop(); void statement(); void id_assign_branch();
void assign_branch(); void id_list_branch(); void return_branch();
void expr_parentheses(); void expr(); void term_branch(); void term();
void factor_branch(); void factor(); void factor_list_branch();
void expr_list(); void list_branch();

//Sytax Error Print statement
void syntax_error(int currentLine) {
	fprintf(stderr, "Syntax Error: line %d\n", currentLine);
	//fprintf(stderr, "%d\n", lookahead); //For testing
	exit(1);
}

//Match Function, compares current lookahead to the expected token it was given
//If match: advance lookahead
//If not match: report syntax error
void match(int expected_token) {
	//fprintf(stderr, "%d ", lookahead); //For testing
	if (lookahead == expected_token) { 
		lookahead = yylex();
		return;
	}
	else syntax_error(lines);
}

//Star symbol prog -> LET decs() IN statements() END
//All-caps and symbols denote terminals, functions are non-terminals
void prog() {
	match(1); decs(); match(2); statements(); match(3);}

// decs -> dec() decs() | e
// Will be using 'e' in place of epsilon to denote empty string
void decs() {
	if (lookahead == 4 || lookahead == 5) {dec(); decs();}}

//dec -> var_dec | func_dec
void dec() {
	if (lookahead == 4) var_dec();
	if (lookahead == 5) func_dec();}

//var_dec -> VAR ID : type()
void var_dec() {
	match(4); match(36); match(21); type();}

//type -> INT | STRING | VOID
void type() {
	if (lookahead == 16) match(16);
	else if (lookahead == 17) match(17);
	else if (lookahead == 18) match(18);
	else syntax_error(lines);
}

//func_dec -> FUNCTION ID func_params_branch()
void func_dec() {
	match(5); match(36); match(19); func_params_branch();}

//func_params_branch -> params func_tail() | func_tail()
void func_params_branch() {
	if (lookahead == 36) {params(); func_tail();}
	else if (lookahead == 20) func_tail();
	else syntax_error(lines);
}

//func_tail -> ) : type() = statements() END
void func_tail() {
	match(20); match(21); type(); match(23); statements(); match(3);}

//params -> param() param_loop();
void params() {
	param(); param_loop();}

//param_loop -> , param() param_loop() | e
void param_loop() {
	if (lookahead == 22) {match(22); param(); param_loop();}}

//param -> ID : type()
void param() {
	match(36); match(21); type();}

//statements -> statement() statement_loop()
void statements() {
	statement(); statement_loop();}

//statement_loop -> ; statement() statement_loop() | e
void statement_loop() {
	if (lookahead == 24) {match(24); statement(); statement_loop();}}

//statement -> ID id_assign_branch() | return return_branch() | 
//printint print_expr() | printstring print_expr()
void statement() {
	if (lookahead == 36) {match(36); id_assign_branch();}
	else if (lookahead == 9) {match(9); return_branch();}
	else if (lookahead == 6) {match(6); expr_parentheses();}
	else if (lookahead == 7) {match(7); expr_parentheses();}
	else syntax_error(lines);
}

//id_assign_branch -> := id_assign_branch() | ( id_list_branch() )
void id_assign_branch() {
	if (lookahead == 25) {match(25); assign_branch();}
	else if (lookahead == 19) {match(19); id_list_branch(); match(20);}
	else syntax_error(lines);
}

//assign_branch -> expr() | GETINT()
void assign_branch() {
	if (lookahead == 19 || lookahead == 37 
			|| lookahead == 38 || lookahead == 36) expr();
	else if (lookahead == 8) {match(8); match(19); match(20);}
	else syntax_error(lines);
}

//id_list_branch -> expr_list() | e
void id_list_branch() {
	if (lookahead == 19 || lookahead == 37
			|| lookahead == 38 || lookahead == 36) expr_list();}

//return_branch -> expr() | e
void return_branch() {
	if (lookahead == 19 || lookahead == 37 
			|| lookahead == 38 || lookahead == 36) expr();}

//expr_parentheses -> ( expr_list() ) | ( )
void expr_parentheses() {
	match(19);
	if (lookahead == 19 || lookahead == 37
		|| lookahead == 38 || lookahead == 36) expr_list(); 
	match(20);
}

//expr -> term term_branch
void expr() {
	term(); term_branch();}

//term_branch -> + term() term_branch() | - term() term_branch() | e
void term_branch() {
	if (lookahead == 26) {match(26); term(); term_branch();}
	else if (lookahead == 27) {match(27); term(); term_branch();}
}

//term -> factor() factor_branch()
void term() {
	factor(); factor_branch();}

//factor_branch -> * factor() factor_branch() | / factor() factor_branch() | e
void factor_branch() {
	if (lookahead == 28) {match(28); factor(); factor_branch();}
	else if (lookahead == 29) {match(29); factor(); factor_branch();}
}

//factor -> expr_parentheses() | NUMBER | STRING | ID factor_list_branch()
void factor() {
	if (lookahead == 19) expr_parentheses();
	else if (lookahead == 37) match(37);
	else if (lookahead == 38) match(38);
	else if (lookahead == 36) {match(36); factor_list_branch();}
	else syntax_error(lines);
}

//factor_list_branch -> id_list_branch() | e
void factor_list_branch() {
	if (lookahead == 19 || lookahead == 37
			|| lookahead == 38 || lookahead == 36) id_list_branch();}

//expr_list -> expr() list_branch()
void expr_list() {
	expr(); list_branch();}

//list_branch -> , expr() list_branch() | e
void list_branch() {
	if (lookahead == 22) {match(22); expr(); list_branch();}}

//Start symbol called from here, Recursive Descent Parsing does the rest
//Summary is printed from here after parser is finished
int main(int argc, char **argv) {
	lookahead = yylex();
	prog();
	if (!lookahead) fprintf(stderr, accept_msg); //yylex() returns 0 at EOF

	//Summary printing
	fprintf(stdout, "Number of global variables: %d\n", globals_count);
	for (int i = 0; i < globals_count; i++) {
		fprintf(stdout, "  %s: line %d\n", globals[i], globals_lines[i]);
	}

	fprintf(stdout, "Number of functions: %d\n", func_count);
	for (int i = 0; i < func_count; i++) {
		fprintf(stdout, "  %s: line %d\n", functions[i], func_lines[i]);
	}

	fprintf(stdout, "Number of comments: %d\n", comm_count);
	return 0;
}
