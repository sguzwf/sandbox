#include<iostream>
#include<fstream>
using namespace std;

int main(){
	char word[100];
	ofstream cintest;
	cintest.open("cintest.txt");
	cin	>> word;
	cintest	<< word;
	cintest.close();
	return 0;
}
