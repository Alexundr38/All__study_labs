#include <stdio.h>
#include "max.h"

int max(int arr[], int len){
	int maximum=arr[0];
	int i;
	for(i=0;i<len;i++){
		if (maximum<arr[i]){
			maximum=arr[i];
		}
	}
        return maximum;
}
