#include"gobang.h"

int BoardMove[CbIntNum][CbIntNum];
int BoardKey[CbIntNum][CbIntNum];//�����������ͣ��ܹ�15*15��
int BoardValue[CbIntNum][CbIntNum];//����λ�ü�ֵ���ͣ��ܹ�15*15
int value[4][4][4][4][4][4];
int val;
int WhoGo;

//
void UnmakeMove(LPLink* p) {
	BoardKey[p->size.y][p->size.x] = P_BLANK;
}
//
void MakeNextMove(LPLink* p,int depth,int who) {
	if (((who + depth) % 2) == 1)
	{
		BoardKey[p->size.y][p->size.x] = P_BLACK;
	}
	else if (((who + depth) % 2) == 0)
	{
		BoardKey[p->size.y][p->size.x] = P_WHITE;
	}
}

LPLink* GenerateLegalMoves() {
	
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

	return creat(BoardMove);
}

LPoint ChoseBest(LPLink* p,int who) {
	LPLink * node;
	LPoint best;
	node = p->next;
	int val=0,valbest=0;
	if (who==1)
	{
		valbest = -9999999;
	}
	if (who==2)
	{
		valbest = 9999999;
	}
	while (p->next != NULL) {
		p = p->next;
		MakeNextMove(p, who,MAX_depth);
		val = P_ValBest(p,who, MAX_depth,999999,-999999);
		UnmakeMove(p);
		if (who == 1)
		{
			if (val > valbest) {
				node = p;
				valbest = val;
			}
		}
		if (who == 2)
		{
			if (val < valbest) {
				node = p;
				valbest = val;
			}
		}
		
	}
	best.value = valbest;
	best.x = node->size.x;
	best.y = node->size.y;
	return best;
}

void freeLPLink(LPLink* node) {
	LPLink* end;
	while (node!= NULL) {
		end = node;
		node = node->next;
		free(end);
	}
}

int P_ValBest(LPLink* thisP, int who, int depth, int alpha, int beta) {
	if (depth == 1) {
		return boardValueEvaluate();
	}
	LPLink* node;
	int val = 0;
	int valbest=0;
	if ((who + depth - 1) % 2 == 1)//����ڵ�
	{
		valbest = -9999999;
	}
	if ((who + depth - 1) % 2 == 0)//��С�ڵ�
	{
		valbest = 9999999;
	}

	LPLink* nextP;
	nextP = GenerateLegalMoves();
	while (nextP->next != NULL) {
		node = nextP;
		nextP = nextP->next;
		free(node);
		MakeNextMove(nextP, who,depth-1);
		val = P_ValBest(thisP,who,depth-1,alpha,beta);
		UnmakeMove(nextP);
		if ((who+depth-1)%2 == 1)
		{
			if (val > valbest) {
				valbest = val;
			}
			if (val > alpha) {
				freeLPLink(nextP);
				return val;
			}
			if (val > beta) {
				beta = val;
			}

			
		}
		if ((who+depth-1)%2 == 0)
		{
			if (val < valbest) {
				valbest = val;
			}
			if (val < beta) {
				freeLPLink(nextP);
				return val;
			}
			if (val < alpha) {
				alpha = val;
			}
		}
		
	}
	//freeLPLink(node);
	return valbest;
}

//���м俪ʼ����һ������Խ�����м����ǰ��
LPLink* creat(int BoardMove[][CbIntNum]) {
	LPLink* head, * node, * end;//����ͷ�ڵ㣬��ͨ�ڵ㣬β���ڵ㣻
	head = (LPLink*)malloc(sizeof(LPLink));//�����ַ
	end = head;         //���ǿ�������ͷβ�ڵ�һ��
	for (int i = 1; i < 8; i++)
	{
		for (int j = -i+1; j <= i; j++)
		{
			if (BoardMove[7+i][7-j] == LegalMove)
			{
				node = (LPLink*)malloc(sizeof(LPLink));
				node->size.y = 7 + i;
				node->size.x = 7 - j;
				end->next = node;
				end = node;
			}
			if (BoardMove[7-i][7+j] == LegalMove)
			{
				node = (LPLink*)malloc(sizeof(LPLink));
				node->size.y = 7 - i;
				node->size.x = 7 + j;
				end->next = node;
				end = node;
			}
			if (BoardMove[7+j][7+i] == LegalMove)
			{
				node = (LPLink*)malloc(sizeof(LPLink));
				node->size.y = 7 + j;
				node->size.x = 7 + i;
				end->next = node;
				end = node;
			}
			if (BoardMove[7-j][7-i] == LegalMove)
			{
				node = (LPLink*)malloc(sizeof(LPLink));
				node->size.y = 7 - j;
				node->size.x = 7 - i;
				end->next = node;
				end = node;
			}
		}
	}

	end->next = NULL;//��������
	return head;
}

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

