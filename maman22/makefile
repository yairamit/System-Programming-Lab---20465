mainmat: mainmat.o mat.o
	gcc -g -ansi -Wall -pedantic mainmat.o mat.o -o mainmat
mainmat.o: mainmat.c
	gcc -c -ansi -Wall -pedantic mainmat.c -o mainmat.o
mat.o: mat.c mat.h
	gcc -c -ansi -Wall -pedantic mat.c -o mat.o
