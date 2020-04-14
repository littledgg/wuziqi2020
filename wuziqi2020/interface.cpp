#include "func.hpp"
#include <time.h>

// ȫ�ֱ���
extern box BOX[15][15];     // ����
int di[4] = { 0,1,1,1 };    // - | \ / �ĸ�����
int dj[4] = { 1,0,1,-1 };	// - | \ / �ĸ�����
int evaluate_map[3][5] = {  // ���ֱ� [�з�����][�ҷ�����] 
	{L1 ,L2, L3, L4, FIVE},
	{S1, S2, S3, S4, FIVE},
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
				setColor(i, j, EMPTY_C);
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
			}
		}
	}
	srand(time(NULL));
	return best[rand() % (count_best + 1)]; 
}

