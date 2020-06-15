#include"game.h"
#include"gobangAI.h"
#include"view.h"

#include<stdio.h>
#include<string.h>

int BoardMove[CbIntNum][CbIntNum];//���� ����λ��
int BoardKey[CbIntNum][CbIntNum];//�����������ͣ��ܹ�15*15��
int BoardValue[CbIntNum][CbIntNum];//����λ�ü�ֵ���ͣ��ܹ�15*15
int BoardValueSum[CbIntNum][CbIntNum];//���� ���������ֵ�ܺ�
int value[4][4][4][4][4][4];// ��ֵ�жϺ�������ֵ �������ӵ�λ��
int val;// 
int WhoGo;// �ֵ�˭��
int Depth;// �ִ� �������
int Steps;// �ߵĲ���
int cutNumA;//alpha��֦����
int cutNumB;//beta��֦����

//������� ���µ��峷��
void UnmakeMove(LPoint p)
{
	BoardKey[p.y][p.x] = P_BLANK;
}

//���������ʱ����һ����
void MakeNextMove(LPoint p,int depth,int who) 
{
	if (((who + depth) % 2) == 1)
	{
		BoardKey[p.y][p.x] = P_BLACK;
	}
	else if (((who + depth) % 2) == 0)
	{
		BoardKey[p.y][p.x] = P_WHITE;
	}
}

//�������̣��������Ӵ��ڵ�λ�õ���Χ2����Ϊ����λ�ã���һ����
void GenerateLegalMoves() {
	for (int i = 0; i < CbIntNum; i++)
	{
		for (int j = 0; j < CbIntNum; j++)
		{			
				BoardMove[i][j] = UnLegalMove;
		}
	}

	for (int i = 2; i < CbIntNum-2; i++)
	{
		for (int j = 2; j < CbIntNum-2; j++)
		{
			//������Χ����Ϊ���������λ��
			if (BoardKey[i][j]==P_BLACK|| BoardKey[i][j] == P_WHITE)
			{
				//��Χһ��
				BoardMove[i + 1][j] = LegalMove;
				BoardMove[i][j + 1] = LegalMove;
				BoardMove[i - 1][j] = LegalMove;
				BoardMove[i][j - 1] = LegalMove;
				BoardMove[i + 1][j + 1] = LegalMove;
				BoardMove[i - 1][j + 1] = LegalMove;
				BoardMove[i - 1][j - 1] = LegalMove;
				BoardMove[i + 1][j - 1] = LegalMove;
				//�����������쵽�ڶ���
				BoardMove[i + 2][j] = LegalMove;
				BoardMove[i][j+2] = LegalMove;
				BoardMove[i - 2][j] = LegalMove;
				BoardMove[i][j - 2] = LegalMove;
				BoardMove[i + 2][j + 2] = LegalMove;
				BoardMove[i - 2][j + 2] = LegalMove;
				BoardMove[i - 2][j - 2] = LegalMove;
				BoardMove[i + 2][j - 2] = LegalMove;
			}
		}
	}

	for (int i = 2; i < CbIntNum-2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (BoardKey[i][j] == P_BLACK || BoardKey[i][j] == P_WHITE)
			{
				//��Χһ��
				BoardMove[i + 1][j] = LegalMove;
				BoardMove[i][j + 1] = LegalMove;
				BoardMove[i - 1][j] = LegalMove;
				BoardMove[i + 1][j + 1] = LegalMove;
				BoardMove[i - 1][j + 1] = LegalMove;
				//�����������쵽�ڶ���
				BoardMove[i + 2][j] = LegalMove;
				BoardMove[i][j+2] = LegalMove;
				BoardMove[i - 2][j] = LegalMove;
				BoardMove[i + 2][j + 2] = LegalMove;
				BoardMove[i - 2][j + 2] = LegalMove;
			}
			if (BoardKey[j][i] == P_BLACK || BoardKey[j][i] == P_WHITE)
			{
				//��Χһ��
				BoardMove[j + 1][i] = LegalMove;
				BoardMove[j][i + 1] = LegalMove;
				BoardMove[j][i - 1] = LegalMove;
				BoardMove[j + 1][i + 1] = LegalMove;
				BoardMove[j + 1][i - 1] = LegalMove;
				//�����������쵽�ڶ���
				BoardMove[j + 2][i] = LegalMove;
				BoardMove[j][i + 2] = LegalMove;
				BoardMove[j][i - 2] = LegalMove;
				BoardMove[j + 2][i + 2] = LegalMove;
				BoardMove[j + 2][i - 2] = LegalMove;

			}
			if (BoardKey[i][14-j] == P_BLACK || BoardKey[i][14-j] == P_WHITE)
			{
				//��Χһ��
				BoardMove[i + 1][14 - j] = LegalMove;
				BoardMove[i][13 - j] = LegalMove;
				BoardMove[i - 1][14 - j] = LegalMove;
				BoardMove[i + 1][13 - j] = LegalMove;
				BoardMove[i - 1][13 - j] = LegalMove;
				//�����������쵽�ڶ���
				BoardMove[i + 2][14 - j] = LegalMove;
				BoardMove[i][12 - j] = LegalMove;
				BoardMove[i - 2][14 - j] = LegalMove;
				BoardMove[i + 2][12 - j] = LegalMove;
				BoardMove[i - 2][12 - j] = LegalMove;

			}
			if (BoardKey[14-j][i] == P_BLACK || BoardKey[14-j][i] == P_WHITE)
			{
				//��Χһ��
				BoardMove[14 - j][i - 1] = LegalMove;
				BoardMove[14 - j][i + 1] = LegalMove;
				BoardMove[13 - j][i] = LegalMove;
				BoardMove[13 - j][i + 1] = LegalMove;
				BoardMove[13 - j][i - 1] = LegalMove;
				//�����������쵽�ڶ���
				BoardMove[14 - j][i - 2] = LegalMove;
				BoardMove[14 - j][i + 2] = LegalMove;
				BoardMove[12 - j][i] = LegalMove;
				BoardMove[12 - j][i - 2] = LegalMove;
				BoardMove[12 - j][i + 2] = LegalMove;
			}
		}
	}

	for (int i = 0; i < CbIntNum; i++)
	{
		for (int j = 0; j < CbIntNum; j++)
		{
			if (BoardKey[i][j] == P_BLACK || BoardKey[i][j] == P_WHITE) 
			{
				BoardMove[i][j] = UnLegalMove;
			}
		}
	}

}

