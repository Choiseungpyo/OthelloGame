#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h>
#include <time.h> 
#include <math.h> 
#include <Windows.h> 
#include <conio.h>

#define ESC 27
#define ENTER 13
#define SPACE 32
#define LEFT 75 
#define RIGHT 77 
#define UP 72 
#define DOWN 80 

#define StartX 0  
#define StartY 0 
#define frameWidth 12 
#define frameHeight 20 
#define Drop 0 
#define MOVE_DOWN 1 
#define MOVE_LEFT 2 
#define MOVE_RIGHT 3 
#define MOVE_DROP 4
#define ROTATION 5

void gotoxy(int x, int y);
void checkKey(); // Ű���尪 �Է� 
void Screen(); // ȭ��ǥ��
void Update(); // ��� ���� ��ȭ ǥ��
void Start(); // ���� ���� ȭ��, ���� �� ����
int Blockclash(); // 1������ �浹 �˻�
void Equality(); // ��ü ����
void Newblock(); // ��� ����ȭ ����
void BarRemove(); // �� ����
void Otherscreen();

int BlockX, BlockY;
int Shape, Rotation;
int Board[frameHeight][frameWidth];
int Blockaction;
int delay = 20;
int count;

int block[7][4][4][4] = {
	{ { { 0, 0, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 } },

	{ { 0, 0, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 } },

	{ { 0, 0, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 } },

	{ { 0, 0, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 } } }, // �����

	{ { { 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 } },

	{ { 0, 0, 0, 0 },
	{ 0, 1, 1, 1 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },

	{ { 0, 1, 1, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 0 } },

	{ { 0, 0, 0, 0 },
	{ 0, 0, 0, 1 },
	{ 0, 1, 1, 1 },
	{ 0, 0, 0, 0 } } }, // ����� 1

	{ { { 0, 0, 1, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 } },

	{ { 0, 0, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 1, 1 },
	{ 0, 0, 0, 0 } },

	{ { 0, 1, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },

	{ { 0, 0, 0, 0 },
	{ 0, 1, 1, 1 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } } }, // ����� 2

	{ { { 0, 1, 0, 0 },
	{ 1, 1, 1, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } },

	{ { 0, 1, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },

	{ { 0, 0, 0, 0 },
	{ 1, 1, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },

	{ { 0, 1, 0, 0 },
	{ 1, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } } }, // �Ǻ��

	{ { { 0, 1, 1, 0 },
	{ 1, 1, 0, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } },

	{ { 1, 0, 0, 0 },
	{ 1, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },

	{ { 0, 1, 1, 0 },
	{ 1, 1, 0, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } },

	{ { 1, 0, 0, 0 },
	{ 1, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } } }, // ����� 1

	{ { { 1, 1, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } },

	{ { 0, 1, 0, 0 },
	{ 1, 1, 0, 0 },
	{ 1, 0, 0, 0 },
	{ 0, 0, 0, 0 } },

	{ { 1, 1, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } },

	{ { 0, 1, 0, 0 },
	{ 1, 1, 0, 0 },
	{ 1, 0, 0, 0 },
	{ 0, 0, 0, 0 } } }, // ����� 2

	{ { { 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 } },

	{ { 0, 0, 0, 0 },
	{ 1, 1, 1, 1 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } },

	{ { 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 } },

	{ { 0, 0, 0, 0 },
	{ 1, 1, 1, 1 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } } } // �Ѻ��
};
int GameOver = 0;


void main()
{
	Start();
	while (!GameOver)
	{
		Screen();
		checkKey();
		Update();
		Sleep(50);
	}
}

void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void Start()
{
	int x, y;
	Newblock();
	count = delay;

	for (x = 0; x < frameWidth; x++)
	{
		for (y = 0; y < frameHeight; y++)
		{
			if (x == 0 || x == frameWidth - 1 ||
				y == 0 || y == frameHeight - 1)
			{
				Board[y][x] = 2;
			}
			else
			{
				Board[y][x] = 0;
			}
		}
	}
}

int Blockclash()
{
	int x, y;
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			if (block[Shape][Rotation][y][x] == 1)
			{
				if (Board[BlockY + y][BlockX + x] != 0)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

void Equality()
{
	int x, y;
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			if (block[Shape][Rotation][y][x] == 1)
			{
				Board[BlockY + y][BlockX + x] = 1;
			}
		}
	}
}

void Newblock()
{
	srand(time(NULL));
	BlockX = frameWidth / 2;
	BlockY = 1;
	Shape = rand() % 7;
	Rotation = 0;
	Blockaction = Drop;
}

void BarRemove()
{
	int x, y, bar, i, j;
	for (y = 1; y < frameHeight - 1; y++)
	{
		bar = 0;
		for (x = 1; x < frameWidth - 1; x++)
		{
			bar += Board[y][x];
		}
		if (bar == frameWidth - 2)
		{


			for (i = y - 1; i > 0; i--)
			{
				for (j = 1; j < frameWidth - 1; j++)
				{
					Board[i + 1][j] = Board[i][j];
				}
			}
		}
	}
}

void Screen()
{
	int x, y;

	for (y = 0; y < frameHeight; y++)
	{
		gotoxy(StartX, StartY + y);
		for (x = 0; x < frameWidth; x++)
		{
			if (Board[y][x] == 1) printf("��");
			else if (Board[y][x] == 2) printf("��");
			else printf("��");
		}
		printf("\n");
	}

	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			if (block[Shape][Rotation][y][x] == 1)
			{
				gotoxy(StartX + (BlockX + x) * 2, StartY + BlockY + y);
				printf("��");
			}
		}
	}
	Otherscreen();
}

void Otherscreen()

{
	gotoxy(35, 4);
	printf("�� ��Ű : �¿� �̵�");

	gotoxy(35, 7);
	printf("��Ű : ��� ȸ����Ű��");

	gotoxy(35, 10);
	printf("��Ű : �Ʒ��� �� ĭ ������");

	gotoxy(35, 13);
	printf("Space Bar : ��� ����߸���");
}

void Update()
{
	switch (Blockaction)
	{
	case MOVE_DROP:
		do {
			BlockY++;
		} while (!Blockclash());
		BlockY--;
		if (BlockY == 1) GameOver = 1;
		Equality();
		BarRemove();
		Newblock();
		count = delay;
		Blockaction = Drop;
		break;
	case MOVE_LEFT:
		BlockX--;
		if (Blockclash()) BlockX++;
		Blockaction = Drop;
		break;
	case MOVE_RIGHT:
		BlockX++;
		if (Blockclash()) BlockX--;
		Blockaction = Drop;
		break;
	case MOVE_DOWN:
		BlockY++;
		if (Blockclash())
		{
			BlockY--;
			if (BlockY == 1) GameOver = 1;
			Equality();
			BarRemove();
			Newblock();
			count = delay;
		}
		Blockaction = Drop;
		break;
	case Drop:
		count--;
		if (count < 0)
		{
			count = delay;
			Blockaction = MOVE_DOWN;
		}
		break;
	case ROTATION:
		Rotation++;
		if (Rotation > 3) Rotation = 0;
		if (Blockclash())
		{
			Rotation--;
			if (Rotation < 0) Rotation = 3;
		}
		Blockaction = Drop;
		break;
	default:
		break;
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
			break;
		case SPACE:
			Blockaction = MOVE_DROP;
			break;
		case LEFT:
			Blockaction = MOVE_LEFT;
			break;
		case RIGHT:
			Blockaction = MOVE_RIGHT;
			break;
		case UP:
			Blockaction = ROTATION;
			break;
		case DOWN:
			Blockaction = MOVE_DOWN;
			break;
		default:
			Blockaction = Drop;
			break;
		}
	}
}


