#include<stdio.h>
#include<stdlib.h>

/* Function Isert:
 * You can give it two pointers, the former is current pointer, and the latter is the pointer of the list you want to insert.
 * It means that you can insert a list into another one, not just insert one node.
 * The return value is the head of the list which you insert. */
struct Listnode * Insert(struct Listnode *,struct Listnode *);
/* Function Create:
 * You do not have to give it any value.
 * just run this function, and it will give you a pointer of a new node. */
struct Listnode * Create();
/* Function Delete:
 * You have to give this function two pointers,
 * the former is current pointer, and the latter is the previous pointer
 * It will return the previous pointer. */
struct Listnode * Delete(struct Listnode *, struct Listnode *);
/* Function Search:
 * You have to give it two value,
 * the former is the node you want to start search,
 * the latter is the value you want to search.
 * It will return the pointer of your search result. */
struct Listnode * Search(struct Listnode *, int);
/* Function Count:
 * you have to tell this function that the node you want to start count.
 * And it will return how many nodes before the one you tell it.*/
unsigned Count(struct Listnode *);
/* Function Sort:
 * this is a bubble sort.
 * Not finished yet. */
struct Listnode * Sort(struct Listnode *);
struct Listnode * Reverse(struct Listnode *);
/*Function Split:
 * This function will split the list after the pointer which you give it. */
struct Listnode * Split(struct Listnode *);
/*Function Printlist:
 * This function just simple display the list.
 * It will print those nodes after the one you tell it(normally the head of a list). */
void Printlist(struct Listnode *);

/*Define the struct*/
struct Listnode{
	int data;
	struct Listnode *Nextnode;
};
/*Unser interface*/
int main(){
	struct Listnode * Head[2];
	struct Listnode * CurrentPtr;
	struct Listnode * PreviousPtr;
	
	int selection=0;
	int i;
	int value;
	int reverse;

	printf("This program is an inplement of Linked List.\n\n");
	Head[0]=NULL;
	Head[1]=NULL;	
	printf("Please select the type of linked list.\n\t1.Normal Head\n\t2.Dummy Head\n:>\n");
	scanf("%d",&selection);
	switch(selection){
		case 1:	/*Normal*/
				while(selection!=6){
					system("exec tput clear");
					printf("Here is your list:\n\n");
					Printlist(Head[0]);
					Printlist(Head[1]);
					printf("\nPlease select operation you want to do.\n\n\t1.Insert\n\t2.Delete\n\t3.Search\n\t4.Reverse\n\t5.Merge\n\t6.Exit\n:>\n");
					scanf("%d",&selection);
					switch(selection){
						case 1:	/*Insert*/
							printf("Please switch the list you want to insert.\n");
							scanf("%d",&i);
							if(Head[i-1]==NULL){
								printf("Please enter the value you want to insert:\n");
								CurrentPtr = Head[i-1] = Create();
								Printlist(Head[i-1]);
							}else{
								CurrentPtr = Insert(CurrentPtr,Create());
								Printlist(Head[i-1]);
							}
							break;
						case 2:	/*Delete*/
							printf("The node you want to delete is in the list No....?\n");
							scanf("%d",&i);
							printf("Please enter the value you want to delete.\n");
							scanf("%d",&value);
							Delete(Search(Head[i-1],value)->Nextnode,Search(Head[i-1],value));
							Printlist(Head[i-1]);
							break;
						case 3:	/*Search*/
							printf("Which list you want to search?\n");
							scanf("%d",&i);
							printf("Please Enter the value you want to search.\n");
							scanf("%d",value);
							printf("The value that you searched is the %d number.\n",Count(Head[i-1])-Count(Search(Head[i-1],value)));
							break;
						case 4:	/*Reverse*/
							break;
						case 5:	/*Merge or Split*/
							break;
						case 6:	/*EXIT*/
							break;
						default:
					}
				}
			break;
		case 2:	/*Dummy Head*/
			break;
		default:
		}
	return 0;
}
/*Operation Create*/
struct Listnode * Create(){
	struct Listnode * Head;
	Head=(struct Listnode *)malloc(sizeof(struct Listnode));
	scanf("%d",&Head->data);
	Head->Nextnode=NULL;
	return Head;
}
/*Operation Insert*/
struct Listnode * Insert(struct Listnode *CurrentPtr,struct Listnode * NewPtrHead){
	struct Listnode * NewPtrTail=NewPtrHead;
	while(NewPtrTail->Nextnode!=NULL)
		NewPtrTail=NewPtrTail->Nextnode;
	NewPtrTail->Nextnode = CurrentPtr->Nextnode;
	CurrentPtr->Nextnode = NewPtrHead;
	return NewPtrHead;
}
/*Operation Delete*/
struct Listnode * Delete(struct Listnode *CurrentPtr,struct Listnode *PreviousPtr){
	if(CurrentPtr==NULL)
		return NULL;
	PreviousPtr->Nextnode = CurrentPtr->Nextnode;
 	free(CurrentPtr);
	return PreviousPtr;	
}
/*Operation Search*/
struct Listnode * Search(struct Listnode *PreviousPtr,int value){
	for(;PreviousPtr->Nextnode->Nextnode!=NULL;PreviousPtr=PreviousPtr->Nextnode){
		if(PreviousPtr->Nextnode->data==value)
			return PreviousPtr;
	}
}
/*Operation Count*/
unsigned Count(struct Listnode *CurrentPtr){
	unsigned counter;
	for(counter=0;CurrentPtr!=NULL;counter++)
		CurrentPtr=CurrentPtr->Nextnode;
	return counter;
}
/*Operation Reverse*/
struct Listnode * Reverse(struct Listnode * CurrentPtr){
	
}
/*Operation Merge*/
/*Operation Sort*/
struct Listnode * Sort(struct Listnode * CurrentPtr){
	struct Listnode * Headtemp = CurrentPtr;
	int temp;
	unsigned num = Count(CurrentPtr);
	unsigned i;
	for(i=0;i<num;i++){
		if(CurrentPtr->Nextnode!=NULL){
			while(CurrentPtr->data>CurrentPtr->Nextnode->data){
				temp = CurrentPtr->Nextnode->data;
				CurrentPtr->Nextnode->data = CurrentPtr->data;
				CurrentPtr->data = temp;
			}
			CurrentPtr=CurrentPtr->Nextnode;
		}
		CurrentPtr=Headtemp;
	}
	return Headtemp;
}
/*Operation Split*/
struct Listnode * Split(struct Listnode * CurrentPtr){
	struct Listnode * newHead=CurrentPtr->Nextnode;
	CurrentPtr->Nextnode=NULL;
	Printlist(newHead);
	return newHead;
}
/*Print List*/
void Printlist(struct Listnode *CurrentPtr){
	unsigned counter;
	for(counter=1;counter<=Count(CurrentPtr);counter++)
		printf("%3d  ",counter);
	printf("\n");
	for(;CurrentPtr!= NULL;CurrentPtr=CurrentPtr->Nextnode)
		printf("%3d->",CurrentPtr->data);
	printf("EOL\n");
}
