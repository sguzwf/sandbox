#include<iostream>
#include<iomanip>
#include<bitset>
using namespace std;

int main(){
	int i;
	//ifstream chii;
	char in[13]="\x30\xD5\x30\xEC\x30\xE4";
	char out[13]="\x30\xA8\x30\xEB\x30\xC0";
	//chii.open("chii");
	//cin	>> in	>> out;
	wcout	<< in	<< " "	<< out	<< endl;
	for(i=0;i<13;i++){
		out[i] ^= in[i];
		cout << setw(2) << hex << (int)out[i] << " ";
	}
	cout 	<< endl;
	for(i=0;i<13;i++)
		cout	<< bitset<8>(out[i])	<< " ";
	cout << endl;
	return 0;
}
