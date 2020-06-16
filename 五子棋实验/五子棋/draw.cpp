#include <graphics.h>
#include <conio.h>
void Draw_board();
void Draw_Circle(int x,int y,int circle_color);


void Draw_board()
{
	setbkcolor(BROWN);
	cleardevice();//���ñ���Ϊ��ɫ

	setcolor(BLACK);       //������ɫ(��ɫ)
	setlinestyle(PS_SOLID, 2);     //������ʽ(ʵ�� ���Ϊ2)

	line(16, 16, 584, 16);
	line(16, 584, 584, 584);
	line(16, 16, 16, 584);
	line(584, 16, 584, 584);		//����Χ�߿�

	for (int i = 0; i < 15; ++i)    //��׼���̣�15 X 15��
	{

		line(20, 40 * i + 20, 580, 40 * i + 20);  //��С����ĺ���
		
		line(40 * i + 20, 20, 40 * i + 20, 580);  //��С���������

	}

	setfillstyle(BLACK);           
	setfillcolor(BLACK);
	fillcircle(300, 300, 4);
	fillcircle(140, 140, 4);
	fillcircle(140, 460, 4);
	fillcircle(460, 140, 4);
	fillcircle(460, 460, 4);					//�������ϵ������(��ɫ)

	//setcolor(BLACK);          //��ʾ�������Ϊ����
	//setlinestyle(PS_SOLID, 2);
	//setfillcolor(BLACK);
	//fillcircle(700, 150, 20);
	RECT r = { 620, 345, 770, 300 };
	drawtext(_T("���¿�ʼ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT a = { 620, 450, 770, 490};
	drawtext(_T("�˳���Ϸ"), &a, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void Draw_Circle(int x,int y,int circle_color)
{
	x = x * 40 + 20;
	y = y * 40 + 20;
	setfillcolor(circle_color);
	fillcircle(x, y, 12);
}