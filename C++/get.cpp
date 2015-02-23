#include<iostream>
#include<fstream>
#include<bitset>
using namespace std;

int main(){
	int i;
	char ch[10];
	
	ifstream fin;
	ofstream fout;
	fout.open("data.ta");
	fout.put('\x01');
	fout.put('\x02');
	fout.put('\x03');
	fout.put('\x04');
	fout.put('\x05');
	fout.put('\x06');
	fout.put('\x07');
	fout.put('\x08');
	fout.put('\x09');
	fout.put('\x00');
	fout.close();

	fin.open("data.ta");
	fin.get(ch,10);
	for(i=0;i<10;i++)
		cout	<< bitset<8>(ch[i])	<< " "	<< endl;

	fout.open("data",ios::app);
	fout	<< ch	<< endl;
	fout.close();
	return 0;
}
