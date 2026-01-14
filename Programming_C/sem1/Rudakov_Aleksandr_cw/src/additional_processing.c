#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "additional_processing.h"

int cmp(const void *first, const void *second){
        const char **f=(const char **)first;
        const char **s=(const char **)second;
        int i=0, j=0;
        while (i<strlen(*f) && j<strlen(*s)){
                if (toupper((*f)[i])>toupper((*s)[i])){
                        return 1;
                } else if (toupper((*f)[i])<toupper((*s)[i])) return -1;
                i++;
                j++;
        }
	if (i<strlen(*f)){
		return 1;
	} else if (j<strlen(*s)){
		return -1;
	}else return 0;
}

int compare(const void *first, const void *second){
        const int *f = (const int*) first;
        const int *s = (const int*) second;
        if (abs(*f)<abs(*s)){
                return 1;
        } else if (abs(*f)<abs(*s)){
                return -1;
        }
        return 0;
}

void split(char ***text, char ***sentence, int *count, int i){
	int len=strlen((*text)[i]);
	char *new_string=malloc(sizeof(char)*len);
	strncpy(new_string,(*text)[i],len-1);
	new_string[len-1]='\0';
	char *word=strtok(new_string," ,");
	while (word!=NULL){
		(*sentence)=realloc((*sentence),sizeof(char*)*((*count)+1));
		(*sentence)[*count]=malloc(sizeof(char)*(strlen(word)+1));
		strncpy((*sentence)[*count],word,strlen(word));
		(*sentence)[*count][strlen(word)]='\0';
		word=strtok(NULL," ,");
		(*count)++;
	}
}
