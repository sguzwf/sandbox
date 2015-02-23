#include<stdio.h>
#include<stdlib.h>

void see(struct OBJECT*);	//print appearance of the object
void get(struct OBJECT*);	//exchange the Ptr into your PACKET
void search(struct OBJECT*);	//print content of the object

struct OBJECT{
	char name[20];
	char appearance[100];
	struct OBJECT * content[10]={NULL};
	unsigned weight;
	unsigned hp;
}

int main(){
	struct OBJECT PACKET;
	
	struct OBJECT DESK;
	struct OBJECT BED;
	struct OBJECT KEY;

	PACKET={
		packet;
		This is where you put your item.;
		;
		0;
		0;
	}

	DESK={
		desk;
		This is a desk.;
		&KEY;
		21;
		21;
	}
	BED={
		bed;
		This is a bed.;
		;
		31;
		31;
	}
	KEY={
		roomkey;
		This is the key of your room.;
		;
		3;
		21;
	}
}
