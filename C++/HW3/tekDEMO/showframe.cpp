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
		//if(ch!='\n'){	//應該會在判斷中文時出問題。
		if(ch1==EOF){
			cout	<< "               |";
		}else{
			for(i=0;i<16;i++){
				manu.get(ch1);
				cout	<< ch1;
			}
		}
		//}else{
		cout	<< "　";
		for(x=0;x<30;x++){	//中文又會爛掉
			main.get(ch2);
			cout	<< ch2;
		}
		cout	<< endl;
		//}
	}

	cout	<< "請輸入任意鍵繼續"	<< endl;
	cin >> ch2;

	manu.close();
	main.close();

	return 0;
}
