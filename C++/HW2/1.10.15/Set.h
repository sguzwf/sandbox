#include<iostream>
#include<fstream>
#define MAX_LINE_CHAR 6000
#define MAX_ELEMENT_LENGTH 52
#define MAX_ELEMENT_NUM 1000
#define MAX_SET_NUM 1000
using namespace std;

class Set{
public:
	Set(char *filename){	//�غc�禡�A�Ψ�Ū�J�Y�ɮ�
		int i;
		now_Set=0;
		
		ifstream input;
		cout	<< "�ŧi�}��"	<< endl;
		input.open(filename);

		for(i=0;i<3;i++)
			ius[i]=NULL;
		
		if(!input){	//�S�����n�}���ɮ�
			cout	<< "�S�����"	<< filename	<< endl;
			exit(0);
		}
		
		while(input.getline(temp,MAX_LINE_CHAR)){
			list[now_Set]= new Set;
			strncpy(list[now_Set]->line,temp,MAX_LINE_CHAR);
			list[now_Set]->put();
			now_Set++;
		}
	}
	Set(){	//���q���غc�禡
		int i;
		now_element=0;
		for(i=0;i<MAX_ELEMENT_NUM;i++)
			data[i][0]='\0';
	}
	~Set(){	//�Ѻc�禡�A�ΨӼg�J��ƨ�Y�ɮסA�ثe�����G�O�@��ӿ��]���򳣨S���g�^
		int i;
		ofstream output;
		output.open("output.txt",ios::app);	//���T�w�Ϊk�C
		output	<<	data[0];
		for(i=1;i<now_element;i++)
			output	<< " "	<<	data[i];
		output	<< endl;
		output.close();
	}
	void put();	//��Constructor��L�Ӫ�line�����@�Ӥ@�Ӫ�element�C
	void add(char*);	//�[�J�s������o��class���C
	void remove(char*);	//�������w�������C
	void show();	//��o��class�����������L�b�ù��W�C

	char* lower(char*);
	
	Set* INTERSECT(Set*);	//����w�����class���������A���涰�A�s���@�ӡ]�e�̡^�C
	Set* UNION(Set*);	//����w���class���������A���p���A�s���@�ӡ]�e�̡^�C
	Set* SUBTRACT(Set*);//����w���class���������A���t���A�s���@�ӡ]�e�̡^�C

	//int now_element;	//�ڲ{�b���DFRIEND�O�ΨӷF�����FOrz
	
	static char temp[MAX_LINE_CHAR];
	static int now_Set;
	static Set* list[MAX_SET_NUM];
	static void maximum();
	static Set* ius[3];
private:
	int now_element;	//�s�������}�C���A�{�b�Ū����@�ӡC
	//static int now_Set=0;	//�sSet��static�������A�{�b�Ū����@�ӡC
	char data[MAX_ELEMENT_NUM][MAX_ELEMENT_LENGTH];	//�sŪ�J���������C
	//static Set* list[1000];	//�s�{�b�s�b��Set���C
	char line[MAX_LINE_CHAR];
};

void Set::put(){
	char *result=NULL;
	//cout	<< "Set::put()"	<< endl;	//debug��
	result=strtok(line," ");
	while(result!=NULL){
		add(result);
		result=strtok(NULL," ");
	}
}

void Set::add(char *word){	//�P�_�j�p�g�o�g�b�o��
	int i;
	//cout	<< "Set::add()"	<< endl;	//debug��
	for(i=0;i<now_element&&strcmp(lower(data[i]),lower(word))!=0;i++);
	if(i==now_element){
		strcpy(data[now_element],word);
		now_element++;
	}
}
void Set::remove(char *word){
	int i,j;
	//cout	<< "Set::remove()"	<< endl;	//debug��
	i=0;
	while(i<now_element){
		if(strcmp(data[i],word)!=0){
			i++;
		}else{
			if(now_element==1){
				strncpy(data[0],"<�Ū����X>",52);	//�o�ӪF��|�ܥշ����L��output�ܡH
				now_element=0;
			}else{
				j=i;
				while(j<now_element){
					//cout	<< "Set::remove()"	<< endl;
					strcpy(data[j],data[j+1]);
					j++;
				}
				now_element--;
			}
		}
	}
}
void Set::show(){
	int i;
	for(i=0;i<now_element;i++)
		cout	<< " "	<< data[i];
	cout	<< endl;
}

char* Set::lower(char* word){
	//cout	<< "lower();"	<< endl;
	int c;
	char* i;
	i=new char[MAX_ELEMENT_LENGTH];
	//cout	<< "new done"	<< endl;
	strncpy(i,word,MAX_ELEMENT_LENGTH);
	//cout	<< "strncpy done"	<< endl;
	c=0;
	while(strcmp(&i[c],"\0")!=0){
		//cout	<< "while"	<< endl;
		if(i[c]>64&&i[c]<=90)
			i[c]+=32;
		c++;
	}
	return i;
}

Set* Set::INTERSECT(Set* S){
	int i;
	ius[0]=new Set;
	for(i=0;i<now_element;i++)
		ius[0]->add(data[i]);
	for(i=0;i<S->now_element;i++)
		ius[0]->add(S->data[i]);
	return ius[0];
}
Set* Set::UNION(Set* S){
	int i,j;
	ius[1]=new Set;
	for(i=0;i<now_element;i++)
		for(j=0;j<S->now_element;j++)
			if(strcmp(lower(data[i]),lower(S->data[j]))==0)
				ius[1]->add(data[i]);
	return ius[1];
}
Set* Set::SUBTRACT(Set* S){
	int i,j;
	ius[2]=new Set;
	for(i=0;i<now_element;i++)
		ius[2]->add(data[i]);
	for(i=0;i<now_element;i++)
		for(j=0;j<S->now_element;j++)
			if(strcmp(lower(data[i]),lower(S->data[j]))==0)
				ius[2]->remove(data[i]);
	return ius[2];
}

int Set::now_Set;
char Set::temp[];
Set* Set::list[];
Set* Set::ius[];
void Set::maximum(){
	int i,j;
	int max_element;
	Set* this_Set;
	Set* max_ius[3];
	
	for(i=0,max_element=0;i<now_Set;i++)
		for(j=0;j<now_Set;j++){
			this_Set=(list[i]->INTERSECT(list[j]));
			if(this_Set->now_element>max_element){
				max_element=this_Set->now_element;
				max_ius[0]=this_Set;
			}
		}
	ius[0]=max_ius[0];
	cout	<< "�o�O�̤j���p��"	<< endl;
	max_ius[0]->show();
	
	for(i=0,max_element=0;i<now_Set;i++)
		for(j=0;j<now_Set;j++){
			this_Set=(list[i]->UNION(list[j]));
			if(this_Set->now_element>max_element){
				max_element=this_Set->now_element;
				max_ius[1]=this_Set;
			}
		}
	ius[1]=max_ius[1];
	cout	<< "�o�O�̤j�涰"	<< endl;
	max_ius[1]->show();
	
	for(i=0,max_element=0;i<now_Set;i++)
		for(j=0;j<now_Set;j++){
			this_Set=(list[i]->SUBTRACT(list[j]));
			if(this_Set->now_element>max_element){
				max_element=this_Set->now_element;
				max_ius[2]=this_Set;
			}
		}
	ius[2]=max_ius[2];
	cout	<< "�o�O�̤j�t��"	<< endl;
	max_ius[2]->show();
}
