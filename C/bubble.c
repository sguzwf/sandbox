/************************************************************************\
 * 		Bubbble Sort -- My first try				*
 * Aruthor : Kuanling Haung						*
 * Prupose : For the linked list.					*
 * Usage :								*
\************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void Printlist(int[]);

int main(){
	srand(time(NULL));
	int list[20];	/*Target list*/
	int i;	/*Counter*/
	for(i=0;i<20;i++)
		list[i]=1+rand()%20;	/*Isert the value of this list*/
	Printlist(list);
}

void Printlist(int list[]){
	int i;
	for(i=0;i<20;i++)
		printf("%2d ",list[i]);
	printf("\n");
}
