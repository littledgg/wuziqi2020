#pragma once
#include <easyx.h>			// ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include <stdio.h>
void drawCb();//������
void drawPiece(int y, int x, int key);
void PrintBoard(int Board[][CbIntNum]);
int IsBLANK(MOUSEMSG mouse, int y, int x);
