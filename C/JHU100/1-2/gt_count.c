#include<stdio.h>
#include<time.h>

int gt_count(int f[],int g[],int n, int m){
	int i,j;
	int sum=0;
	for(i=0;i<n;i++){
		//printf("f[%d]\n",i);
		if(i<m){
			if(g[i]>f[i]){
				for(j=i;g[j]>=f[i]&&j>=0;j--);
				j++;
				//printf("j=%d ",j);
			}
			if(g[i]<f[i]){
				for(j=i;g[j]<f[i]&&j<m;j++);
				//printf("j=%d ",j);
			}
			if(g[i]==f[i]){
				j=i;
				//printf("j=%d ",j);
			}
		}else{
			for(j=m-1;g[j]>=f[i]&&j>=0;j--);
			j++;
			//printf("j=%d ",j);
		}
		sum+=j;
		//printf("\n");
	}
	return	sum;
}

int gt_count2(int f[],int g[],int n, int m){
	int i,j,count;
	i=j=count=0;
	while(i<n&&j<m){
		if(f[i]<=g[j])
			i++;
		else
			j++, count+=n - i;
	}
	return count;
}

int main(){
	int i;
	int f[]={1,3,5,7,9,11,13,15,18,20,23,24,25,26,27,30,33,34,38,40};
	int g[]={2,3,4,7,8,9,10,12,14,19,22,24,26,27,30,35,39};
	int n=sizeof(f)/4;
	int m=sizeof(g)/4;

	time_t cycle;

	cycle = time(NULL);
	for(i=0;i<9999999;i++)
		gt_count2(f,g,n,m);
	cycle = time(NULL) - cycle;
	printf("%d\ntime:%d\n",gt_count2(f,g,n,m),cycle);
}
