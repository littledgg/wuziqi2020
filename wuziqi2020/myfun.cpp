#include "func.hpp"
#include <time.h>


// �������������ߵ�����
#define FIVE 10000000  // ����
#define LFORE 100000  // ����
#define LTHREE 1000  // ����
#define LTWO 100     // ���
#define LONE 10      // ��һ
#define SFORE 1000   // ����
#define STHREE 100   // ����
#define STWO 10      // �߶�
#define SONE 1

// ������ɫ��ֵ
#define BLACK_C 1    // ��ɫ
#define WHITE_C 0    // ��ɫ
#define EMPTY_C -1   // ��

// �����Сֵ��������(����Ϊż��)
// 4���Ѿ��ȽϿ��ˣ����µ������Ƚ���
#define LAYER_LIMIT 4
// ��ͬ��ֵ�ĵ�λ���������ֵ
#define COUNT_BEST_MAX 10

// ȫ�ֱ���
extern box BOX[15][15];     // ����
int di[4] = { 0,1,1,1 };    // - | \ / �ĸ�����
int dj[4] = { 1,0,1,-1 };	// - | \ / �ĸ�����
int evaluate_map[3][5] = {  // ���ֱ� [�з�����][�ҷ�����] 
	{LONE ,LTWO, LTHREE, LFORE, FIVE},
	{SONE, STWO, STHREE, SFORE, FIVE},
	{0, 0, 0, 0, FIVE}
};

// �ӿں���
seat findbestseat2(int color)
{
	seat best[COUNT_BEST_MAX];
	int count_best = 0;

	// MIN MAX SEARCH
	int dump = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (isColor(i, j, EMPTY_C) && have_neighbor55(i, j)) {
				setColor(i, j, color);
				dump = max_min_search(1 - color, INT_MIN, INT_MAX, LAYER_LIMIT - 1);
				if (best[count_best].score < dump) {
					count_best = 0;
					best[0].score = dump;
					best[0].i = i;
					best[0].j = j;
				}
				else if(best[count_best].score == dump && count_best != COUNT_BEST_MAX - 1){
					count_best++;
					best[count_best].score = dump;
					best[count_best].i = i;
					best[count_best].j = j;
				}
				setColor(i, j, EMPTY_C);
			}
		}
	}
	srand(time(NULL));
	return best[rand() % (count_best + 1)]; 
}

// �����Сֵ����
// alpha-beta ��֦�Ż� (����Ҳ����)
// have_seat55 �ж������Ż�
// ����ʽ�����Ż�(���������Ҳ���û������)
int max_min_search(int color, int alpha, int beta, int depth)
{
	if (depth == 0) return evaluate_score(color);
	int score = (depth % 2 == 0) ? INT_MIN : INT_MAX;
	int dump;
	seat a[15 * 15];
	gen(a, color);
	for (int i = 0; i < 15 * 15; i++) {
		if (isColor(a[i].i, a[i].j, EMPTY_C) && have_neighbor55(a[i].i, a[i].j)) {
			setColor(a[i].i, a[i].j, color);
			dump = max_min_search(1 - color, alpha, beta, depth - 1);
			if (depth % 2 == 0) {
				score = compare(score, dump, true);
				alpha = compare(alpha, dump, true);
			}
			else {
				score = compare(score, dump, false);
				beta = compare(beta, dump, false);
			}
			setColor(a[i].i, a[i].j, EMPTY_C);
			if (alpha >= beta) return score;
		}
	}
	return score;
}

// ����ʽ��������
// �����������������ߵģ��ӿ�AB��֦�ٶ�
void gen(seat a[], int color) 
{
	for (int i = 0; i < 15 * 15; i++) {
		a[i].i = i / 15;
		a[i].j = i % 15;
	}
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (isColor(i, j, EMPTY_C)) {
				setColor(i, j, color);
				a[i * 15 + j].score = evaluate_score_one(color, i, j);
				setColor(i, j, 1 - color);
				a[i * 15 + j].score += evaluate_score_one(color, i, j);
				setColor(i, j, EMPTY_C);
			}
		}
	}
	quickSort(a, 0, 15 * 15 - 1);
}


// ������������ -- �ۺϺڰ����ӵ������ܷ�
// ����Խ����color������Խ��
int evaluate_score(int color)
{
	int score = 0;
	for (int b_i = 0; b_i < 15; b_i++) {
		for (int b_j = 0; b_j < 15; b_j++) {
			if (BOX[b_i][b_j].color_val == color) {
				score += evaluate_score_one(color, b_i, b_j);
			}
			else if (BOX[b_i][b_j].color_val == 1 - color) {
				score -= evaluate_score_one(1 - color, b_i, b_j);
			}
		}
	}
	return score;
}
 
// ������������
int evaluate_score_one(int color, int b_i, int b_j)
{
	int cur_i;
	int cur_j;
	int score = 0;
	for (int i = 0; i < 4; i++) {
		// �жϵ�ǰ״��
		int count_my = -1;
		int count_enemy = 0;
		cur_i = b_i;
		cur_j = b_j;
		while (isColor(cur_i,cur_j,color) && inBOX(cur_i,cur_j)) {		
			count_my++;
			cur_i -= di[i];
			cur_j -= dj[i];
		}
		if (isColor(cur_i, cur_j, 1 - color) || !inBOX(cur_i, cur_j)) {
			count_enemy++;
		}
		cur_i = b_i;
		cur_j = b_j;
		while (isColor(cur_i, cur_j, color) && inBOX(cur_i,cur_j)) {
			count_my++;
			cur_i += di[i];
			cur_j += dj[i];
		}
		if (isColor(cur_i, cur_j, 1 - color) || !inBOX(cur_i, cur_j)) {
			count_enemy++;
		}
		// �ж�����
		if (count_my > 5) {
			count_my = 5;
		}
		if (count_enemy > 2) {
			count_enemy = 2;
		}
		score += evaluate_map[count_enemy][count_my - 1];
	}
	return score;
}