#include"includes/Book.h"
#include<iostream>
#include<fstream>
using namespace std;

int main(){
	char data[256];
	ifstream input;
	input.open("HW3.dat");
	input.getline(data,256);
	Linked_List *Head;
	Linked_List *Current_Ptr;
	Head=new Linked_List(Head,data);
	Current_Ptr=Head;

	while(!input.eof()){
		input.getline(data,256);
		Current_Ptr->to_next=new Linked_List(Current_Ptr,data);
		Current_Ptr=Current_Ptr->to_next;
	}
	Current_Ptr=Head;
	while(Current_Ptr!=NULL){
		Current_Ptr->to_Book->show_data();
		Current_Ptr=Current_Ptr->to_next;
	}
	return 0;
}
