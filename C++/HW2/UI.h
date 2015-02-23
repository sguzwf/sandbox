#include<iostream>
#include<fstream>
using namespace std;

class UI{
public:
	UI();
	~UI();

	void MENU();
	void SELE();
	void ADD();
	void REMOVE();
	void INT();
	void UNI();
	void DIF();
	void HELP();
	void NEW();
	void MAX();

	char key[260];
};

UI::UI(){
	char ch;
	ifstream welcome;
	system("exec tput clear");
	welcome.open("welcome.dat");
	if(!welcome)
		cout	<< "�䤣���w��e���Ϊ����n�ɮ�welcome.dat"	<< endl
			<< "�ҥH�z�Ҭݨ쪺�w��e������......"	<< endl;

	while(!welcome.eof()){
		welcome.get(ch);
		ch^=137;
		cout	<< ch;
	}
/*	cout	<< endl
		<< endl
		<< endl
		<< endl
		<< endl
		<< "                    HW2 - Homework 2"	<< endl
		<< endl
		<< "                      ����  0.4.9"	<< endl
		<< "                ���@��: Kuanling Haung"	<< endl
		<< "              HW2 �O�n�浹�Ѯv���{�]�@�~" << endl
		<< endl
		<< "               �����U���\�j�Ǫ��i���ǥ�!"	<< endl
		<< "         �i�@�B�����п�J               help<Enter>"	<< endl
		<< endl
		<< "         �n�}�l�ϥνп�J               ���N�r<Enter>"	<< endl
		<< "         �n���}�п�J                   exit<Enter>"	<< endl
		<< "         �s������T�п�J               new<Enter>"	<< endl;*/
	SELE();
	while(strcmp(key,"exit")!=0)MENU();	//���ӥi�H�令while(1)
}

UI::~UI(){
	char ch;
	ifstream goodbye;
	system("exec tput clear");	//�o�@�����ӥu��UNIX�t���......
	goodbye.open("goodbye.dat");
	if(!goodbye)
		cout	<< "�䤣�쵲���e���һݪ����n�ɮ�goodbye.dat"	<< endl
			<< "���N�u�n���nbye�o�C"	<< endl;

	while(!goodbye.eof()){
		goodbye.get(ch);
		ch^=137;
		cout	<< ch;
	}
/*	cout	<< "################################################################"	<< endl
		<< "            ��Kuanling Haung�M�L���B�̡ͭ]�֧r�^���g"	<< endl
		<< endl
		<< "       �P�±z�ϥ� HW2�A�ڭ̸ۤߪ��Ʊ�z��b�䤤��o�\�h�ֽ�"	<< endl
		<< "         �p�G�A�S���A���A�@�w���I���D�A�M�O�H���Ǥ��P�A�B"	<< endl
		<< "               ���I�ǡC�Ҧ��ιL�o�ӵ{�����H�����n:p"	<< endl
		<< endl                                          
		<< "                   ��M�A HW2�O�Ψӥ�{�]�@�~��"	<< endl
		<< "           �p�G�A�ݨ�@�̦W�٤��OKuanling Haung�ӬO�O�H"	<< endl
		<< "                        �����ӤH���ӤU�a��"	<< endl
		<< endl
		<< "              �p�G�z�b�ϥ� HW2�W�����󪺰��D�A�z�i�H"	<< endl
		<< "            �����ڭ̪��Ȥ�A�ȱM�u�G (06)2757575-51342"	<< endl
		<< endl
		<< "                        HW2�O�b���@212�g��:"	<< endl
		<< "                     Programming: Kuanling Haung"	<< endl
		<< "                          Art: What art?"	<< endl
		<< "                      Design: Kuanling Haung"	<< endl
		<< "                      Design and Support: Fable"	<< endl
		<< endl
		<< "�п�J���N�r����..."	<< endl;*/
	cin	>> key;
	if(strcmp(key,"doom2")==0)
		cout	<< "You know my joke :p"	<< endl;
}

void UI::SELE(){	
	cin	>> key;
	if(!strcmp(key,"help")){
		HELP();
	}else if(!strcmp(key,"exit")){
		return;
	}else if(!strcmp(key,"new")){
		NEW();
	}
}

void UI::MENU(){
	system("exec tput clear");
	int i;
	cout	<< "�{�b��"	<< Set::now_Set	<<"��Set�C"	<< endl;
		for(i=0;i<Set::now_Set;i++){
			cout	<< "Set "	<< i+1	<< "�G";
			Set::list[i]->show();
		}
	cout	<< endl
		<< "�z�Q�n������H"	<< endl
		<< "1.�[�J�@�ӷs����r��Y�@��Set"	<< endl
		<< "2.�q�Y�@��Set�������@�ӳ�r"	<< endl
		<< endl
		<< "3.����N���Set���p��"	<< endl
		<< "4.����N���Set���涰"	<< endl
		<< "5.����N���Set���t��"	<< endl
		<< endl
		<< "6.�D�̤j���X"	<< endl;
	SELE();
	if(!strcmp(key,"1")){
		ADD();
	}else if(!strcmp(key,"2")){
		REMOVE();
	}else if(!strcmp(key,"3")){
		UNI();
	}else if(!strcmp(key,"4")){
		INT();
	}else if(!strcmp(key,"5")){
		DIF();
	}else if(!strcmp(key,"6")){
		MAX();
	}
}

