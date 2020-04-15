#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include"wuziqi.h"

extern int chess[16][16];
extern int computerx, computery;

int score(int a, int map[16][16], int n)
{
	int sum = 0;
	int k = 0;
	for (int i = 1; i <= 15; i++)								// �жϻ�һ
	{
		for (int j = 1; j <= 15; j++)
		{
			if (map[i][j]==a && i>1 && i<15 && j>1 && j<15)
			{
				if (map[i - 1][j - 1] + map[i - 1][j] + map[i - 1][j + 1] + map[i][j - 1]\
					+ map[i][j + 1] + map[i + 1][j - 1] + map[i + 1][j] + map[i + 1][j + 1] == 0)
				{
					sum += 10;
				}
			}
		}
	}

	for (int i = 1; i < 15; i++)								// �жϺ���
	{
		k = 0;
		for (int j = 1; j <= 15; j++)
		{
			if (chess[i][j] == a)
				k++;
			else
				k = 0;
			if (k > 1 && (j == 15 || chess[i][j + 1] != a))
			{
				if (j != k && chess[i][j - k] == 0 && j != 15 && chess[i][j+1]==0)
				{
					sum += pow(10, k);
				}
				else if ((j != k && chess[i][j - k] == 0) || (j != 15 && chess[i][j + 1] == 0))
				{
					if (k == 5)
						sum += 100000;
					else
						sum += pow(10, k)/10;
				}
				else
				{
					if (k == 5)
						sum += 100000;
				}
				k = 0;
			}
		}
	}

	for (int i = 1; i < 15; i++)								// �ж�����
	{
		k = 0;
		for (int j = 1; j <= 15; j++)
		{
			if (chess[j][i] == a)
				k++;
			else
				k = 0;
			if (k > 1 && (j == 15 || chess[j + 1][i] != a))
			{
				if (j != k && chess[j - k][i] == 0 && j != 15 && chess[j + 1][i] == 0)
				{
					sum += pow(10, k);
				}
				else if ((j != k && chess[j - k][i] == 0) || (j != 15 && chess[j + 1][i] == 0))
				{
					if (k == 5)
						sum += 100000;
					else
						sum += pow(10, k)/10;
				}
				else
				{
					if (k == 5)
						sum += 100000;
				}
				k = 0;
			}
		}
	}

	for (int i = 1; i <= 11; i++)								// �ж��°벿�ֵ�\����
	{
		k = 0;
		int j = 0;
		while (i + j <= 15)
		{
			if (chess[i + j][1 + j] == a)
				k++;
			else
				k = 0;
			if (k > 1 && (j == 15 - i || chess[i + j + 1][1 + j + 1] != a))
			{
				if (j != k - 1 && chess[i + j - k][1 + j - k] == 0 && j != 15 - i && chess[i + j + 1][1 + j + 1] == 0)
				{
					sum += pow(10, k);
				}
				else if ((j != k - 1 && chess[i + j - k][1 + j - k] == 0) || (j != 15 - i && chess[i + j + 1][1 + j + 1] == 0))
				{
					if (k == 5)
						sum += 1000000;
					else
						sum += pow(10, k)/10; 
				}
				else
				{
					if (k == 5)
						sum += 1000000;
				}
				k = 0;
			}
			j++;
		}
	}

	for (int i = 2; i <= 11; i++)								//�ж��ϰ벿�ֵ�\����
	{
		k = 0;
		int j = 0;
		while (i + j <= 15)
		{
			if (chess[1 + j][i + j] == a)
				k++;
			else
				k = 0;
			if (k > 1 && (j == 15 - i || chess[1 + j + 1][i + j + 1] != a))
			{
				if (j != k - 1 && chess[1 + j - k][i + j - k] == 0 && j != 15 - i && chess[1 + j + 1][i + j + 1] == 0)
				{
					sum += pow(10, k);
				}
				else if ((j != k - 1 && chess[1 + j - k][i + j - k] == 0) || (j != 15 - i && chess[1 + j + 1][i + j + 1] == 0))
				{
					if (k == 5)
						sum += 100000;
					else
						sum += pow(10, k)/10;
				}
				else
				{
					if (k == 5)
						sum += 100000;
				}
				k = 0;
			}
			j++;
		}
	}

	for (int i = 5; i <= 15; i++)
	{
		k = 0;
		int j = 0;
		while (i - j >= 1)
		{
			if (chess[i - j][1 + j] == a)
				k++;
			else
				k = 0;
			if (k > 1 && (i - j == 1 || chess[i - j - 1][1 + j + 1] != a))
			{
				if (j != k - 1 && chess[i - j + k][j - k] == 0 && i - j != 1 && chess[i - j - 1][1 + j + 1] == 0)
				{
					sum += pow(10, k);
				}
				else if ((j != k - 1 && chess[i - j + k][j - k] == 0) || (i - j != 1 && chess[i - j - 1][1 + j + 1] == 0))
				{
					if (k == 5)
						sum += 100000;
					else
						sum += pow(10, k)/10;
				}
				else
				{
					if (k == 5)
						sum += 100000;
				}
			}
			j++;
		}
	}

	for (int i = 2; i <= 11; i++)
	{
		k = 0;
		int j = 0;
		while (i + j <= 15)
		{
			if (chess[i + j][15 - j] == a)
				k++;
			else
				k = 0;
			if (k > 1 && (i + j == 15 || chess[i + j + 1][15 - j - 1] != a))
			{
				if (j != k - 1 && chess[i + j - k][15 - j + k] == 0 && i + j != 15 && chess[i + j + 1][15 - j - 1] == 0)
					sum += pow(10, k);
				else if ((j != k - 1 && chess[i + j - k][15 - j + k] == 0) || (i + j != 15 && chess[i + j + 1][15 - j - 1] == 0))
				{
					if (k == 5)
						sum += 100000;
					else
						sum += pow(10, k - 1);
				}
				else
				{
					if (k == 5)
						sum += 100000;
				}
			}
			j++;
		}
	}

	if (n == 1)
		return sum;
	else
		return sum - score(1, map, 1);
}

