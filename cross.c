#include <stdio.h>


/*
// Enter 입력후 해당 자리에 블럭을 놓을수 있는지 검사.
int confirmSurrounding()
{
	int isFirst; //자신의 턴의 색깔과 다른 색깔을 처음만나지않았을 경우: 0 처음인 경우 : 1

	if (confirmIfThereIsBlock() == 0)
	{
		return 0;
	}

	for (int i = 1; i <= 4; i++)
	{
		//[1]: 왼 위
		//[2]: 오른 위
		//[3]: 왼 아래
		//[4]: 오른쪽 아래
		isFirst = 0;
		//대각선 검사
		for (int a = 1; a <= screen[i][arry][arrx]; a++)
		{
			if (i == 1)//왼쪽 위방향
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
			else if (i == 2)// 오른쪽 위방향
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
			else if (i == 3)//왼쪽 아래방향
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
			else if (i == 4)//오른쪽 아래방향
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

	// 행 검사 - 위
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

	// 행 검사 - 아래
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

	//열 검사 - 왼쪽
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

	//열 검사 - 오른쪽
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


	return 0; //오류났을경우
}

*/







/*
* void test() //Enter누른 부분으로부터 왼위, 오위, 왼아래, 오아래 대각선 긋기. 테스트용
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
* 
*/

int main()
{
	

	return 0;
}


