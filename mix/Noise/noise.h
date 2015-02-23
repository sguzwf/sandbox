#define LINEAR 0
#define COSINE 1
#define CUBIC 2
#define SMOOTH true
#include<windows.h>
using namespace std;

class CNOISE{
	public:
		CNOISE();
		bool MakeNoise( int iRes0, char **ColorMatrix, int CMWidth0, int Interpolation, bool Smooth);
	private:
		int Random( int x, int y);
		char InterPo( int x, int y, int Type, char **RefMatrix, bool XorY);
		bool Smooth( char **Matrix,  int Width);
		char **InputCM;
		bool IsRandom;
		bool IsInterPo;
		int iRes;
		int CMWidth;
};

CNOISE::CNOISE(){
	bool IsRandom = false;
	bool IsInterPo = false;
}

bool CNOISE::MakeNoise( int iRes0, char **ColorMatrix, int CMWidth0, int Interpolation, bool Smooth){
	int i,j;
	
	iRes = iRes0;
	CMWidth = CMWidth0;
	
	//Make Random Matrix
	InputCM = new char[iRes][iRes];
	for(j=0;j<iRes;j++)
		for(i=0;i<ires;i++)
			InpuCM[i][j] = (char)Random( i, j);
	IsRandom = true;

	//Resample it
	ColorMatrix = new char[CMWidth][CMWidth];

	for(j=0;j<iRes;j++)
		for(i=0;i<CMWidth;i++){
			if(i%(CMWidth/iRes)!=0)	//Is This Necessary?
				ColorMatrix[i][j] = InterPo(i,j,Interpolation,InputMatrix,true);
			else
				ColorMatrix[i][j] = InputCM[i/(CMWidth/iRes)][j];
		}

	for(i=0;i<CMWidth;i++)
		for(j=0;j<CMWidth;j++)
			if(j%(CMWidth/iRes)!=0)
				ColorMatrix[i][j] = InterPo(i,j,Interpolation,ColorMatrix,false);
	IsInterPo = true;

	if(Smooth==true)
		Smooth(ColorMatrix,CMWidth);

	return true;
}
