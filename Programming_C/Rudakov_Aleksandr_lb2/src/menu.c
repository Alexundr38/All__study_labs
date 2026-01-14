#include <stdio.h>
#include "min.h"
#include "max.h"
#include "sum.h"
#include "diff.h"
#include "scan_array.h"

int main(){
	int array[102];
	int n;
	scanf("%d",&n);
	scan_array(array);
	int len=0;
	int i;
	for (i=0;i<101;i++){
		if (array[i]==101){
			len=i;
			break;
		}
	}
	if (array[101]!=102){
		switch(n){
			case 0: ;
				int maximum;
				maximum=max(array, len);
				printf("%d\n",maximum);
				break;
			case 1: ;
				int minimum;
				minimum=min(array, len);
				printf("%d\n",minimum);
				break;
			case 2: ;
				int difference;
				difference=diff(array, len);
				printf("%d\n",difference);
				break;
			case 3: ;
				int summ;
				summ=sum(array,len);
				printf("%d\n",summ);
				break;
			default:
				printf("Данные некорректны\n");
		}
	}else{
		printf("Данные некоректны\n");
	}
}
