#include <iostream>
using namespace std;

int main(){
	int A[20]={20,3,12,8,42,2,5,32,21,13,14,1,25,38,14,31,17,10,9,6};
	int i,j,key;

	for(j=1;j<20;j++){
		key = A[j];
		for(i=j-1;A[i]>key;i--)
			A[i+1] = A[i];
		A[i+1] = key;
	}

	for(i=0;i<20;i++)
		cout	<< A[i]	<< " ";
	cout 	<< endl;
}
