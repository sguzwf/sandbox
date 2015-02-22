#include<stdio.h>

void dB(unsigned);

int main(){
	void *pi; 
	int a[10];
	pi = &a[0];
	dB((unsigned)pi);
	dB((unsigned)(pi+1));
}

void dB(unsigned value){
	unsigned c;
	unsigned displayMask = 1 << 31;

	printf("%7u = ",value);

	for(c=1;c<=32;c++){
		putchar(value & displayMask ? '1' : '0');
		value <<= 1;

		if (c%8==0){
			putchar(' ');
		}
	}
	putchar('\n');
}
