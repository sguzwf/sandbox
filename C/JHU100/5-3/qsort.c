#include<stdio.h>

#define SWAP(x,y) x^=y^=x^=y

void quicksort(int f[],int left,int right){
	int i,j,pivot;
	if(left < right){
		i=left;
		j=right+1;

		pivot=f[left];

		do{
			do
				i++;
			while(f[i]<pivot);

			do
				j--;
			while(f[j]>pivot);

			if(i<j)
				SWAP(f[i],f[j]);
		}while(i<j);
		if(j!=left)
			SWAP(f[left],f[j]);
		for(i=0;i<=19;i++)
			printf("%2d ",f[i]);
		printf("\n");
		quicksort(f,left,j-1);
		quicksort(f,j+1,right);
	}
}

int main(){
	int a[]={10,9,8,7,5,6,4,3,2,1,11,29,33,23,24,31,54,3,2,0};
	int left = 0;
	int right = sizeof(a)/4-1;
	int i;
	quicksort(a,left,right);
	printf("Quick Sort:\n");
	for(i=0;i<=right;i++)
		printf("%2d ",a[i]);
	printf("\n");
	return 0;
}
	
