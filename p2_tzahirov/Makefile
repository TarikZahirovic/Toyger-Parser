CFLAGS=-g -Og -Wall -Wno-unused-variable -Wno-unused-function -std=c99 -lfl
CC=gcc

p2_c:	lex.yy.c tokens.h parser.c
	$(CC) -o $@ parser.c $(CFLAGS)

lex.yy.c:	p2_c.l
	flex p2_c.l

clean:	
	rm -f p2_c lex.yy.c
