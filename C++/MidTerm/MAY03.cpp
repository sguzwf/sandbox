#include<iostream>
using namespace std;

class B{
	public:
		static int s;
		B(){	cout	<< "B Start s="	<< ++s	<< endl;}
		~B(){	cout	<< "B End s="	<< s--	<< endl;}
};

class C: public B{
	public:
		C(){	cout	<< "C Start s="	<< ++s	<< endl;}
		~C(){	cout	<< "C End s="	<< s--	<< endl;}
};

class D: public C{
	public:
		D(){	cout	<< "D Start s="	<< ++s	<< endl;}
		~D(){	cout	<< "D End s="	<< s--	<< endl;}
};

int B::s = 0;
void function();

int main(){
	int i;
	B b1;
	for(i=0;i<100;i++)
		b1.s++;
	D d1;
	for(i=0;i<100;i++)
		++d1.s;
	return 0;
}

void function(){
	C c1;
}