//�Ե�������ӽ��п���λ�ø���
void pointLegalMoves(int y, int x) {
	for (int i = x - 2; i <= x + 2; i++) {
		if (i < 0 || i >= 15) {
			continue;
		}
		for (int j = y - 2; j <= y + 2; j++) {
			if (j < 0 || j >= 15) {
				continue;
			}
			if (i == x && j == y) {
				continue;
			}
			if (BoardKey[i][j] == P_BLANK &&(abs(i-x)==abs(j-y))) {
				BoardMove[i][j] = LegalMove;
			}
		}
	}
}

//����ʽ����
LPoint ChoseBest(int who) {
	LPoint* thisP, thisPA[100],thisPSort[100];
	
	thisP = thisPA;
	int nowMove=0;
	int numMove=0;
	int bestMove=0;
	GenerateLegalMoves();
	thisP = creat(thisPA, &numMove);
	LPoint best;
	int val=0,valbest=0;
	for (int i = 0; i < 100; i++)
	{
		thisPSort[i].value = 1000000;
	}
		valbest = 9999999;

	while (nowMove <= numMove) {

		MakeNextMove(thisPA[nowMove], who, MAX_depth);
		thisPA[nowMove].value = P_ValBest(who, 1, 999999, -999999);
		UnmakeMove(thisPA[nowMove]);
		for (int i = 0; i <= nowMove; i++)
		{
			if (thisPA[nowMove].value < thisPSort[i].value) {
				for (int p = nowMove; p >= i; p--)
				{
					thisPSort[p + 1].value = thisPSort[p].value;
					thisPSort[p + 1].x = thisPSort[p].x;
					thisPSort[p + 1].y = thisPSort[p].y;
				}
				thisPSort[i].value = thisPA[nowMove].value;
				thisPSort[i].x = thisP[nowMove].x;
				thisPSort[i].y = thisP[nowMove].y;
				break;
			}
		}
		nowMove++;
	}

	 nowMove = 0;

	while (nowMove<=numMove) {

		MakeNextMove(thisPSort[nowMove], who,MAX_depth);
		val = P_ValBest(who, MAX_depth,999999,-999999);
		UnmakeMove(thisPSort[nowMove]);

		if (who == 2)
		{
			if (val < valbest) {
				bestMove = nowMove;
				valbest = val;
			}
		}
		nowMove++;
	}
	best.value = valbest;
	best.x = thisPSort[bestMove].x;
	best.y = thisPSort[bestMove].y;
	return best;
}

