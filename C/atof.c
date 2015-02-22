#include<stdio.h>
/*if you don't include stdlib.h, atof will fail its mission*/
#include<stdlib.h>

int main(int argc, char *argv[]){
    float float1;/*double or float is no matter, but WHY?*/
    float float2 = 3.1415;
    double float3;
    
    float3 = atof("3.1415");
    if(argc!=2)
        return 0;
    /*atof will change to a double value*/
    float1 = atof(argv[1]);
    /*this will print 2293520,if I did not include stdlib.h*/
    printf("%f\n",float1);
    printf("%u\n",(unsigned)float1);
    printf("%f\n",float2);
    /*following action will print only the nature number*/
    printf("%u\n",(unsigned)float2);
    /*This is different from this "3,141499"*/
    printf("%f\n",(unsigned)float2);
    printf("%f\n",float3);
    printf("%u\n",(unsigned)float3);
    while(1);
    return 0;
}    
