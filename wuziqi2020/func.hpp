#include "draw.hpp"

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
// ÿ�������������ֵ
#define SEARCH_NUM_MAX 10

// ȫ�ֱ���
extern box BOX[15][15];     // ����
extern int di[4];    // - | \ / �ĸ�����
extern int dj[4];	// - | \ / �ĸ�����
extern int evaluate_map[3][5];// ���ֱ� [�з�����][�ҷ�����] 

// ��������
// math.cpp
void quickSort(seat A[], int low, int high);
int evaluate_score_one(int b_j, int color, int b_i);
#define inBOX(i,j) ((i) >= 0 && (j) >= 0 && (i) <= 14 && (j) <= 14)
#define isColor(i,j,color) (BOX[(i)][(j)].color_val == (color))
#define setColor(i,j,color) (BOX[(i)][(j)].color_val = (color))
#define bigger(x,y) (((x) > (y)) ? (x) : (y))
#define smaller(x,y) (((x) < (y)) ? (x) : (y))
// ���º��neighbor����
#define ADD_NEIGHBOR 1
#define DES_NEIGHBOR -1
void set_neighbor(int i, int j, int type);
extern int neighbor[15][15];
#define have_neighbor(i,j) (neighbor[(i)][(j)] > 0)

// getPosition.cpp
int max_min_search(int color, int alpha, int beta, int depth);