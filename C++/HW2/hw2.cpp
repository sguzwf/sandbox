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
	
	cout	<< "�п�J�n�}�Ҫ��ɮצW�١G";
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
	cout	<< "�{�b��"	<< Set::now_Set	<< "��Set�C"	<< endl;
	for(i=0;i<Set::now_Set;i++){
		cout	<<"Set "	<< i	<< " ";
		Set::list[i]->show();
	}
	cout	<< "�z�Q�n......�H"	<< endl
		<< "1.�W�[�@�ӷs���r��Y��Set��"	<< endl
		<< "2.��Y��Set�����Y�Ӧr����"	<< endl
		<< "�п�J1��2"	<< endl;
	cin	>> selection;

	if(selection==1){
		cout	<< "�A�n�[�J����r�H"	<< endl;
		cin	>> word;
		cout	<< "�A�n�[�쨺�@��Set���]0~"	<< Set::now_Set << "�^"	<< endl;
		cin 	>> selection;
	}else if(selection==2){
	}
}*/
