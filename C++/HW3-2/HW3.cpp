#include<iostream>
#include"includes/Book.h"
using namespace std;

int main(){
	Book *MAHORO;
	MAHORO = new Book;
	MAHORO->PUT_title("MAHORO");
	MAHORO->PUT_author("���s��Q���ADITAMA");
	MAHORO->PUT_publisher("overflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowOVERFLOW!");

	cout	<< MAHORO->GET_title()	<< endl
		<< MAHORO->GET_author()	<< endl;

	MAHORO->show_data();
	delete MAHORO; //�n���L�����O...
	return 0;
}
