#include<iostream>
#include<fstream>
#include<bitset>
using namespace std;

struct BMP_FILE_HEADER{
		char head[2];	//因為OS/2不普及，所以通常是BM
		unsigned int file_size;	//整個檔案的大小
		char reserved[4]; 	//保留，用途不明，一般設為0
		unsigned int data_offset;	//自文件開始，到圖片開始之間的偏移量（單位？）
};
/* t.bmp
 * 01000010 01001101 			BM
 * 01110110 10100000 00000000 00000000	file_size
 * 00000000 00000000 00000000 00000000	reserved
 * 00110110 00000100 00000000 00000000	data_offset
 * 00101000 00000000 00000000 00000000	header_size
 * 11001000 00000000 00000000 00000000	width
 * 11001000 00000000 00000000 00000000	height
 * 00000001 00000000			plans
 */

int main(){
	BMP_FILE_HEADER bfh;
	ifstream input_bmp;
	input_bmp.open("t.bmp",ios::binary);
	input_bmp.get((char*)&bfh,sizeof(BMP_FILE_HEADER));
	input_bmp.close();
	cout	<< bfh.head[0]	<< bfh.head[1]	<< endl	//以下都是基本資訊
		<< "檔案大小： "	<< bfh.file_size	<< endl
		<< "頭的偏移量： "	<< bfh.data_offset	<< endl;
	return 0;
}
	/*input_bmp.open(filename,ios::binary);	我果然是笨蛋，明明就是連在一起的東西，那就一次一起讀進來就好啦
		for(i=0;i<2;i++)
			input_bmp.get(head[i]);
		head[2]='\0';
		cout	<< bitset<16>((int)head)	<< endl;
		//for(i=0;i<4;i++);
			input_bmp.get(((char*)&file_size),4);
		cout	<< bitset<32>(file_size)	<< endl;
		//for(i=0;i<4;i++);
			input_bmp.get(((char*)&reserved),4);
		cout	<< bitset<32>(reserved)	<< endl;
		//for(i=0;i<4;i++);
			input_bmp.get(((char*)&data_offset),4);
		cout	<< bitset<32>(data_offset)	<< endl;
		//for(i=0;i<4;i++);
			input_bmp.get(((char*)&header_size),4);
		cout	<< bitset<32>(header_size)	<< endl;
		//for(i=0;i<4;i++);
			input_bmp.get(((char*)&width),4);
		cout	<< bitset<32>(width)	<< endl;
		//for(i=0;i<4;i++);
			input_bmp.get(((char*)&height),4);
		cout	<< bitset<32>(height)	<< endl;
		//for(i=0;i<2;i++);
			input_bmp.get(((char*)&plans),2);*/
