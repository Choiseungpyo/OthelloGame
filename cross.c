#include <stdio.h>

int arrx, arry;
int screen[5][8][8] = { 0 };
int turn = 1;

void SetDiagonalCnt() //대각선 방향 입력시 해당 [행,열]의 대각선 개수 출력
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

int testSurrounding()
{
	for (int i = 1; i <= 4; i++)
	{
		//[1]: 왼 위
		//[2]: 오른 위
		//[3]: 왼 아래	
		//[4]: 오른쪽 아래

		//대각선 검사
		for (int a = 1; a < screen[i][arry][arrx]; a++)
		{
			if (i == 1)//왼쪽 위방향
			{
				if (screen[0][arry - a][arrx - a] != turn && screen[0][arry - a][arrx - a] != 0)
				{
					screen[0][arry - a][arrx - a] = 3;
				}
			}
			else if (i == 2)// 오른쪽 위방향
			{
				if (screen[0][arry - a][arrx + a] != turn && screen[0][arry - a][arrx + a] != 0)
				{
					screen[0][arry - a][arrx + a] = 3;
				}
			}
			else if (i == 3)//왼쪽 아래방향
			{
				if (screen[0][arry + a][arrx - a] != turn && screen[0][arry + a][arrx - a] != 0)
				{
					screen[0][arry + a][arrx - a] = 3;
				}
			}
			else if (i == 4)//오른쪽 아래방향
			{
				if (screen[0][arry + a][arrx + a] != turn && screen[0][arry + a][arrx + a] != 0)
				{
					screen[0][arry + a][arrx + a] = 3;
				}
			}
		}
	}

	// 행 검사


	//열 검사
	return -1; //오류났을경우
}


int main()
{
	screen[0][3][3] = 1;
	screen[0][3][4] = 2;
	screen[0][4][3] = 1;
	screen[0][4][4] = 2;
	SetDiagonalCnt();
	
	for (int a = 0; a < 8; a++)
	{
		for (int b = 0; b < 8; b++)
		{
			printf("%d", screen[0][a][b]);
		}
		//pritnf("\n");
	}

	return 0;
}


