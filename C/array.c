#include<stdio.h>
void f(float* A);
int main()
{
	  float* b;
	    b[0]=1;
	      b[1]=2;
	        b[2]=3;
		  b[3]=4;
		    f(b);
}
void f(float* A)
{
	 printf("%5.0f%5.0f\n",A[0],A[1]);
	  printf("%5.0f%5.0f\n",A[2],A[3]);
}

