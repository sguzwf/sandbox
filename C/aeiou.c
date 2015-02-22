#include<stdio.h>
#include<stdlib.h>

int main(){
	char z[30];
	while(1){
		scanf("%[^aeiou]",z);
		printf("%s\n",z);
	}
	system("pause");
}
