#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#define SCREEN 8

#define ESC 27
#define ENTER 13
#define LEFT 75 
#define RIGHT 77 
#define UP 72 
#define DOWN 80 

#define MOVE_UP 0
#define MOVE_DOWN 1 
#define MOVE_LEFT 2 
#define MOVE_RIGHT 3 

int GameOver = 0;
int x, y;
int arrx, arry;
int screen[SCREEN][SCREEN] = { 0 }; //0: 기본세팅(하얀 별) 1: 플레이어(파랑색 별) 2: 컴퓨터(빨강색 별)
int clickEnter = 0; //0 :false 1:True
int turn = 1; // 플레이어 : 1	컴퓨터 :2
int xyInPlaying;

//파랑색 9 - 플레이어
//빨간색 12 - 컴퓨터

void changeTextColor(int textColor);
void SetStartScreen(int textColor);
void gotoxy();
void matchXY();
void inGameScreen();
void checkKey();

int main()
{
	//화면 그리기
	int textColor = 7;

	SetStartScreen(textColor);
	while (GameOver ==0)
	{	
		if (clickEnter == 1)
		{
			if (turn == 2)
			{
				turn = 1;
			}
			else if (turn == 1)
			{
				turn = 2;
			}
			inGameScreen();
			xyInPlaying = 0;
		}
		checkKey();
		gotoxy();
		
		//Sleep(250); //1000 = 1초 지연
	}

	return 0;
}

void matchXY()
{
	switch (x)
	{
	case 1:
		arrx = 0;
		break;
	case 4:
		arrx = 1;
		break;
	case 7:
		arrx = 2;
		break;
	case 10:
		arrx = 3;
		break;
	case 13:
		arrx = 4;
		break;
	case 16:
		arrx = 5;
		break;
	case 19:
		arrx = 6;
		break;
	case 22:
		arrx = 7;
		break;
	}

	switch (y)
	{
	case 0:
		arry = 0;
		break;
	case 2:
		arry = 1;
		break;
	case 4:
		arry = 2;
		break;
	case 6:
		arry = 3;
		break;
	case 8:
		arry = 4;
		break;
	case 10:
		arry = 5;
		break;
	case 12:
		arry = 6;
		break;
	case 7:
		arry = 7;
		break;

	}

	if (turn == 1)
	{
		screen[arry][arrx] = 1;
	}
	else if (turn == 2)
	{
		screen[arry][arrx] = 2;
	}
}

void changeTextColor(int textColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor);
	
}

void SetStartScreen(int textColor)
{
	screen[3][3] = 1;
	screen[3][4] = 2;
	screen[4][3] = 1;
	screen[4][4] = 2;

	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			if (screen[row][col] == 1)
			{
				changeTextColor(9);
				printf(" * ");
				changeTextColor(7);
				continue;
			}
			else if (screen[row][col] == 2)
			{
				changeTextColor(12);
				printf(" * ");
				changeTextColor(7);
				continue;
			}

			printf(" * ");
		}
		printf("\n\n");
	}
}

void checkKey()
{
	int key;
	if (_kbhit() != 0)
	{
		key = _getch();
		if (key == 224)
		{
			key = _getch();
		}
		switch (key)
		{
		case ESC:
			GameOver = 1;
			break;
		case ENTER:
			clickEnter = 1;
			matchXY();
			break;
		case LEFT:
			x = x - 3;
			break;
		case RIGHT:
			x = x + 3;
			break;
		case UP:
			y = y - 2;
			break;
		case DOWN:
			y = y + 2;
			break;
		}
		if (x < 0)
		{
			x = x + 3;
		}
		else if (x > 22)
		{
			x = x - 3;
		}
		if (y < 0)
		{
			y = y + 2;
		}
		else if (y > 14)
		{
			y = y - 2;
		}
	}
}

void inGameScreen()
{
	clickEnter = 0;
	x = 0; y = 0;
	gotoxy();
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			if (screen[row][col] == 1)
			{
				changeTextColor(9);
				printf(" * ");
				changeTextColor(7);
				continue;
			}
			else if (screen[row][col] == 2)
			{
				changeTextColor(12);
				printf(" * ");
				changeTextColor(7);
				continue;
			}

			printf(" * ");
		}
		printf("\n\n");
	}
}

void gotoxy()
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	if (clickEnter == 0 && xyInPlaying ==0)
	{
		x = 10;
		y = 6;
		++xyInPlaying;
	}
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void a(int textColor)
{
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor);
			printf(" * ");
		}
		printf("\n\n");
	}
}