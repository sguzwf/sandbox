#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void bed(int),desk(int),window(int),door(int),computer(int);
int act=0;
int item=0;
int noise=0;
char how[10];
char what[25];
char *strstr(const char *,const char *);

int main(){
	system("exec tput clear");
	printf("##This is test for me first game...\nIf you think this thing can be called \"GAME\".\n\n");
	room();
}

int room(){
	printf("This is your room.You suddenly wake up in the mid-night without any reason.\nYou are sitting on your \"bed\", and there are your \"desk\". Your \"computer\" is on it. You can see \"door\" and \"window\"\nWhat do you want to do?\n[HINT:see, get, search, kick, ENTER \"<ACT> <ITEM>\" BEFORE \">>\" or PRESS Ctrl+C to exit.]\n");
	while(noise<3){
	printf(">>");
	scanf("%s %s",how,what);
        if (strstr(how,"see")!=NULL)act=1;
	if (strstr(how,"get")!=NULL)act=2;
	if (strstr(how,"search")!=NULL)act=3;
	if (strstr(how,"kick")!=NULL)act=4;
	if (strstr(what,"bed")!=NULL)item=1;
	if (strstr(what,"desk")!=NULL)item=2;
	if (strstr(what,"window")!=NULL)item=3;
	if (strstr(what,"door")!=NULL)item=4;
	if (strstr(what,"computer")!=NULL)item=5;
	switch(item){
		case 0 :
			printf("What?\n");
			break;
		case 1 :
			bed(act);
			break;
		case 2 :
			desk(act);
			break;
		case 3 :
			window(act);
			break;
		case 4 :
			door(act);
			break;
		case 5 :
			computer(act);
			break;

		}
	act=item=0;
	}
	printf("\n\"What are you doing??\"\nYou hear your father is yelling.\nWhen you try to go to the bed, it's already too late....\n<<<<<<GAME OVER>>>>>>\n");
}

void bed(int act){
	switch(act){
		case 0 :
			printf("What do you want to do to your bed?\n");
			break;
		case 1 :
			printf("This is your bed, you are sitting on it.\n");
			break;
		case 2 :
			printf("You can't take something that heavy\n");
			break;
		case 3 :
			printf("You found nothing.\n");
			break;
		case 4 :
			printf("This is not a good idea when everybody is asleep.\n");
			break;
	}
}

void desk(int act){
	switch(act){
		case 0 :
			printf("What do you want to do with your desk?\n");
			break;
		case 1 :
			printf("This is your desk. You see your CALCULUS textbook on it.\n");
			break;
		case 2 :
			printf("You are kidding!\n");
			break;
		case 3 :
			printf("You see a picture of your GF.\n");
			break;
		case 4 :
			printf("\"BOOM!\"\nYou feel a little pain because of your foolish.\n");
			noise++;
			break;
	}
}

void window(int act){
	switch(act){
		case 0 :
			printf("This is a window.\n");
			break;
		case 1 :
			printf("You can see the moonlight go though it.\n");
			break;
		case 2 :
			printf("This is not a good idea to take out the window.\n");
			break;
		case 3 :
			printf("You found nothing on the window.\n");
			break;
		case 4 :
			printf("You think it may be broken if you do so.\n");
			break;
	}
}

void door(int act){
	switch(act){
		case 0 :
			printf("This is the door of your room.\n");
			break;
		case 1 :
			printf("It is closed. It works well.\n");
			break;
		case 2 :
			printf("You can't take out the door without any tool.\n");
			break;
		case 3 :
			printf("You found nothing.\n");
			break;
		case 4 :
			printf("You give it an \"Axe kick\", and make some noise.\n");
			noise++;
			break;
	}
}

void computer(int act){
	printf("You can see some little green texts jump out in your screen.\n\"THE MATRIX HAS YOU...\"\n\"AND YOU CAN'T DO ANYTHING TO YOUR COMPUTER IN THIS VERSION.\"\n");
}
