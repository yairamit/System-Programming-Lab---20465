mainmat: mainmat.o mymat.o utills.o
	gcc -g -ansi -Wall -pedantic mainmat.o mymat.o utills.o -o mainmat
mainmat.o: mainmat.c
	gcc -c -ansi -Wall -pedantic mainmat.c
mat.o: mymat.c mymat.h
	gcc -c -ansi -Wall -pedantic mymat.c
utills.o: utills.h
	gcc -c -ansi -Wall -pedantic utills.c
