#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void scan_text(char *** text, int * count_begin){
	int k=0;
	int last=0;
	char symbol;
	int count_char=0;
	while (k==0){
                scanf("%c",&symbol);
		if ((symbol=='\t')){
			if (last==1){
				(*text)=realloc((*text),sizeof(char*)*((*count_begin)+1));
                                (*text)[*count_begin]=malloc(sizeof(char));
				last=0;
			}
			continue;
		}else if (symbol=='!'){
			(*text)[*count_begin]=realloc((*text)[*count_begin],sizeof(char)*(count_char+1));
                        (*text)[*count_begin][count_char]=symbol;
			k=1;
			break;
                } else if ((symbol=='.') || (symbol==';') || (symbol=='?')){
			(*text)[*count_begin]=realloc((*text)[*count_begin],sizeof(char)*(count_char+1));
                        (*text)[*count_begin][count_char]=symbol;
                        count_char=0;
                        (*count_begin)++;
			(*text)=realloc((*text),sizeof(char*)*((*count_begin)+1));
                        (*text)[*count_begin]=malloc(sizeof(char));
			scanf("%c",&symbol);
                } else {
			if ((symbol==' ' && count_char==0)){
				continue;
			} else{
                               	(*text)[*count_begin]=realloc((*text)[*count_begin],sizeof(char)*(count_char+1));  //---
                               	(*text)[*count_begin][count_char]=symbol;
                               	count_char++;
			}
                }
        }
}

void processing(char *** text,int* count_end){
	int i=0;
	int big_letter=0;
	char signs[11] = {',','1','2','3','4','5','6','7','8','9','0'};
	int chek;
	int j=0;
	char symb;
	while (i<(*count_end)){
		j=0;
		symb=(*text)[i][j];
		while ((symb!='.') && (symb!='?') && (symb!=';')){
			chek=0;
			for (int l=0; l<11; l++){
				if (symb==signs[l]) chek++;
			}
			if ((chek==0) && (toupper(symb)==symb) && (symb!=' ')){
				big_letter++;
			}			
			j++;
			symb=(*text)[i][j];
		}
		(*text)[i]=realloc((*text)[i],sizeof(char)*(j+2));
		(*text)[i][j+1]='\0';
		if (big_letter>1){
			for (int l=i; l<(*count_end);l++){
				(*text)[l]=realloc((*text)[l+1],sizeof(char)*strlen((*text)[l+1]));
			}
			(*count_end)--;
		}else{
			i++;
		}
		big_letter=0;
	}
}

int main(){
	char** text=malloc(sizeof(char*));
	int count_begin=0;
	scan_text(&text,&count_begin);
	int count_end=count_begin;
	processing(&text,&count_end);

	text[count_end]=realloc(text[count_end],sizeof(char)*(18));
                text[count_end][17]='\0';
	for (int i=0; i<count_end+1;i++){
		for (int j=0; j<strlen(text[i]); j++){
			printf("%c",text[i][j]);
		}
		printf("\n");
	}
	printf("Количество предложений до %d и количество предложений после %d\n",count_begin,count_end);
	
}

