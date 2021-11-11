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
int screen[5][SCREEN][SCREEN] = { 0 }; //0: �⺻����(�Ͼ� ��) 1: �÷��̾�(�Ķ��� ��) 2: ��ǻ��(������ ��)
									 //[��+ �밢�� (4����)][screen][screen]
//[0]: turn
//[1]: �� ��
//[2]: ���� ��
//[3]: �� �Ʒ�
//[4]: ������ �Ʒ�

int clickEnter = 0; //0 :false 1:True
int turn = 1; // �÷��̾� : 1	��ǻ�� :2
int xyInPlaying;


//�Ķ��� 9 - �÷��̾�
//������ 12 - ��ǻ��

void changeTextColor(int textColor);
void SetStartScreen(int textColor);
void gotoxy();
void matchXY();
void inGameScreen();
void checkKey();
void SetDiagonalCnt();
int confirmSurrounding();
void test(); //�밢�� �� ��, ��  Ȯ�ο�

int main()
{
	//ȭ�� �׸���
	int textColor = 7;
	SetDiagonalCnt();
	SetStartScreen(textColor);
	while (GameOver ==0)
	{	
		if (clickEnter == 1)
		{
			if (confirmSurrounding() == 1) //�ڽ��� Enter�� �αٿ� ���� �� ������� 
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
		
		//Sleep(250); //1000 = 1�� ����
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
			//�׽�Ʈ��
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

// Enter �Է��� �ش� �ڸ��� ���� ������ �ִ��� �˻�.
int confirmSurrounding()
{
	for (int i = 1; i <= 4; i++)
	{
		//[1]: �� ��
		//[2]: ���� ��
		//[3]: �� �Ʒ�	
		//[4]: ������ �Ʒ�

		//�밢�� �˻�
		for (int a = 1; a <= screen[i][arry][arrx]; a++)
		{
			if (i == 1)//���� ������
			{
				if (screen[0][arry - a][arrx - a] == 0 || screen[0][arry - a][arrx - a] == turn)
				{
					break;
				}
				else if (screen[0][arry - a][arrx - a] != turn)
				{
					//screen[0][arry - a][arrx - a] = 3;
					return 1; //�ش� �밢���� �ڽŰ� �ݴ�Ǵ� ���� ����.
				}
			}
			else if (i == 2)// ������ ������
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
			else if (i == 3)//���� �Ʒ�����
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
			else if (i == 4)//������ �Ʒ�����
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

	// �� �˻� - ��
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
	// �� �˻� - �Ʒ�
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

	//�� �˻� - ����
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

	//�� �˻� - ������
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

	
	return 0; //�����������
}

void test() //Enter���� �κ����κ��� ����, ����, �޾Ʒ�, ���Ʒ� �밢�� �߱�. �׽�Ʈ��
{
	for (int i = 1; i <= 4; i++)
	{
		//[1]: �� ��
		//[2]: ���� ��
		//[3]: �� �Ʒ�	
		//[4]: ������ �Ʒ�

		//�밢�� �˻�
		for (int a = 1; a <= screen[i][arry][arrx]; a++)
		{
			if (i == 1)//���� ������
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
			else if (i == 2)// ������ ������
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
			else if (i == 3)//���� �Ʒ�����
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
			else if (i == 4)//������ �Ʒ�����
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

	// �� �˻� - ��
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
	// �� �˻� - �Ʒ�
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

	//�� �˻� - ����
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

	//�� �˻� - ������
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
		// �� �˻� - �Ʒ�
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

