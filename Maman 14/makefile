asm: main.o error.o list_handling.o files.o parser.o pre_asm.o
	gcc -o asm main.o error.o list_handling.o files.o parser.o pre_asm.o


main.o: main.c parser.h list_handling.h error.h files.h
	gcc -c -ansi -Wall -pedantic main.c
parser.o: parser.h error.h list_handling.h files.h
	gcc -c -ansi -Wall -pedantic parser.c
list_handling.o: list_handling.h
	gcc -c -ansi -Wall -pedantic list_handling.c
error.o: error.h
	gcc -c -ansi -Wall -pedantic error.c
files.o: files.h error.h list_handling.h
	gcc -c -ansi -Wall -pedantic files.c
pre_asm.o: pre_asm.h
	gcc -c -ansi -Wall -pedantic pre_asm.c
