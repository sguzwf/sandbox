#include<stdio.h>
#include<time.h>
/**********************************************************
 *	HOMEWORK 04
 *
 *	Try to passing an 2D array without telling the function how long the array is.
 *
 *	Author: Kuanling Haung
 *
 *	Purpose: My homework.
 *
 *	Usage:
 *		./hw4 [<"N" of this N*N matrix>]
 *
 **********************************************************/ 
/*SAMPLE I/O
 *
 *  ./hw4 2
 *  M1: the first matrix
 *    7    6
 *
 *   13   16
 *
 *  M2: the second matrix
 *    5    7
 *
 *    5   19
 *
 *
 *  The sum of two matrices :
 *
 *   12   13
 *
 *   18   35
 *
 *  The product of multiplication :
 *
 *   65  163
 *
 *  145  395
 *
 *  The determinant value of the first matrix :
 *
 *  34
 ***********************************************************/          
/*Function prototypes*/
void makematrix(long **,long [][]);
void printmatrix(long **);
void sum(long **,long **,long **);
void mul(long **,long **,long **);
void det(long **);
/*General counters and input "N"*/
int i,j,N;

int main(int argc,char *argv[]){
	/*Define the matrix first*/
	long *M[10];
	long Ms[10][10];
	/*Another one*/
	long *M2[10];
	long M2s[10][10];
	/*This is for storing the answer*/
	long *R[10];
	long Rs[10][10];
	/*Set N equal to the first input of argument list*/
	N=atoi(argv[1]);
	if(N>10){
		printf("The input is too big. (N must < 10)");
		return 0;
	}
	/*Random number generator*/
	srand(time(NULL));
	/*Create link between M[i] and Ms[i][1]*/
	for(i=0;i<N;i++)
		M[i]=Ms[i];
	/*Store random value into this matrix*/
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			M[i][j]=1+rand()%20;
	/*Print this matrix on the screen*/
	printf("M1: the first matrix\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
			printf("%4d ",M[i][j]);
		printf("\n\n");
	}
	/*Try to make another matrix by function*/
	makematrix(M2,M2s);
	/*Print out this matrix by function*/
	printf("M2: the second matrix\n");
	printmatrix(M2);
	/*By using function, it is more easy to creat such matrix.*/
	makematrix(R,Rs);
	/*Calculate the sum, the mulity, and the deteminant value of those matrices*/
	printf("\nThe sum of two matrices :\n\n");
	sum(M,M2,R);
	printf("The product of multiplication :\n\n");
	mul(M,M2,R);
	printf("The determinant value of the first matrix :\n\n");
	det(M);
	/*THE END*/
	return 0;
}

void makematrix(long **M,long Ms[][10]){
	for(i=0;i<N;i++)
		M[i]=Ms[i];
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			M[i][j]=1+rand()%20;
}

void sum(long **M, long **M2, long **R){
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			R[i][j]=M[i][j]+M2[i][j];
		}
	}
	printmatrix(R);
}

void mul(long **M, long **M2, long **R){
	int m=0;
	int sum=0;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			for(m=0;m<N;m++){
				sum+=M[i][m]*M2[m][j];
			}
			R[i][j]=sum;
			sum=0;
		}
	}
	printmatrix(R);
}

void det(long **M){
	int l;
	int m;
	for(i=0;i+1<N;i++){
		for(m=1;i+m<N;m++){
			for(l=1;i+l<N;l++){
				M[i+m][i+l]=M[i+m][i+l]*M[i][i]-M[i][i+l]*M[i+m][i];
			}
		}
	}
	printf("%d\n\n",M[N-1][N-1]);
}

void printmatrix(long **M){
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
			printf("%4d ",M[i][j]);
		printf("\n\n");
	}
}
