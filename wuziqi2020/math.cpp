#include "func.hpp"
void setColor(int i, int j, int color)
{
	BOX[i][j].color_val = color;
}
// �Ƿ���������
bool inBOX(int i, int j)
{
	return i >= 0 && j >= 0 && i <= 14 && j <= 14;
}
// �Ƚϴ�С
// type 'b' : ���ؽϴ����
// type 's' : ���ؽ�С����
int compare(int x, int y, bool bigger)
{
	if (bigger)
		return (x > y) ? x : y;
	else
		return (x < y) ? x : y;
}
// �жϵ�ǰλ���Ƿ�Ϊ�������ɫ
bool isColor(int i, int j, int color)
{
	return BOX[i][j].color_val == color;
}
// �Ż��ٶȺ��� 
// �ж������ 5 * 5 �ĸ������Ƿ������� 
// Ҳ����Ҫ�����жϷ�Χ
bool have_neighbor55(int i, int j)
{
	int cur_i = i;
	int cur_j = j;
	int pd = false;
	i -= 2;
	j -= 2;
	if (i < 0) i = 0;
	if (j < 0) j = 0;
	for (int a = i; a < cur_i + 2 && a <= 14; a++) {
		for (int b = j; b < cur_j + 2 && b <= 14; b++) {
			if (BOX[a][b].color_val != -1) {
				pd = true;
				goto there;
			}
		}
	}
there:
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