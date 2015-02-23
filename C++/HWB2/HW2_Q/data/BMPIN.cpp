#include<iostream>
#include<fstream>
#include<iomanip>
#include<bitset>
using namespace std;

int main(){
	int i;
	char ch;
	ifstream bmp;
	bmp.open("t.bmp");
	cout.setf(ios::hex,ios::basefield);
	for(i=0;i<32;i++){
		bmp.get(ch);
		//if(ch<0)
			//ch = ~ch;
	cout	<< bitset<8>((int)ch)	<< " ";
	if((i+1)%4==0)
		cout	<< endl;
	}
	return 0;
}
