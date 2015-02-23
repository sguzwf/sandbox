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
		cout	<< "找不到歡迎畫面用的重要檔案welcome.dat"	<< endl
			<< "所以您所看到的歡迎畫面很爛......"	<< endl;

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
		<< "                      版本  0.4.9"	<< endl
		<< "                維護者: Kuanling Haung"	<< endl
		<< "              HW2 是要交給老師的程設作業" << endl
		<< endl
		<< "               請幫助成功大學的可憐學生!"	<< endl
		<< "         進一步說明請輸入               help<Enter>"	<< endl
		<< endl
		<< "         要開始使用請輸入               任意字<Enter>"	<< endl
		<< "         要離開請輸入                   exit<Enter>"	<< endl
		<< "         新版本資訊請輸入               new<Enter>"	<< endl;*/
	SELE();
	while(strcmp(key,"exit")!=0)MENU();	//應該可以改成while(1)
}

UI::~UI(){
	char ch;
	ifstream goodbye;
	system("exec tput clear");	//這一行應該只有UNIX系能用......
	goodbye.open("goodbye.dat");
	if(!goodbye)
		cout	<< "找不到結束畫面所需的重要檔案goodbye.dat"	<< endl
			<< "那就只好說聲bye囉。"	<< endl;

	while(!goodbye.eof()){
		goodbye.get(ch);
		ch^=137;
		cout	<< ch;
	}
/*	cout	<< "################################################################"	<< endl
		<< "            由Kuanling Haung和他的朋友們（誰呀）撰寫"	<< endl
		<< endl
		<< "       感謝您使用 HW2，我們誠心的希望您能在其中獲得許多樂趣"	<< endl
		<< "         如果你沒有，那你一定有點問題，和別人有些不同，且"	<< endl
		<< "               有點怪。所有用過這個程式的人都說好:p"	<< endl
		<< endl                                          
		<< "                   當然， HW2是用來交程設作業的"	<< endl
		<< "           如果你看到作者名稱不是Kuanling Haung而是別人"	<< endl
		<< "                        那那個人應該下地獄"	<< endl
		<< endl
		<< "              如果您在使用 HW2上有任何的問題，您可以"	<< endl
		<< "            撥打我們的客戶服務專線： (06)2757575-51342"	<< endl
		<< endl
		<< "                        HW2是在光一212寫的:"	<< endl
		<< "                     Programming: Kuanling Haung"	<< endl
		<< "                          Art: What art?"	<< endl
		<< "                      Design: Kuanling Haung"	<< endl
		<< "                      Design and Support: Fable"	<< endl
		<< endl
		<< "請輸入任意字結束..."	<< endl;*/
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
	cout	<< "現在有"	<< Set::now_Set	<<"個Set。"	<< endl;
		for(i=0;i<Set::now_Set;i++){
			cout	<< "Set "	<< i+1	<< "：";
			Set::list[i]->show();
		}
	cout	<< endl
		<< "您想要做什麼？"	<< endl
		<< "1.加入一個新的單字到某一個Set"	<< endl
		<< "2.從某一個Set中移除一個單字"	<< endl
		<< endl
		<< "3.對任意兩個Set做聯集"	<< endl
		<< "4.對任意兩個Set做交集"	<< endl
		<< "5.對任意兩個Set做差集"	<< endl
		<< endl
		<< "6.求最大集合"	<< endl;
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
	cout	<< "請輸入您要增加的字："	<< endl;
	cin	>> word;
	cout	<< "您要加到那一個Set呢？（1~"	<< Set::now_Set	<< "）"	<< endl;
	cin	>> i;
	Set::list[i-1]->put(word);
}
void UI::REMOVE(){
	int i;
	char word[52];
	cout	<< "請輸入您要刪除的字："	<< endl;
	cin	>> word;
	cout	<< "您要刪那一個Set裡的呢？（1~"	<< Set::now_Set	<< "）"	<< endl;
	cin	>> i;
	Set::list[i-1]->remove(word);
}
void UI::INT(){
	int i,j,selection;
	cout	<< "您想要做什麼呢？"	<< endl
		<< "1.秀出上次做的交集"	<< endl
		<< "2.做新的交集"	<< endl;
	cin	>> selection;
	if(selection==2){
		cout	<< "請輸入第一個Set的編號"	<< endl;
		cin	>> i;
		cout	<< "請輸入第二個Set的編號"	<< endl;
		cin	>> j;
		Set::list[i-1]->INTERSECT(Set::list[j-1]);
	}else if(selection==1){
		if(Set::ius[1]==NULL){
			cout	<< "你還沒有做過交集"	<< endl;
		}else{
			cout	<< "這是您上一次做的交集：";
			Set::ius[1]->show();
			cout	<< "請輸入任意字繼續..."	<< endl;
			SELE();
		}
	}
}
void UI::UNI(){
	int i,j,selection;
	cout	<< "您想要做什麼呢？"	<< endl
		<< "1.秀出上次做的聯集"	<< endl
		<< "2.做新的聯集"	<< endl;
	cin	>> selection;
	if(selection==2){
		cout	<< "請輸入第一個Set的編號"	<< endl;
		cin	>> i;
		cout	<< "請輸入第二個Set的編號"	<< endl;
		cin	>> j;
		Set::list[i-1]->UNION(Set::list[j-1]);
	}else if(selection==1){
		if(Set::ius[0]==NULL){
			cout	<< "您還沒有做過聯集"	<< endl;
		}else{
			cout	<< "這是您上一次做的聯集：";
			Set::ius[0]->show();
			cout	<< "請輸入任意字繼續..."	<< endl;
			SELE();
		}
	}
}
void UI::DIF(){
	int i,j,selection;
	cout	<< "您想要做什麼呢？"	<< endl
		<< "1.秀出上次做的差集"	<< endl
		<< "2.做新的差集"	<< endl;
	cin	>> selection;
	if(selection==2){
		cout	<< "請輸入第一個Set的編號"	<< endl;
		cin	>> i;
		cout	<< "請輸入第二個Set的編號"	<< endl;
		cin	>> j;
		Set::list[i-1]->SUBTRACT(Set::list[j-1]);
	}else if(selection==1){
		if(Set::ius[2]==NULL){
			cout	<< "您還沒有做過差集"	<< endl;
		}else{
			cout	<< "這是您上一次做的差集：";
			Set::ius[2]->show();
			cout	<< "請輸入任意字繼續..."	<< endl;
			SELE();
		}
	}
}
void UI::MAX(){
	cout	<< "以下會花一段時間，求取交集，聯集，和差集的最大集合。"	<< endl;
	Set::maximum();
	cout	<< "請輸入任意字繼續..."	<< endl;
	SELE();
}

