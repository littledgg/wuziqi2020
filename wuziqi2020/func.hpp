#include "draw.hpp"
#include <time.h>

// �������������ߵ�����
#define FIVE 10000000  // ����
#define L4 100000  // ����
#define L3 1000  // ����
#define L2 100     // ���
#define L1 10      // ��һ
#define S4 1000   // ����
#define S3 100   // ����
#define S2 10      // �߶�
#define S1 1
#define NOUSE 0

// ������ɫ��ֵ
#define BLACK_C 1    // ��ɫ
#define WHITE_C 0    // ��ɫ
#define EMPTY_C -1   // ��

// �����Сֵ��������(����Ϊż��)
#define LAYER_LIMIT 4
// ��ͬ��ֵ�ĵ�λ���������ֵ
#define COUNT_BEST_MAX 10

// ȫ�ֱ���
extern box BOX[15][15];     // ����
extern int di[4];    // - | \ / �ĸ�����
extern int dj[4];	// - | \ / �ĸ�����
extern int evaluate_map[3][5];// ���ֱ� [�з�����][�ҷ�����] 
//extern int step; // ��������������
//extern seat steps[225];

// ��������

// math
bool inBOX(int i, int j);
void setColor(int i, int j, int color);
int compare(int x, int y, bool bigger);
bool isColor(int i, int j, int color);
bool have_neighbor55(int i, int j);
int paritition(seat A[], int low, int high);
void quickSort(seat A[], int low, int high);

// getPosition
int max_min_search(int color, int alpha, int beta, int depth);
int evaluate_score(int color);
int evaluate_score_one(int b_i, int b_j, int color);
void gen(seat a[], int color);