#ifndef BOARD_H
#define BOARD_H

#include<iomanip>

#define BOARD_SIZE 15

enum neighbor{
	topNeighbor = 0,
	topRightNeighbor = 1,
	rightNeighbor = 2,
	bottomRightNeighbor = 3,
	bottomNeighbor = 4,
	bottomLeftNeighbor = 5,
	leftNeighbor = 6,
	topLeftNeighbor = 7
};
class Point
{
public:
	int value = 0;
	int neighbors[8];
	bool hasNeighbor() {
		if (getNeighborCounts() > 0) {
			return true;
		}
		return false;
	}
	int getNeighborCounts() {
		int count = 0;
		for (auto n : neighbors) {
			if (n != 0) {
				++count;
			}
		}
		return count;
	}
};

int score[9] = { 10, 100, 1000, 100000, 1000000, 1, 10, 100, 10000};
class Board
{
private:
	Point points[BOARD_SIZE][BOARD_SIZE];
public:
	void draw(); 
	int evaluate() {
		int result, value, counts, a, b;
		for (int i = 0; i < BOARD_SIZE; ++i) {
			for (int j = 0; j < BOARD_SIZE; ++j) {
				if (points[i][j].value != 0) {
					value = points[i][j].value;
					counts = 0, a = i, b = j;
					while (a >= 0 && b >= 0) { 
						if (points[a][b].neighbors[leftNeighbor] == value) {
							counts++;
						} else {
							if (points[a][b].neighbors[leftNeighbor] == 0) {
								result += score[counts];
							} else {
								result += score[counts + 5];
							}
						}
						--b;
					}
					counts = 1, a = i, b = j;
					while (a >= 0 && b >= 0 && points[a][b].neighbors[topLeftNeighbor] == value) {
						counts++;
						if (counts == 5) {
							return true;
						}
						--a;
						--b;
					}
					counts = 1, a = i, b = j;
					while (a >= 0 && b >= 0 && points[a][b].neighbors[topNeighbor] == value) {
						counts++;
						if (counts == 5) {
							return true;
						}
						--a;
					}
					counts = 1, a = i, b = j;
					while (a >= 0 && b >= 0 && points[a][b].neighbors[topRightNeighbor] == value) {
						counts++;
						if (counts == 5) {
							return true;
						}
						--a;
						++b;
					}
				}
			}
		}
	}
	Point getPoint(int x, int y) {
		return points[x][y];
	}
	void setPoint(int x, int y, int value) {
		points[x][y].value = value;
		points[x - 1][y - 1].neighbors[bottomRightNeighbor] = value;
		points[x - 1][y].neighbors[bottomNeighbor] = value;
		points[x - 1][y + 1].neighbors[bottomLeftNeighbor] = value;
		points[x][y - 1].neighbors[rightNeighbor] = value;
		points[x][y + 1].neighbors[leftNeighbor] = value;
		points[x + 1][y - 1].neighbors[topRightNeighbor] = value;
		points[x + 1][y].neighbors[topNeighbor] = value;
		points[x + 1][y + 1].neighbors[topLeftNeighbor] = value;
	}
	bool win();
};

#endif