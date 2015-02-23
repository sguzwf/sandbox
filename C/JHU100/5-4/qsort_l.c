#include<stdio.h>
#include<stdlib.h>
#define DEBUG

/* QUICK SORT IN LINKED LIST
 *
 * My programming is poor at linked list......Orz
 *
 * 1. remember to write delete()
 *
 * 2004 OCT 27
 */

struct node{
	int data;
	struct node *next;
};

void debug(const char *string){
	printf("%s\n",string);
}

/* init()
 * Initialize the node that passed.
 */
struct node *init(struct node *current){
#ifdef DEBUG
	debug("INIT START");
#endif
	
	current->data = -1;
	current->next = NULL;

#ifdef DEBUG
	debug("INIT END");
#endif
	
	return current;
}

/* cut()
 * Pass a pointer of struct node, then the function will return the Ptr right after this node or NULL if there are no node following current one.
 */
struct node *cut(struct node *current){
	struct node *temp;

#ifdef DEBUG
	debug("CUT START");
#endif
	
	temp = current->next;
	current->next = NULL;

#ifdef DEBUG
	debug("CUT END");
#endif
	
	return temp;
}

/* merge()
 * Pass two head of target linked lists, then function will return the address of the first one, and merge another after the end of the first list.
 */
struct node *merge(struct node *former, struct node *latter){
	struct node *current;

#ifdef DEBUG
	debug("MERGE START");
#endif
	
	current = former;
	while(current->next)
		current = current->next;

	if(latter->data==-1)
		current->next = latter->next;
	else
		current->next = latter;
	
#ifdef DEBUG
	debug("MERGE END");
#endif
	
	return former;
}

/* new()
 * This function will create a new node right after the end of the list, which is passes as first parament, and return the address of this list.
 */
struct node *new(struct node *current, int num){
	struct node *new;

#ifdef DEBUG
	debug("NEW START");
#endif
	
	new = malloc(sizeof(struct node));
	
	init(new);

	new->data = num;

#ifdef DEBUG
	debug("NEW END");
#endif
	
	return merge(current,new);
}

/* listsize()
 * This one will try to count the size of the list you pass.
 */
int listsize(struct node *current){
	int counter;

#ifdef DEBUG
	debug("LISTZISE START");
#endif
	
	for(counter=0;current->next;counter++)
		current = current->next;

#ifdef DEBUG
	debug("LISTSIZE END");
#endif
	
	return counter;
}

/* show()
 * Print the list that passed.
 */
void show(struct node *current){
#ifdef DEBUG
	debug("SHOW START");
#endif
	
	while(current->next){
		current = current->next;
		printf(" %2d ->",current->data);
	}
	printf(" NULL\n");
	
#ifdef DEBUG
	debug("SHOW END");
#endif
}
/* quicksort()
 * This is the most important function. My goal is to implement Quick Sort in Linked List.
 * Pass the head of any list to be sorted.
 */
//void quicksort(struct node *);

int main(){
	struct node list1, list2;
	int i;

	init(&list1);
	init(&list2);
	
	for(i=0;i<10;i++)
		new(&list1,i);

	for(i=14;i>=0;i--)
		new(&list2,i);

	show(&list1);
	show(&list2);
	
	merge(&list1,&list2);

	show(&list1);
}
