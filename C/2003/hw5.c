/**************************************************\
 *       C Programming Language Homewoek 5        *
 *        ----Pointer to function                 *
 **************************************************
 * Author: F74926735 Kuanling Haung               *
 *                                                *
 * Purpose:                                       *
 * 	1. Learn how to use pointer to function.  *
 * 	2. Pass this course....                   *
 *                                                *
 * Usage:                                         *
 *                                                *
\**************************************************/
#include<stdio.h>
int i;
double power(double, int);
double multiple(double, int);
double powerpower(double(*whichone)(double basement,int exponent), int);

int main(){
	int n,m,order;
	double x;
	printf("I am F74925735's Homework 5.\nI can calculate x^n and x*n.\nPlease Enter X:\n");
	scanf("%lf",&x);
	printf("Please Enter n:\n");
	scanf("%d",&n);
	printf("Now, that me show you the answer:\nx^n:\n%f\nx*n:\n%f\n\nI can also calculate (x^n)^m or (x*n)^m.i\nTell me the number m:\n",power(x,n),multiple(x,n));
	scanf("%d",&m);
	printf("Select which one you want me to print:\n==========\n\t1.(x^n)^m\n\t2.(x*n)^m\n==========\n");
	scanf("%d",&order);
	switch(order){
		case 1:
			printf("(x^n)^m is:\n%f\n",powerpower(power,m));
			break;
		case 2:
			printf("(x*n)^m is:\n%f\n",powerpower(multiple,m,n,x));
			break;
		default:
			printf("I don't understand your choice....\n==<The End>==");
			return 0;
	}
	
}

double power(double basenumber, int exponent){
	double answer =1;
	for(i=0;i<exponent;i++){
		answer*=basenumber;
	}
	return answer;
}

double multiple(double multiplier, int multicand){
	double answer =1;
	answer = multiplier*multicand;
	return answer;
}

double powerpower(double (*witchone)(double x,int n),int exponent,int n,double x){
	double answer =1;
	double input=(*witchone)(x,n);
	for(i=0;i<exponent;i++){
		answer*=input;
	}
	return answer;
}