int boardValueEvaluate() {
	int totalvalue=0;
	for (int i = 0; i < CbIntNum; i++)
	{
		for (int j = 0; j < CbIntNum; j++)
		{
			BoardValue[i][j]=0;
		}
	}
	//ֱ�߽߱�
	for (int i = 0; i < CbIntNum; i++)
	{
		BoardValue[i][0] += value[P_BOUND][BoardKey[i][0]][BoardKey[i][1]][BoardKey[i][2]][BoardKey[i][3]][BoardKey[i][4]];
		BoardValue[0][i] += value[P_BOUND][BoardKey[0][i]][BoardKey[1][i]][BoardKey[2][i]][BoardKey[3][i]][BoardKey[4][i]];
		BoardValue[i][10] += value[BoardKey[i][10]][BoardKey[i][11]][BoardKey[i][12]][BoardKey[i][13]][BoardKey[i][14]][P_BOUND];
		BoardValue[10][i] += value[BoardKey[10][i]][BoardKey[11][i]][BoardKey[12][i]][BoardKey[13][i]][BoardKey[14][i]][P_BOUND];
	}
	//б�߽߱�
	for (int i = 0; i < CbBoardValueNum+1; i++)
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
	//�����������
	for (int i = 0; i < CbIntNum; i++)
	{
		for (int j = 0; j < CbIntNum; j++)
		{
			totalvalue += BoardValue[i][j];
		}
	}
	return totalvalue;
}

int gamewin() {
	for (int i = 0; i < CbIntNum; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if ((BoardKey[i][j] == P_BLACK) && (BoardKey[i][j + 1] == P_BLACK) && (BoardKey[i][j + 2] == P_BLACK) && (BoardKey[i][j + 3] == P_BLACK) && (BoardKey[i][j + 4] == P_BLACK))
			{
				return 1;
			}
			if ((BoardKey[i][j] == P_WHITE) && (BoardKey[i][j + 1] == P_WHITE) && (BoardKey[i][j + 2] == P_WHITE) && (BoardKey[i][j + 3] == P_WHITE) && (BoardKey[i][j + 4] == P_WHITE))
			{
				return 2;
			}
			if ((BoardKey[j][i] == P_BLACK) && (BoardKey[j + 1][i] == P_BLACK) && (BoardKey[j + 2][i] == P_BLACK) && (BoardKey[j + 3][i] == P_BLACK) && (BoardKey[j + 4][i] == P_BLACK))
			{
				return 1;
			}
			if ((BoardKey[j][i] == P_WHITE) && (BoardKey[j + 1][i] == P_WHITE) && (BoardKey[j + 2][i] == P_WHITE) && (BoardKey[j + 3][i] == P_WHITE) && (BoardKey[j + 4][i] == P_WHITE))
			{
				return 2;
			}

		}
	}
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if ((BoardKey[i][j] == P_BLACK) && (BoardKey[i + 1][j + 1] == P_BLACK) && (BoardKey[i + 2][j + 2] == P_BLACK) && (BoardKey[i + 3][j + 3] == P_BLACK) && (BoardKey[i + 4][j + 4] == P_BLACK))
			{
				return 1;
			}
			if ((BoardKey[i][j] == P_WHITE) && (BoardKey[i + 1][j + 1] == P_WHITE) && (BoardKey[i + 2][j + 2] == P_WHITE) && (BoardKey[i + 3][j + 3] == P_WHITE) && (BoardKey[i + 4][j + 4] == P_WHITE))
			{
				return 2;
			}
			if ((BoardKey[i + 4][j] == P_BLACK) && (BoardKey[i + 3][j + 1] == P_BLACK) && (BoardKey[i + 2][j + 2] == P_BLACK) && (BoardKey[i + 1][j + 3] == P_BLACK) && (BoardKey[i][j + 4] == P_BLACK))
			{
				return 1;
			}
			if ((BoardKey[i + 4][j] == P_WHITE) && (BoardKey[i + 3][j + 1] == P_WHITE) && (BoardKey[i + 2][j + 2] == P_WHITE) && (BoardKey[i + 1][j + 3] == P_WHITE) && (BoardKey[i][j + 4] == P_WHITE))
			{
				return 2;
			}
		}
	}
	return 0;
}

int main()
{
	BoardKey[7][7] = P_WHITE; 
	BoardKey[7][8] = P_WHITE;
	BoardKey[7][9] = P_WHITE;
	BoardKey[7][10] = P_WHITE;
	
	valueInitialization();
	drawCb();
	WhoGo = P_BLACKMove;
	drawPiece(7, 7, P_WHITE);
	drawPiece(7, 8, P_WHITE);
	drawPiece(7, 9, P_WHITE);
	drawPiece(7, 10, P_WHITE);
	while (1)
	{
		if (WhoGo == P_BLACKMove)
		{
			// �������
			MOUSEMSG mouse = GetMouseMsg(); // ��ȡ�����Ϣ
			for (int i = 0; i < CbIntNum; i++)
			{
				for (int j = 0; j < CbIntNum; j++)
				{
					if (IsBLANK(mouse,i,j))
					{
						// ���ͣ��ĳһ����λ������
						if (mouse.mkLButton)
						{
							// ���������
							BoardKey[i][j] = P_BLACK; // ����
							drawPiece(i, j, P_BLACK);   // ��λ�ø���
							// ��һ�����
							WhoGo = P_WHITEMove;
							if (gamewin() != 0)
							{
								break;
							}
						}
					}
				}
			}
		}
		
		if (WhoGo == P_WHITEMove)
		{
			// ��������
			LPoint Best;
			LPLink* pp;
			pp = GenerateLegalMoves();
			Best = ChoseBest(pp, WhoGo); // Ѱ�����λ��
			BoardKey[Best.y][Best.x] = P_WHITE; // ����
			drawPiece(Best.y, Best.x, P_WHITE);
			WhoGo = P_BLACKMove;
			if (gamewin() != 0)
			{
				break;
			}
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
