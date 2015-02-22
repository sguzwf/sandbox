#include<stdio.h>

int main (){
	float income,tax;
	printf("Please insert your income: ");
	scanf("%2f",&income);
	if (income<1000){
		tax=income*0.2;
		printf("\nTax is %.2f",tax);
	}
	else if (1000<=income<=2000){
		tax=income*0.3;
		printf("\nTax is %.2f",tax);
	}
	else{
		tax=income*0.4;
		printf("\nTax is %.2f",tax);
	}
}

