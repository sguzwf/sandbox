#include<iostream>
#include<fstream>
#define MAX_LINE_CHAR 6000
#define MAX_ELEMENT_LENGTH 52
#define MAX_ELEMENT_NUM 1000
#define MAX_SET_NUM 1000
using namespace std;

class Set{
public:
	Set(char *filename){	//建構函式，用來讀入某檔案
		int i;
		now_Set=0;
		
		cerr	<< "Set::Set(filename);"	<< endl;
		
		ifstream input;
		cout	<< "宣告開檔"	<< endl;
		input.open(filename);

		for(i=0;i<3;i++)
			ius[i]=NULL;
		
		if(!input){	//沒有找到要開的檔案
			cout	<< "沒有找到"	<< filename	<< endl;
			exit(0);
		}
		
		while(input.getline(temp,MAX_LINE_CHAR)){
			list[now_Set]= new Set;
			strncpy(list[now_Set]->line,temp,MAX_LINE_CHAR);
			list[now_Set]->put(list[now_Set]->line);
			now_Set++;
		}
	}
	Set(){	//普通的建構函式
		int i;
		cerr	<< "Set::Set();"	<< endl;
		now_element=0;
		for(i=0;i<MAX_ELEMENT_NUM;i++)
			data[i][0]='\0';
	}
	~Set(){	//解構函式，用來寫入資料到某檔案，目前的結果是一整個錯（什麼都沒有寫）
		int i;
		cerr	<< "Set::~Set();"	<< endl;
		ofstream output;
		output.open("output.txt",ios::app);	//不確定用法。
		output	<<	data[0];
		for(i=1;i<now_element;i++)
			output	<< " "	<<	data[i];
		output	<< endl;
		output.close();
	}
	void put(char *);	//把Constructor交過來的line切成一個一個的element。
	//void add(char*);	//加入新元素到這個class中。1.10.15後取消他的功能，由put取代
	void remove(char*);	//移除指定的元素。
	void show();	//把這個class中的元素都印在螢幕上。

	char* lower(char*);
	
	Set* INTERSECT(Set*);	//把指定的兩個class中的元素，做交集，存成一個（前者）。
	Set* UNION(Set*);	//把指定兩個class中的元素，做聯集，存成一個（前者）。
	Set* SUBTRACT(Set*);//把指定兩個class中的元素，取差集，存成一個（前者）。

	//int now_element;	//我現在知道FRIEND是用來幹嘛的了Orz
	
	static char temp[MAX_LINE_CHAR];
	static int now_Set;
	static Set* list[MAX_SET_NUM];
	static void maximum();
	static Set* ius[3];
private:
	int now_element;	//存元素的陣列中，現在空的那一個。
	//static int now_Set=0;	//存Set的static元素中，現在空的那一個。
	char data[MAX_ELEMENT_NUM][MAX_ELEMENT_LENGTH];	//存讀入的元素的。
	//static Set* list[1000];	//存現在存在的Set的。
	char line[MAX_LINE_CHAR];
};

void Set::put(char *line){
	int i;
	char *result=NULL;
	cerr	<< "Set::put(char*);"	<< endl;
	//cout	<< "Set::put()"	<< endl;	//debug用
	result=strtok(line," \0");
	while(result!=NULL){
		for(i=0;i<now_element&&strcmp(lower(data[i]),lower(result))!=0;i++);
			if(i==now_element){
				strcpy(data[now_element],result);
				now_element++;
		}
		result=strtok(NULL," \0");
	}
}

/*void Set::add(char *word){	//判斷大小寫得寫在這裡
	int i;
	//cout	<< "Set::add()"	<< endl;	//debug用
	for(i=0;i<now_element&&strcmp(lower(data[i]),lower(word))!=0;i++);
	if(i==now_element){
		strcpy(data[now_element],word);
		now_element++;
	}
}*/
void Set::remove(char *word){
	int i,j;
	cerr	<< "Set::remove(char*);"	<< endl;
	//cout	<< "Set::remove()"	<< endl;	//debug用
	i=0;
	while(i<now_element){
		if(strcmp(data[i],word)!=0){
			i++;
		}else{
			if(now_element==1){
				strncpy(data[0],"<空的集合>",52);	//這個東西會很白痴的印到output嗎？
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
	cerr	<< "Set::show();"	<< endl;
	for(i=0;i<now_element;i++)
		cout	<< " "	<< data[i];
	cout	<< endl;
}

char* Set::lower(char* word){
	cerr	<< "Set::lower(char*);"	<< endl;
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

Set* Set::UNION(Set* S){
	int i;
	cerr	<< "UNION"	<< endl;
	ius[0]=new Set;
	for(i=0;i<now_element;i++)
		ius[0]->put(data[i]);
	for(i=0;i<S->now_element;i++)
		ius[0]->put(S->data[i]);
	return ius[0];
}
Set* Set::INTERSECT(Set* S){
	int i,j;
	cerr	<< "INTERSECT"	<< endl;
	ius[1]=new Set;
	for(i=0;i<now_element;i++)
		for(j=0;j<S->now_element;j++)
			if(strcmp(lower(data[i]),lower(S->data[j]))==0)
				ius[1]->put(data[i]);
	return ius[1];
}
Set* Set::SUBTRACT(Set* S){
	int i,j;
	cerr	<< "SUBTRACT"	<< endl;
	ius[2]=new Set;
	for(i=0;i<now_element;i++)
		ius[2]->put(data[i]);
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
	cerr	<< "Set::maximum"	<< endl;
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
	cout	<< "這是最大的聯集"	<< endl;
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
	cout	<< "這是最大交集"	<< endl;
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
	cout	<< "這是最大差集"	<< endl;
	max_ius[2]->show();
}
