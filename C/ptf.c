#include<stdio.h>
double ptftest(double (*whichone)(double,int),double,int,int);
double input(double,int);

int main(){
    double x=1.2;
    int n=2;
    int m=2;
    printf("%lf\n",input(x,n));
    printf("%lf\n",ptftest(input,x,n,m));
    while(1);
    return 0;
}

double input(double x,int n){
    double answer=1;
    int i=0;
    for(i=0;i<n;i++)
        answer*=x;
    return answer;
}

double ptftest(double (*whichone)(double,int),double x,int n,int m){
    double answer=1;
    int i=0;
    for(i=0;i<m;i++)
        answer*=(*whichone)(x,n);
    return answer;
}
