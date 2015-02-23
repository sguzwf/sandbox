#include<iostream>
#include<fstream>
#include"string.h"
using namespace std;

class Book{	//The base class Book class should include private data members to represent a bookˇs title, author, publisher, published-year, review_class, and price. 
	public:
		Book(){
			title[0]='\0';
			author[0]='\0';
			publisher[0]='\0';
			published_year[0]='\0';
			review_class[0]='\0';
			price[0]='\0';
			output_done = 0;
		}
		virtual void read_data();
		virtual void show_data();
		void output();
		bool output_done;
		virtual ~Book(){
			if(!output_done)
				output();
		}
	private:
		char title[256];
		char author[256];
		char publisher[256];
		char published_year[5];
		char review_class[6];
		char price[9];
};
void Book::read_data(){
	strncpy(title,strtok(NULL," "),256);
	strncpy(author,strtok(NULL," "),256);
	strncpy(publisher,strtok(NULL," "),256);
	strncpy(published_year,strtok(NULL," "),5);
	strncpy(review_class,strtok(NULL," "),6);
	strncpy(price,strtok(NULL," "),9);
}
void Book::show_data(){
	cout	<< ":"	<< title	<< endl
		<< ":"	<< author	<< endl
		<< ":"	<< publisher	<< endl
		<< ":"	<< published_year	<< endl
		<< "蝶だ:"	<< review_class	<< endl
		<< "基:"	<< price	<<endl;
}
void Book::output(){	//Destructorぃ∕﹚抖
	ofstream outfile;
	outfile.open("HW3.log",ios::app);
	if(!output_done)
		outfile	<< "Book"	<< " ";
	outfile	<< title	<< " "
		<< author	<< " "
		<< published_year	<< " "
		<< review_class	<< " "
		<< price;
	if(!output_done)
		outfile	<< endl;	
	outfile.close();
}

class SF:public Book{
	public:
		SF(){
			sale_price[0]='\0';	//How?
			scientist[0]='\0';
		}
		virtual void read_data();
		virtual void show_data();
		~SF(){	//禲ЧDestructor,ぃ禲BookDestructor?
			ofstream outfile;
			outfile.open("HW3.log",ios::app);
			output_done = 1;
			outfile	<< "Science_Story"	<< " ";
			Book::output();
			outfile	<< sale_price	<< " "
				<< scientist	<< endl;
			outfile.close();
		}
	private:
		char sale_price[9];
		char scientist[256];
};
void SF::read_data(){
	Book::read_data;
	//strncpy(title,strtok(NULL," "),256);
	//strncpy(author,strtok(NULL," "),256);
	//strncpy(publisher,strtok(NULL," "),256);
	//strncpy(published_year,strtok(NULL," "),5);
	//strncpy(review_class,strtok(NULL," "),6);
	//strncpy(price,strtok(NULL," "),9);
	strncpy(sale_price,strtok(NULL," "),9);
	strncpy(scientist,strtok(NULL," "),256);
}
void SF::show_data(){
	Book::show_data;
	cout	//<< ":"	<< title	<< endl
		//<< ":"	<< author	<< endl
		//<< ":"	<< publisher	<< endl
		//<< ":"	<< published_year	<< endl
		//<< "蝶だ:"	<< review_class	<< endl
		//<< "基:"	<< price	<< endl
		<< "穦基:"	<< sale_price	<< endl
		<< "厩產(?):"	<< scientist	<< endl;
}

class Comic:public Book{
	public:
		Comic(){
			sale_price[0]='\0';
			actor[0]='\0';
		}
		virtual void read_data();
		virtual void show_data();
		~Comic(){
			ofstream outfile;
			outfile.open("HW3.log",ios::app);
			output_done = 1;
			outfile	<< "Comic_Story"	<< " ";
			Book::output();
			outfile	<< sale_price	<< " "
				<< actor	<< endl;
			outfile.close();
		}
	private:
		char sale_price[9];
		char actor[256];
};
void Comic::read_data(){
	Book::read_data;
	//strncpy(title,strtok(NULL," "),256);
	//strncpy(author,strtok(NULL," "),256);
	//strncpy(publisher,strtok(NULL," "),256);
	//strncpy(published_year,strtok(NULL," "),5);
	//strncpy(review_class,strtok(NULL," "),6);
	//strncpy(price,strtok(NULL," "),9);
	strncpy(sale_price,strtok(NULL," "),9);
	strncpy(actor,strtok(NULL," "),256);
}
void Comic::show_data(){
	Book::show_data;
	cout	//<< ":"	<< title	<< endl
		//<< ":"	<< author	<< endl
		//<< ":"	<< publisher	<< endl
		//<< ":"	<< published_year	<< endl
		//<< "蝶だ:"	<< review_class	<< endl
		//<< "基:"	<< price	<< endl
		<< "穦基:"	<< sale_price	<< endl
		<< "簍(?):"	<< actor	<< endl;
}

class Linked_List{
	public:
		Linked_List(Linked_List*,char *);
		static void search(char *);
		~Linked_List();
		Book *to_Book;
		Linked_List *to_next;	//Destructorよ獽
		Linked_List *to_previous;
};

Linked_List::Linked_List(Linked_List *previous_Ptr, char *data){
	to_next = NULL;
	to_previous = previous_Ptr;
	if("Book",(strtok(data," "))==0){
		to_Book = new Book;
	}else if("Science_Story",(strtok(data," "))==0){
		to_Book = new SF;
	}else if("Comic_Story",(strtok(data," "))==0){
		to_Book = new Comic;
	}
	to_Book->read_data();
}

Linked_List::~Linked_List(){
	if(to_next!=NULL){
		to_next->to_previous = to_previous;
		to_previous->to_next = to_next;
	}else{
		to_previous->to_next = NULL;
	}
	delete to_Book;
}

void Linked_List::search(char *target){
	cout	<<	"Under Construction."	<< endl;
}
