#ifndef SCAN_ARRAY_H
#define SCAN_ARRAY_H

#include <stdio.h>

void scan_array(int arr[]){
	char symbol;
	int i=0;
	int proverka=0;
	do{
		if (scanf("%d%c",&arr[i],&symbol)==0){
			proverka=1;
			arr[101]=102;
		}
		if (arr[i]>100){
			proverka=1;
			arr[101]=102;
		}
		i++;
	}while(symbol!='\n' && proverka==0);
	arr[i]=101;
}

#endif
