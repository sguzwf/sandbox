#include <fstream>
#include <iostream>

using namespace std;

struct BITMAPFILEHEADER
{
  char bfType[2];
  unsigned int bfSize;
  char bfReserved[4];
  unsigned int bfOffBits;
};

int main (int argc, char * argv[])
{
  BITMAPFILEHEADER bfh;
  ifstream input;
  input.open ("t.bmp", ios::binary);          

  input.read ((char *) &bfh, sizeof (BITMAPFILEHEADER));

  input.close();
  input.clear();

  cout << "Magic # had better be BM: " << bfh.bfType[0] << bfh.bfType[1] << endl;
  cout << "test.bmp is " << bfh.bfSize << " bytes!" << endl;
  cout << "Offset to data is " << bfh.bfOffBits << " bytes!" << endl;  

  return 0;
}
