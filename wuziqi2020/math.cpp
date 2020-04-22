#include "func.hpp"
// �Ż��ٶȺ��� 
// �ж������ 5 * 5 �ĸ������Ƿ������� 
bool have_neighbor55(int i, int j)
{
	bool pd = false;
	for (int a = i - 2; a < i + 2 && pd == false; a++) {
		for (int b = j - 2; b < j + 2 && pd == false; b++) {
			if (a == i && b == j) continue;
			if (inBOX(a, b) && !isColor(a, b, EMPTY_C)) {
				pd = true;
			}
		}
	}
	return pd;
}
int paritition(seat A[], int low, int high)
{
	seat pivot = A[low];
	while (low < high) {
		while (low < high && A[high].score <= pivot.score) {
			--high;
		}
		A[low] = A[high];
		while (low < high && A[low].score >= pivot.score) {
			++low;
		}
		A[high] = A[low];
	}
	A[low] = pivot;
	return low;
}
// �Ӵ�С����
void quickSort(seat A[], int low, int high) //����ĸ����
{
	if (low < high) {
		int pivot = paritition(A, low, high);
		quickSort(A, low, pivot - 1);
		quickSort(A, pivot + 1, high);
	}
}
void initStar(seat* star, int i, int j)
{
	int count = 0;
	for (int a = 0; a < 4; a++) {
		for (int b = 1; b <= 5; b++) {
			star[count].i = i + b * di[a];
			star[count++].j = j + b * dj[a];
			star[count].i = i - b * di[a];
			star[count++].j = j - b * dj[a];
		}
	}
}