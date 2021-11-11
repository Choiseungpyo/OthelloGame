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
int screen[5][SCREEN][SCREEN] = { 0 }; //0: 기본세팅(하얀 별) 1: 플레이어(파랑색 별) 2: 컴퓨터(빨강색 별)
									 //[턴+ 대각선 (4가지)][screen][screen]
//[0]: turn
//[1]: 왼 위
//[2]: 오른 위
//[3]: 왼 아래
//[4]: 오른쪽 아래

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
void SetDiagonalCnt();
int confirmSurrounding();
void test(); //대각선 및 열, 행  확인용

int main()
{
	//화면 그리기
	int textColor = 7;
	SetDiagonalCnt();
	SetStartScreen(textColor);
	while (GameOver ==0)
	{	
		if (clickEnter == 1)
		{
			if (confirmSurrounding() == 1) //자신이 Enter한 부근에 놓을 수 있을경우 
			{
				//test();
				if (turn == 1)
				{
					screen[0][arry][arrx] = 1;
				}
				else if (turn == 2)
				{
					screen[0][arry][arrx] = 2;
				}

				inGameScreen();
				
				xyInPlaying = 0;
				if (turn == 2)
				{
					turn = 1;
				}
				else if (turn == 1)
				{
					turn = 2;
				}
			}
			else
			{
				gotoxy(arrx, arry);
			}
			
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
	case 14:
		arry = 7;
		break;

	}

}

void changeTextColor(int textColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor);
	
}

