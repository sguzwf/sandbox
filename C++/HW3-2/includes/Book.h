#include<fstream>
#include<iostream>
#include<string.h>
using namespace std;

class Book{
	public:
		Book(){
			cout	<< "Book::Constructor"	<< endl;
			title[0]='\0';
			author[0]='\0';
			publisher[0]='\0';
			published_year[0]='\0';
			review_class[0]='\0';
			price[0]='\0';
		}
		~Book(){
			cout	<< "Book::Destructor"	<< endl;
		}
		char *GET_title(){
			return title;
		}	//DATA PROCESSOR
		char *GET_author(){
			return author;
		}
		char *GET_publisher(){
			return publisher;
		}
		char *GET_published_year(){
			return published_year;
		}
		char *GET_review_class(){
			return review_class;
		}
		char *GET_price(){
			return price;
		}
		bool PUT_title(char *the_title){
			if(strlen(the_title)>256)
				cout	<< "夹肈,程256じ.ㄓ场盢砆┻斌"	<< endl;
			cout	<< strncpy(title,the_title,256)	<< endl;
			return true;
		}
		bool PUT_author(char *the_author){
			if(strlen(the_author)>256)
				cout	<< ",程256じ.ㄓ场盢砆┻斌"	<< endl;
			cout	<< strncpy(author,the_author,256)	<< endl;
			return true;
		}
		bool PUT_publisher(char *the_publisher){
			if(strlen(the_publisher)>256)
				cout	<< ",程256じ.ㄓ场盢砆┻斌"	<< endl;
			cout	<< strncpy(publisher,the_publisher,256)	<< endl;
			return true;
		}
		bool PUT_published_year(char *the_published_year){
			if(strlen(the_published_year)!=5)
				cout	<< "Τ"	<< endl;
			strncpy(published_year,the_published_year,5);
			return true;
		}
		bool PUT_review_class(char *the_review_class){
			if(strlen(the_review_class)>6)
				cout	<< "琍琍程き"	<< endl;
			strncpy(review_class,the_review_class,6);
			return true;
		}
		bool PUT_price(char *the_price){
			if(strlen(the_price)>16)
				cout	<< "基窥16"	<< endl;
			strncpy(price,the_price,16);
			return true;
		}
		
		virtual void show_data(){
			cout	<< "SHOWER"	<< endl
				<< GET_title()	<< endl
				<< GET_author()	<< endl
				<< GET_publisher()	<< endl
				<< GET_published_year()	<< endl
				<< GET_review_class()	<< endl
				<< GET_price()	<< endl;
		}	//SHOWER(?)
		virtual void read_data(){
			cout	<< "Nothing for now."	<< endl;
		}
	private:	//DATA MEMBERS
		char title[256];
		char author[256];
		char publisher[256];
		char published_year[5];
		char review_class[6];
		char price[16];
};
/*
class Science:public Book{
	public:
		Science();
		~Science();	//I have some problem about the Destructor.
		char *GET_sale_price();	//If I want to call those functions outside, it must be virtual.
		char *GET_scientist();
		bool PUT_sale_price(char *);
		bool PUT_scientist(char *);
		
		virtual void show_data();	//SHOWER(?)
		virtual void read_data();
	private:
		char sale_price[16];
		char scientist[256];
};

class Comic:public Book{
	public:
		Comic();
		~Comic();
		char *GET_sale_price();
		char *GET_actor();
		void *PUT_sale_price(char *);
		void *PUT_actor(char *);
	
		virtual void show_data();	//SHOWER(?)
		virtual void read_data();
	private:
		char sale_price[16];
		char actor[256];
};

class Reader{	//USELESS FOR THIS HW
};

class Writter{	//USELESS TOO
};

//Container -- Linked List

class Container{
	public:
		Container(Container *,Container *);
		~Container();
		static void search();
		Book *GET_Book_Ptr();
	private:
		Book *Book_Ptr;
		Container *Next_Ptr;	//Container Ptr can't be use by outher classes.
		Container *Previous_Ptr;
};

class UI{	//This is my lovest part.
};
*/
