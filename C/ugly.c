#include<stdio.h>
#include<stdlib.h>

int insert(int);
int ugly[2000]={0};

int main(){
	int input,where,zero;
	int i;
		
	while(1){
		scanf("%d",&input);

		for(zero=0;zero<2000;zero++){
			if(ugly[zero]==0)
				break;
		}
		where = zero;
		ugly[zero]=input;
		for(i=zero;i>=0;i--){
			if(ugly[i]>input)
				where = i;
		}
		for(i=zero;i>where;i--)
			ugly[i]^=ugly[i-1]^=ugly[i]^=ugly[i-1];
		for(i=0;i<zero;i++)
			printf("--%3d--",i);
		printf("\n");
		for(i=0;i<zero;i++)
			printf("-[%3d]-",ugly[i]);
		printf("\n");
	}
}
