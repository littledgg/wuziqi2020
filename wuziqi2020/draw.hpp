#ifndef __DRAW__
#define __DRAW__


#include <conio.h>
#include <graphics.h>

// �ඨ��

// ����λ�õ���
class seat
{
public:
	int i = 0;      // y ����
	int j = 0;      // x ����
	int score = INT_MIN;  // ����
};

// �������̵���
class box
{
public:
	void draw();            // ����
public:
	int x = 0;              // x ����
	int y = 0;              // y ����
	int color_val = -1;     // ֵ�����壺1�����壺0����λ��-1��
	int modle;              // ģʽ
	bool isnew = false;     // �Ƿ���ѡ���
	int score = 0;          // ����
	COLORREF color = WHITE; // ���̱���ɫ
};


// ��������
void draw();                  // ����
void init();                  // ��ʼ��
seat findbestseat1(int);	  // Ѱ�����λ��
void isWIN();                 // �ж���Ӯ
void game();                  // ��Ϸ������

#endif // !__DRAW__


