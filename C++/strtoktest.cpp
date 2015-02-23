#include<iostream>
using namespace std;

int main(){
	int i;
	char *result = NULL;
	char test[] = "This is a string";
	result=strtok(test," ");
	cout	<< result	<< endl;
	while(result!=NULL){
		result=strtok(NULL," ");
		cout	<< result	<< endl;
	}
	return 0;
}
