#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "scan_text.h"
#include "processing_functions.h"
#include "additional_processing.h"
#include "fatal_error.h"
#include "output_text.h"

int main(){
	printf("Course work for option 4.18, created by Aleksandr Rudakov.\n");
	char flag, flag2;
	int point;
	flag=getchar();
	if (flag=='\n'){
		fatal_error();
	}else if (isdigit(flag)==0){
		fatal_error();
	}else{
		flag2=getchar();
		if (flag2!='\n'){
			fatal_error();
		}else {
			int f=flag-'0';
			if (((f>5) || (f<0)) && f!=9){
				fatal_error();
			}
		}
	}
	point=flag-'0';
	int count_sentence=0;
	int n=0;
        char **text=(char **)malloc(sizeof(char*));
	if (point!=5 && point!=9){
		scan_text(&text,&count_sentence);
		mandatory_processing(&text,&count_sentence);
	} else if (point==9){
		scanf("%d",&n);
		scan_text(&text,&count_sentence);
                mandatory_processing(&text,&count_sentence);
	}
	switch (point){
		case 0:
			break;
		case 1:
			delete_while_the_same(&text,&count_sentence);
			break;
		case 2:
			sort_lexicographic_order(&text,&count_sentence);
			break;
		case 3:
			remove_palindromes(&text,&count_sentence);
			break;
		case 4:
			find_word(&text,&count_sentence);
			break;
		case 5:
			function_info();
			break;
		case 9:
			f9(&text,&count_sentence,n);
			break;
		default:
			fatal_error;
	}
	if (point!=5){
		output_text(&text,&count_sentence);
	}
	return 0;
}

