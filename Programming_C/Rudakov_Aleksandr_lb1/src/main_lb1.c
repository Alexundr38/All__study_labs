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

int max(int first, int second){
	if (first>second){
		return first;
	} else{
		return second;
	}
}

int min(int first, int second){
	if (first<second){
		return first;
	} else{
		return second;
	}
}

void def_max(int arr[],int len){
	int maximum=arr[0];
        for (int i=0;i<len;i++){
                maximum=max(maximum,arr[i]);
	}
        printf("%d\n",maximum);
}

void def_min(int arr[],int len){
	int minimum=arr[0];
        for (int i=0;i<len;i++){
        	minimum=min(minimum,arr[i]);
        }
        printf("%d\n",minimum);
}

void def_diff(int arr[],int len){
	int minimum=arr[0];
	int maximum=arr[0];
	for (int i=0;i<len;i++){
		maximum=max(maximum,arr[i]);
		minimum=min(minimum,arr[i]);
	}
	int diff=maximum-minimum;
	printf("%d\n",diff);
}

void def_sum(int arr[],int len){
	int minimum=arr[len];
	int minimum_old=minimum;
	int sum=0;
	for (int i=len;i>-1;i--){
		minimum=min(minimum,arr[i]);
		if (minimum==minimum_old && arr[i]!=minimum){
			sum+=arr[i];
		}else{
			sum=0;
			minimum_old=minimum;
		}
	}
	printf("%d\n",sum);
}

int main(){
	int array[102];
	int n;
	scanf("%d",&n);
	scan_array(array);
	int len=0;
	for (int i=0;i<101;i++){
		if (array[i]==101){
			len=i;
			break;
		}
	}
	if (array[101]!=102){
		switch(n){
			case 0:
				def_max(array,len);
				break;
			case 1:
				def_min(array,len);
				break;
			case 2:
				def_diff(array,len);
				break;
			case 3:
				def_sum(array,len);
				break;
			default:
				printf("Данные некорректны\n");
		}
	}else{
		printf("Данные некоректны\n");
	}
}
