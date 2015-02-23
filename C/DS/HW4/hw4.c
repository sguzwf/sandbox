#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define MAX_X 5
#define MAX_Y 5
#define MAX_CELL 100
#define STEPS 8

/*#define DEBUG*/

int map[MAX_Y][MAX_X];

struct pt{
	int x;
	int y;
}now={0,0},
//add another 1, 1 can make my mouse being like to go right down.
move[STEPS]={
	{-1,-1},
	{-1,0},
	{1,0},
	{0,-1},
	{0,1},
	{1,-1},
	{-1,1},
	{1,1}
};

struct node{
	struct node *previous_node;
	struct node *next_node[8];
	struct pt position;
};

struct pt stack[MAX_CELL];
int stack_current=0;

int push(struct pt);
int pop(struct pt*);
void walk(struct pt,struct node *);
int go(int);
void show();
void debug(const char *);

void tree_init(struct node *);
struct node *tree_add(struct pt, struct node *);
void tree_show(struct node *);
struct node *tree_search(struct node *,struct pt *);

int main(){
	int i,j;
	struct node head;
	struct node *exit=NULL;
	struct pt end={MAX_X-1,MAX_Y-1};
#ifdef DEBUG
	debug("MAIN");
#endif
	head.previous_node=NULL;
	tree_init(&head);
	head.position.x=0;
	head.position.y=0;
	
	srand(time(NULL));
	for(j=0;j<MAX_X;j++)
		for(i=0;i<MAX_Y;i++)
			map[j][i]=rand()%2;
	map[0][0]=0;
	map[MAX_Y-1][MAX_X-1]=0;
	
	walk(head.position, &head);
	show();
	exit=tree_search(&head,&end);
	printf("%d\n",exit);
	if(exit==NULL)
		printf("NO EXIT\n");
	else{
		printf("DONE\n");
		//tree_path();
	}
#ifdef DEBUG
	debug("END MAIN");
#endif

	tree_show(&head);

	return 0;
}

int push(struct pt point){
#ifdef DEBUG
	debug("PUSH");
#endif
	if(stack_current==MAX_CELL)
		return 1;

	stack[stack_current].x=point.x;
	stack[stack_current++].y=point.y;
#ifdef DEBUG
	debug("END PUSH");
#endif
	return 0;
}

int pop(struct pt *result){
#ifdef DEBUG
	debug("POP");
#endif
	if(stack_current==0)
		return 1;

	result->x=stack[--stack_current].x;
	result->y=stack[stack_current].y;
#ifdef DEBUG
	debug("END POP");
#endif
	return 0;
}

void walk(struct pt start_pt, struct node *current){
	int i;
	int step;
	struct pt temp;
#ifdef DEBUG
	debug("WALK");
#endif
	if(map[MAX_Y-1][MAX_X-1]==2)
		return;
	map[start_pt.y][start_pt.x]=2;
	//show();
	
	//SOME CODE HERE...
	go(1);
	for(i=0;i<STEPS;i++){	
		step=go(0);
		temp.x=start_pt.x+move[step].x;
		temp.y=start_pt.y+move[step].y;
		if(temp.x<0||temp.x>=MAX_X);
		else if(temp.y<0||temp.y>=MAX_Y);
		else if(map[temp.y][temp.x]==0){
			push(start_pt);
			walk(temp,tree_add(temp,current));
		}
	}
	if(!pop(&temp))
		walk(temp,current->previous_node);
#ifdef DEBUG
	debug("END WALK");
#endif
}

void show(){
	int i,j;
#ifdef DEBUG
	debug("SHOW");
#endif
	//sleep(1);
	system("tput clear");
	printf("========MAP========\n");
	for(j=0;j<MAX_Y;j++){
		for(i=0;i<MAX_X;i++){
			if(map[j][i]==1)
				printf("# ");
			if(map[j][i]==0)
				printf(". ");
			//if(now.x==i&&now.y==j)
			//	printf("@ ");
			if(map[j][i]==2)
				printf("o ");
		}
		printf("\n");
	}
#ifdef DEBUG
	debug("END SHOW");
#endif
}

int go(int init){
	static int outputed[STEPS];
	int temp,i;

	for(i=0;i<STEPS;i++)
		if(!outputed[i])
			break;
	if(i==STEPS||init)
		for(i=0;i<STEPS;i++)
			outputed[i]=0;
	
	while(!init){
		temp=rand()%STEPS;
		if(outputed[temp]==0){
			outputed[temp]=1;
			return temp;
		}
	}
}

void debug(const char *string){
	printf("%s\n",string);
}

//TREE
void tree_init(struct node *current_node){
	int i;
#ifdef DEBUG
	debug("INIT NODE");
#endif
	for(i=0;i<8;i++)
		current_node->next_node[i]=NULL;
	current_node->position.x=-1;
	current_node->position.y=-1;
#ifdef DEBUG
	debug("END INIT");
#endif
}


struct node *tree_add(struct pt next_point, struct node *current_node){
	int i;
#ifdef DEBUG
	debug("ADD NODE");
#endif
	for(i=0;i<8;i++)
		if(current_node->next_node[i]==NULL)
			break;
	if(i==8)
		return NULL;
	current_node->next_node[i]=malloc(sizeof(struct node));
	tree_init(current_node->next_node[i]);

	current_node->next_node[i]->previous_node=current_node;
	current_node->next_node[i]->position.x=next_point.x;
	current_node->next_node[i]->position.y=next_point.y;

#ifdef DEBUG
	debug("END ADD");
#endif
	
	return current_node->next_node[i];
}

void tree_show(struct node *current){
	int i;

	printf("[%d,%d] => ",current->position.x,current->position.y);
	
	for(i=0;i<8&&current->next_node[i];i++)
		printf("(%d,%d) ",current->next_node[i]->position.x,current->next_node[i]->position.y);
	
	if(!i)
		printf("NULL");
	
	printf("\n");

	for(i=0;i<8&&current->next_node[i];i++)
		tree_show(current->next_node[i]);
}

struct node *tree_search(struct node *head,struct pt *point){
	int i;
	static struct node *result=NULL;
	if(head->position.x==point->x&&head->position.y==point->y)
		result=head;
	else
		for(i=0;i<8&&head->next_node[i];i++)
			tree_search(head->next_node[i],point);
	return result;
}
		
