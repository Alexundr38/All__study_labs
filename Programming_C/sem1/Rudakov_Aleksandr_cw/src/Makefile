all: main.o scan_text.o processing_functions.o additional_processing.o removes.o output_text.o fatal_error.o
	gcc main.o scan_text.o processing_functions.o additional_processing.o removes.o output_text.o fatal_error.o -o cw
scan_text.o: scan_text.c scan_text.h
	gcc -c scan_text.c
processing_functions.o: processing_functions.c processing_functions.h additional_processing.h
	gcc -c processing_functions.c
additional_processing.o: additional_processing.c additional_processing.h
	gcc -c additional_processing.c
removes.o: removes.c removes.h additional_processing.h
	gcc -c removes.c
output_text.o: output_text.c output_text.h
	gcc -c output_text.c
fatal_error.o: fatal_error.c fatal_error.h
	gcc -c fatal_error.c
main.o: main.c processing_functions.h additional_processing.h scan_text.h output_text.h fatal_error.h
	gcc -c main.c
clean:
	rm cw *.o