bool judge(int x, int y)
{
	int i,j;
	for (i = x - 1; i < x + 1; i++)
		for (j = y - 1; j < y + 1; j++)
			if ((i > 0 && j > 0 && i < 16 && j < 16) && (chess[i][j] == 1 || chess[i][j] == 2))
				return 1;
	for (i = x - 2; i < x + 2; i += 2)
		for (j = y - 2; j < y + 2; j += 2)
			if ((i > 0 && j > 0 && i < 16 && j < 16) && (chess[i][j] == 1 || chess[i][j] == 2))
				return 1;
	return 0;
}

int maxmin(int map[16][16], int deep, int Alpha, int Beta)
{
	int val;
	int temp[16][16];
	if (deep % 2 == 0)
	{
		for (int i = 1; i <= 15; i++)
		{
			for (int j = 1; j <= 15; j++)
			{
				if (chess[i][j] == 0 && judge(i, j))
				{
					memcpy(temp, map, sizeof(int) * 256);
					val = maxmin(temp, deep - 1, Alpha, Beta);
					if (val > Alpha)
					{
						if (deep == DEPTH)
						{
							computerx = i;
							computery = j;
							printf("%d %d\n", i, j);
						}
						Alpha = val;
					}
					if (Alpha > Beta)
						return Alpha;
				}
			}
		}
	}
	else if (deep == 1)
	{
		return score(2, map, 2);
	}
	else
	{
		for (int i = 1; i <= 15; i++)
		{
			for (int j = 1; j <= 15; j++)
			{
				if (chess[i][j] == 0 && judge(i, j))
				{
					memcpy(temp, map, sizeof(int) * 256);
					val = maxmin(temp, deep - 1, Alpha, Beta);
					if (val < Beta)
					{
						Beta = val;
					}
					if (Alpha > Beta)
						return Beta;
				}
			}
		}
	}
}