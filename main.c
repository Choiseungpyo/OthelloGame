#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

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
									 // 3: 플레이어가 이미 놓았던 곳(파랑색 별) 4: 컴퓨터가 이미 놓았던 곳(빨강색 별)
//[0]: turn
//[1]: 왼 위
//[2]: 오른 위
//[3]: 왼 아래
//[4]: 오른쪽 아래

int clickEnter = 0; //0 :false 1:True
int turn = 1; // 플레이어 : 1	컴퓨터 :2
int resetMiddlePlace;
int isFirstTimeTocheckWhereCurrentUserCanPutBlock = 0; //블럭 놓을 수 있는 곳 위치 확인하는게 처음인가?
char computerRandomPlace[8][8] = {0};
int enableMoveNextTurn = 0;

//파랑색 9 - 플레이어
//빨간색 12 - 컴퓨터

void changeTextColor(int textColor);
void SetStartScreen(int textColor);
void gotoxy();
void matchXY();
void viewInGameScreen();
void checkKey();
void SetDiagonalCnt();
int confirmSurrounding();
void changeBlockColor(); //대각선 및 열, 행  확인용
int changeOppositeNumOfCurrentTurn();
int confirmIfThereIsBlock();
int confirmGameOver();
void viewGameResult();
void checkWhereCurrentUserCanPutBlock();
int calComputerRandPlace(int randomComputerNum);
void moveNextTurn();
void setErrorSetting();
void clearScreen();


int main()
{
	int textColor = 7;

	srand((unsigned int)time(NULL));

	SetDiagonalCnt();
	SetStartScreen(textColor);
	
	while (GameOver ==0)
	{	
		if (confirmGameOver() == 1)
		{
			viewGameResult();
			return 0;
		}

		if (clickEnter == 1)
		{
			if (confirmSurrounding() == 1) //자신이 Enter한 부근에 놓을 수 있을경우 
			{
				//Enter 입력후 해당 자리에 블럭을 놓을 수 있는지 검사 후 현재위치 색깔 바꾸기
				screen[0][arry][arrx] = 1;

				changeBlockColor();
				viewInGameScreen(); //clickEnter 이함수에서 0으로 바뀜.
				
				resetMiddlePlace = 0;
				
				turn = changeOppositeNumOfCurrentTurn(); // 결과 : 플레이어 턴에서 컴퓨터 턴으로 넘어가게됨. 
				
				isFirstTimeTocheckWhereCurrentUserCanPutBlock = 0;
			}
			else
			{
				gotoxy();
			}			
		}

		moveNextTurn(); // 플레이어가 놓을 수 있는 곳이 없을 경우 다음턴으로 넘긴다.

		if (confirmGameOver() == 1)
		{
			viewGameResult();
			return 0;
		}

		if (turn ==2 && isFirstTimeTocheckWhereCurrentUserCanPutBlock == 0 || enableMoveNextTurn ==1 && turn == 2)
		{
			//Sleep(3000);
			checkWhereCurrentUserCanPutBlock();
			++isFirstTimeTocheckWhereCurrentUserCanPutBlock;
			enableMoveNextTurn = 0;
		}
		
		checkKey();
		gotoxy();
	}

	return 0;
}

