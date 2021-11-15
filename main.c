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
int screen[5][SCREEN][SCREEN] = { 0 }; //0: �⺻����(�Ͼ� ��) 1: �÷��̾�(�Ķ��� ��) 2: ��ǻ��(������ ��)
									 //[��+ �밢�� (4����)][screen][screen]
									 // 3: �÷��̾ �̹� ���Ҵ� ��(�Ķ��� ��) 4: ��ǻ�Ͱ� �̹� ���Ҵ� ��(������ ��)
//[0]: turn
//[1]: �� ��
//[2]: ���� ��
//[3]: �� �Ʒ�
//[4]: ������ �Ʒ�

int clickEnter = 0; //0 :false 1:True
int turn = 1; // �÷��̾� : 1	��ǻ�� :2
int resetMiddlePlace;
int isFirstTimeTocheckWhereCurrentUserCanPutBlock = 0; //�� ���� �� �ִ� �� ��ġ Ȯ���ϴ°� ó���ΰ�?
char computerRandomPlace[8][8] = {0};
int enableMoveNextTurn = 0;

//�Ķ��� 9 - �÷��̾�
//������ 12 - ��ǻ��

void changeTextColor(int textColor);
void SetStartScreen(int textColor);
void gotoxy();
void matchXY();
void viewInGameScreen();
void checkKey();
void SetDiagonalCnt();
int confirmSurrounding();
void changeBlockColor(); //�밢�� �� ��, ��  Ȯ�ο�
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
			if (confirmSurrounding() == 1) //�ڽ��� Enter�� �αٿ� ���� �� ������� 
			{
				//Enter �Է��� �ش� �ڸ��� ���� ���� �� �ִ��� �˻� �� ������ġ ���� �ٲٱ�
				screen[0][arry][arrx] = 1;

				changeBlockColor();
				viewInGameScreen(); //clickEnter ���Լ����� 0���� �ٲ�.
				
				resetMiddlePlace = 0;
				
				turn = changeOppositeNumOfCurrentTurn(); // ��� : �÷��̾� �Ͽ��� ��ǻ�� ������ �Ѿ�Ե�. 
				
				isFirstTimeTocheckWhereCurrentUserCanPutBlock = 0;
			}
			else
			{
				gotoxy();
			}			
		}

		moveNextTurn(); // �÷��̾ ���� �� �ִ� ���� ���� ��� ���������� �ѱ��.

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
				//changeTextColor(10); //�ʷϻ�
				printf("   ");
				//changeTextColor(7);
				continue;
			}
			else if (screen[0][row][col] == 3) //��ǻ�Ͱ� ���� ��ġ 
			{
				changeTextColor(10); //�ʷϻ�
				printf(" * ");
				changeTextColor(7);
				continue;
			}
			else if (screen[0][row][col] == 1) //�÷��̾�
			{
				changeTextColor(9); //�Ķ���
				printf(" * ");
				changeTextColor(7);
				continue;
			}
			else if (screen[0][row][col] == 2) //��ǻ��
			{
				changeTextColor(12); //������
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


void SetDiagonalCnt() //�밢�� ���� �Է½� �ش� [��,��]�� �밢�� ���� ����
{
	int remainingCol = 0;
	int num;
	int diagonalDir;

	//���� ��
	diagonalDir = 1;

	for (int i = 0; i < 8; i++)
	{
		for (int a = 7; a >= i; a--) //8��, 7�� ... 1��
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

	//������ �� �밢�� ���� 
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

	//���� �Ʒ�
	diagonalDir = 3;

	for (int i = 7; i >= 0; i--)
	{
		for (int a = 7; a >= 7 - i; a--) //8��, 7�� ... 1��
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

	//������ �Ʒ� �밢�� ����
	diagonalDir = 4;

	for (int i = 7; i >= 0; i--)
	{
		for (int a = 0; a < 8 - (7 - i); a++) //8��, 7�� ... 1��
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

// Enter �Է��� -> �ش� �ڸ��� ���� ������ �ִ��� �˻�.
int confirmSurrounding()
{
	if (confirmIfThereIsBlock() == 1) //���� �ڸ��� �̹� ������ ���� ���� �����Ƿ� ������ġ�� ���� ���� �� ����. 
	{
		return 0;
	}

	for (int i = 1; i <= 4; i++)
	{
		//[1]: �� ��
		//[2]: ���� ��
		//[3]: �� �Ʒ�	
		//[4]: ������ �Ʒ�

		//�밢�� �˻�
		if (i == 1) //���� �� ����
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
		else if (i == 2) //������ �� ����
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
		else if (i == 3) //���� �Ʒ� ����
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
		else if (i == 4) //������ �Ʒ� ����
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



	// �� �˻� - ��
	if (screen[0][arry - 1][arrx] == changeOppositeNumOfCurrentTurn())
	{
		for (int a = arry - 1; a >= 0; a--) //�� �������� �˻�
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


	// �� �˻� - �Ʒ�
	if (screen[0][arry + 1][arrx] == changeOppositeNumOfCurrentTurn())
	{
		for (int a = arry + 1; a < 8; a++) //�Ʒ��������� �˻�
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

	//�� �˻� - ����
	if (screen[0][arry][arrx - 1] == changeOppositeNumOfCurrentTurn()) //�ڱⰡ ���� �� �ٷ� ���� ĭ.
	{
		for (int a = arrx - 1; a >= 0; a--) // <-- �������� ��.
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


	//�� �˻� - ������
	if (screen[0][arry][arrx + 1] == changeOppositeNumOfCurrentTurn()) // --> �������� �˻�
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

	
	return 0; //�����������
}

void changeBlockColor() //���� ������ �ٲ۴�. screen[][][]�� ���� ����/ ����� viewInGameScreen������
{

	for (int i = 1; i <= 4; i++)
	{
		//[1]: �� ��
		//[2]: ���� ��
		//[3]: �� �Ʒ�	
		//[4]: ������ �Ʒ�

		//�밢�� �˻�
		if (i == 1) //���� �� ����
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
		else if (i == 2) //������ �� ����
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
		else if (i == 3) //���� �Ʒ� ����
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
		else if (i == 4) //������ �Ʒ� ����
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

		
	

	// �� �˻� - ��
	if (screen[0][arry - 1][arrx] == changeOppositeNumOfCurrentTurn())
	{
		for (int a = arry - 1; a >= 0; a--) //�� �������� �˻�
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


	// �� �˻� - �Ʒ�
	if (screen[0][arry + 1][arrx] == changeOppositeNumOfCurrentTurn())
	{
		for (int a = arry + 1; a < 8; a++) //�Ʒ��������� �˻�
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

	//�� �˻� - ����
	if (screen[0][arry][arrx - 1] == changeOppositeNumOfCurrentTurn()) //�ڱⰡ ���� �� �ٷ� ���� ĭ.
	{
		for (int a = arrx - 1; a >= 0; a--) // <-- �������� ��.
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


	//�� �˻� - ������
	if (screen[0][arry][arrx + 1] == changeOppositeNumOfCurrentTurn()) // --> �������� �˻�
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

int changeOppositeNumOfCurrentTurn() // �÷��̾� -> ��ǻ�� �Ǵ� ��ǻ�� -> �÷��̾� ������ �ٲ��ش�.
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
		return -1; //������ ���
	}
}

int confirmIfThereIsBlock() //�ش� ��ġ�� ���� �ִ��� ������ �˻�
{
	if (screen[0][arry][arrx] == 1 || screen[0][arry][arrx] == 2)
	{
		return 1; //���� �ڸ��� ���� ����. 
	}
	else
	{
		return 0; //���� �ڸ��� ���� ����.
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
		return 1; //��� �ڸ��� ���� �������Ƿ� ��������
	}
	else
	{
		return 0; //���� ��� �ڸ��� ���� �� ���� ����.
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

	Sleep(5000); //5�� ��ٸ� �� ���

	viewInGameScreen();

	Sleep(3000); //5�� ��ٸ� �� ���

	clearScreen();
	viewInGameScreen();

	gotoxy();
	printf("�÷��̾� : %d �� \n", playerBlockCnt);
	printf("��ǻ��   : %d �� \n", computerBlockCnt);

	if (playerBlockCnt > computerBlockCnt)
	{
		printf("�÷��̾� �¸�");
	}
	else
	{
		printf("��ǻ�� �¸�");
	}
	Sleep(5000);
	
}

//��ǻ�Ͱ� ���� ���� �� �ִ� <��ġ> ǥ�� �� ���
void checkWhereCurrentUserCanPutBlock()
{
	int originalArrx, originalArry;
	int randomComputerNum = 1; // computerRandomPlace[arry][arrx]�� ��. �ش� �ƴ� ������ ��� 0���� �ʱ�ȭ�Ǿ�����. 
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
			//�������� ++randomComputerNum�̱� ������ -1�ؼ� ����ؾ���.
			if (computerRandomPlace[arry][arrx] == randomComputerNum)
			{
				screen[0][arry][arrx] = 3;
				tmpArrx = arrx;
				tmpArry = arry;
			}
		}
	}
	
	viewInGameScreen(); //�������� ���� ��ǻ���� ��ġ�� �ʷϻ����� ���

	screen[0][tmpArry][tmpArrx] = 2;
	arrx = tmpArrx;
	arry = tmpArry;

	x = arrx + (arrx * 2 + 1); //��ǻ�Ͱ� ���� �ٲٴ� ���� Ŀ���� �д�.
	y = arry * 2;

	changeBlockColor();
	
	gotoxy();
	Sleep(3000); //3����
	viewInGameScreen(); //���� �ش� ��ġ ��ǻ�� ����� ���ϰ� �ϱ�

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
	randNum = rand() % randomComputerNum + 1; //1~�ش� ������
	return randNum;
}


// �ش� ������ ������ �� ���� ������ ���� �������� ���� �ѱ��.
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
				if (confirmSurrounding() == 1) //���������� �ش� ��ġ�� ���� �� ���� ���
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
