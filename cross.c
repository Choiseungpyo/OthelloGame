#include <stdio.h>

int arrx, arry;
int screen[5][8][8] = { 0 };
int turn = 1;

void SetDiagonalCnt() //�밢�� ���� �Է½� �ش� [��,��]�� �밢�� ���� ���
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

int testSurrounding()
{
	for (int i = 1; i <= 4; i++)
	{
		//[1]: �� ��
		//[2]: ���� ��
		//[3]: �� �Ʒ�	
		//[4]: ������ �Ʒ�

		//�밢�� �˻�
		for (int a = 1; a < screen[i][arry][arrx]; a++)
		{
			if (i == 1)//���� ������
			{
				if (screen[0][arry - a][arrx - a] != turn && screen[0][arry - a][arrx - a] != 0)
				{
					screen[0][arry - a][arrx - a] = 3;
				}
			}
			else if (i == 2)// ������ ������
			{
				if (screen[0][arry - a][arrx + a] != turn && screen[0][arry - a][arrx + a] != 0)
				{
					screen[0][arry - a][arrx + a] = 3;
				}
			}
			else if (i == 3)//���� �Ʒ�����
			{
				if (screen[0][arry + a][arrx - a] != turn && screen[0][arry + a][arrx - a] != 0)
				{
					screen[0][arry + a][arrx - a] = 3;
				}
			}
			else if (i == 4)//������ �Ʒ�����
			{
				if (screen[0][arry + a][arrx + a] != turn && screen[0][arry + a][arrx + a] != 0)
				{
					screen[0][arry + a][arrx + a] = 3;
				}
			}
		}
	}

	// �� �˻�


	//�� �˻�
	return -1; //�����������
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


