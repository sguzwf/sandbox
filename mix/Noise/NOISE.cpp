/*
 * 	NOISE.cpp -- Simple Noise Generator
 * 	2004 AUG 16
 */

#include<windows.h>
#include<cmath>
#include<ctime>
using namespace std;

#define WINWIDTH 512
//#define SMOOTH

void PixelSum(COLORREF [][WINWIDTH][WINWIDTH],int,COLORREF [][WINWIDTH]);
void Cubic(COLORREF [][WINWIDTH],int);
void MakeNoise(COLORREF [][WINWIDTH],int iRes);
COLORREF CubicInterpolation2D(int,int,int,int,int,int);
COLORREF SmoothNoise(COLORREF [][WINWIDTH],int, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(	HINSTANCE	hInstance,
			HINSTANCE	hPrevInstance,
			PSTR		scCmdLine,
			int		iCmdShow)
{
	static TCHAR szAppName[] = TEXT("Perlin Noise");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style		= CS_HREDRAW|CS_VREDRAW;
	wndclass.lpfnWndProc	= WndProc;
	wndclass.cbClsExtra	= 0;
	wndclass.cbWndExtra	= 0;
	wndclass.hInstance	= hInstance;
	wndclass.hIcon		= LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor	= LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground	= NULL;
	wndclass.lpszMenuName	= NULL;
	wndclass.lpszClassName	= szAppName;

	if(!RegisterClass(&wndclass))
	{
		MessageBox(NULL,TEXT("You should never see this message in XP."),szAppName,MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow( 	szAppName,
				TEXT("Perlin Noise"),
				WS_SYSMENU,
				CW_USEDEFAULT,CW_USEDEFAULT,
				WINWIDTH,WINWIDTH,
				NULL,
				NULL,
				hInstance,
				NULL);

	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(	HWND	hwnd,
				UINT	message,
				WPARAM	wParam,
				LPARAM	lParam)
{
	static int cxClient,cyClient;
	HDC hdc;
	int i,j,k;
	PAINTSTRUCT ps;
	static COLORREF crMatrices[5][WINWIDTH][WINWIDTH], crResult[WINWIDTH][WINWIDTH];

	switch(message)
	{
		case WM_CREATE:
			srand(time(NULL));
			for(i=0;i<5;i++)
				MakeNoise(crMatrices[i],(int)(16*pow((double)2,i)));	//YAK...
			PixelSum(crMatrices,5,crResult);
			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);
			for(j=0;j<WINWIDTH;j++)
				for(i=0;i<WINWIDTH;i++)
					SetPixel(hdc,i,j,crResult[i][j]);
			EndPaint(hwnd,&ps);
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}

COLORREF SmoothNoise(COLORREF crMatrix[][WINWIDTH],int x, int y)	//This is my own smooth...
{
	int iXP,iYP,iXM,iYM,iCorner,iSide,iCenter,iSmoothNoise;

	iXP = x==WINWIDTH?0:WINWIDTH;
	iYP = y==WINWIDTH?0:WINWIDTH;
	iXM = x==0?WINWIDTH:0;
	iYM = y==0?WINWIDTH:0;

	iCorner = (GetRValue(crMatrix[iXP][iYP])+GetRValue(crMatrix[iXP][iYM])+GetRValue(crMatrix[iXM][iYM])+GetRValue(crMatrix[iXM][iYP]))/5;
	iSide = (GetRValue(crMatrix[iXP][y])+GetRValue(crMatrix[x][iYM])+GetRValue(crMatrix[iXM][y])+GetRValue(crMatrix[x][iYP]))*0;
	iCenter = GetRValue(crMatrix[x][y])/5;
	iSmoothNoise = iCorner + iSide + iCenter;

	return RGB(iSmoothNoise,iSmoothNoise,iSmoothNoise);
}

COLORREF CubicInterpolation2D(int p1,int p2,int p3,int p4,int width,int num)
{
	int P,Q,R,S;
	float result;

	P = (p4 - p3) - (p1 - p2);
	Q = (p1 - p2) - P;
	R = p3 - p1;
	S = p2;

	result = P*pow((double)num/width,3)+Q*pow((double)num/width,2)+R*num/width+S;

	return RGB((int)result,(int)result,(int)result);
}

void Cubic(COLORREF crMatrix[][WINWIDTH],int iRes)
{
	int i,j,k,p1,p2,p3,p4,width;
	width = WINWIDTH/iRes;

	for(j=0;j<iRes;j++)
		for(i=0;i<iRes;i++)
			for(k=1;k<width;k++){
				p2 = GetRValue(crMatrix[i*width][j*width]);
				p1 = GetRValue(crMatrix[(i-1<0?iRes+i-1:i-1)*width][j*width]);
				p3 = GetRValue(crMatrix[(i+1>=iRes?i+1-iRes:i+1)*width][j*width]);
				p4 = GetRValue(crMatrix[(i+2>=iRes?i+2-iRes:i+2)*width][j*width]);

				crMatrix[i*width+k][j*width] = CubicInterpolation2D(p1,p2,p3,p4,width,k);
			}

	for(i=0;i<WINWIDTH;i++)
		for(j=0;j<iRes;j++)
			for(k=1;k<width;k++){
				p2 = GetRValue(crMatrix[i][j*width]);
				p1 = GetRValue(crMatrix[i][(j-1<0?iRes+j-1:j-1)*width]);
				p3 = GetRValue(crMatrix[i][(j+1>=iRes?j+1-iRes:j+1)*width]);
				p4 = GetRValue(crMatrix[i][(j+2>=iRes?j+2-iRes:j+2)*width]);

				crMatrix[i][j*width+k] = CubicInterpolation2D(p1,p2,p3,p4,width,k);
			}
}

void MakeNoise(COLORREF crMatrix[][WINWIDTH],int iRes)
{
	int i,j,iNoise;

	if(iRes<=0||iRes>WINWIDTH)
		return;

	for(j=0;j<iRes;j++)
		for(i=0;i<iRes;i++)
		{
			iNoise = rand()%152+52;
			//iNoise = random3D(i,j,time(NULL));	//too dark
			crMatrix[i*WINWIDTH/iRes][j*WINWIDTH/iRes] = RGB(iNoise,iNoise,iNoise);
		}
	if(iRes!=WINWIDTH)
		Cubic(crMatrix,iRes);
#ifdef SMOOTH
	for(j=0;j<WINWIDTH;j++)
		for(i=0;i<WINWIDTH;i++)
			SmoothNoise(crMatrix,i,j);
#endif
}

void PixelSum(COLORREF crMatrices[][WINWIDTH][WINWIDTH], int num, COLORREF crResult[][WINWIDTH])
{
	int i,j,k,iNoise;

	for(j=0;j<WINWIDTH;j++)
		for(i=0;i<WINWIDTH;i++)
			crResult[i][j] = RGB(0,0,0);

	for(j=0;j<WINWIDTH;j++)
		for(i=0;i<WINWIDTH;i++)
			for(k=0;k<num;k++){
				iNoise = GetRValue(crMatrices[k][i][j])/num;
				crResult[i][j]+=RGB(iNoise,iNoise,iNoise);
			}
}
