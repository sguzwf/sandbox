#include<fstream>
using namespace std;

int main(){
	char ch;
	ifstream in;
	ofstream out;
	in.open("0.dat");
	out.open("1.dat");
	while(!in.eof()){
		in.get(ch);
		ch^=137;
		out.put(ch);
	}
	in.close();
	out.close();
}
