asm: main.o error.o list_handling.o files.o
	gcc -o asm main.o error.o list_handling.o files.o


main.o: main.c parser.h list_handling.h error.h files.h
	gcc -c -ansi -Wall -pedantic main.c

list_handling.o: list_handling.h
	gcc -c -ansi -Wall -pedantic list_handling.c
error.o: error.h
	gcc -c -ansi -Wall -pedantic error.c
files.o: files.h error.h list_handling.h
	gcc -c -ansi -Wall -pedantic files.c

