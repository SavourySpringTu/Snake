#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <ctime>

using namespace std;

int toadox[20];
int toadoy[20];
int sl=4;
int save_random[2];
int diem=0;
int check;

void gotoxy( int x, int y)
{
	static HANDLE h = NULL;  
	if(!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };  
	SetConsoleCursorPosition(h,c);
}
void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
 
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
 
    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;
 
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void Nocursortype() /// an con tro chuot
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void box()
{
	gotoxy(0,0);
	cout<<char(218);
	gotoxy(37,13);
	cout<<char(217);
	gotoxy(37,0);
	cout<<char(191);
	gotoxy(0,13);
	cout<<char(192);
	for(int i=1;i<37;i++)
	{
		gotoxy(i,0);
		cout<<char(196);
		gotoxy(i,13);
		cout<<char(196);
	}
	for(int i=1;i<13;i++)
	{
		gotoxy(0,i);
		cout<<char(179);
		gotoxy(37,i);
		cout<<char(179);
	}
}
void khoitao()
{
	int xkhoitao=14;
	int ykhoitao=8;
	for(int i=0;i<4;i++)
	{
		toadox[i]= xkhoitao--;
		toadoy[i]= ykhoitao;
	}
}
void snake(int toadox[],int toadoy[])
{
	for(int i=0;i<sl;i++)
	{
		gotoxy(toadox[i],toadoy[i]);
		if(i==0)
			cout<<"0";
		else
			cout<<"o";
	}
}
void kethua(int toadox[],int toadoy[])
{
	for(int i=sl-1;i>0;i--)
	{
		toadox[i]=toadox[i-1];
		toadoy[i]=toadoy[i-1];
	}
}
int random()
{
	int x;
	int y;
	srand(time(0));
	int res=rand() % ( 35 - 0 + 1) + 1;
	int res1=rand() % (35 - 0 + 1) + 1;
	int res2=rand() % (12 - 0 + 1) + 1;
	int res3=rand() % (12 - 0 + 1) + 1;
	x=int((res+res1)/2);
	y=int((res3+res2)/2);
	gotoxy(x,y);
	save_random[0]=x;
	save_random[1]=y;	
}
void move()
{
	kethua(toadox,toadoy);
	if(_kbhit())
	{
		char kt=getch();
		if(kt==72)
			check=0;
		if(kt==80)
			check=1;
		if(kt==75)
			check=2;
		if(kt==77)
			check=3;
	}
	if(check==0)
	{
		toadoy[0]--;
	}
	else if(check==1)
	{
		toadoy[0]++;
	}
	else if(check==2)
	{
		toadox[0]--;
	}
	else if(check==3)
	{
		toadox[0]++;
	}
}
void all()
{
	khoitao();
	while(true)
	{
		box();
		move();	
		snake(toadox,toadoy);
		Sleep(500);
		system("cls");
//		gotoxy(save_random[0],save_random[1]);
//		cout<<"*";
//		if(save_random[0]==toadox[0] && save_random[1]==toadoy[0])
//		{
//			random();
//			sl++;
//			diem++;
//		}
//		if(toadox[0]==0 || toadoy[0]==0 ||toadox[0]==37 || toadoy[0]==13)
//		{
//			break;
//		}
	}
	system("cls");
	gotoxy(12,4);
	cout<<"GAME OVER";
	gotoxy(0,10);
}
int main()
{
	Nocursortype();
	random();
	all();
}
