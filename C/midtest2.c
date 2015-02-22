#include<stdio.h>
int main(){
	int x = 10;
	int *y = &x;
	int **z = &y;
	printf("%d, %d, %d, %d, %d, %d\n",x, y, *y, z, *z, **z);
	return 0;
}
