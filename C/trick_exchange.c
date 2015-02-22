#include<stdio.h>
#include<stdlib.h>
int main(){
	int a,b;
	printf("Please enter 2 int...\n");
	scanf("%d %d",&a,&b);
	printf("%d %d\n",a,b);
	printf("then I will exchange them\n");
	a^=b^=a^=b;
	printf("%d %d\n",a,b);
	return 0;
}
