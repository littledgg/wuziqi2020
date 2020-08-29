//��������ຯ����ȫ�ֱ���
#pragma once
#include <iostream>
#include <graphics.h>
#include <conio.h>

class seat //ֻ��ai_function��������
{
public:
	int i = 0;      // x ����
	int j = 0;      // y ����
	int number = 0; // ����
};

class box //ÿһ�鴢�����ӵ����࣬���ӵ����꣬
{
public:
	void draw();            //���ÿ��ͼ��
public:
	int x = 0;              
	int y = 0;              
	int value = -1;         // �������������ʲô�壨���壺1�����壺0����λ��-1��
	int modle = 0;          // ��361������ֻࣨ���ж�������������ϵ�λ�ã��Ա㻭��ͬ��������
	bool isnew = false;     // �Ƿ���ѡ��������ͣʱ��ָʾ�򣬻�ͼʱ��Ҫ���£�
	COLORREF color = WHITE; // ���̱���ɫ
};

// ȫ�ֱ���
box BOX[19][19];      // �����̻��ֳ�19*19��
int win = -1;         // ˭Ӯ�ˣ�0������壬1������壬2����ƽ�֣�
int whoplay = 0;      // �ֵ�˭�����ˣ�1��������£�0��������£�
int playercolor = -1;  // �����ɫ��0Ϊ��ɫ��1Ϊ��ɫ��
int dx[4]{ 1,0,1,1 }; // ������- | \ / �ĸ����򣬵�ʱ��ֱ�ӵ���
int dy[4]{ 0,1,1,-1 };
int Score[3][5] = //���ֱ���ʵ���������ҵ�������������ǱȽϼ򵥵��ˣ��ѵĲ�����...��
{
	{ 0, 80, 250, 1000, 1000 }, // �з��ӣ�����ǽ������Ϊ0��Ȼ���ǰ����ҷ���ĳ�������˺�������������-1������0~4
	{ 0, 0,  80,  250, 1000 }, // �з��ӣ�����ǽ������Ϊ1
	{ 0, 0,  0,   80,  1000 }  // �з��ӣ�����ǽ������Ϊ2
};
int MAXxs[361];   //ÿ����߷ֿ����Ե�x����
int MAXys[361];   //ÿ����߷ֿ����Ե�y����
int mylength = 0; //�õ��������Ŀ����Ը���

void box::draw()
{
	COLORREF thefillcolor = getfillcolor(); // ���������ɫ
	setlinestyle(PS_SOLID, 2);              // ����ʽ����
	setfillcolor(color);                    // �����ɫ����
	solidrectangle(x, y, x + 30, y + 30);   // �����ޱ߿��������
	if (isnew)
	{
		// ����������µ����ӣ���ô�ͻ���
		setlinecolor(LIGHTGRAY);
		line(x + 1, y + 2, x + 8, y + 2);
		line(x + 2, y + 1, x + 2, y + 8);
		line(x + 29, y + 2, x + 22, y + 2);
		line(x + 29, y + 1, x + 29, y + 8);
		line(x + 2, y + 29, x + 8, y + 29);
		line(x + 2, y + 22, x + 2, y + 29);
		line(x + 29, y + 29, x + 22, y + 29);
		line(x + 29, y + 22, x + 29, y + 29);
	}
	setlinecolor(BLACK);
	switch (modle)
	{
		// ����ÿһС��Ĳ�ͬλ������ͼ
	case 0:
		line(x + 15, y, x + 15, y + 30);
		line(x - 1, y + 15, x + 30, y + 15);
		break;
		// һ���
	case 1:
		line(x + 14, y + 15, x + 30, y + 15);
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y, x + 15, y + 30);
		setlinestyle(PS_SOLID, 2);
		break;
		// ��߱�Ե��
	case 2:
		line(x - 1, y + 15, x + 15, y + 15);
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y, x + 15, y + 30);
		setlinestyle(PS_SOLID, 2);
		break;
		// �ұ߱�Ե��
	case 3:
		line(x + 15, y + 15, x + 15, y + 30);
		setlinestyle(PS_SOLID, 3);
		line(x - 1, y + 15, x + 30, y + 15);
		setlinestyle(PS_SOLID, 2);
		break;
		// �ϱ߱�Ե��
	case 4:
		line(x + 15, y, x + 15, y + 15);
		setlinestyle(PS_SOLID, 3);
		line(x - 1, y + 15, x + 30, y + 15);
		setlinestyle(PS_SOLID, 2);
		break;
		// �±߱�Ե��
	case 5:
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y, x + 15, y + 15);
		line(x + 15, y + 15, x + 30, y + 15);
		setlinestyle(PS_SOLID, 2);
		break;
		// ���½�
	case 6:
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y, x + 15, y + 15);
		line(x - 1, y + 15, x + 15, y + 15);
		setlinestyle(PS_SOLID, 2);
		break;
		// ���½�
	case 7:
		setlinestyle(PS_SOLID, 3);
		line(x - 1, y + 15, x + 15, y + 15);
		line(x + 15, y + 15, x + 15, y + 30);
		setlinestyle(PS_SOLID, 2);
		break;
		// ���Ͻ�
	case 8:
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y + 15, x + 30, y + 15);
		line(x + 15, y + 15, x + 15, y + 30);
		setlinestyle(PS_SOLID, 2);
		break;
		// ���Ͻ�
	case 9:
		line(x + 15, y, x + 15, y + 30);
		line(x - 1, y + 15, x + 30, y + 15);
		setfillcolor(BLACK);
		setlinestyle(PS_SOLID, 1);
		fillcircle(x + 15, y + 15, 5);
		break;
		// ����ľŸ��㣨��Ҫ��һ��СԲ��
	}
	switch (value)
	{
	case 0: // ����
		setfillcolor(WHITE);
		setlinestyle(PS_SOLID, 1);
		fillcircle(x + 15, y + 15, 13);
		break;
	case 1: // ����
		setfillcolor(BLACK);
		setlinestyle(PS_SOLID, 1);
		fillcircle(x + 15, y + 15, 13);
		break;
	}
	setfillcolor(thefillcolor); // ��ԭ���ɫ
}