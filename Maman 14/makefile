asm: main.o error.o parser.o list_handling.o
	gcc -o asm main.o error.o parser.o list_handling.o


main.o: main.c parser.h list_handling.h error.h
	gcc -c -ansi -Wall -pedantic main.c
parser.o: parser.h list_handling.h error.h
	gcc -c -ansi -Wall -pedantic parser.c
list_handling.o: list_handling.h
	gcc -c -ansi -Wall -pedantic list_handling.c
error.o: error.h
	gcc -c -ansi -Wall -pedantic error.c

