#include <stdio.h>
#include <stdlib.h>
#include "output_text.h"

void output_text(char ***text, int *count_sentence){
        for (int i=0; i<*count_sentence; i++){
                        puts((*text)[i]);
                        free((*text)[i]);
                }
        free(*text);
}

