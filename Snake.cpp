#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <ctime>

using namespace std;

int toadox[50];
int toadoy[50];
int save_random[2];
int sl=4;
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
	gotoxy(1,1);
	cout<<char(218);
	gotoxy(47,22);
	cout<<char(217);
	gotoxy(1,22);
	cout<<char(192);
	gotoxy(47,1);
	cout<<char(191);
	for(int i=0;i<45;i++)
	{
		gotoxy(i+2,1);
		cout<<char(196);
		gotoxy(i+2,22);
		cout<<char(196);
	}
	for(int i=0;i<20;i++)
	{
		gotoxy(1,i+2);
		cout<<char(179);
		gotoxy(47,i+2);
		cout<<char(179);
	}
}
void create()
{
	int khoitaox=15;
	int khoitaoy=5;
	for(int i=0;i<sl;i++)
	{
		toadox[i]=khoitaox;
		toadoy[i]=khoitaoy;
		khoitaox--;
	}	
}
void paint()
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
void move(int x,int y)
{
	for(int i=sl;i>0;i--)
	{
		toadox[i]=toadox[i-1];
		toadoy[i]=toadoy[i-1];
	}
	toadox[0]=x;
	toadoy[0]=y;
}
int random()
{
	int x;
	int y;
	srand(time(0));
	int res=rand() % ( 46 - 0 + 1) + 1;
	int res1=rand() % (46 - 0 + 1) + 1;
	int res2=rand() % (21 - 0 + 1) + 1;
	int res3=rand() % (21 - 0 + 1) + 1;
	x=int((res+res1)/2);
	y=int((res3+res2)/2);
	gotoxy(x,y);
	save_random[0]=x;
	save_random[1]=y;	
}
void menu()
{
	gotoxy(50,2);
	cout<<"1. Choi lai";
	gotoxy(50,3);
	cout<<"2. Thoat";
}
int chon_menu()
{
	int n;
	gotoxy(50,4);
	cout<<"Nhap lua chon: ";
	cin>>n;
	return n;
}
void all()
{	
	back:
	system("cls");
	int check=2;
	int check1;
	// ve khung
	box();
	//khoi tao vi tri ran
	create();
	//ve ran
	paint();
	int x=toadox[0];
	int y=toadoy[0];
	//diem
	gotoxy(50,2);
	cout<<"DIEM:";
	//random moi`
	XT:
	random();
	gotoxy(save_random[0],save_random[1]);
	cout<<"*";
	gotoxy(56,2);
	cout<<sl-4;
	while(true)
	{
		gotoxy(toadox[sl],toadoy[sl]);
		cout<<" ";
		paint();
		if(_kbhit()==true)
		{
			check1=check;
			char c=_getch();
			if(c==-32)
			{
				c=_getch()	;
				if(c==72)
					check=1;
				else if(c==80)
					check=0;
				else if(c==75)
					check=3;
				else if(c=77)
					check=2;
				if(check1==1 and check==0)
					check=1;
				else if(check1==0 and check==1)
					check=0;
				else if(check1==2 and check==3)
					check=2;
				else if(check1==3 and check==2)
					check=3;
			}	
		}
		if(check==0)
			y++;
		else if(check==1)
			y--;
		else if(check==2)
			x++;
		else if(check==3)
			x--;
		// xu ly vi tri xy
		move(x,y);
		//xu ly + diem va random point
		if(x==save_random[0] && y==save_random[1])
		{
			sl++;
			goto XT;
		}
		//Xu ly logic
		if(toadox[0]==47 || toadoy[0]==23 || toadox[0]==0 || toadoy[0]==0)
			goto out;
		for(int i=4;i<sl;i++)
		{
			if(x==toadox[i] && y==toadoy[i])
			{
				goto out;
			}
		}
		Sleep(300);
	}
	out:
	gotoxy(17,10);
	cout<<"GAME OVER";	
	gotoxy(50,3);
	menu();
	int chon=chon_menu();
	switch(chon)
	{
		case 1:
		{
			goto back;
		}
		case 2:
		{
			break;
		}
	}
	system("cls");
}
int main()
{
	Nocursortype();
	all();
}
