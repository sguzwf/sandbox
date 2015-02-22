#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/******************************************************************************************/
#define MAX_STRING 100
typedef struct node *tree_pointer;
typedef struct node{
    int data_L;
    int data_R;
    tree_pointer left_child, middle_child, right_child;
}node;
/******************************************************************************************/
void input_string(int string[MAX_STRING], int *element);
void insert(tree_pointer *treePtr, int string[MAX_STRING]);
void preOrder(tree_pointer treePtr);
/******************************************************************************************/
int main()
{
	int j;
	int element;  //string裡面的元素數目
    int string[MAX_STRING];  //儲存元素用的矩陣
	tree_pointer rootPtr = NULL;  //tree的指標
    input_string(string, &element);  //讀取string.txt
	for ( j = 0; j < element; j++)
	insert(&rootPtr, string);  //插入元素到tree裡面
	preOrder(rootPtr);
	system("pause");
	return 0;

}
void input_string(int string[MAX_STRING], int *element)
{
	int i = 0;
    char *token;
    char temp[MAX_STRING];
    FILE *INPUT;
    INPUT = fopen("string.txt", "r");
    while(!feof(INPUT))
    {
        fgets(temp, MAX_STRING, INPUT);
        token = strtok( temp, ",");
        while(token != NULL)
        {
            string[i] = atoi(token);
            token = strtok(NULL, ",");
			i++;
        }
    }//end while
    fclose(INPUT);  *element = i;//總元素數目
}//end input_string
void insert(tree_pointer *treePtr, int string[MAX_STRING])
{
    static int i = 0;
	int choice;
    if (*treePtr == NULL)  //如果是一個空的tree則創造一個tree
	{
        *treePtr = malloc(sizeof(tree_pointer));  //設立一個新結點
        (*treePtr)->data_L = -1;
        (*treePtr)->data_R = -1;
        if (*treePtr != NULL)
        {
            (*treePtr)->data_L = string[i];  i++;  //將string裡的值加入data_L
            (*treePtr)->left_child = NULL;         //Left_child初值化
            (*treePtr)->middle_child = NULL;       //middle_child初值化
            (*treePtr)->right_child = NULL;        //right_child初值化
        }//end if 根節點設立
    }
    else  //如果不是一個空的tree則加入新值
    {
        //當data_R = -1 且 加入的值比data_L大
		if ( (string[i] > (*treePtr)->data_L) && ((*treePtr)->data_R == -1) )
            choice = 1;
        //當data_R = -1 且 加入的值比data_L小
        else if ( (string[i] < (*treePtr)->data_L) && ((*treePtr)->data_R == -1) )
            choice = 2;
        //當data_R != -1 且 加入的值比data_L小 則加入左節點
        else if ( string[i] < (*treePtr)->data_L && ((*treePtr)->data_R != -1) )
            choice = 3;
        //當data_R != -1 且 介於data_l & data_R 加入中間的節點
        else if ( (string[i] < (*treePtr)->data_R && string[i] > (*treePtr)->data_L) && ((*treePtr)->data_R != -1) )
            choice = 4;
        //當data_R != -1 且 加入的值比data_R大 則加入右節點
        else if ( string[i] > (*treePtr)->data_R && ((*treePtr)->data_R != -1) )
            choice = 5;
        switch(choice)
        {
            case 1:  //加入值到data_R
               (*treePtr)->data_R = string[i];  i++;  break;
            case 2:  //加入值到data_R 並進行swap
               (*treePtr)->data_R = (*treePtr)->data_L;
               (*treePtr)->data_L = string[i];  i++;  break;
            case 3:  //在left_child新增一個節點 並將值加入新結點data_L
               insert(&((*treePtr)->left_child), string);  break;
            case 4:  //在middle_child新增一個節點 並將值加入新結點data_L
               insert(&((*treePtr)->middle_child), string);  break;
            case 5:  //在right_child新增一個節點 並將值加入新結點data_L
               insert(&((*treePtr)->right_child), string);  break;
        }//end switch
    }
}
void preOrder(tree_pointer treePtr)
{
	static int level = 0;
    if (treePtr != NULL)
    {
		printf("start\n");
        printf("%d,", treePtr->data_L);
		
		if ( treePtr->data_R == -1 )
            printf("NULL ");
		else
            printf("%d \n", treePtr->data_R);

printf("left 00\n");
        preOrder( treePtr->left_child );
printf("left NULL,NULL\n");

printf("middle 00\n");
        preOrder( treePtr->middle_child );
printf("middle NULL,NULL\n");

printf("right 00\n");
		preOrder( treePtr->right_child );
printf("right NULL,NULL\n");
level++;
printf("end  %d\n",level);
    }
}
