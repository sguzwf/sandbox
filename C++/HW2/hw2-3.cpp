#include<iostream>
using namespace std;

int main(){
	int i;
	int key=0;
	char word[256];

	cin	>> word;

	while(strcmp(word,"END")!=1){
		for(i=0;i<256;i++)
			key+=(int)word[i];
		cout	<< key%1001	<< endl;

		cin	>> word;
	}

	return 0;
}
