#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
	int i;
	srand(time(NULL));

	for(i=0;i<10;i++)
		printf("%2d ",rand()%20);
	printf("\n");

	return 0;
}
