#include <stdio.h>
#include <graphics.h>
#include "gamerun.h"
void game_again();
void HeQi(int i);

void game_again()
{
	MOUSEMSG m;
	while (1)
	{
		if (MouseHit())
		{
			m = GetMouseMsg();
			FlushMouseMsgBuffer();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				if (m.x <= 770 && m.x >= 620 && m.y <= 345 && m.y >= 300)    //�����¿�ʼ��α��ť(��Ϸ����ʱ�ſ�ʹ��)
				{
					gamerun();
				}
				if (m.x <= 770 && m.x >= 620 && m.y <= 490 && m.y >= 450)    //���˳���Ϸ��α��ť(��Ϸ����ʱ�ſ�ʹ��)
				{
					exit(0);
				}
			}
		}
	}
}

void HeQi(int i)
{
	IMAGE img;
	if (i == 225)
	{
		loadimage(&img, _T("C:\\Users\\Ƥ��c\\Desktop\\�˻���ս\\������\\HEQI.jpg"));
		putimage(200, 280, &img);
		
	}
}

int ResultCheck(int x, int y, int i,int status[15][15])
{
	int j, k, h;
	int n1, n2;                           //�������������ۼ����Ӹ���

	if (i % 2 == 0)
	{
			h = 2;
	}//���ݼ�����i����ż�ԣ��л�����Ͱ���ļ��
		
	else
	{
			h = 1;
	}
		

	while (1)
	{
		n1 = 0;
		n2 = 0;
		for (j = x, k = y; j >= 0; j--)                      //������
		{
			if (status[j][k] == h)                     //�ж��Ƿ�Ϊ����
				n1++;
			else
				break;
		}
		for (j = x, k = y; j < 15; j++)                            //���Ҽ��
		{
			if (status[j][k] == h)
				n2++;
			else
				break;
		}
		if (n1 + n2 - 1 >= 5)
		{
			return(1);
		}
		n1 = 0;
		n2 = 0;
		for (j = x, k = y; k >= 0; k--)                                //���ϼ��
		{
			if (status[j][k] == h)
				n1++;
			else
				break;
		}
		for (j = x, k = y; k < 15; k++)                               //���¼��
		{
			if (status[j][k] == h)
				n2++;
			else
				break;
		}
		if (n1 + n2 - 1 >= 5)
		{
			return(1);
		}
		n1 = 0;
		n2 = 0;
		for (j = x, k = y; (j >= 0) && (k >= 0); j--, k--)                    //�����ϼ��
		{
			if (status[j][k] == h)
				n1++;
			else
				break;
		}
		for (j = x, k = y; (j < 15) && (k < 15); j++, k++)                      //�����¼��
		{
			if (status[j][k] == h)
				n2++;
			else
				break;
		}
		if (n1 + n2 - 1 >= 5)
		{
			return(1);
		}
		n1 = 0;
		n2 = 0;
		for (j = x, k = y; (j < 15) && (k >= 0); j++, k--)                    //�����ϼ��
		{
			if (status[j][k] == h)
				n1++;
			else
				break;
		}
		for (j = x, k = y; (j >= 0) && (k < 15); j--, k++)                       //�����¼��
		{
			if (status[j][k] == h)
				n2++;
			else
				break;
		}
		if (n1 + n2 - 1 >= 5)
		{
			return(1);
		}
		return(0);
	}
}