void UI::HELP(){
	system("exec tput clear");
	cout	<< endl
		<< "HW2是一個簡單的作業，他實作了一個class『Set』，用來"	<< endl
		<< "存放一連串的單字。而你可以增刪任一Set中的單字，並且"	<< endl
		<< "對任意兩個Set做交集，聯集和差集。但是現在的版本，在"	<< endl
		<< "單字的存放量和Set的數量上都還有限制，詳情請參考"	<< endl
		<< "Change Log。"	<< endl
		<< endl
		<< "要使用這個程式，只要按照畫面上所指示的，輸入數字來"	<< endl
		<< "選擇要做的事就好了。"	<< endl
		<< endl
		<< "請輸入任意字繼續..."	<< endl;
	SELE();
}
void UI::NEW(){
	char ch;
	
	ifstream log;
	log.open("HW2.log");

	system("exec tput clear");
	
	if(!log){
		cout	<< "找不到HW2.log"	<<	endl
			<< "請檢查此作業壓縮檔的MD5（最好是真的有啦...）"	<< endl
			<< "這可能不是由Kuanling Haung交的"	<< endl;
		exit(0);
	}

	while(!log.eof()){
		log.get(ch);
		cout	<< ch;
	}

	cout	<< endl
		<< "請輸入任意字繼續..."	<< endl;
	SELE();
}
