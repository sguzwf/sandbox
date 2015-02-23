#include<iostream>
#include<fstream>
#include"Set.h"
#include"UI.h"

using namespace std;

int main(){
	int i;
	int selection;
	
	char filename[260];

	//cout	<< "main()"	<< endl;
	
	cout	<< "請輸入要開啟的檔案名稱：";
	cin	>> filename ;
	Set A(filename);
	UI HW2;
	for(i=0;i<Set::now_Set;i++)
		delete Set::list[i];
	
	return 0;
}

/*void UI(){
	int i,selection;
	char word[52];
	cout	<< "現在有"	<< Set::now_Set	<< "個Set。"	<< endl;
	for(i=0;i<Set::now_Set;i++){
		cout	<<"Set "	<< i	<< " ";
		Set::list[i]->show();
	}
	cout	<< "您想要......？"	<< endl
		<< "1.增加一個新的字到某個Set中"	<< endl
		<< "2.把某個Set中的某個字移除"	<< endl
		<< "請輸入1或2"	<< endl;
	cin	>> selection;

	if(selection==1){
		cout	<< "你要加入什麼字？"	<< endl;
		cin	>> word;
		cout	<< "你要加到那一個Set中（0~"	<< Set::now_Set << "）"	<< endl;
		cin 	>> selection;
	}else if(selection==2){
	}
}*/
