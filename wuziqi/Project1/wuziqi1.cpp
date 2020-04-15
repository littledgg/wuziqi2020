#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include"wuziqi.h"

int whostart = 0;									// �жϵ�ǰ��Ϸ��
int chess[16][16] = { 0 };							// ��¼������Ϣ
CURRENT now;										// ��¼����µĵ��λ��
int computerx,computery;							// ��¼���������λ��
int steps=0;										// ��¼���岽��

int main()
{
	putmap();
	RECT r = { 800, 275, 1100, 325 };
	drawtext(_T(sp"Play now!                              "), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	while (!win(now.x,now.y))
	{
		if (whostart > 0)
		{
			r = { 800, 350, 1100, 400 };
			drawtext(_T(sp"It's your turn!                              "), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			playchess();
			steps++;
		}
		else
		{
			r = { 800, 350, 1100, 400 };
			drawtext(_T(sp"Please wait...                              "), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			computerchess();
		}
		whostart *= -1;
	}

	if (whostart < 0)
	{
		r = { 800, 350, 1100, 400 };
		drawtext(_T(sp"You win!                              "), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else
	{
		r = { 800, 350, 1100, 400 };
		drawtext(_T(sp"Computer win!                              "), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	getchar();
}