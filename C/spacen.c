#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
	int num,i;
	srand(time(NULL));
	for(i=0;i<10000;i++){
		num=rand()%20+1;
		printf(" %d",num);
	}
	printf("\n");
	return 0;
}
