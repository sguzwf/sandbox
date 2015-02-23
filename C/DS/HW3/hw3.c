#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define MAX_X 15
#define MAX_Y 15

int room[MAX_Y][MAX_X]={0};
int sum=0;
int ibug=8;
int jbug=8;
int imove[]={-1,0,1,1,1,0,-1,-1};
int jmove[]={1,1,1,0,-1,-1,-1,0};

//判斷醉蟑螂走完了沒有
int is_done();

//叫蟑螂走，要是傳回非零，就重走
void cockraoch_walk();

void show_room();

int main(){
	srand(time(NULL));
	
	system("tput clear");
	
	while(!is_done()||sum<=50000)
		cockraoch_walk();

	show_room();

	return 0;
}

int is_done(){
	int i;

	for(i=0;i<MAX_X*MAX_Y;i++)
		if(room+i==0)
			return 0;

	return 1;
}

void cockraoch_walk(){

	int itemp,jtemp,temp;

	temp=rand()%8;
	
	itemp=ibug+imove[temp];
	jtemp=jbug+jmove[temp];

	if(itemp<0||itemp>=MAX_X)
		return;
	if(jtemp<0||jtemp>=MAX_Y)
		return;

	ibug=itemp;
	jbug=jtemp;

	room[jbug][ibug]++;

	sum++;
	
	if(1){
		show_room();
		sleep(1);
		system("tput clear");
	}
}

void show_room(){
	int i,j;
	printf("======ROOM======\n");
	for(j=0;j<MAX_Y;j++){
		for(i=0;i<MAX_X;i++)
			if(i==ibug&&j==jbug)
				printf("MrC ");
			else if(room[j][i]==0)
				printf("... ");
			else
				printf("%3d ",room[j][i]);
		printf("\n");
	}
}
