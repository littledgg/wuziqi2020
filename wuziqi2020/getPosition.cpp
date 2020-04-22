#include "func.hpp"
#include <stdio.h>

// �����Сֵ����
// alpha-beta ��֦�Ż�
// have_neighbor �ж������Ż�
// ����ʽ�����Ż�
int max_min_search(int color, int alpha, int beta, int depth)
{
	if (depth == 0) return evaluate_score(color);
	int score = (depth % 2 == 0) ? INT_MIN : INT_MAX;
	int temp;
	seat a[15 * 15];
	int count = gen(a, color);
	for (int i = 0; i < count; i++) {
		setColor(a[i].i, a[i].j, color);
		set_neighbor(a[i].i, a[i].j, ADD_NEIGHBOR);
		temp = max_min_search(1 - color, alpha, beta, depth - 1);
		set_neighbor(a[i].i, a[i].j, DES_NEIGHBOR);
		setColor(a[i].i, a[i].j, EMPTY_C);
		if (depth % 2 == 0) {
			score = bigger(score, temp);
			alpha = bigger(alpha, temp);
		}
		else {
			score = smaller(score, temp);
			beta = smaller(beta, temp);
		}
		if (alpha >= beta) return score;
	}
	return score;
}

// ����ʽ��������
// �����������������ߵģ��ӿ�AB��֦�ٶ�
int gen(seat a[], int color)
{
	int count = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (isColor(i, j, EMPTY_C) && have_neighbor(i,j)) {
				a[count].i = i;
				a[count].j = j;
				setColor(i, j, color);
				a[count].score = evaluate_score_one(color, i, j);
				// ��Ҫ�Ļ���һ����
				setColor(i, j, 1 - color);
				a[count].score += evaluate_score_one(color, i, j);
				setColor(i, j, EMPTY_C);
				count++;
			}
		}
	}
	quickSort(a, 0, count);
	return count;
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
		while (isColor(cur_i, cur_j, color) && inBOX(cur_i, cur_j)) {
			count_my++;
			cur_i -= di[i];
			cur_j -= dj[i];
		}
		if (isColor(cur_i, cur_j, 1 - color) || !inBOX(cur_i, cur_j)) {
			count_enemy++;
		}
		cur_i = b_i;
		cur_j = b_j;
		while (isColor(cur_i, cur_j, color) && inBOX(cur_i, cur_j)) {
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