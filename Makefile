CC = gcc
CFLAGS = -g -Wall

all: ccomp

ccomp: main.o lexer.o parser.o ast.o symtab.o
	$(CC) $(CFLAGS) -o ccomp main.o lexer.o parser.o ast.o symtab.o

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

lexer.c: lexer.l
	flex -o lexer.c lexer.l

parser.c parser.h: parser.y
	bison -d -Wcounterexamples -o parser.c parser.y

run: ccomp
	gcc -E test.c -o test.i
	./ccomp test.i

clean:
	rm -f ccomp *.o lexer.c parser.c parser.h test.i
