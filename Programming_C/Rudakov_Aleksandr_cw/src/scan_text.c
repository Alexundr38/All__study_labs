#include <stdio.h>
#include <stdlib.h>
#include "scan_text.h"

void scan_text(char ***text, int *count_sentence){
	int flag=0;
	int count_flag=0;
	char symbol;
	int count_symbol=0;
	(*text)[0]=(char *)malloc(sizeof(char));
	while (flag<2){
		symbol=getchar();
		if (symbol=='\n'){
			flag++;
			continue;
		} else if (count_symbol==0  && (symbol==' ' || symbol=='\n' || symbol=='\t')){
				continue;
		}else{
			(*text)[*count_sentence]=(char *)realloc((*text)[*count_sentence],sizeof(char)*(count_symbol+1));
			(*text)[*count_sentence][count_symbol]=symbol;
			count_symbol++;
			count_flag=(*count_sentence)+1;
			flag=0;
		}
		if (symbol=='.'){
			(*text)[*count_sentence]=(char *)realloc((*text)[*count_sentence],sizeof(char)*(count_symbol+1));
                        (*text)[*count_sentence][count_symbol]='\0';
			count_symbol=0;
			(*count_sentence)++;
			(*text)=(char **)realloc((*text),sizeof(char *)*((*count_sentence)+1));
			(*text)[*count_sentence]=(char *)malloc(sizeof(char));
		}
	}
	if (count_flag>(*count_sentence)){
		if ((*text)[*count_sentence][count_symbol-1]!='.'){
			(*text)[*count_sentence]=(char *)realloc((*text)[*count_sentence], sizeof(char)*(count_symbol+2));
			(*text)[*count_sentence][count_symbol]='.';
			(*text)[*count_sentence][count_symbol+1]='\0';
			(*count_sentence)++;
		}
	}
}
