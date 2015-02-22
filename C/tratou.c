/*I thought that it will print float in unsigned data type, but infact, it changes the float into unsigned and ignore all floating numbers*/
#include<stdio.h>
#include<stdlib.h>

void printunsigned(unsigned);
/*this function will print float as unsigned*/
void printfloat(float);
void displayBits(unsigned);

int main(int argc,char *argv[]){
	if(argc!=2)
		return 0;
	float value = atof(argv[1]);
	printf("%f\n",value);
	printf("%d\n",&value);
	displayBits(*(unsigned *)&value);
	printfloat(value);
	while(1);
	return 0;
}

void printunsigned(unsigned value){
	printf("%u\n",value);
}

void printfloat(float value){
	printf("%u\n",value);
}

void displayBits( unsigned value){
    unsigned c;/* counter */
    
    /*declare displayMask and left shift 31 bits*/
    unsigned displayMask = 1 << 32-1;
   
     /*loop trough bits */
    for ( c = 1; c <=32; c++ ){
    putchar( value & displayMask ? '1' : '0');
    displayMask >>= 1; /*Shift displayMask right by 1*/
    
        if (c%8 == 0){/*Output a space after 8 bits*/
            putchar(' ');
        }/*end if*/
    }/*end for*/
    
    putchar('\n');
}/*end function displayBits*/
