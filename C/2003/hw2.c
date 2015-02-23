/******************************************************
 *
 * Filename: f74926735.c
 *
 * Programmer: Kuanling Haung(F74926735)
 *
 * Purpose:
 *	Enter two number in argument list, the first one will switch what will compute the second number.
 *
 *    
 *
 * Input: command line argument list
 *
 * Output: the standard out
 *
 * Compilation: gcc f74926735.c -o f74926735 
 *
 * Sample input: 
 * 	f74926735 1 9
 * 	f74926735 2 9
 * 	f74926735 3 9
 * 	f74926735 4 9
 * 	f74926735 5 9
 * Sample Output:
 * 	1+2+3+...+n=45(This will print 10000 times....)
 * 	TIME=0.000003
 * 	1+2+3+...+n=45(This will print 10000 times....)
 * 	TIME=0.000002
 * 	f(n)=62,
 * 	g(n)=61
 * 	TIME=0.000000
 * 	f(n)=62,(This will print 10000 times, too....)
 * 	g(n)=61
 * 	TIME=0.000009
 * 	f(n)=62,(This will print 10000 times, too....)
 * 	g(n)=61
 * 	TIME=0.000009
 * 	
 *
 * Date: 2003/10/28
 *
 * *******************************************************/
#include<stdio.h>
#include<time.h>

int func1(int);/*The prototype of a function that computes the sum of 1+2+...+n in iterative way*/
int func2(int);/*The prototype of a function that computes the sum of 1+2+...+n in recursive way*/
int f(int);/*The prototype of function f(n)*/
int g(int);/*The prototype of function g(n)*/
int f2(int);/*The prototype of another version of f(n) using array*/
int g2(int);/*The prototype of another version of g(n) using array*/
int farray[1000000]={0};/*array using in f2()*/
int garray[1000000]={0};/*array using in g2()*/
int func5(int);/*The prototype of last function*/
clock_t clock();/*The prototype of clock()*/
clock_t start, stop;
/*in case 1, 2, 4 and 5,program will run "counter" times to compute the duration time.*/
int counter=10000;
int i=0;

int main(int argc, char *argv[]){
        if (argc!=3){
		printf("Usage: f74926735 <witch program to run> <N>\n");
		return 0;
	}/*When user run this file without enter any in argument list, print Usage of this file and exit.*/
        switch(atoi(argv[1])){/*Use switch statement to chose which program to run*/
        	case 1 :
			start=clock();/*start compute duration time*/
			while(i<counter){
	                printf("1+2+3+...+n=%d\n",func1(atoi(argv[2])));/*print the answer*/
			i++;
			}
			stop=clock();/*stop computer the duration time, and the next line is to print the time in SEC.*/
			printf("TIME=%f\n",(((double)(stop-start))/CLOCKS_PER_SEC)/10000);
	                break;
	        case 2 :
			start=clock();/*Do the same thing as in case 1*/
			while(i<counter){
	                printf("1+2+3+...+n=%d\n",func2(atoi(argv[2])));
			i++;
			}
			stop=clock();
			printf("TIME=%f\n",(((double)(stop-start))/CLOCKS_PER_SEC)/10000);
	                break;
	        case 3 :
			start=clock();
	                printf("f(n)=%d,\ng(n)=%d\n",f(atoi(argv[2])),g(atoi(argv[2])));
	                stop=clock();
			printf("TIME=%f\n",((double)(stop-start))/CLOCKS_PER_SEC);
			break;
		case 4 :
			start=clock();
	                while(i<counter){
			printf("f(n)=%d,\ng(n)=%d\n",f2(atoi(argv[2])),g2(atoi(argv[2])));
			i++;
			}
			stop=clock();
			printf("TIME=%f\n",(((double)(stop-start))/CLOCKS_PER_SEC)/10000);
			break;
		case 5 :
			start=clock();
			while(i<counter){
	                func5(atoi(argv[2]));/*The func5() will print the answer by itself, so here have no "printf"*/
			i++;
			}
			stop=clock();
			printf("TIME=%f\n",(((double)(stop-start))/CLOCKS_PER_SEC)/10000);
	                break;

	        }
}
/*func1(),caculate the sum of 1+2+...+n by for loop, then send the answer back to main()*/
int func1(int n){
        int sum;
        for(sum=0;n>=0;n--)sum+=n;
        return sum;
}
/*func2(),by using the recursive program, let the function call itself for compute the f(n-1) until n=1.then return the anser to main()*/
int func2(int n){
        if (n==1)return 1;
        return(func2(n-1)+n);
}
/*In case 3, I have to caculate f(n) and g(n) by using recursive way. Here is how it works.*/
int f(int n){
        if (n==1)return 1;
        if (n==0)return 0;
        return(f(n-1)+g(n-2));
}                                                         

int g(int n){
        if (n==1)return 2;
        if (n==0)return 1;
        return(g(n-1)+f(n-2));
}
/*In case 4, I have to avoid redundant computation, so when the program caculate one value, I input it into an array, and tell the program if the value in the array is not 0, using that value instead of caculate it by the program itself.*/
int f2(int n){
	farray[0]=0/*It is not a good idea that initalise farray[] here.*/;
	farray[1]=1;/*Better initialise it out of main()*/
	if (n==1)return 1;/*2003OCT30*/
	if (n==0)return 0;
	if (farray[n-1]!=0 && garray[n-2]!=0){
		farray[n]=(farray[n-1]+garray[n-2]);
	}
	else {
		farray[n]=(f2(n-1)+g2(n-2));
	}
	return farray[n];
}

int g2(int n){
	garray[0]=1;
	garray[1]=2;
	if (n==1)return 2;
	if (n==0)return 1;
	if (garray[n-1]!=0 && farray[n-2]!=0){
		garray[n]=(garray[n-1]+farray[n-2]);
	}
	else {
		garray[n]=(g2(n-1)+f2(n-2));
	}
	return garray[n];
}
/*In case 5, I have to caculate the f(n) and g(n) by using some loop.*/
int func5(int n){
	int m;
	farray[0]=0;
	farray[1]=1;
	garray[0]=1;
	garray[1]=2;
	for (m=2;m<=n;m++){
		farray[m]=farray[m-1]+garray[m-2];
		garray[m]=garray[m-1]+farray[m-2];
	}
	printf("f(n)=%d,\ng(n)=%d\n",farray[n],garray[n]);
}
/*END OF SOUCECODE......*/
