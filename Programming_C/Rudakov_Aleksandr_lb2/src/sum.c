#include <stdio.h>
#include "sum.h"
#include "min.h"

int sum(int arr[],int len){
	int minimum=min(arr,len);
	int sum=0;
	int i=0;
	while (arr[i]!=minimum){
		sum+=arr[i];
		i++;
	}
	return sum;
}
