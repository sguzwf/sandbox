#include<stdarg.h>
void av(int, ...); 

int main(){
	double w = 11;
	double x = 12.33;
	double y = 15.43;
	double z = 163.22;

	av(3,x,y,z);
	av(8,w,x,y,z);
	return 0;
}

void av(int i, ...){
	int j;
	va_list ap;
	double sum=0;

	va_start(ap, i);
	for(j=0;j<i;j++)
		sum += va_arg(ap , double);
	va_end(ap);

	printf("%f\n",sum/i);
}
