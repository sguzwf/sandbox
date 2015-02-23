/*****************************************************

Filename: F74926735.c

Programmer: Kauling-Haung

Purpose: print an N¡¦N multiplication table

Input: command line argument list

Output: the standard out

Compilation: gcc -o hw1 hw1.c

Run: hw1 9

Date: 2003/10/6

*******************************************************/
#include<stdio.h>

int mtable(int a);
int main(int argc, char *argv[]){
        if(argc!=2){
                printf("Usage:<filename> <n>\n");
        }
        else{
                int a;
                a=atoi(argv[1]);
                mtable(a);
        }
        return 0;
}
/*===============================================

Function: nxn_table(int n, FILE *fp)

Purpose: print a nxn table

Input: an integer n and a file pointer fp

Output to the file fp

================================================*/
int mtable(int a){

        int num1=1;
        int num2=1;
        int t=3;
        int d;
        while(t!=(a+3)){
                while(num2<=a){
                        d=num1;
                        while(num1<=t){
                                printf("%2d X %2d = %4d ",num1,num2,num1*num2);
                                num1++;
                        }
                        printf("\n");
                        num2++;
                        num1=d;
                }
                printf("\n");
                num2=1;
                num1=num1+3;
                t=t+3;
                if(t==a+2){
                        t=a;
                }else if(t==a+1){
                        t=a;
                }
        }
}