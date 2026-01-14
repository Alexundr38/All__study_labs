#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "processing_functions.h"
#include "additional_processing.h"
#include "removes.h"

#define BLOCK 1000

void f9(char ***text, int *count_sentence, int n){
	for (int i =0; i<*count_sentence; i++){
		int len=strlen((*text)[i])+1;
		(*text)[i][len-1]='\0';
		char * dup_str=strdup((*text)[i]);
		dup_str[len-2]=' ';
		free((*text)[i]);
		(*text)[i]=strdup(dup_str);
		for (int j=0; j<n-1; j++){	
			(*text)[i]=(char *)realloc((*text)[i],sizeof(char)*BLOCK*(j+2));
			strcat((*text)[i],dup_str);
			(*text)[i][len*(j+2)+1]='\0';
		}
		(*text)[i][(len-1)*(n)-1]='.';
		(*text)[i][(len-1)*n]='\0';
		free(dup_str);
	}
}

void mandatory_processing(char ***text, int *count_sentence){
	int *delete=(int *)malloc(sizeof(int));
	int len=0;
	for (int i=0; i<(*count_sentence)-1; i++){
		for (int j=i+1; j<(*count_sentence); j++){
			if (strlen((*text)[i])!=strlen((*text)[j])){
				continue;
			} else{
				int count=0;
				for (int k=0; k<strlen((*text)[i]);k++){
					if (toupper((*text)[i][k])!=toupper((*text)[j][k])) count++;
				}
				if (count==0){
					int j1=0;
					for (int l=0; l<len; l++){
						if (delete[l]==j){
							j1=1;
						}
					}
					if (j1==0){
						delete=(int *)realloc(delete,sizeof(int)*(len+1));
						delete[len]=j;
						len++;
					}
				}
			}
		}
	}
	removes(&(*text),&(*count_sentence),&delete,len);
	for (int i=0; i<(*count_sentence); i++){
		int point=strlen((*text)[i])-2;
		if (point>0){
			char c=(*text)[i][point];
			while ((c==' ' || c==',') && point>0){
				point--;
				c=(*text)[i][point];
			}
			(*text)[i]=(char *)realloc((*text)[i],sizeof(char)*(point+3));
			(*text)[i][point+1]='.';
			(*text)[i][point+2]='\0';
		}
	}
}

void delete_while_the_same(char ***text, int *count_sentence){
	for (int i=0; i<(*count_sentence); i++){
		char *new_string=(char *)(malloc(sizeof(char)*strlen((*text)[i])));
		strncpy(new_string,(*text)[i],strlen((*text)[i])-1);
		new_string[strlen((*text)[i])-1]='\0';
		char *ptr_begin=new_string;
		char *ptr_end=new_string+strlen(new_string)-1;
		while (ptr_begin<ptr_end){
			if (toupper(*ptr_begin)==toupper(*ptr_end)){
				ptr_begin++;
				ptr_end--;
			} else break;
		}
		free((*text)[i]);
		int len=ptr_end-ptr_begin+1;
		(*text)[i]=(char *)malloc(sizeof(char)*(len+2));
		strncpy((*text)[i],ptr_begin,len);
		(*text)[i][len]='.';
		(*text)[i][len+1]='\0';
		free(new_string);
	}
}


void sort_lexicographic_order(char ***text, int *count_sentence){
	for (int i=0; i<(*count_sentence); i++){
		char **sentence=(char **)malloc(sizeof(char *));
		int count=0;
		split(&(*text),&sentence,&count,i);
		if (count!=0){
			free((*text)[i]);
			qsort(sentence,count,sizeof(char *),cmp);
			int new_len=strlen(sentence[0])+1;
			(*text)[i]=(char *)malloc(sizeof(char)*new_len);
                	strncpy((*text)[i],sentence[0],new_len);
			for (int j=1; j<count; j++){
				(*text)[i][new_len-1]=' ';
				(*text)[i][new_len]='\0';
				new_len+=strlen(sentence[j])+1;
				(*text)[i]=(char *)realloc((*text)[i],sizeof(char)*(new_len+1));
				strcat((*text)[i],sentence[j]);
			}
			(*text)[i][new_len-1]='.';
			(*text)[i][new_len]='\0';
			for (int j=0; j<count; j++){
				free(sentence[j]);
			}
			free(sentence);
		}
	}
}

void remove_palindromes(char ***text, int *count_sentence){
	int *delete=(int *)malloc(sizeof(int));
	int len=0;
	for (int i=0; i<(*count_sentence); i++){
		char **sentence=(char **)malloc(sizeof(char*));
		int count=0;
		split(&(*text),&sentence,&count,i);
		int big_flag=0;
		for (int j=0; j<count; j++){
			int flag=0;
			char *ptr_begin=sentence[j];
			char *ptr_end=sentence[j]+strlen(sentence[j])-1;
			while (ptr_begin<ptr_end){
				if (toupper(*ptr_begin)!=toupper(*ptr_end)) {
					flag++;
				}
				ptr_begin++;
				ptr_end--;
			}
			if (flag==0){
				big_flag=1;
				break;
			}
		}
		if (big_flag==1){
			delete=(int *)realloc(delete,sizeof(int)*(len+1));
			delete[len]=i;
			len++;
		}
		for (int j=0; j<count; j++){
			free(sentence[j]);
		}
		free(sentence);
	}
	removes(&(*text),&(*count_sentence),&delete,len);
}

void find_word(char ***text, int *count_sentence){
	char find_str[]="HiddenTiger";
	int *delete=(int *)malloc(sizeof(int));
	int len=0;
	for (int i=0; i<*count_sentence; i++){
		char *ptr = strstr((*text)[i],find_str);
		if (ptr==NULL || ptr==(*text)[i]){
			delete=(int*)realloc(delete,sizeof(int)*(len+1));
			delete[len]=i;
			len++;
		} else {
			if (*(ptr-1)!=' ' && *(ptr-1)!=','){
				delete=(int*)realloc(delete,sizeof(int)*(len+1));
        	                delete[len]=i;
	                        len++;
			} else if (*(ptr+11)!=' ' && *(ptr+11)!=',' && *(ptr+11)!='.'){
				delete=(int*)realloc(delete,sizeof(int)*(len+1));
                        	delete[len]=i;
                        	len++;
			}
		}
	}
	removes(&(*text),&(*count_sentence),&delete,len);
}

void function_info(){
	puts("   List of commands:\n"
        "      0 - Print preprocessed text.\n"
        "      1 - Delete all characters at the beginning and end of the sentence so that in the end the first and last characters of the sentence are different (case insensitive).\n"
        "      2 - Sort all the words in the sentence in lexicographic order.\n"
        "      3 - Delete all sentences in which at least one word is a palindrome.\n"
        "      4 - Print all sentences that contain the word “HiddenTiger” and which is not the first word.\n"
        "      5 - Print help message.\n"
        "\n"
        "   The text consists of sentences separated by a period. Sentences are a set of words separated by a space or comma, words are a set of Latin letters and numbers. Double \'\\n\' is interpreted as an end of text.");
}
