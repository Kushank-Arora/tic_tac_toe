#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <stdio.h>
#include <windows.h>
#include "resource.h"

/* User defined Macros */
#define SIZE 500
#define START 40

/* STRUCTURE */

struct colom
{
	int num;
	char var;
}arr[9];

int over=0,allowed;

/* User Defined procedure */
void OnPaint(HWND);
int opp_check();
int self_check();
int self_win();
int self_atlast();
void LClick(HWND,int,int);
void OnCreate(HWND);
void LUp(HWND);
void OnDestroy(HWND);

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("KushankWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance,LPSTR lpszArgument,int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (hThisInstance, MAKEINTRESOURCE(MY_ICON2));
    wincl.hIconSm = LoadIcon (hThisInstance, MAKEINTRESOURCE(MY_ICON2));
    wincl.hCursor = LoadCursor (hThisInstance,MAKEINTRESOURCE(IDC_CUR));//(NULL, IDC_HAND);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
  //  hbmp =  ;
    //hbr =

    wincl.hbrBackground = CreatePatternBrush ( LoadBitmap ( hThisInstance, MAKEINTRESOURCE ( IDB_BITMAP1 ) ) ) ;//(HBRUSH)COLOR_BACKGROUND;//(HBRUSH)MAKEINTRESOURCE(IDB_BITMAP1);//

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Tic-Tac-Toe by Kushank Arora"),       /* Title Text */
           WS_SIZEBOX,
           //WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           SIZE+2.5*START,                 /* The programs width */
           SIZE+2.5*START+20,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            OnCreate(hwnd);
            break;
        case WM_PAINT:
            OnPaint(hwnd);
            break;
        case WM_LBUTTONDOWN:
            LClick(hwnd,LOWORD(lParam),HIWORD(lParam));
            break;
        case WM_LBUTTONUP:
            LUp(hwnd);
            break;
        case WM_DESTROY:
             OnDestroy(hwnd);      /* send a WM_QUIT to the message queue */
            break;

        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
void OnDestroy(HWND hwnd)
{
    if(over==1)
            PostQuitMessage (0);
}
void OnCreate(HWND hwnd)
{
    //printf("M in oncreate\n");
    HDC hdc=GetDC(hwnd);
    Rectangle(hdc,START,START,SIZE+START,SIZE+START);
    int i;
    for(i=0;i<9;i++)
		arr[i].num=4;
    allowed=0;
    over=0;
    MoveToEx(hdc,START,START,NULL);
    LineTo(hdc,SIZE+START,START);
    LineTo(hdc,SIZE+START,SIZE+START);
    LineTo(hdc,START,SIZE+START);
    LineTo(hdc,START,START);

    MoveToEx(hdc,START+SIZE/3,START,NULL);
    LineTo(hdc,START+SIZE/3,START+SIZE);

    MoveToEx(hdc,START+2*SIZE/3,START,NULL);
    LineTo(hdc,START+2*SIZE/3,START+SIZE);

    MoveToEx(hdc,START, START+SIZE/3,NULL);
    LineTo(hdc,START+SIZE,START+SIZE/3);

    MoveToEx(hdc,START,START+2*SIZE/3,NULL);
    LineTo(hdc,START+SIZE,START+2*SIZE/3);
}

void OnPaint(HWND hwnd)
{
//    printf("M in onpaint\n");
    PAINTSTRUCT ps;
    HDC hdc;
    HBRUSH hbr;
    HPEN hpen;
    HGDIOBJ holdbr,holdpen;
    hdc=BeginPaint(hwnd,&ps);
    int i,j;
    // Draw the square
    hbr = CreateSolidBrush ( RGB ( 255, 255, 255) ) ;
    holdbr = SelectObject ( hdc, hbr ) ;

    Rectangle(hdc,START,START,SIZE+START,SIZE+START);

    MoveToEx(hdc,START,START,NULL);
    LineTo(hdc,SIZE+START,START);
    LineTo(hdc,SIZE+START,SIZE+START);
    LineTo(hdc,START,SIZE+START);
    LineTo(hdc,START,START);

    MoveToEx(hdc,START+SIZE/3,START,NULL);
    LineTo(hdc,START+SIZE/3,START+SIZE);

    MoveToEx(hdc,START+2*SIZE/3,START,NULL);
    LineTo(hdc,START+2*SIZE/3,START+SIZE);

    MoveToEx(hdc,START, START+SIZE/3,NULL);
    LineTo(hdc,START+SIZE,START+SIZE/3);

    MoveToEx(hdc,START,START+2*SIZE/3,NULL);
    LineTo(hdc,START+SIZE,START+2*SIZE/3);

    hpen = CreatePen ( PS_SOLID, 3, RGB ( 255, 0, 0 ) ) ;
    holdpen = SelectObject ( hdc, hpen ) ;

    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
        {
            if(arr[i*3+j].num==0)
                Ellipse(hdc,START + i*SIZE/3 +20 , START + j*SIZE/3 +20,START + (i+1)*SIZE/3 -20,START + (j+1)*SIZE/3-20);
            else if(arr[i*3+j].num==1){

                MoveToEx(hdc,START+ i*SIZE/3 +20,START + j*SIZE/3 +20,NULL);
                LineTo(hdc,START + (i+1)*SIZE/3 -20,START + (j+1)*SIZE/3-20);
                MoveToEx(hdc,START+ (i+1)*SIZE/3 -20,START + j*SIZE/3 +20,NULL);
                LineTo(hdc,START + i*SIZE/3 +20,START + (j+1)*SIZE/3-20);
            }
        }

    //END SQUARE
    SelectObject ( hdc, holdpen ) ;
    DeleteObject ( hpen ) ;

    SelectObject ( hdc, holdbr ) ;
    DeleteObject ( hbr ) ;

    EndPaint(hwnd,&ps);
}

void LUp(HWND hwnd)
{
   // printf("M in LUP\n");
    if(over==1) return;
    if(allowed==0)   return;
    allowed=0;
    HPEN hpen;
    HGDIOBJ holdpen;
    int m;
    HDC hdc=GetDC(hwnd);

    hpen = CreatePen ( PS_SOLID, 3, RGB ( 0, 0, 0 ) ) ;
    holdpen = SelectObject ( hdc, hpen ) ;



    for(m=0;m<4;m=m+3)
	{
		if((arr[0].num+arr[1].num+arr[2].num)==m||(arr[3].num+arr[4].num+arr[5].num)==m||(arr[6].num+arr[7].num+arr[8].num)==m||(arr[0].num+arr[3].num+arr[6].num)==m||(arr[1].num+arr[4].num+arr[7].num)==m||(arr[2].num+arr[5].num+arr[8].num)==m||(arr[0].num+arr[4].num+arr[8].num)==m||(arr[2].num+arr[4].num+arr[6].num)==m)
		{
			char arr1[2][35]={"You Win","Computer Wins"};
			sprintf(arr1[0],"%s  !!\n",arr1[-(m/3)+1]);
			MessageBox(0,arr1[0],"Game Over",0);
			int i;
			i=MessageBox(0,"Wanna Re-Try?","Title",4);
            if(i==6){
                    OnCreate(hwnd); return; }
			over=1;
			OnDestroy(hwnd);

			return;
		}
	}
	if(arr[0].num!=4&&arr[1].num!=4&&arr[2].num!=4&&arr[3].num!=4&&arr[4].num!=4&&arr[5].num!=4&&arr[6].num!=4&&arr[7].num!=4&&arr[8].num!=4)
	{
//		fun();
char arr[30];
		sprintf(arr,"Game Draw!!!\n");
		MessageBox(0,arr,"Game Over",0);
		int i;
			i=MessageBox(0,"Wanna Re-Try?","Title",4);
            if(i==6)
                return OnCreate(hwnd);
		over=1;
		OnDestroy(hwnd);

//		goto end;
	}


    int pr=self_check();
		if(pr==1)
		{
			pr=opp_check();
			if(pr==1)
			{
				pr=self_win();
				if(pr==1)
					self_atlast();
       //         over=1;
			}
		}
    int prr,i,j;
	for(prr=0;prr<10;prr++)
        if(arr[prr].num==0)
			arr[prr].var='O';


    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
        {
            if(arr[i*3+j].num==0)
                Ellipse(hdc,START + i*SIZE/3 +20 , START + j*SIZE/3 +20,START + (i+1)*SIZE/3 -20,START + (j+1)*SIZE/3-20);
            else if(arr[i*3+j].num==1){
                MoveToEx(hdc,START+ i*SIZE/3 +20,START + j*SIZE/3 +20,NULL);
                LineTo(hdc,START + (i+1)*SIZE/3 -20,START + (j+1)*SIZE/3-20);
                MoveToEx(hdc,START+ (i+1)*SIZE/3 -20,START + j*SIZE/3 +20,NULL);
                LineTo(hdc,START + i*SIZE/3 +20,START + (j+1)*SIZE/3-20);

            }
        }




    for(m=0;m<4;m=m+3)
	{
		if((arr[0].num+arr[1].num+arr[2].num)==m||(arr[3].num+arr[4].num+arr[5].num)==m||(arr[6].num+arr[7].num+arr[8].num)==m||(arr[0].num+arr[3].num+arr[6].num)==m||(arr[1].num+arr[4].num+arr[7].num)==m||(arr[2].num+arr[5].num+arr[8].num)==m||(arr[0].num+arr[4].num+arr[8].num)==m||(arr[2].num+arr[4].num+arr[6].num)==m)
		{
			char arr1[2][35]={"You Win","Computer Wins"};
			sprintf(arr1[0],"%s  !!\n",arr1[-(m/3)+1]);
			MessageBox(0,arr1[0],"Game Over",0);
			int i;
			i=MessageBox(0,"Wanna Re-Try?","Title",4);
            if(i==6){
                    OnCreate(hwnd); return; }
			over=1;
			OnDestroy(hwnd);

			return;
		}
	}
	if(arr[0].num!=4&&arr[1].num!=4&&arr[2].num!=4&&arr[3].num!=4&&arr[4].num!=4&&arr[5].num!=4&&arr[6].num!=4&&arr[7].num!=4&&arr[8].num!=4)
	{
//		fun();
char arr[30];
		sprintf(arr,"Game Draw!!!\n");
		MessageBox(0,arr,"Game Over",0);
		int i;
			i=MessageBox(0,"Wanna Re-Try?","Title",4);
            if(i==6)
                return OnCreate(hwnd);
		over=1;
		OnDestroy(hwnd);

//		goto end;
	}
	SelectObject ( hdc, holdpen ) ;
    DeleteObject ( hpen ) ;
}

void LClick(HWND hwnd,int x,int y)
{
     //   printf("M in LClick\n");
        allowed=0;
        if(over==1) return;
        int a,b;

    HPEN hpen;
    HGDIOBJ holdpen;
    HDC hdc=GetDC(hwnd);
    hpen = CreatePen ( PS_SOLID, 3, RGB ( 0, 0, 0 ) ) ;
    holdpen = SelectObject ( hdc, hpen ) ;



        if(x>START+SIZE||y>START+SIZE)
            return;
        if(x<START||y<START)
            return;

        a=(float)(x-START)/(SIZE/3);
        b=(float)(y-START)/(SIZE/3);
        if(arr[3*a+b].num!=4)
        {
            allowed=0; //no
            return;
        }
        allowed=1;   //yes
   //     if((arr[j-1].num==1||arr[j-1].num==0)&&c==0)
//	{
	//	if(c==0)
	//	cout<<"\nNo Cheating Please!!\n";
	//	goto reenter;
	//}
        MoveToEx(hdc,START+ a*SIZE/3 +20,START + b*SIZE/3 +20,NULL);
                LineTo(hdc,START + (a+1)*SIZE/3 -20,START + (b+1)*SIZE/3-20);
                MoveToEx(hdc,START+ (a+1)*SIZE/3 -20,START + b*SIZE/3 +20,NULL);
                LineTo(hdc,START + a*SIZE/3 +20,START + (b+1)*SIZE/3-20);arr[3*a+b].var='X';
        arr[3*a+b].num=1;
//        printf("x=%d y=%d\n",a,b);
    //    char arr[20]="",temp[2][3];
     //   temp[0][0]=a-48; temp[0][1]='\0';
     //   temp[1][0]=b-48; temp[1][1]='\0';
      //  strcat(strcat(arr,temp[0]),temp[1]);
    //    MessageBox(0,arr,"Title",0);
    //    play=1;
    SelectObject ( hdc, holdpen ) ;
    DeleteObject ( hpen ) ;
}


int opp_check()
{
	int k=1;
	if(arr[0].num==1&&arr[4].num==4)
    {
        arr[4].num=0;
        k=0;
    }
    else if(arr[0].num+arr[5].num+arr[7].num==3&&arr[3].num+arr[6].num+arr[8].num+arr[2].num==16&&arr[1].num+arr[4].num==0)
    {
        arr[6].num=0;
        k=0;
    }
	else if(arr[0].num+arr[1].num+arr[2].num==6)
	{
		if(arr[0].num==4)
			arr[0].num=0;
		else if(arr[1].num==4)
			arr[1].num=0;
		else if(arr[2].num==4)
			arr[2].num=0;
		k=0;
	}
	else if(arr[3].num+arr[4].num+arr[5].num==6)
	{
		if(arr[3].num==4)
			arr[3].num=0;
		else if(arr[4].num==4)
			arr[4].num=0;
		else if(arr[5].num==4)
			arr[5].num=0;
		k=0;
	}
	else if(arr[6].num+arr[7].num+arr[8].num==6)
	{
		if(arr[6].num==4)
			arr[6].num=0;
		else if(arr[7].num==4)
			arr[7].num=0;
		else if(arr[8].num==4)
			arr[8].num=0;
		k=0;
	}
	else if(arr[0].num+arr[3].num+arr[6].num==6)
	{
		if(arr[0].num==4)
			arr[0].num=0;
		else if(arr[3].num==4)
			arr[3].num=0;
		else if(arr[6].num==4)
			arr[6].num=0;
		k=0;
	}
	else if(arr[1].num+arr[4].num+arr[7].num==6)
	{
		if(arr[1].num==4)
			arr[1].num=0;
		else if(arr[4].num==4)
			arr[4].num=0;
		else if(arr[7].num==4)
			arr[7].num=0;
		k=0;
	}
	else if(arr[2].num+arr[5].num+arr[8].num==6)
	{
		if(arr[2].num==4)
			arr[2].num=0;
		else if(arr[5].num==4)
			arr[5].num=0;
		else if(arr[8].num==4)
			arr[8].num=0;
		k=0;
	}
	else if(arr[0].num+arr[4].num+arr[8].num==6)
	{
		if(arr[0].num==4)
			arr[0].num=0;
		else if(arr[4].num==4)
			arr[4].num=0;
		else if(arr[8].num==4)
			arr[8].num=0;
		k=0;
	}
	else if(arr[2].num+arr[4].num+arr[6].num==6)
	{
		if(arr[2].num==4)
			arr[2].num=0;
		else if(arr[4].num==4)
			arr[4].num=0;
		else if(arr[6].num==4)
			arr[6].num=0;
		k=0;
	}
	return k;
}
int self_check()
{
	int k=1;
	if(arr[0].num+arr[1].num+arr[2].num==4)
	{
		if(arr[0].num==4)
			arr[0].num=0;
		else if(arr[1].num==4)
			arr[1].num=0;
		else if(arr[2].num==4)
			arr[2].num=0;
		k=0;
	}
	else if(arr[3].num+arr[4].num+arr[5].num==4)
	{
		if(arr[3].num==4)
			arr[3].num=0;
		else if(arr[4].num==4)
			arr[4].num=0;
		else if(arr[5].num==4)
			arr[5].num=0;
		k=0;
	}
	else if(arr[6].num+arr[7].num+arr[8].num==4)
	{
		if(arr[6].num==4)
			arr[6].num=0;
		else if(arr[7].num==4)
			arr[7].num=0;
		else if(arr[8].num==4)
			arr[8].num=0;
		k=0;
	}
	else if(arr[0].num+arr[3].num+arr[6].num==4)
	{
		if(arr[0].num==4)
			arr[0].num=0;
		else if(arr[3].num==4)
			arr[3].num=0;
		else if(arr[6].num==4)
			arr[6].num=0;
		k=0;
	}
	else if(arr[1].num+arr[4].num+arr[7].num==4)
	{
		if(arr[1].num==4)
			arr[1].num=0;
		else if(arr[4].num==4)
			arr[4].num=0;
		else if(arr[7].num==4)
			arr[7].num=0;
		k=0;
	}
	else if(arr[2].num+arr[5].num+arr[8].num==4)
	{
		if(arr[2].num==4)
			arr[2].num=0;
		else if(arr[5].num==4)
			arr[5].num=0;
		else if(arr[8].num==4)
			arr[8].num=0;
		k=0;
	}
	else if(arr[0].num+arr[4].num+arr[8].num==4)
	{
		if(arr[0].num==4)
			arr[0].num=0;
		else if(arr[4].num==4)
			arr[4].num=0;
		else if(arr[8].num==4)
			arr[8].num=0;
		k=0;
	}
	else if(arr[2].num+arr[4].num+arr[6].num==4)
	{
		if(arr[2].num==4)
			arr[2].num=0;
		else if(arr[4].num==4)
			arr[4].num=0;
		else if(arr[6].num==4)
			arr[6].num=0;
		k=0;
	}
	return k;
}
int self_win()
{
	int k=1;
	if(arr[0].num+arr[1].num+arr[2].num==8)
	{
		if(arr[0].num==4)
			arr[0].num=0;
		else if(arr[1].num==4)
			arr[1].num=0;
		else if(arr[2].num==4)
			arr[2].num=0;
		k=0;
	}
	else if(arr[3].num+arr[4].num+arr[5].num==8)
	{
		if(arr[3].num==4)
			arr[3].num=0;
		else if(arr[4].num==4)
			arr[4].num=0;
		else if(arr[5].num==4)
			arr[5].num=0;
		k=0;
	}
	else if(arr[6].num+arr[7].num+arr[8].num==8)
	{
		if(arr[6].num==4)
			arr[6].num=0;
		else if(arr[7].num==4)
			arr[7].num=0;
		else if(arr[8].num==4)
			arr[8].num=0;
		k=0;
	}
	else if(arr[0].num+arr[3].num+arr[6].num==8)
	{
		if(arr[0].num==4)
			arr[0].num=0;
		else if(arr[3].num==4)
			arr[3].num=0;
		else if(arr[6].num==4)
			arr[6].num=0;
		k=0;
	}
	else if(arr[1].num+arr[4].num+arr[7].num==8)
	{
		if(arr[1].num==4)
			arr[1].num=0;
		else if(arr[4].num==4)
			arr[4].num=0;
		else if(arr[7].num==4)
			arr[7].num=0;
		k=0;
	}
	else if(arr[2].num+arr[5].num+arr[8].num==8)
	{
		if(arr[2].num==4)
			arr[2].num=0;
		else if(arr[5].num==4)
			arr[5].num=0;
		else if(arr[8].num==4)
			arr[8].num=0;
		k=0;
	}
	else if(arr[0].num+arr[4].num+arr[8].num==8)
	{
		if(arr[0].num==4)
			arr[0].num=0;
		else if(arr[4].num==4)
			arr[4].num=0;
		else if(arr[8].num==4)
			arr[8].num=0;
		k=0;
	}
	else if(arr[2].num+arr[4].num+arr[6].num==8)
	{
		if(arr[2].num==4)
			arr[2].num=0;
		else if(arr[4].num==4)
			arr[4].num=0;
		else if(arr[6].num==4)
			arr[6].num=0;
		k=0;
	}
	return k;
}
int self_atlast()
{
	for(int i=0;i<10;i++)
		if(arr[i].num==4)
			{
			arr[i].num=0;
			goto end2;
			}
	end2:
	    return 0;
}