//alpha - beta ��֦
int P_ValBest(int who, int depth, int alpha, int beta) {
	if (depth == 1) {
		return boardValueEvaluate();
	}
	LPoint* thisP, thisPA[1000];
	thisP = thisPA;
	int val = 0;
	int valbest=0;
	int numMove = 0;
	int nowMove = 0;
	if ((who + depth - 1) % 2 == 1)//����ڵ�
	{
		valbest = -9999999;
	}
	if ((who + depth - 1) % 2 == 0)//��С�ڵ�
	{
		valbest = 9999999;
	}
	GenerateLegalMoves();
	thisP=creat(thisPA,&numMove);
	while (nowMove<=numMove) {

		MakeNextMove(thisPA[nowMove], who,depth-1);
		val = P_ValBest(who,depth-1,alpha,beta);
		UnmakeMove(thisPA[nowMove]);

		if ((who + depth - 1) % 2 == 1)
		{
			if (val > valbest) {
				valbest = val;
			}
			if (val > alpha) {
				cutNumA++;
				return val;
			}
			if (val > beta) {
				beta = val;
			}
		}

		if ((who + depth - 1) % 2 == 0)
		{
			if (val < valbest) {
				valbest = val;
			}
			if (val < beta) {
				cutNumB++;
				return val;
			}
			if (val < alpha) {
				alpha = val;
			}
		}
		nowMove++;
	}
	return valbest;
}

//���������λ�� �γ�һ������
LPoint* creat(LPoint LMoves[],int * numMove) {
	int n = 0;
	for (int i = 1; i < 8; i++)
	{
		for (int j = -i + 1; j <= i; j++)
		{
			if (BoardMove[7 + i][7 - j] == LegalMove)
			{
				LMoves[n].y = 7 + i;
				LMoves[n].x = 7 - j;
				n++;
			}
			if (BoardMove[7 - i][7 + j] == LegalMove)
			{
				LMoves[n].y = 7 - i;
				LMoves[n].x = 7 + j;
				n++;
			}
			if (BoardMove[7 + j][7 + i] == LegalMove)
			{
				LMoves[n].y = 7 + j;
				LMoves[n].x = 7 + i;
				n++;
			}
			if (BoardMove[7 - j][7 - i] == LegalMove)
			{
				LMoves[n].y = 7 - j;
				LMoves[n].x = 7 - i;
				n++;
			}
		}
	}
	*numMove = n - 1;
	return LMoves;
}

