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
	./ccomp tests/test.c a.s
	gcc -o a.out a.s
	./a.out

test: ccomp
	./ccomp tests/test.c a.s
	gcc -o tests/output/test1.out a.s
	./ccomp tests/test2.c a.s
	gcc -o tests/output/test2.out a.s
	./ccomp tests/test3.c a.s
	gcc -o tests/output/test3.out a.s
	./ccomp tests/test4.c a.s
	gcc -o tests/output/test4.out a.s
	./ccomp tests/test5.c a.s
	gcc -o tests/output/test5.out a.s
	./ccomp tests/test6.c a.s
	gcc -o tests/output/test6.out a.s
	./ccomp tests/test7.c a.s
	gcc -o tests/output/test7.out a.s
	./ccomp tests/test8.c a.s
	gcc -o tests/output/test8.out a.s
	./ccomp tests/test9.c a.s
	gcc -o tests/output/test9.out a.s
	./ccomp tests/test10.c a.s
	gcc -o tests/output/test10.out a.s

clean:
	rm -f ccomp *.o lexer.c parser.c parser.h tests/*.i a.s *.out tests/output/*.out
	rm -rf fail_tests tests/output
