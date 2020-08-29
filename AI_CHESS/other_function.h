//һЩ���˺����㷨�ĺ�������������
#pragma once
#include <iostream>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include "class.h"
#include "ai_function.h"

void draw()
{
	int number = 0;
	// Ҫ���ϵ���������
	TCHAR strnum[19][3] = { _T("1"),_T("2") ,_T("3") ,_T("4"),_T("5") ,_T("6") ,_T("7"),_T("8"),_T("9"),_T("10"), _T("11"),_T("12") ,_T("13") ,_T("14"),_T("15") ,_T("16") ,_T("17"),_T("18"),_T("19") };
	LOGFONT style;
	gettextstyle(&style);
	settextstyle(0, 0, NULL);
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			BOX[i][j].draw(); // ��ÿһС�黭����
			if (BOX[i][j].isnew == true)
			{
				BOX[i][j].isnew = false; // ��֮ǰ����λ�õĺڿ����
			}
		}
	}
	// ������
	for (int i = 0; i < 19; i++)
	{
		outtextxy(75 + number, 35, strnum[i]);
		outtextxy(47, 55 + number, strnum[i]);
		number += 30;
	}
	settextstyle(&style);
}

// �����ÿһ��BOX��ֵxy���������Ӧ��������ʽ
void prepare()
{
	win = -1;// ��������۸����ԣ����޸����dog��
	for (int i = 0, k = 0; i < 570; i += 30)
	{
		for (int j = 0, g = 0; j < 570; j += 30)
		{
			int modle = 0;  // ÿһС�������
			BOX[k][g].value = -1;
			BOX[k][g].color = RGB(204, 177, 136);// ���̵�ɫ�����ĵ���ɫ
			BOX[k][g].x = 65 + j;
			BOX[k][g].y = 50 + i;//������ݻ�Ҫ��һ��ʼ�����Ĵ��ڴ�С���ϣ����������ͼƬ��ʾ��Ҫ��������鷳
			if (k == 0 && g == 0)//ÿһ��model��������class.h�е�box::draw()�б�ע��
			{
				modle = 8;
			}
			else if (k == 0 && g == 18)
			{
				modle = 7;
			}
			else if (k == 18 && g == 18)
			{
				modle = 6;
			}
			else if (k == 18 && g == 0)
			{
				modle = 5;
			}
			else if (k == 0)
			{
				modle = 3;
			}
			else if (k == 18)
			{
				modle = 4;
			}
			else if (g == 0)
			{
				modle = 1;
			}
			else if (g == 18)
			{
				modle = 2;
			}
			else  if ((k == 3 && g == 3) || (k == 3 && g == 15) || (k == 15 && g == 3) || (k == 15 && g == 15) || (k == 3 && g == 9) || (k == 9 && g == 3) || (k == 15 && g == 9) || (k == 9 && g == 15) || (k == 9 && g == 9))
			{
				modle = 9;
			}
			else
			{
				modle = 0;
			}
			BOX[k][g].modle = modle;
			g++;
		}
		k++;
	}
}

