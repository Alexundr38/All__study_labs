#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void*first, const void*second){
	const int *f = (const int*) first;
	const int *s = (const int*) second;
	if (abs(*f)<abs(*s)){
		return 1;
	} else if (abs(*f)<abs(*s)){
		return -1;
	}
	return 0;
}

int main(){
	int len=1000;
	int arr[len];
	for (int i=0; i<len; i++){
		scanf("%d",&arr[i]);
	}
	time_t begin = clock();
	qsort(arr,len,sizeof(int),compare);
	time_t end = clock();
	double time = (double) (end-begin);
	for (int i=0; i<len;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
	printf("%lf\n",time);
}
