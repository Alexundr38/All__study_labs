all: menu.o max.o min.o diff.o sum.o
	gcc menu.o max.o min.o diff.o sum.o -o menu	
max.o: max.c max.h 
	gcc -c max.c
min.o: min.c min.h 
	gcc -c min.c
diff.o: diff.c diff.h max.h min.h
	gcc -c diff.c
sum.o: sum.c sum.h min.h
	gcc -c sum.c
menu.o: menu.c scan_array.h min.h max.h diff.h sum.h 
	gcc -c menu.c
clean: 
	rm *.o
