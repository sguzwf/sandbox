#include<stdio.h>
#include<time.h>

#define TIMES 10000000

int eq_count(int f[],int g[],int n, int m){
	int i,j;
	int result=0;
	for(i=0;i<n;i++){
		//printf("f[%d]\n",i);
		if(i<m){
			if(g[i]>f[i]){
				for(j=i;g[j]>f[i]&&j>=0;j--);
				//printf("%d ",j);
			}
			if(g[i]<f[i]){
				for(j=i;g[j]<f[i]&&j<m;j++);
				//printf("%d ",j);
			}
			if(g[i]==f[i]){
				j=i;
			}
		}else{
			for(j=m-1;g[j]>=f[i]&&j>=0;j--);
			//printf("%d ",j);
		}
		if(g[j]==f[i])
			result++;
		//printf("\n");
	}
	return	result;
}

int eq_count2(int f[], int g[], int n, int m){
	int i,j,count;
	i=j=count=0;
	while(i<n&&j<m){
		if(f[i]>g[j]){
			//printf("%d,%d\n",f[i],g[j]);
			j++;
		}else if(g[j]>f[i]){
			//printf("%d,%d\n",f[i],g[j]);
			i++;
		}else{
			//printf("%d,%d,%d\n",f[i],g[j],count+1);
			i++,j++,count++;
		}
	}
	return count;
}

int main(){
	int i;
	int f[]={1,3,4,7,9,10,11,12,13,15,17,19,21,23,25,27,29,33,39,40};
	int g[]={1,3,5,7,8,10,11,12,13,16,17,23,25,28,31,32,35,39,41,43,45};
	int n=sizeof(f)/4;
	int m=sizeof(g)/4;
	int result;

	time_t cycle;

	cycle = time(NULL);
	for(i=0;i<TIMES;i++){
		if(!i)
			result=eq_count2(f,g,n,m);
		else
			eq_count2(f,g,n,m);
	}
	cycle = time(NULL) - cycle;
	printf("%d\ntime:%d\n",result,cycle);
}
