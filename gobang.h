#pragma once
#include <easyx.h>			// ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include <stdio.h>

#define CheckerboardColor RGB(255, 222, 173)//R 255 G 222 B 173���̻�ɫ
#define CbInt 40							//���̼����С
#define CbLen CbInt*14						//���̳���
#define CbIntNum 15							//���̸���
#define CbBoundNum	2						//���̱߽�����
#define CbBoardKeyNum CbIntNum+CbBoundNum	//������������
#define CbBoardValueNum 10					//����λ�ü�ֵ��������
#define WinLen CbLen+CbInt*2				//���ڳ���
#define charlen 14
#define MAX_depth 2

#define P_BLACKMove 1
#define P_WHITEMove 2

#define LegalMove 1
#define UnLegalMove 0

#define P_BLANK 0 
#define P_BLACK 1
#define P_WHITE 2
#define P_BOUND 3
#define liveOne		10
#define liveTwo		100
#define liveThree	1000
#define liveFour	10000
#define liveFive	100000
#define sleepOne	1
#define sleepTwo	10
#define sleepThree	100
#define sleepFour	1000
#define unknown		0

typedef struct ActualPoint {
	int x;
	int y;
}APoint;//����λ�ã������ش�С��ʾ
typedef struct LogicPoint {
	int x;
	int y;
	int value;
}LPoint;//�߼�λ��
typedef struct LPointLinkList
{
	LPoint size;
	struct LPointLinkList* next;
}LPLink;

extern int BoardMove[CbIntNum][CbIntNum];
extern int BoardKey[CbIntNum][CbIntNum];//�����������ͣ��ܹ�15*15��
extern int BoardValue[CbIntNum][CbIntNum];//����λ�ü�ֵ���ͣ��ܹ�15*15
extern int value[4][4][4][4][4][4];
extern int val;
extern int WhoGo;
extern APoint IP;


void drawCb();//������
void drawPiece(int y, int x, int key);
void PrintBoard(int Board[][CbIntNum]);
int IsBLANK(MOUSEMSG mouse, int y, int x);

int boardValueEvaluate();
//void printBoard(int Board[][CbIntNum]);
void MakeNextMove(LPLink* p, int depth, int who);
void UnmakeMove(LPLink* p);
int P_ValBest(LPLink* thisP, int who, int depth, int alpha, int beta);
LPLink* creat(int BoardMove[][CbIntNum]);
LPoint ChoseBest(LPLink* p, int who);
LPLink* GenerateLegalMoves();
int boardValueEvaluate();
void valueInitialization();


