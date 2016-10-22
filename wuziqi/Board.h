#ifndef BOARD_H
#define BOARD_H

#include<vector>
#include<iomanip>
#include<algorithm>
#include"point.h"
#include"neighbor.h"

#define BOARD_SIZE 15

class Board
{
private:
	Point points[BOARD_SIZE][BOARD_SIZE];
	Board()
	{
		for (int i = 0; i < BOARD_SIZE; ++i) {
			for (int j = 0; j < BOARD_SIZE; ++j) {
				points[i][j].set(i, j);
			}
		}
	}
	Board(Board &) = delete;
	Board & operator=(Board &) = delete;
	static Board *instance;
	int computeLeft(int x, int y, int value);
	int computeTopLeft(int x, int y, int value);
	int computeTop(int x, int y, int value);
	int computeTopRight(int x, int y, int value);
public:
	int sum = 0;
	static int score[9];
	void setPoint(int x, int y, int value);
	bool win();
	int getPointEvaluate(Point point, bool isMax)
	{
		int x = point.x, y = point.y, value, pointScore = 0;
		if (isMax) {
			value = 2;
		} else {
			value = 1;
		}
		/*
		if (y + 1 <= 14 && points[x][y + 1].value != value) {
			pointScore += computeLeft(x, y, value);
		}

		if (x + 1 <= 14 && y + 1 <= 14 && points[x + 1][y + 1].value != value) {
			pointScore += computeTopLeft(x, y, value);
		}

		if (x + 1 <= 14 && points[x + 1][y].value != value) {
			pointScore += computeTop(x, y, value);
		}

		if (x + 1 <= 14 && y - 1 >= 0 && points[x + 1][y - 1].value != value) {
			pointScore += computeTopRight(x, y, value);
		}
	*/
		while (y + 1 <= 14 && points[x][y + 1].value == value) {
			++y;
		}
		pointScore += computeLeft(x, y, value);

		while (x + 1 <= 14 && y + 1 <= 14 && points[x + 1][y + 1].value == value) {
			++x, ++y;
		}
		pointScore += computeTopLeft(x, y, value);

		while (x + 1 <= 14 && points[x + 1][y].value == value) {
			++x;
		}
		pointScore += computeTop(x, y, value);

		while (x + 1 <= 14 && y - 1 >= 0 && points[x + 1][y - 1].value == value) {
			++x, --y;
		}
		pointScore += computeTopRight(x, y, value);

		/*while (y + 1 <= 14 && points[x][y + 1].value == value) {
			++y;
		}
		pointScore += computeLeft(x, y, value);

		while (x + 1 <= 14 && y + 1 <= 14 && points[x + 1][y + 1].value != value) {
			++x, ++y;
		}
		pointScore += computeTopLeft(x, y, value);

		while (x + 1 <= 14 && points[x + 1][y].value != value) {
			++x;
		}
		pointScore += computeTop(x, y, value);

		while (x + 1 <= 14 && y - 1 >= 0 && points[x + 1][y - 1].value != value) {
			++x, --y;
		}
		pointScore += computeTopRight(x, y, value);*/
		return pointScore;
	}
	vector<Point> getViablePoints(bool isMax);
	void draw(); 
	Point getPoint(int x, int y) {
		return points[x][y];
	}
	static Board *getInstance()
	{
		if (instance == nullptr) {
			instance = new Board();
		}

		return instance;
	}
	int evaluate();
};
#endif