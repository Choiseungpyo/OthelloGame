#include <stdio.h>


/*
// Enter �Է��� �ش� �ڸ��� ���� ������ �ִ��� �˻�.
int confirmSurrounding()
{
	int isFirst; //�ڽ��� ���� ����� �ٸ� ������ ó���������ʾ��� ���: 0 ó���� ��� : 1

	if (confirmIfThereIsBlock() == 0)
	{
		return 0;
	}

	for (int i = 1; i <= 4; i++)
	{
		//[1]: �� ��
		//[2]: ���� ��
		//[3]: �� �Ʒ�
		//[4]: ������ �Ʒ�
		isFirst = 0;
		//�밢�� �˻�
		for (int a = 1; a <= screen[i][arry][arrx]; a++)
		{
			if (i == 1)//���� ������
			{
				if (screen[0][arry - a][arrx - a] == 0 || (screen[0][arry - a][arrx - a] == turn && isFirst ==0))
				{
					break;
				}
				else if (screen[0][arry - a][arrx - a] == turn && isFirst == 1)
				{
						return 1;
				}
				else if (screen[0][arry - a][arrx - a] != turn)
				{
					//screen[0][arry - a][arrx - a] = 3;
					isFirst = 1;
					continue;
				}
			}
			else if (i == 2)// ������ ������
			{
				if (screen[0][arry - a][arrx + a] == 0 || (screen[0][arry - a][arrx + a] == turn && isFirst ==0))
				{
					break;
				}
				else if (screen[0][arry - a][arrx + a] == turn && isFirst ==1)
				{
					return 1;
				}
				else if (screen[0][arry - a][arrx + a] != turn)
				{
					//screen[0][arry - a][arrx + a] = 3;
					isFirst = 1;
					continue;
				}
			}
			else if (i == 3)//���� �Ʒ�����
			{
				if (screen[0][arry + a][arrx - a] == 0 || (screen[0][arry + a][arrx - a] == turn && isFirst ==0))
				{
					break;
				}
				else if (screen[0][arry + a][arrx - a] == turn && isFirst ==1)
				{
					return 1;
				}
				else if (screen[0][arry + a][arrx - a] != turn)
				{
					//screen[0][arry + a][arrx - a] = 3;
					isFirst = 1;
					continue;
				}
			}
			else if (i == 4)//������ �Ʒ�����
			{
				if (screen[0][arry + a][arrx + a] == 0 || (screen[0][arry + a][arrx + a] == turn && isFirst ==0))
				{
					break;
				}
				else if (screen[0][arry + a][arrx + a] == turn && isFirst ==1)
				{
					return 1;
				}
				else if (screen[0][arry + a][arrx + a] != turn)
				{
					//screen[0][arry + a][arrx + a] = 3;
					isFirst = 1;
					continue;
				}
			}
		}
	}

	isFirst = 0;

	// �� �˻� - ��
	for (int a = arry-1; a >= 0; a--)
	{
		if(screen[0][a][arrx] == 0 || (screen[0][a][arrx] == turn && isFirst ==0))
		{
			break;
		}
		else if (screen[0][a][arrx] == turn && isFirst ==1)
		{
			return 1;
		}
		else if (screen[0][a][arrx] != turn)
		{
			isFirst = 1;
			continue;
		}
	}

	isFirst = 0;

	// �� �˻� - �Ʒ�
	for (int a = arry+1; a < 8; a++)
	{
		if (screen[0][a][arrx] == 0 || (screen[0][a][arrx] == turn && isFirst ==0))
		{
			break;
		}
		else if (screen[0][a][arrx] == turn && isFirst ==1)
		{
			return 1;
		}
		else if (screen[0][a][arrx] != turn)
		{
			isFirst = 1;
			continue;
		}
	}

	isFirst = 0;

	//�� �˻� - ����
	for (int a = arrx-1; a >= 0; a--)
	{
		if (screen[0][arry][a] == 0 || (screen[0][arry][a] == turn && isFirst ==0))
		{
			break;
		}
		else if (screen[0][arry][a] == turn && isFirst ==1)
		{
			return 1;
		}
		else if (screen[0][arry][a] != turn)
		{
			isFirst = 1;
			continue;
		}
	}

	if (screen[0][arry][arrx - 1] != turn)
	{
		for (int a = arrx -1; a >=0 ; a--)
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

	isFirst = 0;

	//�� �˻� - ������
	for (int a = arrx+1; a < 8; a++)
	{
		if (screen[0][arry][a] == 0 || (screen[0][arry][a] == turn && isFirst ==0))
		{
			break;
		}
		else if (screen[0][arry][a] == turn && isFirst ==1)
		{
			return 1;
		}
		else if (screen[0][arry][a] != turn)
		{
			isFirst = 1;
			continue;
		}
	}


	return 0; //�����������
}

*/







/*
* void test() //Enter���� �κ����κ��� ����, ����, �޾Ʒ�, ���Ʒ� �밢�� �߱�. �׽�Ʈ��
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
* 
*/

/*
* //��ǻ�Ͱ� ���� ���� �� �ִ� ��ġ ���θ� ����Ѵ�.
void checkWhereCurrentUserCanPutBlock()
{
	int originalArrx, originalArry;
	int randomComputerNum = 1; // computerRandomPlace[arry][arrx]�� ��. �ش� �ƴ� ������ ��� 0���� �ʱ�ȭ�Ǿ�����.

	originalArrx = arrx;
	originalArry = arry;

	for (arry = 0; arry < SCREEN; arry++)
	{
		for (arrx = 0; arrx < SCREEN; arrx++)
		{
			if (confirmSurrounding() == 1)
			{
				screen[0][arry][arrx] = 3;
				computerRandomPlace[arry][arrx] = randomComputerNum;
				++randomComputerNum;
			}
		}
	}

	for (arry = 0; arry < SCREEN; arry++)
	{
		for (arrx = 0; arrx < SCREEN; arrx++)
		{
			if (computerRandomPlace[arry][arrx] == calComputerRandPlace(randomComputerNum))
			{
				screen[0][arry][arrx] = 3;
			}
		}
	}

	viewInGameScreen();

	for (arry = 0; arry < SCREEN; arry++)
	{
		for (arrx = 0; arrx < SCREEN; arrx++)
		{
			if (confirmSurrounding() == 1)
			{
				screen[0][arry][arrx] = 0;
				computerRandomPlace[arry][arrx] = 0;
			}
		}
	}

	arrx = originalArrx;
	arry = originalArry;
}

*/









int main()
{
	char test[8][8][2] = { "" };

	for (int a = 0; a < 8; a++)
	{
		for (int b = 0; b < 8; b++)
		{
			test[a][b][0] = 'a';
			test[a][b][1] = 'b';
			for (int c = 0; c < 2; c++)
			{
				printf("%c", test[a][b][c]);
			}
			printf("	");
		}
		printf("\n");

	}

	return 0;
}


