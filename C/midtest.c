#include<stdio.h>

int main(){
	typedef int *A;
	A a[3];
	typedef int B;
	B *b[3];
	int x=1;
	int i;
	
	a[0]=x;
	a[1]=&x;
	a[2]='\0';

	for(i=0;i<3;i++)
	printf("%d\n",a[i]);

	b[0]=x;
	b[1]=&x;
	b[2]='\0';

	for(i=0;i<3;i++)
	printf("%d\n",b[i]);

	return 0;
}