//��ֵ������ʼ��
void valueInitialization() {
	//����
	value[P_BLANK][P_BLACK][P_BLACK][P_BLACK][P_BLACK][P_BLANK] = liveFour;
	value[P_BLANK][P_WHITE][P_WHITE][P_WHITE][P_WHITE][P_BLANK] = -liveFour;
	//����
	value[P_BOUND][P_BLACK][P_BLACK][P_BLACK][P_BLACK][P_BLACK] = liveFive;
	value[P_BLANK][P_BLACK][P_BLACK][P_BLACK][P_BLACK][P_BLACK] = liveFive;
	value[P_WHITE][P_BLACK][P_BLACK][P_BLACK][P_BLACK][P_BLACK] = liveFive;
	value[P_BOUND][P_WHITE][P_WHITE][P_WHITE][P_WHITE][P_WHITE] = -liveFive;
	value[P_BLANK][P_WHITE][P_WHITE][P_WHITE][P_WHITE][P_WHITE] = -liveFive;
	value[P_BLACK][P_WHITE][P_WHITE][P_WHITE][P_WHITE][P_WHITE] = -liveFive;
	//���� 1 ���� ���ظ��Ŀ���
	value[P_BLANK][P_BLANK][P_BLACK][P_BLACK][P_BLACK][P_BLANK] = liveThree;
	value[P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_BLACK][P_BLANK] = liveThree;
	value[P_BLANK][P_BLACK][P_BLACK][P_BLANK][P_BLACK][P_BLANK] = liveThree;
	value[P_BLANK][P_BLACK][P_BLACK][P_BLACK][P_BLANK][P_BLANK] = liveThree;
	value[P_BLANK][P_BLANK][P_WHITE][P_WHITE][P_WHITE][P_BLANK] = -liveThree;
	value[P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_WHITE][P_BLANK] = -liveThree;
	value[P_BLANK][P_WHITE][P_WHITE][P_BLANK][P_WHITE][P_BLANK] = -liveThree;
	value[P_BLANK][P_WHITE][P_WHITE][P_WHITE][P_BLANK][P_BLANK] = -liveThree;
	//����  ֻ��һ��λ�õĶ·�
	value[P_BLANK][P_BLACK][P_BLACK][P_BLANK][P_BLACK][P_BLACK] = sleepFour;
	value[P_WHITE][P_BLACK][P_BLACK][P_BLANK][P_BLACK][P_BLACK] = sleepFour;
	value[P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_BLACK][P_BLACK] = sleepFour;
	value[P_WHITE][P_BLACK][P_BLANK][P_BLACK][P_BLACK][P_BLACK] = sleepFour;
	value[P_BLANK][P_BLACK][P_BLACK][P_BLACK][P_BLANK][P_BLACK] = sleepFour;
	value[P_WHITE][P_BLACK][P_BLACK][P_BLACK][P_BLANK][P_BLACK] = sleepFour;
	value[P_BLANK][P_WHITE][P_WHITE][P_BLANK][P_WHITE][P_WHITE] = -sleepFour;
	value[P_BLACK][P_WHITE][P_WHITE][P_BLANK][P_WHITE][P_WHITE] = -sleepFour;
	value[P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_WHITE][P_WHITE] = -sleepFour;
	value[P_BLACK][P_WHITE][P_BLANK][P_WHITE][P_WHITE][P_WHITE] = -sleepFour;
	value[P_BLANK][P_WHITE][P_WHITE][P_WHITE][P_BLANK][P_WHITE] = -sleepFour;
	value[P_BLACK][P_WHITE][P_WHITE][P_WHITE][P_BLANK][P_WHITE] = -sleepFour;
	//����  ��������һ�߶�
	value[P_WHITE][P_BLACK][P_BLACK][P_BLACK][P_BLACK][P_BLANK] = sleepFour;
	value[P_BLANK][P_BLACK][P_BLACK][P_BLACK][P_BLACK][P_WHITE] = sleepFour;
	value[P_BLACK][P_WHITE][P_WHITE][P_WHITE][P_WHITE][P_BLANK] = -sleepFour;
	value[P_BLANK][P_WHITE][P_WHITE][P_WHITE][P_WHITE][P_BLACK] = -sleepFour;
	//����  �߽�
	value[P_BOUND][P_BLACK][P_BLACK][P_BLACK][P_BLACK][P_BLANK] = sleepFour;
	value[P_BOUND][P_BLACK][P_BLACK][P_BLACK][P_BLANK][P_BLACK] = sleepFour;
	value[P_BOUND][P_BLACK][P_BLACK][P_BLANK][P_BLACK][P_BLACK] = sleepFour;
	value[P_BOUND][P_BLACK][P_BLANK][P_BLACK][P_BLACK][P_BLACK] = sleepFour;
	value[P_BOUND][P_WHITE][P_WHITE][P_WHITE][P_WHITE][P_BLANK] = -sleepFour;
	value[P_BOUND][P_WHITE][P_WHITE][P_WHITE][P_BLANK][P_WHITE] = -sleepFour;
	value[P_BOUND][P_WHITE][P_WHITE][P_BLANK][P_WHITE][P_WHITE] = -sleepFour;
	value[P_BOUND][P_WHITE][P_BLANK][P_WHITE][P_WHITE][P_WHITE] = -sleepFour;

	value[P_BLANK][P_BLACK][P_BLACK][P_BLACK][P_BLACK][P_BOUND] = sleepFour;
	value[P_BLACK][P_BLANK][P_BLACK][P_BLACK][P_BLACK][P_BOUND] = sleepFour;
	value[P_BLACK][P_BLACK][P_BLANK][P_BLACK][P_BLACK][P_BOUND] = sleepFour;
	value[P_BLACK][P_BLACK][P_BLACK][P_BLANK][P_BLACK][P_BOUND] = sleepFour;
	value[P_BLANK][P_WHITE][P_WHITE][P_WHITE][P_WHITE][P_BOUND] = -sleepFour;
	value[P_WHITE][P_BLANK][P_WHITE][P_WHITE][P_WHITE][P_BOUND] = -sleepFour;
	value[P_WHITE][P_WHITE][P_BLANK][P_WHITE][P_WHITE][P_BOUND] = -sleepFour;
	value[P_WHITE][P_WHITE][P_WHITE][P_BLANK][P_WHITE][P_BOUND] = -sleepFour;
	//���� 
	value[P_WHITE][P_BLACK][P_BLANK][P_BLACK][P_BLANK][P_BLACK] = sleepThree;
	value[P_WHITE][P_BLACK][P_BLACK][P_BLACK][P_BLANK][P_BLANK] = sleepThree;
	value[P_WHITE][P_BLACK][P_BLACK][P_BLANK][P_BLACK][P_BLANK] = sleepThree;
	value[P_WHITE][P_BLACK][P_BLANK][P_BLACK][P_BLACK][P_BLANK] = sleepThree;
	value[P_BLACK][P_WHITE][P_BLANK][P_WHITE][P_BLANK][P_WHITE] = -sleepThree;
	value[P_BLACK][P_WHITE][P_WHITE][P_WHITE][P_BLANK][P_BLANK] = -sleepThree;
	value[P_BLACK][P_WHITE][P_WHITE][P_BLANK][P_WHITE][P_BLANK] = -sleepThree;
	value[P_BLACK][P_WHITE][P_BLANK][P_WHITE][P_WHITE][P_BLANK] = -sleepThree;
	 
	value[P_BLACK][P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_WHITE] = sleepThree;
	value[P_BLANK][P_BLANK][P_BLACK][P_BLACK][P_BLACK][P_WHITE] = sleepThree;
	value[P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_BLACK][P_WHITE] = sleepThree;
	value[P_BLANK][P_BLACK][P_BLACK][P_BLANK][P_BLACK][P_WHITE] = sleepThree;
	value[P_WHITE][P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_BLACK] = -sleepThree;
	value[P_BLANK][P_BLANK][P_WHITE][P_WHITE][P_WHITE][P_BLACK] = -sleepThree;
	value[P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_WHITE][P_BLACK] = -sleepThree;
	value[P_BLANK][P_WHITE][P_WHITE][P_BLANK][P_WHITE][P_BLACK] = -sleepThree;
	//����  �߽�
	value[P_BOUND][P_BLACK][P_BLACK][P_BLACK][P_BLANK][P_BLANK] = sleepThree;
	value[P_BOUND][P_BLACK][P_BLACK][P_BLANK][P_BLACK][P_BLANK] = sleepThree;
	value[P_BOUND][P_BLACK][P_BLANK][P_BLACK][P_BLACK][P_BLANK] = sleepThree;
	value[P_BOUND][P_WHITE][P_WHITE][P_WHITE][P_BLANK][P_BLANK] = -sleepThree;
	value[P_BOUND][P_WHITE][P_WHITE][P_BLANK][P_WHITE][P_BLANK] = -sleepThree;
	value[P_BOUND][P_WHITE][P_BLANK][P_WHITE][P_WHITE][P_BLANK] = -sleepThree;

	value[P_BLANK][P_BLANK][P_BLACK][P_BLACK][P_BLACK][P_BOUND] = sleepThree;
	value[P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_BLACK][P_BOUND] = sleepThree;
	value[P_BLANK][P_BLACK][P_BLACK][P_BLANK][P_BLACK][P_BOUND] = sleepThree;
	value[P_BLANK][P_BLANK][P_WHITE][P_WHITE][P_WHITE][P_BOUND] = -sleepThree;
	value[P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_WHITE][P_BOUND] = -sleepThree;
	value[P_BLANK][P_WHITE][P_WHITE][P_BLANK][P_WHITE][P_BOUND] = -sleepThree;
	//��� 
	value[P_BLANK][P_BLANK][P_BLANK][P_BLACK][P_BLACK][P_BLANK] = liveTwo;
	value[P_BLANK][P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_BLANK] = liveTwo;
	value[P_BLANK][P_BLANK][P_BLACK][P_BLACK][P_BLANK][P_BLANK] = liveTwo;

	value[P_BLANK][P_BLANK][P_BLANK][P_BLACK][P_BLACK][P_BLANK] = liveTwo;
	value[P_BLANK][P_BLACK][P_BLANK][P_BLANK][P_BLACK][P_BLANK] = liveTwo;
	value[P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_BLANK][P_BLANK] = liveTwo;

	value[P_BLANK][P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_BLANK] = liveTwo;
	value[P_BLANK][P_BLACK][P_BLANK][P_BLANK][P_BLACK][P_BLANK] = liveTwo;
	value[P_BLANK][P_BLACK][P_BLACK][P_BLANK][P_BLANK][P_BLANK] = liveTwo;

	value[P_BLANK][P_BLANK][P_BLACK][P_BLACK][P_BLANK][P_BLANK] = liveTwo;
	value[P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_BLANK][P_BLANK] = liveTwo;
	value[P_BLANK][P_BLACK][P_BLACK][P_BLANK][P_BLANK][P_BLANK] = liveTwo;

	value[P_BLANK][P_BLANK][P_BLANK][P_WHITE][P_WHITE][P_BLANK] = -liveTwo;
	value[P_BLANK][P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_BLANK] = -liveTwo;
	value[P_BLANK][P_BLANK][P_WHITE][P_WHITE][P_BLANK][P_BLANK] = -liveTwo;

	value[P_BLANK][P_BLANK][P_BLANK][P_WHITE][P_WHITE][P_BLANK] = -liveTwo;
	value[P_BLANK][P_WHITE][P_BLANK][P_BLANK][P_WHITE][P_BLANK] = -liveTwo;
	value[P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_BLANK][P_BLANK] = -liveTwo;

	value[P_BLANK][P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_BLANK] = -liveTwo;
	value[P_BLANK][P_WHITE][P_BLANK][P_BLANK][P_WHITE][P_BLANK] = -liveTwo;
	value[P_BLANK][P_WHITE][P_WHITE][P_BLANK][P_BLANK][P_BLANK] = -liveTwo;

	value[P_BLANK][P_BLANK][P_WHITE][P_WHITE][P_BLANK][P_BLANK] = -liveTwo;
	value[P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_BLANK][P_BLANK] = -liveTwo;
	value[P_BLANK][P_WHITE][P_WHITE][P_BLANK][P_BLANK][P_BLANK] = -liveTwo;
	//�߶� �߽�
	value[P_BOUND][P_BLACK][P_BLACK][P_BLANK][P_BLANK][P_BLANK] = sleepTwo;
	value[P_BOUND][P_BLACK][P_BLANK][P_BLACK][P_BLANK][P_BLANK] = sleepTwo;
	value[P_BOUND][P_BLACK][P_BLANK][P_BLANK][P_BLACK][P_BLANK] = sleepTwo;
	value[P_BOUND][P_BLACK][P_BLANK][P_BLANK][P_BLANK][P_BLACK] = sleepTwo;
	value[P_BOUND][P_WHITE][P_WHITE][P_BLANK][P_BLANK][P_BLANK] = -sleepTwo;
	value[P_BOUND][P_WHITE][P_BLANK][P_WHITE][P_BLANK][P_BLANK] = -sleepTwo;
	value[P_BOUND][P_WHITE][P_BLANK][P_BLANK][P_WHITE][P_BLANK] = -sleepTwo;
	value[P_BOUND][P_WHITE][P_BLANK][P_BLANK][P_BLANK][P_WHITE] = -sleepTwo;

	value[P_BLACK][P_BLANK][P_BLANK][P_BLANK][P_BLACK][P_BOUND] = sleepTwo;
	value[P_BLANK][P_BLACK][P_BLANK][P_BLANK][P_BLACK][P_BOUND] = sleepTwo;
	value[P_BLANK][P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_BOUND] = sleepTwo;
	value[P_BLANK][P_BLANK][P_BLANK][P_BLACK][P_BLACK][P_BOUND] = sleepTwo;
	value[P_WHITE][P_BLANK][P_BLANK][P_BLANK][P_WHITE][P_BOUND] = -sleepTwo;
	value[P_BLANK][P_WHITE][P_BLANK][P_BLANK][P_WHITE][P_BOUND] = -sleepTwo;
	value[P_BLANK][P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_BOUND] = -sleepTwo;
	value[P_BLANK][P_BLANK][P_BLANK][P_WHITE][P_WHITE][P_BOUND] = -sleepTwo;
	//�߶� 
	value[P_WHITE][P_BLACK][P_BLACK][P_BLANK][P_BLANK][P_BLANK] = sleepTwo;
	value[P_WHITE][P_BLACK][P_BLANK][P_BLACK][P_BLANK][P_BLANK] = sleepTwo;
	value[P_WHITE][P_BLACK][P_BLANK][P_BLANK][P_BLACK][P_BLANK] = sleepTwo;
	value[P_WHITE][P_BLACK][P_BLANK][P_BLANK][P_BLANK][P_BLACK] = sleepTwo;
	value[P_BLACK][P_WHITE][P_WHITE][P_BLANK][P_BLANK][P_BLANK] = -sleepTwo;
	value[P_BLACK][P_WHITE][P_BLANK][P_WHITE][P_BLANK][P_BLANK] = -sleepTwo;
	value[P_BLACK][P_WHITE][P_BLANK][P_BLANK][P_WHITE][P_BLANK] = -sleepTwo;
	value[P_BLACK][P_WHITE][P_BLANK][P_BLANK][P_BLANK][P_WHITE] = -sleepTwo;

	value[P_BLACK][P_BLANK][P_BLANK][P_BLANK][P_BLACK][P_WHITE] = sleepTwo;
	value[P_BLANK][P_BLACK][P_BLANK][P_BLANK][P_BLACK][P_WHITE] = sleepTwo;
	value[P_BLANK][P_BLANK][P_BLACK][P_BLANK][P_BLACK][P_WHITE] = sleepTwo;
	value[P_BLANK][P_BLANK][P_BLANK][P_BLACK][P_BLACK][P_WHITE] = sleepTwo;
	value[P_WHITE][P_BLANK][P_BLANK][P_BLANK][P_WHITE][P_BLACK] = -sleepTwo;
	value[P_BLANK][P_WHITE][P_BLANK][P_BLANK][P_WHITE][P_BLACK] = -sleepTwo;
	value[P_BLANK][P_BLANK][P_WHITE][P_BLANK][P_WHITE][P_BLACK] = -sleepTwo;
	value[P_BLANK][P_BLANK][P_BLANK][P_WHITE][P_WHITE][P_BLACK] = -sleepTwo;
	//��һ
	value[P_WHITE][P_BLANK][P_BLACK][P_BLANK][P_BLANK][P_BLANK] = liveOne;
	value[P_WHITE][P_BLANK][P_BLANK][P_BLACK][P_BLANK][P_BLANK] = liveOne;
	value[P_WHITE][P_BLANK][P_BLANK][P_BLANK][P_BLACK][P_BLANK] = liveOne;
	value[P_BLACK][P_BLANK][P_WHITE][P_BLANK][P_BLANK][P_BLANK] = -liveOne;
	value[P_BLACK][P_BLANK][P_BLANK][P_WHITE][P_BLANK][P_BLANK] = -liveOne;
	value[P_BLACK][P_BLANK][P_BLANK][P_BLANK][P_WHITE][P_BLANK] = -liveOne;

	value[P_BLANK][P_BLACK][P_BLANK][P_BLANK][P_BLANK][P_WHITE] = liveOne;
	value[P_BLANK][P_BLANK][P_BLACK][P_BLANK][P_BLANK][P_WHITE] = liveOne;
	value[P_BLANK][P_BLANK][P_BLANK][P_BLACK][P_BLANK][P_WHITE] = liveOne;
	value[P_BLANK][P_WHITE][P_BLANK][P_BLANK][P_BLANK][P_BLACK] = -liveOne;
	value[P_BLANK][P_BLANK][P_WHITE][P_BLANK][P_BLANK][P_BLACK] = -liveOne;
	value[P_BLANK][P_BLANK][P_BLANK][P_WHITE][P_BLANK][P_BLACK] = -liveOne;
	//��һ�߽�
	value[P_BOUND][P_BLANK][P_BLACK][P_BLANK][P_BLANK][P_BLANK] = liveOne;
	value[P_BOUND][P_BLANK][P_BLANK][P_BLACK][P_BLANK][P_BLANK] = liveOne;
	value[P_BOUND][P_BLANK][P_BLANK][P_BLANK][P_BLACK][P_BLANK] = liveOne;
	value[P_BOUND][P_BLANK][P_WHITE][P_BLANK][P_BLANK][P_BLANK] = -liveOne;
	value[P_BOUND][P_BLANK][P_BLANK][P_WHITE][P_BLANK][P_BLANK] = -liveOne;
	value[P_BOUND][P_BLANK][P_BLANK][P_BLANK][P_WHITE][P_BLANK] = -liveOne;

	value[P_BLANK][P_BLACK][P_BLANK][P_BLANK][P_BLANK][P_BOUND] = liveOne;
	value[P_BLANK][P_BLANK][P_BLACK][P_BLANK][P_BLANK][P_BOUND] = liveOne;
	value[P_BLANK][P_BLANK][P_BLANK][P_BLACK][P_BLANK][P_BOUND] = liveOne;
	value[P_BLANK][P_WHITE][P_BLANK][P_BLANK][P_BLANK][P_BOUND] = -liveOne;
	value[P_BLANK][P_BLANK][P_WHITE][P_BLANK][P_BLANK][P_BOUND] = -liveOne;
	value[P_BLANK][P_BLANK][P_BLANK][P_WHITE][P_BLANK][P_BOUND] = -liveOne;

}