void matchXY()
{
	switch (x)
	{
	case 1:
		arrx = 0; //+1 <-- (arrx * 2)+1
		break;
	case 4:
		arrx = 1; //+3
		break;
	case 7:
		arrx = 2; //+5
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
	screen[0][4][3] = 2;
	screen[0][4][4] = 1;
	//setErrorSetting();

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

void viewInGameScreen()
{
	clickEnter = 0;
	x = 0; y = 0;
	gotoxy();
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			if (screen[0][row][col] == -1) //clearScreen
			{
				//changeTextColor(10); //초록색
				printf("   ");
				//changeTextColor(7);
				continue;
			}
			else if (screen[0][row][col] == 3) //컴퓨터가 놓을 위치 
			{
				changeTextColor(10); //초록색
				printf(" * ");
				changeTextColor(7);
				continue;
			}
			else if (screen[0][row][col] == 1) //플레이어
			{
				changeTextColor(9); //파랑색
				printf(" * ");
				changeTextColor(7);
				continue;
			}
			else if (screen[0][row][col] == 2) //컴퓨터
			{
				changeTextColor(12); //빨강색
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
	
	if (clickEnter == 0 && resetMiddlePlace == 0) 
	{
		x = 10;
		y = 6;
		++resetMiddlePlace;
	}
	if (confirmGameOver() == 1 || GameOver == 1)
	{
		x = 0;
		y = 0;
	}
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

// Enter 입력후 -> 해당 자리에 블럭을 놓을수 있는지 검사.
int confirmSurrounding()
{
	if (confirmIfThereIsBlock() == 1) //현재 자리에 이미 이전에 놓인 블럭이 있으므로 현재위치에 블럭을 놓을 수 없다. 
	{
		return 0;
	}

	for (int i = 1; i <= 4; i++)
	{
		//[1]: 왼 위
		//[2]: 오른 위
		//[3]: 왼 아래	
		//[4]: 오른쪽 아래

		//대각선 검사
		if (i == 1) //왼쪽 위 방향
		{
			if (screen[0][arry - 1][arrx - 1] == changeOppositeNumOfCurrentTurn())
			{
				for (int a = 1; a <= screen[i][arry][arrx]; a++)
				{
					if (screen[0][arry - a][arrx - a] == 0)
					{
						break;
					}
					else if (screen[0][arry - a][arrx - a] == turn)
					{
						return 1;
					}
				}
			}
		}
		else if (i == 2) //오른쪽 위 방향
		{
			if (screen[0][arry - 1][arrx + 1] == changeOppositeNumOfCurrentTurn())
			{
				for (int a = 1; a <= screen[i][arry][arrx]; a++)
				{
					if (screen[0][arry - a][arrx + a] == 0)
					{
						break;
					}
					else if (screen[0][arry - a][arrx + a] == turn)
					{
						return 1;
					}
				}
			}
		}
		else if (i == 3) //왼쪽 아래 방향
		{
			if (screen[0][arry + 1][arrx - 1] == changeOppositeNumOfCurrentTurn())
			{
				for (int a = 1; a <= screen[i][arry][arrx]; a++)
				{
					if (screen[0][arry + a][arrx - a] == 0)
					{
						break;
					}
					else if (screen[0][arry + a][arrx - a] == turn)
					{
						return 1;
					}
				}
			}
		}
		else if (i == 4) //오른쪽 아래 방향
		{
			if (screen[0][arry + 1][arrx + 1] == changeOppositeNumOfCurrentTurn())
			{
				for (int a = 1; a <= screen[i][arry][arrx]; a++)
				{
					if (screen[0][arry + a][arrx + a] == 0)
					{
						break;
					}
					else if (screen[0][arry + a][arrx + a] == turn)
					{
						return 1;
					}
				}
			}
		}
	}



	// 행 검사 - 위
	if (screen[0][arry - 1][arrx] == changeOppositeNumOfCurrentTurn())
	{
		for (int a = arry - 1; a >= 0; a--) //위 방향으로 검사
		{
			if (screen[0][a][arrx] == 0)
			{
				break;
			}
			else if (screen[0][a][arrx] == turn)
			{
				return 1;
			}
		}
	}


	// 행 검사 - 아래
	if (screen[0][arry + 1][arrx] == changeOppositeNumOfCurrentTurn())
	{
		for (int a = arry + 1; a < 8; a++) //아래방향으로 검사
		{
			if (screen[0][a][arrx] == 0)
			{
				break;
			}
			else if (screen[0][a][arrx] == turn)
			{
				return 1;
			}
		}
	}

	//열 검사 - 왼쪽
	if (screen[0][arry][arrx - 1] == changeOppositeNumOfCurrentTurn()) //자기가 놓은 곳 바로 왼쪽 칸.
	{
		for (int a = arrx - 1; a >= 0; a--) // <-- 방향으로 감.
		{
			if (screen[0][arry][a] == 0)
			{
				break;
			}
			else if (screen[0][arry][a] == turn)
			{
				return 1;
			}
		}
	}


	//열 검사 - 오른쪽
	if (screen[0][arry][arrx + 1] == changeOppositeNumOfCurrentTurn()) // --> 방향으로 검사
	{
		for (int a = arrx + 1; a < 8; a++)
		{
			if (screen[0][arry][a] == 0)
			{
				break;
			}
			else if (screen[0][arry][a] == turn)
			{
				return 1;
			}
		}
	}

	
	return 0; //오류났을경우
}

void changeBlockColor() //블럭의 색깔을 바꾼다. screen[][][]의 값만 변경/ 출력은 viewInGameScreen에서만
{

	for (int i = 1; i <= 4; i++)
	{
		//[1]: 왼 위
		//[2]: 오른 위
		//[3]: 왼 아래	
		//[4]: 오른쪽 아래

		//대각선 검사
		if (i == 1) //왼쪽 위 방향
		{
			if (screen[0][arry - 1][arrx - 1] == changeOppositeNumOfCurrentTurn())
			{
				for (int a = 1; a <= screen[i][arry][arrx]; a++)
				{
					if (screen[0][arry - a][arrx - a] == 0)
					{
						break;
					}
					else if (screen[0][arry - a][arrx - a] == turn)
					{
						for (int b = 1; b < a; b++)
						{
							screen[0][arry - b][arrx - b] = turn;
						}
						break;
					}
				}
			}
		}
		else if (i == 2) //오른쪽 위 방향
		{
			if (screen[0][arry - 1][arrx + 1] == changeOppositeNumOfCurrentTurn())
			{
				for (int a = 1; a <= screen[i][arry][arrx]; a++)
				{
					if (screen[0][arry - a][arrx + a] == 0)
					{
						break;
					}
					else if (screen[0][arry - a][arrx + a] == turn)
					{
						for (int b = 1; b < a; b++)
						{
							screen[0][arry - b][arrx + b] = turn;
						}
						break;
					}
				}
			}
		}
		else if (i == 3) //왼쪽 아래 방향
		{
			if (screen[0][arry + 1][arrx - 1] == changeOppositeNumOfCurrentTurn())
			{
				for (int a = 1; a <= screen[i][arry][arrx]; a++)
				{
					if (screen[0][arry + a][arrx - a] == 0)
					{
						break;
					}
					else if (screen[0][arry + a][arrx - a] == turn)
					{
						for (int b = 1; b < a; b++)
						{
							screen[0][arry + b][arrx - b] = turn;
						}
						break;
					}
				}
			}
		}
		else if (i == 4) //오른쪽 아래 방향
		{
			if (screen[0][arry + 1][arrx + 1] == changeOppositeNumOfCurrentTurn())
			{
				for (int a = 1; a <= screen[i][arry][arrx]; a++)
				{
					if (screen[0][arry + a][arrx + a] == 0)
					{
						break;
					}
					else if (screen[0][arry + a][arrx + a] == turn)
					{
						for (int b = 1; b < a; b++)
						{
							screen[0][arry + b][arrx + b] = turn;
						}
						break;
					}
				}
			}
		}

	}

		
	

	// 행 검사 - 위
	if (screen[0][arry - 1][arrx] == changeOppositeNumOfCurrentTurn())
	{
		for (int a = arry - 1; a >= 0; a--) //위 방향으로 검사
		{
			if (screen[0][a][arrx] == 0)
			{
				break;
			}
			else if (screen[0][a][arrx] == turn)
			{
				for (int b = arry - 1; b > a; b--)
				{
					screen[0][b][arrx] = turn;
				}
				break;
			}
		}
	}


	// 행 검사 - 아래
	if (screen[0][arry + 1][arrx] == changeOppositeNumOfCurrentTurn())
	{
		for (int a = arry + 1; a < 8; a++) //아래방향으로 검사
		{
			if (screen[0][a][arrx] == 0)
			{
				break;
			}
			else if (screen[0][a][arrx] == turn)
			{
				for (int b = arry+1; b < a; b++)
				{
					screen[0][b][arrx] = turn;
				}
				break;
			}
		}
	}

	//열 검사 - 왼쪽
	if (screen[0][arry][arrx - 1] == changeOppositeNumOfCurrentTurn()) //자기가 놓은 곳 바로 왼쪽 칸.
	{
		for (int a = arrx - 1; a >= 0; a--) // <-- 방향으로 감.
		{
			if (screen[0][arry][a] == 0)
			{
				break;
			}
			else if (screen[0][arry][a] == turn)
			{
				for (int b = arrx-1; b > a; b--)
				{
					screen[0][arry][b] = turn;
				}
				break;
			}
		}
	}


	//열 검사 - 오른쪽
	if (screen[0][arry][arrx + 1] == changeOppositeNumOfCurrentTurn()) // --> 방향으로 검사
	{
		for (int a = arrx + 1; a < 8; a++)
		{
			if (screen[0][arry][a] == 0)
			{
				break;
			}
			else if (screen[0][arry][a] == turn)
			{
				for (int b = arrx + 1; b < a; b++)
				{
					screen[0][arry][b] = turn;
				}
				break;
			}
		}
	}
}

int changeOppositeNumOfCurrentTurn() // 플레이어 -> 컴퓨터 또는 컴퓨터 -> 플레이어 턴으로 바꿔준다.
{
	if (turn == 1)
	{
		return 2;
	}
	else if (turn == 2)
	{
		return 1;
	}
	else
	{
		return -1; //오류인 경우
	}
}

int confirmIfThereIsBlock() //해당 위치에 블럭이 있는지 없는지 검사
{
	if (screen[0][arry][arrx] == 1 || screen[0][arry][arrx] == 2)
	{
		return 1; //현재 자리에 블럭이 있음. 
	}
	else
	{
		return 0; //현재 자리에 블럭이 없음.
	}
}

int confirmGameOver()
{
	int spaceFilledCnt=0;

	for (int row = 0; row < SCREEN; row++)
	{
		for (int col = 0; col < SCREEN; col++)
		{
			if (screen[0][row][col] == 1 || screen[0][row][col] == 2)
			{
				++spaceFilledCnt;
			}
		}
	}

	if (spaceFilledCnt == SCREEN * SCREEN)
	{
		return 1; //모든 자리에 블럭을 놓았으므로 게임종료
	}
	else
	{
		return 0; //아직 모든 자리에 블럭을 다 놓지 않음.
	}
}

void viewGameResult()
{
	int playerBlockCnt = 0;
	int computerBlockCnt=0;
	int tmpBlockCnt;

	for (int row = 0; row < SCREEN; row++)
	{
		for (int col = 0; col < SCREEN; col++)
		{
			if (screen[0][row][col] == 1)
			{
				++playerBlockCnt;
			}
			else if (screen[0][row][col] == 2)
			{
				++computerBlockCnt;
			}
		}
	}

	tmpBlockCnt = 0;
	for (int row = 0; row < SCREEN; row++)
	{
		for (int col = 0; col < SCREEN; col++)
		{
			if (tmpBlockCnt < playerBlockCnt)
			{
				screen[0][row][col] = 1;
				++tmpBlockCnt;
			}
			else
			{
				screen[0][row][col] = 2;
			}
		}
	}

	Sleep(5000); //5초 기다린 후 출력

	viewInGameScreen();

	Sleep(3000); //5초 기다린 후 출력

	clearScreen();
	viewInGameScreen();

	gotoxy();
	printf("플레이어 : %d 개 \n", playerBlockCnt);
	printf("컴퓨터   : %d 개 \n", computerBlockCnt);

	if (playerBlockCnt > computerBlockCnt)
	{
		printf("플레이어 승리");
	}
	else
	{
		printf("컴퓨터 승리");
	}
	Sleep(5000);
	
}

//컴퓨터가 블럭을 놓을 수 있는 <위치> 표시 및 출력
void checkWhereCurrentUserCanPutBlock()
{
	int originalArrx, originalArry;
	int randomComputerNum = 1; // computerRandomPlace[arry][arrx]의 값. 해당 아닌 값들은 모두 0으로 초기화되어있음. 
	int tmpArrx;
	int tmpArry;

	originalArrx = arrx;
	originalArry = arry;
	
	for (arry = 0; arry < SCREEN; arry++)
	{
		for (arrx = 0; arrx < SCREEN; arrx++)
		{
			if (confirmSurrounding() == 1)
			{
				//screen[0][arry][arrx] = 3;
				computerRandomPlace[arry][arrx] = randomComputerNum;
				++randomComputerNum;
			}
		}
	}
	
	randomComputerNum = calComputerRandPlace(randomComputerNum - 1);

	for (arry = 0; arry < SCREEN; arry++)
	{
		for (arrx = 0; arrx < SCREEN; arrx++)
		{
			//마지막에 ++randomComputerNum이기 때문에 -1해서 계산해야함.
			if (computerRandomPlace[arry][arrx] == randomComputerNum)
			{
				screen[0][arry][arrx] = 3;
				tmpArrx = arrx;
				tmpArry = arry;
			}
		}
	}
	
	viewInGameScreen(); //랜덤으로 나온 컴퓨터의 위치를 초록색으로 출력

	screen[0][tmpArry][tmpArrx] = 2;
	arrx = tmpArrx;
	arry = tmpArry;

	x = arrx + (arrx * 2 + 1); //컴퓨터가 블럭을 바꾸는 곳에 커서를 둔다.
	y = arry * 2;

	changeBlockColor();
	
	gotoxy();
	Sleep(3000); //3초후
	viewInGameScreen(); //이후 해당 위치 컴퓨터 색깔로 변하게 하기

	for (arry = 0; arry < SCREEN; arry++)
	{
		for (arrx = 0; arrx < SCREEN; arrx++)
		{
			/*if (computerRandomPlace[arry][arrx] == randomComputerNum)
			{
				screen[0][arry][arrx] = 0;			
			}*/
			computerRandomPlace[arry][arrx] = 0;
		}
	}

	arrx = originalArrx;
	arry = originalArry;

	resetMiddlePlace = 0;
	turn = 1;
}

int calComputerRandPlace(int randomComputerNum)
{
	int randNum = 0;
	randNum = rand() % randomComputerNum + 1; //1~해당 값까지
	return randNum;
}


// 해당 차례의 유저가 둘 곳이 없으면 다음 유저에게 턴을 넘긴다.
void moveNextTurn()
{
	int originalArrx, originalArry;
	int originalx, originaly;
	int placeCurrentUserCannotPut_cnt = 0;

	originalx = x;
	originaly = y;
	originalArrx = arrx;
	originalArry = arry;

	for (int row = 0; row < SCREEN; row++)
	{
		for (int col = 0; col < SCREEN; col++)
		{
			if (screen[0][row][col] == 0)
			{
				arrx = col;
				arry = row;
				if (confirmSurrounding() == 1) //현재유저가 해당 위치에 놓을 수 있을 경우
				{ 
					++placeCurrentUserCannotPut_cnt; 				
				}
			}
		}
	}

	if (placeCurrentUserCannotPut_cnt ==  0)
	{
		turn = changeOppositeNumOfCurrentTurn();
		enableMoveNextTurn = 1;
	}

	arrx = originalArrx;
	arry = originalArry;
	x = originalx;
	y = originaly;
}

void setErrorSetting()
{
	for (int row = 0; row < SCREEN; row++)
	{
		for (int col = 0; col < SCREEN; col++)
		{
			screen[0][row][col] = 1;
		}
	}

	screen[0][1][6] = 2;
	screen[0][6][1] = 2;
	screen[0][7][0] = 0;
	screen[0][0][7] = 0;

}

void clearScreen()
{
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			screen[0][row][col] = -1;
		}
	}
}
