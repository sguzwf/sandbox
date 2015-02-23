#include<fstream>
#include<iostream>
using namespace std;

void encode(char[][100],char[][100]),string_sort(char*[],int[]),decode(char[][100],char[][100]),unsort(char*[],int[]);

int main(){
	ifstream infile1;
	ifstream infile2;
	ofstream outfile1;
	ofstream outfile2;

	int i,j,k,table[201];
	char question[2];
	char groundfloor[200][100], basement[200][100];

	char *basement_b[200];
	char infile_name1[259];
	char infile_name2[259];
	char outfile_name[259];

		for(i=0;i<200;i++)
			basement_b[i] = basement[i];

	cout	<< "你要加密嗎？(y/n)"	<< endl;
	cin	>>	question;
	if(question[0]=='y'){
		cout	<< "第一個要處理的檔案名稱是input1.txt"	<< endl;
		//cin	>>	infile_name1;
		cout	<< "第二個要處理的檔案名稱input2.txt"	<< endl;
		//cin	>>	infile_name2;
		cout	<< "輸出的檔案名稱是output.txt"	<< endl;
		//cin	>> outfile_name;

		infile1.open ("input1.txt");
		infile2.open ("input2.txt");
		outfile1.open ("output.txt");
		outfile2.open ("output.tmp");

		for(i=0;i<200;i++)
			for(j=0;j<100;j++)
				groundfloor[i][j]='\0';
		for(i=0;i<200;i++)
			table[i]=i;
		for(i=0;i<100;i++)
			infile1 >> groundfloor[i];
		for(i=100;i<200;i++)
			infile2 >> groundfloor[i];
		encode(groundfloor,basement);
		string_sort(basement_b,table);
		cout	<< 3	<< endl;
		for(k=0;k<200;k++){
			//if(basement_b[k][0]!='\0')
				outfile1	<< basement_b[k]	<< endl;
		}
		for(k=0;k<200;k++)
			outfile2	<< table[k]	<< endl;
	}else if(question[0]=='n'){
		cout	<< "那就是要解密囉。"	<< endl
			<< "要解密的檔是output.txt"	<< endl
			<< "抱歉，本功能尚未完成 "	<< endl;
/*		cin	>> outfile_name;
		outfile1.open ("infile.txt");
		outfile2.open ("infile.txt");
		infile1.open ("output.txt");
		infile2.open ("output.tmp");
		for(i=0;i<200;i++){
			infile1	>>	groundfloor[i];
			infile2	>>	table[i];
		}
		decode(groundfloor,basement);
		unsort(basement_b,table);
		for(i=0;i<100;i++)
			outfile1 << basement_b[i];
		for(i=100;i<200;i++)
			outfile2 << basement_b[i];
	}
*/
	infile1.close();
	infile2.close();
	outfile1.close();
	outfile2.close();
}

void encode(char groundfloor[][100], char basement[][100]){
	int i,j,k,flag;
	char ABCD[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	char abcd[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	char shar[26] = { 's','h','a','r','t','y','v','w','b','d','l','q','n','c','x','g','z','e','k','i','p','u','f','o','m','j' };

	for(k=0;k<200;k++){
		i=0;
		j=0;
		while(groundfloor[k][i]!='\0'){
			if(groundfloor[k][i]==abcd[j]||groundfloor[k][i]==ABCD[j]){	//單純對字母來說，不會有兩個都成立的情況
				basement[k][i]=shar[j];
				flag=1;
				i++;
				j=0;
			}else{
				j++;	//單純對字母來說，不會有j>=26卻找不到的情況
			}
			if(j>26&&flag==0){
				basement[k][i]=groundfloor[k][i];
				i++;
				j=0;
			}
		}
	}
}

void decode(char groundfloor[][100], char basement[][100]){
	int i,j,k,flag;
	char abcd[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	char shar[26] = { 's','h','a','r','t','y','v','w','b','d','l','q','n','c','x','g','z','e','k','i','p','u','f','o','m','j' };

	for(k=0;k<200;k++){
		i=0;
		j=0;
		while(groundfloor[k][i]!='\0'){
			if(groundfloor[k][i]==shar[j]){
				basement[k][i]=abcd[j];
				flag=1;
				i++;
				j=0;
			}else{
				j++;	//單純對字母來說，不會有j>=26卻找不到的情況
			}
			if(j>26&&flag==0){
				basement[k][i]=groundfloor[k][i];
				i++;
				j=0;
			}
		}
	}
}

void string_sort(char *basement_b[],int table[]){
	int i,j,i_now;
	char *key_string;

	for(i_now=1;i_now<200;i_now++){
		key_string = basement_b[i_now];
		table[200] = table[i_now];
		i = i_now-1;
		j = 0;

		while(i>=0&&j<200){
			if(key_string[j]==basement_b[i][j]){
				j++;
			}else if(key_string[j]<basement_b[i][j]){
				cout	<< 5	<< endl;
				basement_b[i+1] = basement_b[i];
				table[i+1] = table[i];
				i--;
				j=0;
			}else if(key_string[j]>basement_b[i][j]){
				break;
			}
		}
		basement_b[i+1] = key_string;
		table[i+1] = table[200];
	}
}

void unsort(char *basement_b[],int table[]){
	int i,j;
	char *key_string;

	for(j=1;j<200;j++){
		key_string = basement_b[i+1];
		table[200] = table[j];
		for(i=j-1;table[i]>table[200];i--){
			basement_b[i+1] = basement_b[i];
			table[i+1] = table[i];
		}
		basement_b[i+1] = key_string;
		table[i+1] = table[200];
	}
}

