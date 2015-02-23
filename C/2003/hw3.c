#include<stdio.h>
#include<time.h>
#include<stdio.h>

int i=0;
int j=0;
int n;
void main1();
void main2();
void sum1d(long *,long *);
void mul1d(long *,long *);
void det1d(long *);
void printmatrix1d(long *);
void sum2d(long [][],long [][]);
void mul2d(long [][],long [][]);
void det2d(long [][]);
void printmatrix2d(long [][]);

int main(int argc,char *argv[]){
	srand(time(NULL));
	n=atoi(argv[2]);
	if(argc!=3){
		printf("Usage: <filename> <which way to use array?> <how big is n?>");
		return 0;
	}
	switch(atoi(argv[1])){
		case 1:
			main1();
			break;
		case 2:
			main2();
			break;
		defulf:
			printf("Usage: <filename> <which way to use array?> <how big is n?>");
	}
	return 0;
}

void main1(){
	long M1[10][10]={0};
	long M2[10][10]={0};
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			M1[i][j]=1+rand()%20;
		}
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			M2[i][j]=1+rand()%20;
		}
	}
	printmatrix2d(M1);
	printmatrix2d(M2);
	sum2d(M1,M2);
	mul2d(M1,M2);
	det2d(M1);
}

void main2(){
	long M1[100]={0};
	long M2[100]={0};
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			M1[i*10+j]=1+rand()%20;
		}
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			M2[i*10+j]=1+rand()%20;
		}
	}
	printmatrix1d(M1);
	printmatrix1d(M2);
	sum1d(M1,M2);
	sum1d(M1,M2);
	det1d(M1);
}

void sum1d(long *M1,long *M2){
	long R[100]={0};
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			R[i*10+j]=M1[i*10+j]+M2[i*10+j];
		}
	}
	printmatrix1d(R);
}

void sum2d(long M1[][10],long M2[][10]){
	long R[10][10]={0};
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			R[i][j]=M1[i][j]+M2[i][j];
		}
	}
	printmatrix2d(R);
}

void mul1d(long *M1,long *M2){
	int m=0;
	int sum=0;
	long R[100]={0};
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			for(m=0;m<n;m++){
				sum+=M1[i*10+m]*M2[m*10+j];
			}
			R[i*10+j]=sum;
			sum=0;
		}
	}
}

void mul2d(long M1[][10],long M2[][10]){
	int m=0;
	int sum=0;
	long R[10][10]={0};
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			for(m=0;m<n;m++){
				sum+=M1[i][m]*M2[m][j];
			}
			R[i][j]=sum;
			sum=0;
		}
	}
	printmatrix2d(R);
}

void det1d(long *M1){
	int l;
	int m;
	for(i=0;i<n;i++){
		for(m=1;i+m<n;m++){
			for(l=1;i+l<n;l++){
				M1[(i+m)*10+(i+l)]=M1[(i+m)*10+(i+l)]*M1[i*11]-M1[i*11+1]*M1[(i+m)*10+i];
			}
		}
	}
	printf("%d\n\n",M1[11*(n-1)]);
}

void det2d(long M1[][10]){
	int l;
	int m;
	for(i=0;i+1<n;i++){
		for(m=1;i+m<n;m++){
			for(l=1;i+l<n;l++){
				M1[i+m][i+l]=M1[i+m][i+l]*M1[i][i]-M1[i][i+l]*M1[i+m][i];
			}
		}
	}
	printf("%d\n\n",M1[n-1][n-1]);
}

void printmatrix1d(long *smith){
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%9d",smith[i*10+j]);
		}
	printf("\n\n");
	}
	printf("\n");
}

void printmatrix2d(long smith[][10]){
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%9d ",smith[i][j]);
		}
	printf("\n\n");
	}
	printf("\n");
}
