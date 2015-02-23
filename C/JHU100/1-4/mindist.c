#include<stdio.h>
#include<string.h>
#include<limits.h>
#define MAX_LENGHT 256

int mindist(int f[],int g[],int m,int n){
	int i,j,min,result;
	for(i=0;i<m;i++)
		printf("%d ",f[i]);
	printf("\n");
	for(j=0;j<n;j++)
		printf("%d ",g[j]);
	printf("\n");
	
	i=j=0;
	min=INT_MAX;
	while(i<m&&j<n){
		result=f[i]-g[j];
		if(result>0){
			if(result<min)
				min=result;
			j++;
		}else if(result<0){
			if(-result<min)
				min=-result;
			i++;
		}else{
			return 0;
		}
	}
	return min;
}

int main(){
	FILE *input;
	char temp[MAX_LENGHT];
	char *result;
	int f[MAX_LENGHT],g[MAX_LENGHT],m,n;
	m=n=0;
	input = fopen("array","r");

	//printf("1\n");
	fgets(temp,MAX_LENGHT,input);
	result=strtok(temp," \n");
	while(result!=NULL){
		f[m]=atoi(result);
		m++;
		result=strtok(NULL," \n");
	}
	
	//printf("2\n");
	fgets(temp,MAX_LENGHT,input);
	result=strtok(temp," \n");
	while(result!=NULL){
		g[n]=atoi(result);
		n++;
		result=strtok(NULL," \n");
	}

	printf("minest distance is : %d\n",mindist(f,g,m,n));
}
