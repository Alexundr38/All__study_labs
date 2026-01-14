#include <stdlib.h>
#include "removes.h"
#include "additional_processing.h"

void removes(char ***text, int *count_sentence, int **delete, int len){
	qsort(*delete,len,sizeof(int),compare);
	for (int i=0; i< len; i++){
		free((*text)[(*delete)[i]]);
		for (int j=(*delete)[i]+1; j<*count_sentence; j++){
			(*text)[j-1]=(*text)[j];
		}
		(*count_sentence)--;
		(*text)=(char **)realloc((*text),sizeof(char*)*(*count_sentence));
	}
	free(*delete);
}
