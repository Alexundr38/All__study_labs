#include <stdio.h>
#include "diff.h"
#include "max.h"
#include "min.h"

int diff(int arr[], int len){
	int maximum=max(arr,len);
	int minimum=min(arr,len);
	int diff=maximum-minimum;
	return diff;
}
