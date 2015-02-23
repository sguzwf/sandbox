#include<cstdlib>
#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

class Set{
public:
	Set();	//歸零用...
	void insert(int);
	void remove(int);
	Set operator+(Set &);
	Set operator-(Set &);
	Set operator*(Set &);
	Set operator++();
	Set operator++(int);
	Set operator--();
	Set operator--(int);
	friend ostream &operator<<(ostream &,Set &);
	friend istream &operator>>(istream &,Set &);
	int *GET_data();
	void SHOW_data();
private:
	int data[100];
	unsigned int len;
};

void Set::insert(int num){
	int i;
	bool the_same = false;
	for(i=len-1;i>=0;i--)
		if(data[i]==num)
			the_same = true;	//check if any value == what we want to insert.
	//if everything is different.
	if(!the_same){
		data[len] = num;
		for(i=len;num<data[i-1]&&i!=0;i--)
			data[i]^=data[i-1]^=data[i]^=data[i-1];
		len++;
	}
}

void Set::remove(int num){
	int i,j;
	for(i=0;i<len;i++){
		if(data[i]==num){
			for(j=i;j<len;j++)
				data[j]=data[j+1];
			len--;
			break;
		}
	}
}

Set::Set(){
	int i;
	for(i=0;i<100;i++)
		data[i] = -1;
	len = 0;
}

Set Set::operator+(Set &c){
	int i;
	bool the_same = false;
	Set tmp;
	cout	<< "operator +"	<< endl;

	for(i=0;i<len;i++)	//copy this object to object tmp.
		tmp.data[i] = data[i];
	tmp.len = len;

	for(i=0;i<c.len;i++)
		tmp.insert(c.data[i]);

	//insert and sort.

	return tmp;
}

Set Set::operator-(Set &c){
	int i;
	Set tmp;
	cout	<< "operator -"	<< endl;

	for(i=0;i<len;i++)
		tmp.data[i] = data[i];
	tmp.len = len;

	for(i=0;i<c.len;i++)
		tmp.remove(c.data[i]);
	
	return tmp;
}

Set Set::operator*(Set &c){
	int i,j;
	Set tmp;
	cout	<< "operator *"	<< endl;

	for(i=0;i<c.len;i++)
		for(j=c.data[i];j>=0;j--)
			if(c.data[i]==data[j])
				tmp.insert(c.data[i]);
	return tmp;
}

Set Set::operator++(int){
	int i;
	Set tmp;
	cout	<< "postfix operator ++"	<< endl;

	for(i=0;i<len;i++)
		tmp.data[i] = data[i]++;
	tmp.len = len;
	
	return tmp;
}

Set Set::operator++(){
	int i;
	cout	<< "prefix operator ++"	<< endl;
	for(i=0;i<len;i++)
		++data[i];
	return *this;
}

Set Set::operator--(int){
	int i;
	Set tmp;
	cout	<< "postfix operator --"	<< endl;

	for(i=0;i<len;i++)
		tmp.data[i] = data[i]--;
	tmp.len = len;
	
	return tmp;
}

Set Set::operator--(){
	int i;
	cout	<< "prefix operator --"	<< endl;
	
	for(i=0;i<len;i++)
		--data[i];
	return *this;
}

ostream &operator<<(ostream &s,Set &c){	//s表示stream吧? 那c表示class...
	int i;
	cout	<< "operator <<"	<< endl;
	for(i=0;i<c.len;i++)
		s	<< c.data[i];
	s	<< endl;
	return s;
}

istream &operator>>(istream &s,Set &c){
	int num;
	char *tmp,temp[256],line[256];
	cout	<< "please enter number(s):"	<< endl;
	tmp = temp;
	s.getline(line,256);
	strncpy(tmp,strtok(line," 　"),256);
	while(tmp!=NULL){
		cout	<< "Start"	<< endl;
		c.insert(atoi(tmp));
		cout	<< "Maou"	<< endl;
		strncpy(tmp,strtok(NULL," 　"),256);
	}
	return s;
	
}	//並不像我想的那樣簡單...果然還是要唸書

int *Set::GET_data(){
	return data;
}

void Set::SHOW_data(){
	int i;
	if(len==0)
		cout	<< "No data";
	for(i=0;i<len;i++)
		cout 	<< data[i]	<< " ";
	cout	<< endl;
}

int main(){
	Set A,B,C;

	cin	>> A;
	cin	>> B;

	C = A + B;
	C.SHOW_data();
	C = A - B;
	C.SHOW_data();
	C = A * B;
	C.SHOW_data();
	C = A++;
	C.SHOW_data();
	A.SHOW_data();
	C = ++A;
	C.SHOW_data();
	A.SHOW_data();
	C = A--;
	C.SHOW_data();
	A.SHOW_data();
	C = --A;
	C.SHOW_data();
	A.SHOW_data();

	cout	<< C;
	return 0;
}
