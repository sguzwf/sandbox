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
	int element;  //string�̭��������ƥ�
    int string[MAX_STRING];  //�x�s�����Ϊ��x�}
	tree_pointer rootPtr = NULL;  //tree������
    input_string(string, &element);  //Ū��string.txt
	for ( j = 0; j < element; j++)
	insert(&rootPtr, string);  //���J������tree�̭�
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
    fclose(INPUT);  *element = i;//�`�����ƥ�
}//end input_string
void insert(tree_pointer *treePtr, int string[MAX_STRING])
{
    static int i = 0;
	int choice;
    if (*treePtr == NULL)  //�p�G�O�@�ӪŪ�tree�h�гy�@��tree
	{
        *treePtr = malloc(sizeof(tree_pointer));  //�]�ߤ@�ӷs���I
        (*treePtr)->data_L = -1;
        (*treePtr)->data_R = -1;
        if (*treePtr != NULL)
        {
            (*treePtr)->data_L = string[i];  i++;  //�Nstring�̪��ȥ[�Jdata_L
            (*treePtr)->left_child = NULL;         //Left_child��Ȥ�
            (*treePtr)->middle_child = NULL;       //middle_child��Ȥ�
            (*treePtr)->right_child = NULL;        //right_child��Ȥ�
        }//end if �ڸ`�I�]��
    }
    else  //�p�G���O�@�ӪŪ�tree�h�[�J�s��
    {
        //��data_R = -1 �B �[�J���Ȥ�data_L�j
		if ( (string[i] > (*treePtr)->data_L) && ((*treePtr)->data_R == -1) )
            choice = 1;
        //��data_R = -1 �B �[�J���Ȥ�data_L�p
        else if ( (string[i] < (*treePtr)->data_L) && ((*treePtr)->data_R == -1) )
            choice = 2;
        //��data_R != -1 �B �[�J���Ȥ�data_L�p �h�[�J���`�I
        else if ( string[i] < (*treePtr)->data_L && ((*treePtr)->data_R != -1) )
            choice = 3;
        //��data_R != -1 �B ����data_l & data_R �[�J�������`�I
        else if ( (string[i] < (*treePtr)->data_R && string[i] > (*treePtr)->data_L) && ((*treePtr)->data_R != -1) )
            choice = 4;
        //��data_R != -1 �B �[�J���Ȥ�data_R�j �h�[�J�k�`�I
        else if ( string[i] > (*treePtr)->data_R && ((*treePtr)->data_R != -1) )
            choice = 5;
        switch(choice)
        {
            case 1:  //�[�J�Ȩ�data_R
               (*treePtr)->data_R = string[i];  i++;  break;
            case 2:  //�[�J�Ȩ�data_R �öi��swap
               (*treePtr)->data_R = (*treePtr)->data_L;
               (*treePtr)->data_L = string[i];  i++;  break;
            case 3:  //�bleft_child�s�W�@�Ӹ`�I �ñN�ȥ[�J�s���Idata_L
               insert(&((*treePtr)->left_child), string);  break;
            case 4:  //�bmiddle_child�s�W�@�Ӹ`�I �ñN�ȥ[�J�s���Idata_L
               insert(&((*treePtr)->middle_child), string);  break;
            case 5:  //�bright_child�s�W�@�Ӹ`�I �ñN�ȥ[�J�s���Idata_L
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
