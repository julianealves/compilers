#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 1
#
# Makefile for three compiler calls
# Read the comments on Makefile2. All of them apply here too.
# But now the hash table is compiled in a separate gcc call
# Therefore, there must be a header of it to be included in scanner.l
#

etapa3: y.tab.o lex.yy.o main.o hash.o ast.o
	gcc -o etapa3 y.tab.o lex.yy.o main.o ast.o hash.o
main.o: main.c
	gcc -c main.c
hash.o: hash.c
	gcc -c hash.c
ast.o: ast.c
	gcc -c ast.c
y.tab.o: y.tab.c
	gcc -c y.tab.c
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
y.tab.c: parser.y
	yacc -d parser.y
lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l
clean:
	rm *.o lex.yy.c lex.yy.h y.tab.c y.tab.h etapa3