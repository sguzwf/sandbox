#define MAIN_HEIGHT 30
#define MAIN_WIDTH 50

#include<iostream>
#include<fstream>
using namespace std;

int main(){
	ifstream manu;
	ifstream main;

	int x,y,i;
	
	char ch1;
	char ch2;

	manu.open("manu.dat");
	main.open("index.dat");
	
	manu.get(ch1);
	for(y=0;y<20;y++){
		//if(ch!='\n'){	//���ӷ|�b�P�_����ɥX���D�C
		if(ch1==EOF){
			cout	<< "               |";
		}else{
			for(i=0;i<16;i++){
				manu.get(ch1);
				cout	<< ch1;
			}
		}
		//}else{
		cout	<< "�@";
		for(x=0;x<30;x++){	//����S�|�걼
			main.get(ch2);
			cout	<< ch2;
		}
		cout	<< endl;
		//}
	}

	cout	<< "�п�J���N���~��"	<< endl;
	cin >> ch2;

	manu.close();
	main.close();

	return 0;
}
