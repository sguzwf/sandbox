/* classes.h
 * �o�O�@�ӧ�class���w�n���ɮסC
 * �]�N�O�{�����D��M�����C���Ӫ��o�i�N�������F���C
 * ���L�n�p��define���~�ΡC
 */
#include<iostream>
#define MAX_CHAR 256	//�W�r�ҥΪ��r���W���C
#define MAX_ITEM 20	//�@�Ӫ��~�ү�]�t�����~�ƤW���C

using namespace std;

class Room {
public:
	char name[MAX_CHAR];	//�F�誺�W�r�A�H�U����L����]�����ۤv���W�r�C
	char message[MAX_CHAR];	//�ԭz�Ϊ��T���C
	int height;	//���סA�bRoom�����O���C�b��L����A�h�������C
	int width;	//�e�סA�bRoom�����O�e�C
	Item* contain[MAX_ITEM];	//��ܸ˨�L�F�誺�a��C
};

class Item : public Room {
public:
	int weight;	//���q�A�o�ORoom�ҨS�����ݩʡC
	char addtional_message[MAX_CHAR];	//���~�Q�լd�ɪ��T���C
	//�o�������٦��@�ӭȡA��ܳo��Item�ϥΫ�|�]���@��function�A�Ө��ӭȬO��function��Ptr�C
	Room* where;	//�b���̡A�o��ܤ@��Item����m�A�bCreature�����o�@���O�Ҧb���ж��C
};

class Creature : public Item {
public:
	//�ͪ��~�����ʧ@�C
	Room* see(Room* where);	//�ݡA�����ݬO�C�X�o�өж��������~�C�]�i�H�ݬY���~�C
	Item* search(Item* be_search);	//�j���A½��@�����~�A�C�X���]�t�����~�C
	//Item* get();	//��Y���~���_�ӡC
	Item* drop();	//��Y���~�ᱼ�A�u���b�ж��̡C�i��y���o�өж������~�L�h�ӶW�L�}�C�������C
	Item* use();	//�ϥάY���~�A�i�H�F�����P���ĪG�C
};

Room* Creature::see(Room* where){
	int i;
	int empty_contain;
	char item_name[MAX_CHAR];
	bool empty = 1;
	bool get_done = 0;
	for(i=0;i<MAX_ITEM;i++)
		if(where->contain[i]!=NULL){	//��Ҧb�]where�^���F��C�X��
			cout	<< where->contain[i]->name	<< endl;
			empty = 0;
		}
	if(empty==1)	//�n�O�o�Ӧa��S���]�t����F��A�h�i�D���a���򳣨S���C
		cout	<< "���򳣨S��"	<< endl;
	if(empty==0){
		cout	<< "�A�Q�n���_����H"	<< endl
			<< ">>";
		cin	>> item_name;
		for(empty_contain=0;this.contain[empty_contain]!=NULL&&empty_contain<MAX_ITEM;empty_contain++);	//�䪫�~�椤���Ů�
		if(this.contain[empty_contain]==NULL){	//�ˬd�O���O�Ū��A�Y�O�Ū��N��n�D���F���i�h�C
			for(i=0;i<MAX_ITEM;i++)
				if(strcmp(item_name,where->contain[i]->name)==0){
					this.contain[empty_contain] = where->contain[i];
					where->contain[i] = NULL;
					get_done = 1;	//���ҭn���F��F�C
				}
		}else{
			cout	<< "�z�S���a��i�H�񥦤F"	<< endl;	//�S���Ŷ��N���񤣤U�C
		}
	}
	if(get_done==0)
		cout	<< "�o�̨S���o�ӪF��"	<< endl;	//�䤣��ҭn���F��C
}
Item* Creature::search(Item* be_search){
	int i;
	int empty_contain;
	char item_name[AX_CHAR];
	bool empty = 1;
	bool get_done = 0;
	for(i=0;i<MAX_ITEM;i++)
		if(be_search->contain[i]!=NULL){	//��Y���̪��F��C�X��
			cout	<< be_search->contain[i]->name	<< endl;
			empty = 0;
		}
	if(empty==1)	//�n�O�o�Ӧa��S���]�t����F��A�h�i�D���a���򳣨S���C
		cout	<< "���򳣨S��"	<< endl;
	if(empty==0){
		cout	<< "�A�Q�n���_����H"	<< endl
			<< ">>";
		cin	>> item_name;
		for(empty_contain=0;this.contain[empty_contain]!=NULL&&empty_contain<MAX_ITEM;empty_contain++);
		if(this.contain[empty_contain]==NULL){
			for(i=0;i<MAX_ITEM;i++)
				if(strcmp(item_name,be_search->contain[i]->name)==0){
					this.contain[empty_contain] = be_search->contain[i];
					be_search->contain[i] = NULL;
					get_done = 1;
				}
		}else{
			cout	<< "�z�S���a��i�H�񥦤F"	<< endl;
		}
	}
	if(get_done==0)
		cout	<< "�o�̨S���o�ӪF��"	<< endl;
}
//Item* Creature::get(char name[MAX_CHAR]){}
Item* Creature::drop(char be_drop[MAX_CHAR]){	//�ˬd�a�W���F�S�]�H�H�^�A�M��⨭�W���F���a�W�C			
}
Item* Creature:use(char be_use[MAX_CHAR]){	//����YItem���y�ĪG�zfunction�C
}
