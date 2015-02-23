#include<iostream>
#include<cmath>
using namespace std;

char **Cubic(int **crMatrix,int iWidth,int iResample);
int CubicInterploation(int v1,int v2,int v3,int v4,int iWidth);

int main(){
}

char **Cubic(int **crMatrix, int iWidth, int iResample){
	char **result = new char[iResample][iResample];