//���̼�ֵ�ܺͼ���
int sumValue() {
	int totalvalue = 0;
	
	for (int i = 0; i < CbIntNum; i++)
	{
		for (int j = 0; j < CbIntNum; j++)
		{
			totalvalue += BoardValueSum[i][j];
		}
	}
	return totalvalue;
}

//���̼�ֵ����
int boardValueEvaluate() {
	//ֱ�߽߱�
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			BoardValue[i][j] = 0;
		}
	}
	for (int i = 0; i < CbIntNum; i++)
	{
		BoardValue[i][0] += value[P_BOUND][BoardKey[i][0]][BoardKey[i][1]][BoardKey[i][2]][BoardKey[i][3]][BoardKey[i][4]];
		BoardValue[0][i] += value[P_BOUND][BoardKey[0][i]][BoardKey[1][i]][BoardKey[2][i]][BoardKey[3][i]][BoardKey[4][i]];
		BoardValue[i][10] += value[BoardKey[i][10]][BoardKey[i][11]][BoardKey[i][12]][BoardKey[i][13]][BoardKey[i][14]][P_BOUND];
		BoardValue[10][i] += value[BoardKey[10][i]][BoardKey[11][i]][BoardKey[12][i]][BoardKey[13][i]][BoardKey[14][i]][P_BOUND];
	}
	//б�߽߱�
	for (int i = 0; i < CbBoardValueNum + 1; i++)
	{
		BoardValue[i][10] += value[BoardKey[i][10]][BoardKey[i + 1][11]][BoardKey[i + 2][12]][BoardKey[i + 3][13]][BoardKey[i + 4][14]][P_BOUND];
		BoardValue[10][i] += value[BoardKey[10][i]][BoardKey[11][i + 1]][BoardKey[12][i + 2]][BoardKey[13][i + 3]][BoardKey[14][i + 4]][P_BOUND];
		BoardValue[i][4] += value[P_BOUND][BoardKey[i + 4][0]][BoardKey[i + 3][1]][BoardKey[i + 2][2]][BoardKey[i + 1][3]][BoardKey[i][4]];
		BoardValue[10][14 - i] += value[P_BOUND][BoardKey[14][10 - i]][BoardKey[13][11 - i]][BoardKey[12][12 - i]][BoardKey[11][13 - i]][BoardKey[10][14 - i]];
	}
	//ֱ�����̱���
	for (int i = 0; i < CbBoardValueNum; i++)
	{
		for (int j = 0; j < CbIntNum; j++)
		{
			BoardValue[i][j] += value[BoardKey[i][j]][BoardKey[i + 1][j]][BoardKey[i + 2][j]][BoardKey[i + 3][j]][BoardKey[i + 4][j]][BoardKey[i + 5][j]];
			BoardValue[j][i] += value[BoardKey[j][i]][BoardKey[j][i + 1]][BoardKey[j][i + 2]][BoardKey[j][i + 3]][BoardKey[j][i + 4]][BoardKey[j][i + 5]];
		}
	}
	//б�����̱���
	for (int i = 0; i < CbBoardValueNum; i++)
	{
		for (int j = 0; j < CbBoardValueNum; j++)
		{
			BoardValue[i][j] += value[BoardKey[i][j]][BoardKey[i + 1][j + 1]][BoardKey[i + 2][j + 2]][BoardKey[i + 3][j + 3]][BoardKey[i + 4][j + 4]][BoardKey[i + 5][j + 5]];
			BoardValue[i][14 - j] += value[BoardKey[i][14 - j]][BoardKey[i + 1][13 - j]][BoardKey[i + 2][12 - j]][BoardKey[i + 3][11 - j]][BoardKey[i + 4][10 - j]][BoardKey[i + 5][9 - j]];
		}
	}
	int total = 0;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			total += BoardValue[i][j];
		}
	}
	return total;
}

