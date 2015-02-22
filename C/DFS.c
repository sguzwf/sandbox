/* Using Adjacency Matrix
 * 00 01 02 03 04 05 
 * 06 07 08 09 10 11
 * 12 13 14 15 16 17
 * 18 19 20 21 22 23
 * 24 25 26 27 28 29
 * 30 31 31 33 34 35
 */

struct vertex{
	char color;
	int edge[36];
};

//int time=0;
struct vertex list[36];
void show();
void DFS__VISIT(int);

int main(){
	int i,j;
	int start=0;

	for(i=0;i<36;i++)
		for(j=0;j<36;j++)
			list[i].edge[j]=0;
	
	list[0].edge[1] =1;

	list[1].edge[0] =1;
	list[1].edge[2] =1;
	list[1].edge[7] =1;

	list[2].edge[1] =1;
	list[2].edge[3] =1;

	list[3].edge[2] =1;

	list[4].edge[5] =1;
	list[4].edge[10] =1;

	list[5].edge[4] =1;

	list[6].edge[7] =1;
	list[6].edge[12] =1;

	list[7].edge[1] =1;
	list[7].edge[6] =1;
	list[7].edge[8] =1;
	list[7].edge[13] =1;

	list[8].edge[7] =1;
	list[8].edge[9] =1;
	list[8].edge[14] =1;

	list[9].edge[8] =1;
	list[9].edge[10] =1;

	list[10].edge[4] =1;
	list[10].edge[9] =1;
	list[10].edge[11] =1;

	list[11].edge[10] =1;
	list[11].edge[17] =1;

	list[12].edge[6] =1;
	list[12].edge[18] =1;


	list[13].edge[7] =1;
	list[13].edge[14] =1;

	list[14].edge[8] =1;
	list[14].edge[13] =1;
	list[14].edge[20] =1;

	list[15].edge[16] =1;
	list[15].edge[21] =1;

	list[16].edge[15] =1;
	list[16].edge[22] =1;

	list[17].edge[11] =1;
	list[17].edge[23] =1;
	
	list[18].edge[12] =1;
	list[18].edge[24] =1;

	list[19].edge[20] =1;
	list[19].edge[25] =1;

	list[20].edge[14] =1;
	list[20].edge[19] =1;
	list[20].edge[21] =1;
	list[20].edge[26] =1;

	list[21].edge[15] =1;
	list[21].edge[20] =1;
	list[21].edge[22] =1;
	list[21].edge[27] =1;

	list[22].edge[16] =1;
	list[22].edge[21] =1;

	list[23].edge[17] =1;

	list[24].edge[18] =1;
	list[24].edge[25] =1;
	list[24].edge[30] =1;

	list[25].edge[19] =1;
	list[25].edge[24] =1;
	list[25].edge[26] =1;
	
	list[26].edge[20] =1;
	list[26].edge[25] =1;
	list[26].edge[27] =1;

	list[27].edge[21] =1;
	list[27].edge[26] =1;
	list[27].edge[28] =1;
	list[27].edge[33] =1;

	list[28].edge[27] =1;
	list[28].edge[29] =1;

	list[29].edge[28] =1;
	list[29].edge[35] =1;

	list[30].edge[24] =1;
	list[30].edge[31] =1;
	
	list[31].edge[30] =1;
	list[31].edge[32] =1;

	list[32].edge[31] =1;
	list[32].edge[33] =1;

	list[33].edge[27] =1;
	list[33].edge[32] =1;
	list[33].edge[34] =1;

	list[34].edge[33] =1;

	list[35].edge[25] =1;
	
	while(start<1||start>35){
		system("exec tput clear");
		printf("這是簡單版的DFS展示\n左上角是1,右下角是36\n請輸入想要開始的點:\n");
		scanf("%d",&start);
	}
	
	for(i=0;i<36;i++)
		list[i].color='W';
	show();

	DFS_VISIT(start-1);
	return 0;
}

void DFS_VISIT(int root){
	int i;
	list[root].color='G';
	show();
	for(i=0;i<36;i++)
		if(list[root].edge[i]==1&&list[i].color=='W')
			DFS_VISIT(i);
	list[root].color='B';
	show();
}

void show(){
	int i;
	system("exec tput clear");
	for(i=0;i<36;i++){
		if(i%6==0)
			printf("\n");
		printf("%c ",list[i].color);
	}
	printf("\n");
	//sleep(0);
}
