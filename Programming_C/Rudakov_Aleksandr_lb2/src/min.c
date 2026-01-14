#include <stdio.h>
#include "min.h"

int min(int arr[], int len){
	int minimum=arr[0];
	int i;
	for (i=0;i<len;i++){
		if (minimum>arr[i]){
			minimum=arr[i];
		}
	}
	return minimum;
}
