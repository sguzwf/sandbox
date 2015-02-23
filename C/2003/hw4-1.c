#include<stdio.h>
#include<time.h>

void makematrix(int **,int **);
/*void ADD(int**,int**);
void MUL(int**,int**);*/
void printmatrix(int **);
int i;
int j;
int N;

main(int argc,char* argv[]){
	int *M1mask[10];
	int M1[10][10];
	int *M2mask[10];
	int M2[10][10];
	makematrix(M1mask,M1);
	makematrix(M2mask,M2);
	srand(time(NULL));
	N=atoi(argv[1]);
/*	ADD(M1,M2);
	MUL(M1,M2);
	DET(M1);*/
	printmatrix(&M1);
}

void makematrix(int *Matrixmask[],int Matrix[][10]){
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			Matrix[i][j]=(1+rand()%20);
		}
	}
	for(i=0;i<N;i++){
		Matrixmask[i]=&Matrix[i][1];
	}
}

void printmatrix(int smith){
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf(" %4d",smith[i][j]);
		}
		printf("\n\n");
	}
}
