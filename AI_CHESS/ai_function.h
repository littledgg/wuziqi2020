//�����Ǻ����㷨�����ǱȽϽ���ȡʵ�鱨��ȥ����һ���ִ���Ľ���˵��
#pragma once
#include <iostream>
#include <time.h>//199����Ҫ
#include <stdlib.h>//200����Ҫ
#include "class.h"

// Ѱ�����λ��
seat findbestseat(int color, int c)
{
	if (c == 0)
	{
		//mylength����MAXxs��MAYys���±�
		mylength = 0;//�õ��������Ŀ����Ը���
	}
	int MAXnumber = -1e9;    //��ǰ�����£����ط������㼰�õ�ķ���
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			if (BOX[i][j].value == -1) {
				//����ÿһ����λ��
				int length;        //�ڸõ����˺󣬿������ɵ���󳤶�
				int emeny;         //��ǰ������ӵĸ���
				int nowi = 0;      //���ڱ�������x����
				int nowj = 0;      //���ڱ�������y����
				int thescore = 0;  //���λ�õĳ�ʼ����
				//�ж��ܱ���û�����ӣ�������ܱ���ָ�ĸ�����һ�������ڣ�Ȼ��һ�¾��ǰ˸�������
				int is = 0;//�൱��һ����ǣ�������û��
				for (int k = 0; k < 4; k++)
				{
					nowi = i;
					nowj = j;
					nowi += dx[k];
					nowj += dy[k];
					if (nowi >= 0 && nowj >= 0
						&& nowi <= 18 && nowj <= 18
						&& BOX[nowi][nowj].value != -1)
					{
						is = 1;
						break;
					}//������     *
					 //         0 *
					 //         * *  ��4�������������ת180�ȷ�����
					nowi = i;
					nowj = j;
					nowi -= dx[k];
					nowj -= dy[k];
					if (nowi >= 0 && nowj >= 0
						&& nowi <= 18 && nowj <= 18
						&& BOX[nowi][nowj].value != -1)
					{
						is = 1;
						break;
					}
				}
				if (!is)
				{
					//�����Χû�����ӣ��Ͳ��õݹ���
					continue;
				}
				//����
				BOX[i][j].value = color;//�������������ʵ��û���£������ȱ���ϣ�
				for (int k = 0; k < 4; k++)
				{
					//����ĸ�����
					length = 0;
					emeny = 0;
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == color)
					{
						length++;
						nowi += dx[k];
						nowj += dy[k];
	
					}
					if (nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18 || BOX[nowi][nowj].value == !color)//�ж�֮ǰѭ��������ԭ��
					{																					//����������ڵ��������з����Ӿͼ�
						                                                                                //����������Ҳ��
						emeny++;
					}
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == color)
					{
						length++;
						nowj -= dy[k];
						nowi -= dx[k];
					}
					if (nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18 || BOX[nowi][nowj].value == !color)
					{
						emeny++;
					}
					length -= 2;//�жϳ��ȣ�������ָ���������µ�����������������������󳤶ȣ�Ȼ������Լ���
					if (length > 4)
					{
						length = 4;
					}
					if (Score[emeny][length] == 1000)
					{
						//����ʤ���������ݹ�
						BOX[i][j].value = -1;
						return{ i,j,Score[emeny][length] };
					}
					thescore += Score[emeny][length];
					length = 0;
					emeny = 0;
				}
				//���ˣ�color�����ڸô����ĸ�����÷��ܺ���ȷ������color���������Ƕ��ٵ÷��Ƕ��٣�
				BOX[i][j].value = !color;
				for (int k = 0; k < 4; k++)
				{
					length = 0;
					emeny = 0;
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == !color)
					{
						length++;
						nowj += dy[k];
						nowi += dx[k];
					}
					if (nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18 || BOX[nowi][nowj].value == color)
					{
						emeny++;
					}
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == !color)
					{
						length++;
						nowj -= dy[k];
						nowi -= dx[k];
					}
					if (nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18 || BOX[nowi][nowj].value == color)
					{
						emeny++;
					}
					length -= 2;
					if (length > 4)
					{
						length = 4;
					}
					if (Score[emeny][length] == 1000)
					{
						BOX[i][j].value = -1;
						return{ i,j,Score[emeny][length] };
					}
					thescore += Score[emeny][length];
					length = 0;
					emeny = 0;
				}
				//���thescore�൱��Խ�󣬶�˫�����ԣ���һ��֮�ڶ�Խ��Ҫ
				BOX[i][j].value = -1;
				//����Ѿ�����߷���С����û��Ҫ�ݹ���
				if (thescore >= MAXnumber)
				{
					if (c < 3)
					{
						//ֻ����4�㣬����ʱ��̫��
						BOX[i][j].value = color;
						//nowscorce������4��֮�ڣ��õ����Ҫ��
						int nowScore = thescore - findbestseat(!color, c + 1).number;//�ݹ�������λ�õķ�ֵ
						BOX[i][j].value = -1;
						if (nowScore > MAXnumber)// MAXnumber��ָ���о����£�֮ǰ�������������е�nowscore���ֵ
						{
							//����߷�ֵ��
							MAXnumber = nowScore;
							if (c == 0)//ֻ�е�һ��Ҫ�ı��±�
							{
								mylength = 0;//�±��0
							}
						}
						if (c == 0)
						{
							//��һ��
							if (nowScore >= MAXnumber)
							{
								//�ѵ�ǰλ�ü�������
								MAXxs[mylength] = i;
								MAXys[mylength] = j;
								mylength++;//���еȷֿ��ܷ�һ�𣬵�ʱ�����ȡǰmylength���ȵĿ���
							}
						}
					}
					else {
						//����ݹ鵽�����һ��
						if (thescore > MAXnumber)
						{
							//ֱ�Ӹ���
							MAXnumber = thescore;
						}
					}
				}
			}
		}
	}
	if (c == 0)
	{
		
		srand(time(NULL));//���������λ�ã��Է�ֹÿ�ζ�һ����ͬһ��λ�ã�����·��
		int mynum = rand() % mylength;
		return { MAXxs[mynum],MAXys[mynum],MAXnumber };//��mynum�ĳ�0������·���������ˣ���ͬ����һ����ĳһ��λ�ã�
	}
	//������
	return { 0,0,MAXnumber };
}