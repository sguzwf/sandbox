struct node{
	int data;
	struct node *nextPtr;
};

typedef struct node Node;
typedef Node *NodePtr;

Node startnode;
NodePtr nowPtr;
NodePtr newPtr;
int i;

int main(int argc,char *argv[]){
	startnode.data=atoi(argv[1]);
	startnode.nextPtr=NULL;
	nowPtr=startnode;

	for(i=2;i<argc;i++){
		newPtr=malloc(sizeof(Node));
		nowPtr->nextPtr=newPtr;
		newPtr->nextPtr=NULL;
		newPtr->data=atoi(argv[i]);
	}
}