void UI::ADD(){
	int i;
	char word[260];
	cout	<< "�п�J�z�n�W�[���r�G"	<< endl;
	cin	>> word;
	cout	<< "�z�n�[�쨺�@��Set�O�H�]1~"	<< Set::now_Set	<< "�^"	<< endl;
	cin	>> i;
	Set::list[i-1]->put(word);
}
void UI::REMOVE(){
	int i;
	char word[52];
	cout	<< "�п�J�z�n�R�����r�G"	<< endl;
	cin	>> word;
	cout	<< "�z�n�R���@��Set�̪��O�H�]1~"	<< Set::now_Set	<< "�^"	<< endl;
	cin	>> i;
	Set::list[i-1]->remove(word);
}
void UI::INT(){
	int i,j,selection;
	cout	<< "�z�Q�n������O�H"	<< endl
		<< "1.�q�X�W�������涰"	<< endl
		<< "2.���s���涰"	<< endl;
	cin	>> selection;
	if(selection==2){
		cout	<< "�п�J�Ĥ@��Set���s��"	<< endl;
		cin	>> i;
		cout	<< "�п�J�ĤG��Set���s��"	<< endl;
		cin	>> j;
		Set::list[i-1]->INTERSECT(Set::list[j-1]);
	}else if(selection==1){
		if(Set::ius[1]==NULL){
			cout	<< "�A�٨S�����L�涰"	<< endl;
		}else{
			cout	<< "�o�O�z�W�@�������涰�G";
			Set::ius[1]->show();
			cout	<< "�п�J���N�r�~��..."	<< endl;
			SELE();
		}
	}
}
void UI::UNI(){
	int i,j,selection;
	cout	<< "�z�Q�n������O�H"	<< endl
		<< "1.�q�X�W�������p��"	<< endl
		<< "2.���s���p��"	<< endl;
	cin	>> selection;
	if(selection==2){
		cout	<< "�п�J�Ĥ@��Set���s��"	<< endl;
		cin	>> i;
		cout	<< "�п�J�ĤG��Set���s��"	<< endl;
		cin	>> j;
		Set::list[i-1]->UNION(Set::list[j-1]);
	}else if(selection==1){
		if(Set::ius[0]==NULL){
			cout	<< "�z�٨S�����L�p��"	<< endl;
		}else{
			cout	<< "�o�O�z�W�@�������p���G";
			Set::ius[0]->show();
			cout	<< "�п�J���N�r�~��..."	<< endl;
			SELE();
		}
	}
}
void UI::DIF(){
	int i,j,selection;
	cout	<< "�z�Q�n������O�H"	<< endl
		<< "1.�q�X�W�������t��"	<< endl
		<< "2.���s���t��"	<< endl;
	cin	>> selection;
	if(selection==2){
		cout	<< "�п�J�Ĥ@��Set���s��"	<< endl;
		cin	>> i;
		cout	<< "�п�J�ĤG��Set���s��"	<< endl;
		cin	>> j;
		Set::list[i-1]->SUBTRACT(Set::list[j-1]);
	}else if(selection==1){
		if(Set::ius[2]==NULL){
			cout	<< "�z�٨S�����L�t��"	<< endl;
		}else{
			cout	<< "�o�O�z�W�@�������t���G";
			Set::ius[2]->show();
			cout	<< "�п�J���N�r�~��..."	<< endl;
			SELE();
		}
	}
}
void UI::MAX(){
	cout	<< "�H�U�|��@�q�ɶ��A�D���涰�A�p���A�M�t�����̤j���X�C"	<< endl;
	Set::maximum();
	cout	<< "�п�J���N�r�~��..."	<< endl;
	SELE();
}

void UI::HELP(){
	system("exec tput clear");
	cout	<< endl
		<< "HW2�O�@��²�檺�@�~�A�L��@�F�@��class�ySet�z�A�Ψ�"	<< endl
		<< "�s��@�s�ꪺ��r�C�ӧA�i�H�W�R���@Set������r�A�åB"	<< endl
		<< "����N���Set���涰�A�p���M�t���C���O�{�b�������A�b"	<< endl
		<< "��r���s��q�MSet���ƶq�W���٦�����A�Ա��аѦ�"	<< endl
		<< "Change Log�C"	<< endl
		<< endl
		<< "�n�ϥγo�ӵ{���A�u�n���ӵe���W�ҫ��ܪ��A��J�Ʀr��"	<< endl
		<< "��ܭn�����ƴN�n�F�C"	<< endl
		<< endl
		<< "�п�J���N�r�~��..."	<< endl;
	SELE();
}
void UI::NEW(){
	char ch;
	
	ifstream log;
	log.open("HW2.log");

	system("exec tput clear");
	
	if(!log){
		cout	<< "�䤣��HW2.log"	<<	endl
			<< "���ˬd���@�~���Y�ɪ�MD5�]�̦n�O�u������...�^"	<< endl
			<< "�o�i�ण�O��Kuanling Haung�檺"	<< endl;
		exit(0);
	}

	while(!log.eof()){
		log.get(ch);
		cout	<< ch;
	}

	cout	<< endl
		<< "�п�J���N�r�~��..."	<< endl;
	SELE();
}
