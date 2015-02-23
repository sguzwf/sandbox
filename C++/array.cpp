#include<iostream>
using namespace std;
int main(){
	char one[10][10],two[10][10],three[10]="Maou";
	two[2] = three;
	one[2] = two[2];
	cout	<< one[2];
	return 0;
}