void SetStartScreen(int textColor)
{
	screen[0][3][3] = 1;
	screen[0][3][4] = 2;
	screen[0][4][3] = 1;
	screen[0][4][4] = 2;

	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			if (screen[0][row][col] == 1)
			{
				changeTextColor(9);
				printf(" * ");
				changeTextColor(7);
				continue;
			}
			else if (screen[0][row][col] == 2)
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
			//테스트용
			if(screen[0][row][col] == 3)
			{
				changeTextColor(6);
				printf(" * ");
				changeTextColor(7);
				continue;
			}
			else if (screen[0][row][col] == 4)
			{
				changeTextColor(3);
				printf(" * ");
				changeTextColor(7);
				continue;
			}
			else if (screen[0][row][col] == 5)
			{
				changeTextColor(5);
				printf(" * ");
				changeTextColor(7);
				continue;
			}
			else if (screen[0][row][col] == 1)
			{
				changeTextColor(9);
				printf(" * ");
				changeTextColor(7);
				continue;
			}
			else if (screen[0][row][col] == 2)
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

void copygotoxy(int X, int Y)
{
	COORD pos;
	pos.X = X;
	pos.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void SetDiagonalCnt() //대각선 방향 입력시 해당 [행,열]의 대각선 개수 설정
{
	int remainingCol = 0;
	int num;
	int diagonalDir;

	//왼쪽 위
	diagonalDir = 1;

	for (int i = 0; i < 8; i++)
	{
		for (int a = 7; a >= i; a--) //8번, 7번 ... 1번
		{
			screen[diagonalDir][i][a] = i;
		}
		remainingCol = i;
		num = 0;
		for (int b = 0; b < remainingCol; b++)
		{
			screen[diagonalDir][i][b] = num;
			++num;
		}
	}

	//오른쪽 위 대각선 개수 
	diagonalDir = 2;	

	for (int i = 0; i < 8; i++)
	{
		for (int a = 0; a < 8 - i; a++)
		{
			screen[diagonalDir][i][a] = i;
		}
		remainingCol = 7 - i;
		num = i;
		for (int b = remainingCol; b < 8; b++)
		{
			screen[diagonalDir][i][b] = num;
			--num;
		}
	}

	//왼쪽 아래
	diagonalDir = 3;

	for (int i = 7; i >= 0; i--)
	{
		for (int a = 7; a >= 7 - i; a--) //8번, 7번 ... 1번
		{
			screen[diagonalDir][i][a] = 7 - i;
		}
		remainingCol = 7 - i; // 0,1,2,..
		num = 0;
		for (int b = 0; b < remainingCol; b++)
		{
			screen[diagonalDir][i][b] = num;
			++num;
		}
	}

	//오른쪽 아래 대각선 개수
	diagonalDir = 4;

	for (int i = 7; i >= 0; i--)
	{
		for (int a = 0; a < 8 - (7 - i); a++) //8번, 7번 ... 1번
		{
			screen[diagonalDir][i][a] = 7 - i;
		}
		remainingCol = i + 1;
		num = 6 - i;
		for (int b = remainingCol; b < 8; b++)
		{
			screen[diagonalDir][i][b] = num;
			--num;
		}
	}
}

// Enter 입력후 해당 자리에 블럭을 놓을수 있는지 검사.
int confirmSurrounding()
{
	for (int i = 1; i <= 4; i++)
	{
		//[1]: 왼 위
		//[2]: 오른 위
		//[3]: 왼 아래	
		//[4]: 오른쪽 아래

		//대각선 검사
		for (int a = 1; a <= screen[i][arry][arrx]; a++)
		{
			if (i == 1)//왼쪽 위방향
			{
				if (screen[0][arry - a][arrx - a] == 0 || screen[0][arry - a][arrx - a] == turn)
				{
					break;
				}
				else if (screen[0][arry - a][arrx - a] != turn)
				{
					//screen[0][arry - a][arrx - a] = 3;
					return 1; //해당 대각선에 자신과 반대되는 블럭이 있음.
				}
			}
			else if (i == 2)// 오른쪽 위방향
			{
				if (screen[0][arry - a][arrx + a] == 0 || screen[0][arry - a][arrx + a] == turn)
				{
					break;
				}
				else if (screen[0][arry - a][arrx + a] != turn)
				{
					//screen[0][arry - a][arrx + a] = 3;
					return 1; 
				}
			}
			else if (i == 3)//왼쪽 아래방향
			{
				if (screen[0][arry + a][arrx - a] == 0 || screen[0][arry + a][arrx - a] == turn)
				{
					break;
				}
				else if (screen[0][arry + a][arrx - a] != turn)
				{
					//screen[0][arry + a][arrx - a] = 3;
					return 1; 
				}
			}
			else if (i == 4)//오른쪽 아래방향
			{
				if (screen[0][arry + a][arrx + a] == 0 || screen[0][arry + a][arrx + a] == turn)
				{
					break;
				}
				else if (screen[0][arry + a][arrx + a] != turn )
				{
					//screen[0][arry + a][arrx + a] = 3;
					return 1; 
				}
			}		
		}
	}

	// 행 검사 - 위
	for (int a = arry-1; a >= 0; a--)
	{	
		if(screen[0][a][arrx] == 0 || screen[0][a][arrx] == turn)
		{
			break;
		}
		else if (screen[0][a][arrx] != turn)
		{
			return 1;
		}	
	}
	// 행 검사 - 아래
	for (int a = arry+1; a < 8; a++)
	{
		if (screen[0][a][arrx] == 0 || screen[0][a][arrx] == turn)
		{
			break;
		}
		else if (screen[0][a][arrx] != turn)
		{
			return 1;
		}
	}

	//열 검사 - 왼쪽
	for (int a = arrx-1; a >= 0; a--)
	{
		if (screen[0][arry][a] == 0 || screen[0][arry][a] == turn)
		{
			break;
		}
		else if (screen[0][arry][a] != turn )
		{
			return 1;
		}
	}

	//열 검사 - 오른쪽
	for (int a = arrx+1; a < 8; a++)
	{
		if (screen[0][arry][a] == 0 || screen[0][arry][a] == turn)
		{
			break;
		}
		else if (screen[0][arry][a] != turn)
		{
			return 1;
		}
	}

	
	return 0; //오류났을경우
}

void test() //Enter누른 부분으로부터 왼위, 오위, 왼아래, 오아래 대각선 긋기. 테스트용
{
	for (int i = 1; i <= 4; i++)
	{
		//[1]: 왼 위
		//[2]: 오른 위
		//[3]: 왼 아래	
		//[4]: 오른쪽 아래

		//대각선 검사
		for (int a = 1; a <= screen[i][arry][arrx]; a++)
		{
			if (i == 1)//왼쪽 위방향
			{
				if (screen[0][arry - a][arrx - a] == 0 || screen[0][arry - a][arrx - a] == turn)
				{
					break;
				}
				else if (screen[0][arry - a][arrx - a] != turn)
				{
					screen[0][arry - a][arrx - a] = 3;
				}
			}
			else if (i == 2)// 오른쪽 위방향
			{
				if (screen[0][arry - a][arrx + a] == 0 || screen[0][arry - a][arrx + a] == turn)
				{
					break;
				}
				else if (screen[0][arry - a][arrx + a] != turn)
				{
					screen[0][arry - a][arrx + a] = 3;
				}
			}
			else if (i == 3)//왼쪽 아래방향
			{
				if (screen[0][arry + a][arrx - a] == 0 || screen[0][arry + a][arrx - a] == turn)
				{
					break;
				}
				else if (screen[0][arry + a][arrx - a] != turn)
				{
					screen[0][arry + a][arrx - a] = 3;

				}
			}
			else if (i == 4)//오른쪽 아래방향
			{
				if (screen[0][arry + a][arrx + a] == 0 || screen[0][arry + a][arrx + a] == turn)
				{
					break;
				}
				else if (screen[0][arry + a][arrx + a] != turn)
				{
					screen[0][arry + a][arrx + a] = 3;

				}
			}
		}
	}


	int up = 0;
	int down = 0;
	int left = 0;
	int right = 0;

	// 행 검사 - 위
	for (int a = arry - 1; a >= 0; a--)
	{
		if (screen[0][a][arrx] == 0 || screen[0][a][arrx] == turn)
		{
			break;
		}
		else if (screen[0][a][arrx] != turn)
		{
			up = 1;
		}
	}
	// 행 검사 - 아래
	for (int a = arry + 1; a < 8; a++)
	{
		if (screen[0][a][arrx] == 0 || screen[0][a][arrx] == turn)
		{
			break;
		}
		else if (screen[0][a][arrx] != turn)
		{
			down = 1;
		}
	}

	//열 검사 - 왼쪽
	for (int a = arrx - 1; a >= 0; a--)
	{
		if (screen[0][arry][a] == 0 || screen[0][arry][a] == turn)
		{
			break;
		}
		else if (screen[0][arry][a] != turn)
		{
			left = 1;
		}
	}

	//열 검사 - 오른쪽
	for (int a = arrx + 1; a < 8; a++)
	{
		if (screen[0][arry][a] == 0 || screen[0][arry][a] == turn)
		{
			break;
		}
		else if (screen[0][arry][a] != turn)
		{
			right = 1;
		}
	}



	if (up == 1)
	{
		for (int a = arry - 1; a >= 0; a--)
		{
			screen[0][a][arrx] = 4;
		}
	}
	if (down == 1)
	{
		// 행 검사 - 아래
		for (int a = arry + 1; a < 8; a++)
		{
			screen[0][a][arrx] = 4;
		}
	}
	if (left == 1)
	{
		for (int a = arrx - 1; a >= 0; a--)
		{
			screen[0][arry][a] = 5;
		}
	}
	if (right == 1)
	{
		for (int a = arrx + 1; a < 8; a++)
		{
			screen[0][arry][a] = 5;
		}
	}

	
}

