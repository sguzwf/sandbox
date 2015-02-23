/* classes.h
 * 這是一個把class都定好的檔案。
 * 也將是程式的主體和引擎。未來的發展將脫離不了它。
 * 不過要小心define的誤用。
 */
#include<iostream>
#define MAX_CHAR 256	//名字所用的字元上限。
#define MAX_ITEM 20	//一個物品所能包含的物品數上限。

using namespace std;

class Room {
public:
	char name[MAX_CHAR];	//東西的名字，以下的其他物件也都有自己的名字。
	char message[MAX_CHAR];	//敘述用的訊息。
	int height;	//高度，在Room指的是長。在其他物件，則指身高。
	int width;	//寬度，在Room指的是寬。
	Item* contain[MAX_ITEM];	//表示裝其他東西的地方。
};

class Item : public Room {
public:
	int weight;	//重量，這是Room所沒有的屬性。
	char addtional_message[MAX_CHAR];	//物品被調查時的訊息。
	//這裡應該還有一個值，表示這個Item使用後會跑那一個function，而那個值是個function的Ptr。
	Room* where;	//在那裡，這表示一項Item的位置，在Creature中的這一項是所在的房間。
};

class Creature : public Item {
public:
	//生物才有的動作。
	Room* see(Room* where);	//看，直接看是列出這個房間有的物品。也可以看某物品。
	Item* search(Item* be_search);	//搜索，翻找一項物品，列出它包含的物品。
	//Item* get();	//把某物品拿起來。
	Item* drop();	//把某物品丟掉，只能丟在房間裡。可能造成這個房間的物品過多而超過陣列的極限。
	Item* use();	//使用某物品，可以達成不同的效果。
};

Room* Creature::see(Room* where){
	int i;
	int empty_contain;
	char item_name[MAX_CHAR];
	bool empty = 1;
	bool get_done = 0;
	for(i=0;i<MAX_ITEM;i++)
		if(where->contain[i]!=NULL){	//把所在（where）的東西列出來
			cout	<< where->contain[i]->name	<< endl;
			empty = 0;
		}
	if(empty==1)	//要是這個地方沒有包含任何東西，則告訴玩家什麼都沒有。
		cout	<< "什麼都沒有"	<< endl;
	if(empty==0){
		cout	<< "你想要拿起什麼？"	<< endl
			<< ">>";
		cin	>> item_name;
		for(empty_contain=0;this.contain[empty_contain]!=NULL&&empty_contain<MAX_ITEM;empty_contain++);	//找物品欄中的空格
		if(this.contain[empty_contain]==NULL){	//檢查是不是空的，若是空的就把要求的東西放進去。
			for(i=0;i<MAX_ITEM;i++)
				if(strcmp(item_name,where->contain[i]->name)==0){
					this.contain[empty_contain] = where->contain[i];
					where->contain[i] = NULL;
					get_done = 1;	//找到所要的東西了。
				}
		}else{
			cout	<< "您沒有地方可以放它了"	<< endl;	//沒有空間就說放不下。
		}
	}
	if(get_done==0)
		cout	<< "這裡沒有這個東西"	<< endl;	//找不到所要的東西。
}
Item* Creature::search(Item* be_search){
	int i;
	int empty_contain;
	char item_name[AX_CHAR];
	bool empty = 1;
	bool get_done = 0;
	for(i=0;i<MAX_ITEM;i++)
		if(be_search->contain[i]!=NULL){	//把某物裡的東西列出來
			cout	<< be_search->contain[i]->name	<< endl;
			empty = 0;
		}
	if(empty==1)	//要是這個地方沒有包含任何東西，則告訴玩家什麼都沒有。
		cout	<< "什麼都沒有"	<< endl;
	if(empty==0){
		cout	<< "你想要拿起什麼？"	<< endl
			<< ">>";
		cin	>> item_name;
		for(empty_contain=0;this.contain[empty_contain]!=NULL&&empty_contain<MAX_ITEM;empty_contain++);
		if(this.contain[empty_contain]==NULL){
			for(i=0;i<MAX_ITEM;i++)
				if(strcmp(item_name,be_search->contain[i]->name)==0){
					this.contain[empty_contain] = be_search->contain[i];
					be_search->contain[i] = NULL;
					get_done = 1;
				}
		}else{
			cout	<< "您沒有地方可以放它了"	<< endl;
		}
	}
	if(get_done==0)
		cout	<< "這裡沒有這個東西"	<< endl;
}
//Item* Creature::get(char name[MAX_CHAR]){}
Item* Creature::drop(char be_drop[MAX_CHAR]){	//檢查地上滿了沒（？？），然後把身上的東西丟地上。			
}
Item* Creature:use(char be_use[MAX_CHAR]){	//執行某Item的『效果』function。
}
