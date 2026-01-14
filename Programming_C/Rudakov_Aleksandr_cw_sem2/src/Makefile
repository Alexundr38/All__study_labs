all: main.o png_process.o additional_functions.o
	gcc main.o png_process.o additional_functions.o -lpng -o cw 

main.o: main.c png_process.h
	gcc -c main.c

png_process.o: png_process.c png_process.h additional_functions.h
	gcc -c png_process.c	

additional_functions.o: additional_functions.c additional_functions.h
	gcc -c additional_functions.c 

clear:
	rm *.o
