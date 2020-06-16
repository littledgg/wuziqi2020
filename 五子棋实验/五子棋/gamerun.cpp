#include <stdio.h>
#include <graphics.h>
#include <Windows.h>
#include "draw.h"
#include "GameManagement.h"
#include "AI.h"
void gamerun();
int Chess_status[15][15] = {0};//1��ʾ���ӣ�2��ʾ���ӣ�0��ʾû������


void gamerun()
{
	IMAGE img = NULL;
	int olds_chess[15][15] = { 0 };
	int x, y;
	int i=0;//������(�ǲ������i����225���ж�Ϊ����)
	MOUSEMSG m;
	memset(Chess_status, 0 * 0, sizeof(Chess_status));         //������飬�ͷ�ǰһ�ֵ�����
	Draw_board();
	while (1)
	{
		if (i % 2 == 0)
		{
			if (MouseHit())
			{
				m = GetMouseMsg();//��ȡ�����Ϣ
				FlushMouseMsgBuffer();
				if (m.uMsg == WM_LBUTTONDOWN)//�ж��Ƿ����Ҽ�
				{
					x = m.x / 40;
					y = m.y / 40;

					i++;
					Draw_Circle(x ,y , BLACK);
					HeQi(i);
					Chess_status[x][y] = 1;
					if (i == 225)                     //�ж������Ƿ���
					{
						break;
					}	
					if (ResultCheck(x, y, i,Chess_status))      //����*�����*������ķ���ֵ��������
					{
						RECT r = { 0, 0, 639, 479 };
						drawtext(_T("�����ʤ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					}
					if (m.x <= 770 && m.x >= 620 && m.y <= 345 && m.y >= 300)    //�����¿�ʼ��
					{
						memset(Chess_status, 0 * 0, sizeof(Chess_status));
						gamerun();
					}
					if (m.x <= 770 && m.x >= 620 && m.y <= 490 && m.y >= 450)    //���˳���Ϸ��
					{
						exit(0);
					}
				}
				
			}
		}
		else if(i % 2 != 0)
		{
			i++;
			pos best_pos = AI(Chess_status,olds_chess);
			Draw_Circle(best_pos.pos_x, best_pos.pos_y, WHITE);
			HeQi(i);
			Chess_status[best_pos.pos_x][best_pos.pos_y] = 2;
			if (ResultCheck(best_pos.pos_x, best_pos.pos_y, i, Chess_status))      //����*�����*������ķ���ֵ��������
			{
				RECT r = { 0, 0, 639, 479 };
				drawtext(_T("�����ʤ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
		}
	}
}