#define pwhite(y,x) do{BoardKey[y][x] = P_WHITE;drawPiece(y, x, P_WHITE);}while(0);
#define pblack(y,x) do{BoardKey[y][x] = P_BLACK;drawPiece(y, x, P_BLACK);}while(0);

int main()
{
	/*BoardKey[7][7] = P_WHITE; 
	BoardKey[7][8] = P_WHITE;
	BoardKey[7][9] = P_WHITE;
	BoardKey[7][10] = P_WHITE;
	PointValueEvaluate(7, 7);
	PointValueEvaluate(7, 8);
	PointValueEvaluate(7, 9);
	PointValueEvaluate(7, 10);

	PointValueUpdate(7, 7);
	PointValueUpdate(7, 8);
	PointValueUpdate(7, 9);
	PointValueUpdate(7, 10);*/

	valueInitialization();
	drawCb();
	WhoGo = P_BLACKMove;
	//drawPiece(7, 7, P_WHITE);
	//drawPiece(7, 8, P_WHITE);
	//drawPiece(7, 9, P_WHITE);
	//drawPiece(7, 10, P_WHITE);
	pblack(7, 7);
	pblack(8, 7);
	pblack(9, 8);

	pwhite(8, 6);
	pwhite(6, 7);
	pwhite(7, 8);



	while (1)
	{
		if (WhoGo == P_BLACKMove)
		{
			// �������
			while (1) {
				MOUSEMSG mouse = GetMouseMsg(); // ��ȡ�����Ϣ
				for (int i = 0; i < CbIntNum; i++)
				{
					for (int j = 0; j < CbIntNum; j++)
					{
						if (IsBLANK(mouse, i, j))
						{
							// ���ͣ��ĳһ����λ������
							if (mouse.mkLButton)
							{
								// ���������
								BoardKey[i][j] = P_BLACK; // ����
								drawPiece(i, j, P_BLACK); // ��λ�ø���
								// ��һ�����
								WhoGo = P_WHITEMove;
							}
						}
					}
				}
				if (WhoGo == P_WHITEMove) {
					break;
				}
			}
		}
		if (gamewin() != 0)
		{
			break;
		}
		cutNumA = 0;
		cutNumB = 0;
		if (WhoGo == P_WHITEMove)
		{
			// ��������
			LPoint Best;
			Best = ChoseBest(WhoGo); // Ѱ�����λ��
			BoardKey[Best.y][Best.x] = P_WHITE; // ����
			drawPiece(Best.y, Best.x, P_WHITE);
			WhoGo = P_BLACKMove;			
		}
		if (gamewin() != 0)
		{
			break;
		}
	}
	if (gamewin() == 2)
	{
		outtextxy(320, 320, _T("��ʤ"));
	}
	if (gamewin() == 1)
	{
		outtextxy(320, 320, _T("��ʤ"));
	}
	Sleep(5000);
	closegraph();			// �رջ�ͼ����
	return 0;
}
