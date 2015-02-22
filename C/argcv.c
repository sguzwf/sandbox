#include<stdio.h>
#include<stdlib.h>

int main(int a,char *b[]){
	int i;
	printf("%d\n",a);
	for(i=0;i<a;i++)
		printf("%s\n",b[i]);
	return 0;
}
