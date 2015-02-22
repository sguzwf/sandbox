/* BFS
 *
 * N N N N
 * N N N N
 * N N S N
 * N N N N
 * 
 */

#include<stdio.h>

struct vertex{
	char color;
	unsigned int distance;
	struct vertex *undirect[4];
	struct vertex *father;
};

void EQ(struct vertex*);
struct vertex *DeQ();
struct vertex *Q[10];
struct vertex list[16];

int main(){
	int i,j,start;
	unsigned int D=0;
	struct vertex *N;
	system("exec tput clear");
	for(i=0;i<16;i++){
		list[i].color='W';
		list[i].father=NULL;
		for(j=0;j<4;j++)
			list[i].undirect[j]=NULL;
	}
	for(i=0;i<10;i++)
		Q[i]=NULL;
	
	printf("這是一個4X4的小圖\n左上角是1右下角是16\n請輸入想要開始的節點:\n");
	start = 0;
	while(start>16||start<1)
		scanf("%d",&start);
	system("exec tput clear");
	
	show();
	
	list[0].undirect[0]=&list[1];
	list[1].undirect[0]=&list[2];
	list[1].undirect[1]=&list[5];
	list[1].undirect[2]=&list[0];
	list[2].undirect[0]=&list[6];
	list[3].undirect[0]=&list[7];
	list[4].undirect[0]=&list[5];
	list[4].undirect[1]=&list[8];
	list[5].undirect[0]=&list[1];
	list[5].undirect[1]=&list[6];
	list[5].undirect[2]=&list[9];
	list[5].undirect[3]=&list[4];
	list[6].undirect[0]=&list[2];
	list[6].undirect[1]=&list[7];
	list[6].undirect[2]=&list[5];
	list[6].undirect[3]=&list[10];
	list[7].undirect[0]=&list[3];
	list[7].undirect[1]=&list[6];
	list[8].undirect[0]=&list[4];
	list[8].undirect[1]=&list[12];
	list[9].undirect[0]=&list[5];
	list[9].undirect[1]=&list[10];
	list[9].undirect[2]=&list[13];
	list[10].undirect[0]=&list[6];
	list[10].undirect[1]=&list[11];
	list[10].undirect[2]=&list[9];
	list[11].undirect[0]=&list[15];
	list[11].undirect[1]=&list[10];
	list[12].undirect[0]=&list[8];
	list[13].undirect[0]=&list[9];
	list[14].undirect[0]=&list[15];
	list[15].undirect[0]=&list[11];
	list[15].undirect[1]=&list[14];

	/*BFS*/
	list[start-1].color='G';/*Start from list[start]*/
	show();
	EQ(&list[start-1]);
	while(Q[0]!=NULL){
		N=DeQ();	//N is vertex*
		for(i=0;i<4;i++){	
			if(N->undirect[i]!=NULL&&N->undirect[i]->color=='W'){
				EQ(N->undirect[i]);
				N->undirect[i]->distance=D++;
				N->undirect[i]->father=N;
				N->undirect[i]->color='G';
				show();
			}
		}
		N->color='B';
		show();
	}
	return 0;
}

show(){
	int i;
	for(i=0;i<16;i++){
		if(i%4==0)
			printf("\n");
		printf("%c ",list[i].color);
	}
	printf("\n");
	sleep(1);
	system("exec tput clear");
}

void EQ(struct vertex *push){
	int i;
	for(i=0;Q[i]!=NULL;i++);
	Q[i]=push;
}

struct vertex *DeQ(){
	int i;
	struct vertex *temp;
	temp=Q[0];
	for(i=0;i<9;i++)
		Q[i]=Q[i+1];
	return temp;
}
