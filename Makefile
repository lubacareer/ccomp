CC = gcc
CFLAGS = -g -Wall

all: ccomp

ccomp: main.o lexer.o parser.o ast.o symtab.o codegen.o
	$(CC) $(CFLAGS) -o ccomp main.o lexer.o parser.o ast.o symtab.o codegen.o

main.o: main.c parser.h ast.h
	$(CC) $(CFLAGS) -c main.c

lexer.o: lexer.c parser.h
	$(CC) $(CFLAGS) -c lexer.c

parser.o: parser.c ast.h
	$(CC) $(CFLAGS) -c parser.c

ast.o: ast.c ast.h
	$(CC) $(CFLAGS) -c ast.c

symtab.o: symtab.c symtab.h
	$(CC) $(CFLAGS) -c symtab.c

codegen.o: codegen.c codegen.h ast.h symtab.h
	$(CC) $(CFLAGS) -c codegen.c

lexer.c: lexer.l
	flex -o lexer.c lexer.l

parser.c parser.h: parser.y
	bison -d -Wcounterexamples -o parser.c parser.y

run: ccomp
	gcc -E tests/test9.c -o tests/test9.i
	./ccomp tests/test9.i

test: ccomp
	./ccomp tests/test1.c
	./ccomp tests/test2.c
	./ccomp tests/test3.c
	./ccomp tests/test4.c
	./ccomp tests/test5.c
	./ccomp tests/test6.c
	./ccomp tests/test7.c
	./ccomp tests/test8.c
	./ccomp tests/test9.c

clean:
	rm -f ccomp *.o lexer.c parser.c parser.h tests/*.i
