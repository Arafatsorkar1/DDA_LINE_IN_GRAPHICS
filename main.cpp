#include <windows.h>

#include <cmath>

#define ROUND(a) ((int) (a + 0.5))

/* set window handle */

static HWND sHwnd;

static COLORREF redColor=RGB(255,0,0);

static COLORREF blueColor=RGB(0,0,255);

static COLORREF greenColor=RGB(0,255,0);


void SetWindowHandle(HWND hwnd){

sHwnd=hwnd;

}

/* SetPixel */

void setPixel(int x,int y,COLORREF& color=redColor){

if(sHwnd==NULL){

MessageBox(NULL,"sHwnd was not initialized !","Error",MB_OK|MB_ICONERROR);

exit(0);

}

HDC hdc=GetDC(sHwnd);

SetPixel(hdc,x,y,color);

ReleaseDC(sHwnd,hdc);

return;

// NEVERREACH //

}


void drawLineDDA(int xa, int ya, int xb, int yb){

int dx = xb - xa, dy = yb - ya, steps, k;

float xIncrement, yIncrement, x = xa, y = ya;

if(abs(dx) > abs(dy)) steps = abs(dx);

else steps = abs(dy);

xIncrement = dx / (float) steps;

yIncrement = dy / (float) steps;

setPixel(ROUND(x), ROUND(y));

for(int k = 0; k < steps; k++){

x += xIncrement;

y += yIncrement;

setPixel(x, y);

}

}

/* Window Procedure WndProc */

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){

switch(message){

case WM_PAINT:

SetWindowHandle(hwnd);

drawLineDDA(10, 20, 250, 300);

break;

case WM_CLOSE: // FAIL THROUGH to call DefWindowProc

break;

case WM_DESTROY:

PostQuitMessage(0);

return 0;

default:

break; // FAIL to call DefWindowProc //

}

return DefWindowProc(hwnd,message,wParam,lParam);

}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int iCmdShow){

static TCHAR szAppName[] = TEXT("Straight Line");

WNDCLASS wndclass;

wndclass.style         = CS_HREDRAW|CS_VREDRAW ;

wndclass.lpfnWndProc   = WndProc ;

wndclass.cbClsExtra    = 0 ;

wndclass.cbWndExtra    = 0 ;

wndclass.hInstance     = hInstance ;

wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;

wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;

wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;

wndclass.lpszMenuName  = NULL ;

wndclass.lpszClassName = szAppName ;

// Register the window //

if(!RegisterClass(&wndclass)){

MessageBox(NULL,"Registering the class failled","Error",MB_OK|MB_ICONERROR);

exit(0);

}

// CreateWindow //

HWND hwnd=CreateWindow(szAppName,"DDA - Programming Techniques",

WS_OVERLAPPEDWINDOW,

CW_USEDEFAULT,

CW_USEDEFAULT,

CW_USEDEFAULT,

CW_USEDEFAULT,

NULL,

NULL,

hInstance,

NULL);

if(!hwnd){

MessageBox(NULL,"Window Creation Failed!","Error",MB_OK);

exit(0);

}

// ShowWindow and UpdateWindow //

ShowWindow(hwnd,iCmdShow);

UpdateWindow(hwnd);

// Message Loop //

MSG msg;

while(GetMessage(&msg,NULL,0,0)){

TranslateMessage(&msg);

DispatchMessage(&msg);

}

/* return no error to the operating system */

return 0;

}
