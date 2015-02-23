#include<iostream>
#include"includes/Book.h"
using namespace std;

int main(){
	Book *MAHORO;
	MAHORO = new Book;
	MAHORO->PUT_title("MAHORO");
	MAHORO->PUT_author("中山文十郎，DITAMA");
	MAHORO->PUT_publisher("overflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowoverflowOVERFLOW!");

	cout	<< MAHORO->GET_title()	<< endl
		<< MAHORO->GET_author()	<< endl;

	MAHORO->show_data();
	delete MAHORO; //好難過的指令...
	return 0;
}
