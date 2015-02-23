#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int main(){
	int i;
	srand(time(NULL));
	for(i=0;i<50000;i++)
		printf("%d\n",rand());
	return 0;
}