// �ж���Ϸ�Ƿ������
void isWIN()
{
	bool isfull = true; // �����Ƿ�����
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (BOX[i][j].value != -1)
			{
				// ����ÿ�����ܵ�λ��
				int nowcolor = BOX[i][j].value; // ���ڱ���������ɫ
				int length[4] = { 0,0,0,0 };    // �ĸ�����ĳ���
				for (int k = 0; k < 4; k++)
				{
					// ԭ��ͬѰ�����λ��
					int nowi = i;
					int nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == nowcolor)
					{
						length[k]++;
						nowj += dx[k];
						nowi += dy[k];
					}
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == 1 - nowcolor)
					{
						length[k]++;
						nowj -= dx[k];
						nowi -= dy[k];
					}
				}
				for (int k = 0; k < 4; k++)
				{
					if (length[k] >= 5) {
						// ���������
						if (nowcolor == playercolor)
						{
							win = playercolor; // ���ʤ
						}
						if (nowcolor == 1 - playercolor)
						{
							win = 1 - playercolor; // ����ʤ
						}
					}
				}
			}
			else
			{
				//���Ϊ��
				isfull = false;//����û��
			}
		}
	}
	if (isfull)
	{
		// �����������
		win = 2; // ƽ��
	}
}
//���庯�����������ܿ���main������
void start()
{
	bool isinit;
	
	int oldi = 0;
	int oldj = 0;// ��һ�����ͣ������
	
	setfillcolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	fillcircle(150, 720, 20);
	setfillcolor(WHITE);
	fillcircle(550, 720, 20);//�����������Թ�ѡ�������ɫ
	
	setfillcolor(RGB(204, 177, 136));// ���Ʊ���
	solidrectangle(40, 25, 645, 630);//��һ������
	settextstyle(30, 15, 0, 0, 0, 1000, false, false, false);// ����������ʽ
	settextcolor(BLACK);
	
	outtextxy(200, 650, _T("������ѡ�������ɫ"));// �������ѡ����ɫ

	box choose[2];//�����ٻ�ȡ����С�����ж���ҵ�ѡ��
	choose[0].x = 130;
	choose[1].x = 530;

	while (playercolor < 0)//ÿѡ������һֱѭ��
	{
		MOUSEMSG mouse = GetMouseMsg();//�õ������Ϣ����һ����
		for (int i = 0; i < 2; i++)
		{
			if (mouse.x > choose[i].x && mouse.x < choose[i].x + 40 && mouse.y>700 && mouse.y < 740)
			{
				if (mouse.mkLButton)//�����������
				{
					if (i == 0) playercolor = 1;
					if (i == 1) playercolor = 0;//�ж�����������
				}
			}
		}
	}
	
	setfillcolor(RGB(162, 162, 162));
	solidrectangle(130, 700, 170, 740);
	solidrectangle(530, 700, 570, 740);//���������ΰ�֮ǰ��Բ���ǵ�

	settextcolor(RGB(162, 162, 162));
	outtextxy(200, 650, _T("������ѡ�������ɫ"));

	settextcolor(BLACK);
	// ��֪��ҵ���ɫѡ����ʲô�������滭����
	if (playercolor == 0)
	{
		isinit = 1;
		outtextxy(290, 650, _T("��Ϊ����"));
		whoplay = 1;
		setfillcolor(WHITE);
		setlinestyle(PS_SOLID, 1);
		fillcircle(350, 720, 20);

	}
	else
	{
		isinit = 0;
		outtextxy(290, 650, _T("��Ϊ����"));
		whoplay = 0;
		setfillcolor(BLACK);
		setlinestyle(PS_SOLID, 1);
		fillcircle(350, 720, 20);
	}
	draw(); // ����
	while (1)
	{
	NEXTPLAYER:
		if (whoplay == 0)//��Һ�
		{
			// ������壨����жϵ�������һ�δ���ѧ�������ֺ����棩
			MOUSEMSG mouse = GetMouseMsg(); // �õ�������Ϣ
			for (int i = 0; i < 19; i++)
			{
				for (int j = 0; j < 19; j++)
				{
					if (mouse.x > BOX[i][j].x && mouse.x<BOX[i][j].x + 30//�ж�x����
						&& mouse.y>BOX[i][j].y && mouse.y < BOX[i][j].y + 30//�ж�y����
						&& BOX[i][j].value == -1)//�ж��Ƿ��ǿ�λ��
					{
						if (mouse.mkLButton)
						{
							// ������������
							BOX[i][j].value = playercolor; // ����
							BOX[i][j].isnew = true;        // ��λ�ø���
							oldi = -1;
							oldj = -1;
							// ��һ�����
							whoplay = 1;
							goto DRAW;
						}
						
						BOX[oldi][oldj].isnew = false;
						BOX[oldi][oldj].draw();
						BOX[i][j].isnew = true;
						BOX[i][j].draw();
						oldi = i;
						oldj = j;// ����ѡ���
					}
				}
			}
		}
		else
		{
			// ��������
			if (isinit)
			{
				// �������
				isinit = 0;
				int drawi = 9;
				int drawj = 9;
				while (BOX[drawi][drawj].value != -1)
				{
					drawi--;
					drawj++;
				}
				BOX[drawi][drawj].value = 1 - playercolor;
				BOX[drawi][drawj].isnew = true;
			}
			else
			{
				seat best;
				best = findbestseat(1 - playercolor, 0); // Ѱ�����λ��
				BOX[best.i][best.j].value = 1 - playercolor;//�������λ��
				BOX[best.i][best.j].isnew = true;
			}
			whoplay = 0;//�ֵ��������
			goto DRAW; // ����һ��ͼ
		}
	}
DRAW: // ����
	isWIN(); // �����Ӯ
	draw();
	oldi = 0;
	oldj = 0;
	if (win == -1)
	{
		// ���û����ʤ������û������
		Sleep(500);
		goto NEXTPLAYER; // ǰ����һ�����
	}
	// ��Ϸ����
	settextcolor(RED);
	Sleep(1000);
	settextstyle(100, 0, NULL);
	if (win == 0)
	{
		outtextxy(200, 250, _T("�׷�ʤ��"));
	}
	if (win == 1)
	{
		outtextxy(200, 250, _T("�ڷ�ʤ��"));
	}
	if (win == 2)
	{
		outtextxy(200, 250, _T("ƽ�֣�"));
	}
	// ����ʱ�仺��
	Sleep(5000);
	return;
}