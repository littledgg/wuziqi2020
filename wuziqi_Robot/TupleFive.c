#include "TupleFive.h"

//const
const TupleFivePoint nextStep[4] = {
	{0,1,0},
	{1,0,0},
	{1,1,0},
	{1,-1,0}
};
const int scoreMyColor[5] = {0,35,800,15000,800000};
const int scoreEnemyColor[5] = {0,15,400,1800,100000};

//function
TupleScore getScore_FiveTuple(GameEngine engine)
{
	//init
	TupleScore result;
	memset(&result, 0, sizeof(TupleScore));
	TupleFivePoint tmpPoint;
	int tmpScore = 0;

	//calculate score
	for(int direction = 0;direction < 4;direction++)
		for(int x = 0;x < 15; x++)
			for (int y = 0; y < 15; y++)
			{
				tmpPoint = (TupleFivePoint){ x,y,direction };
				if (isOutOfTupleStartRange(tmpPoint))
					continue;
				tmpScore = getTmpTupleScore(engine, tmpPoint);
				flushTmpTupleScore(&result, tmpPoint, tmpScore);
			}

	//mark occupied place as -1
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			if (CHESS_EMPTY != engine.squareMap.map[i][j])
				result.map[i][j] = -1;

	return result;
}

int getTmpTupleScore(GameEngine engine, TupleFivePoint point)
{	
	//init
	int b = 0, w = 0;

	//get num of black and white in a tuple
	for (int i = 1; i <= 5; i++)
	{
		if (CHESS_BLACK == engine.squareMap.map[point.x][point.y])
			b++;
		if (CHESS_WHITE == engine.squareMap.map[point.x][point.y])
			w++;
		point = pointPlus(point, nextStep[point.direction]);
	}

	//case polluted
	if (0 != b * w)
		return 0;

	//case blank
	if (0 == b + w)
		return 7;

	if (PLAYER_BLACK == engine.playerColor)
		return (scoreMyColor[b] > scoreEnemyColor[w] ? scoreMyColor[b] : scoreEnemyColor[w]);

	if (PLAYER_WHITE == engine.playerColor)
		return (scoreMyColor[b] > scoreEnemyColor[w] ? scoreMyColor[b] : scoreEnemyColor[w]);
}

void flushTmpTupleScore(TupleScore* score, TupleFivePoint point, int tmpScore)
{
	for (int i = 1; i <= 5; i++)
	{
		score->map[point.x][point.y] += tmpScore;
		point = pointPlus(point, nextStep[point.direction]);
	}
}

int isOutOfTupleStartRange(TupleFivePoint point)
{
	if (point.x < 0 || point.x > 14 || point.y < 0 || point.y > 14)
		return 1;
	switch (point.direction)
	{
	case 0:   //horizontal
		if (point.x > 10)
			return 1;
		break;
	case 1:   //vertical
		if (point.y > 10)
			return 1;
		break;
	case 2:   //oblique 00 to nn
		if (point.x > 10 || point.y > 10)
			return 1;
		break;
	case 3:   //oblique 0n to n0
		if (point.x < 4 || point.y > 10)
			return 1;
		break;
	default:
		break;
	}

	return 0;
}

TupleFivePoint pointPlus(TupleFivePoint a, TupleFivePoint b)
{
	return (TupleFivePoint) { a.x + b.x, a.y + b.y, (a.direction + b.direction) % 4 };
}