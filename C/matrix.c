#include<stdio.h>

int main(){
	long smith[4][4]={{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
	int i;
	int j;
	int k=0;
	int l=0;
	int n=4;
	for(j=0;j+k<n-1;j++){
		for(i=j+1;i+l<n;i++){	
			for(l=0;i+l<n;l++){
				for(k=0;j+k<n;k++){
					smith[i+l][j+k]=smith[j][j+k]*smith[i+l][j]-smith[i+l][j+k]*smith[j][j];
				}
			}
		}
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%3d ",smith[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<n;i++){
		smith[0][0]*=smith[i][i];
	}
	printf("%3d",smith[0][0]);
}

