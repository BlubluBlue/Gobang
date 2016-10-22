#include<iomanip>
#include<iostream>
#include"board.h"

using namespace std;
Board* Board::instance = nullptr;
int Board::score[9] = { 10, 100, 1000, 100000, 1000000, 1, 10, 100, 10000 };

bool compMax(Point &a, Point&b) {
	return a.evaluate > b.evaluate;
}

bool compMin(Point &a, Point&b) {
	return a.evaluate < b.evaluate;
}

vector<Point> Board::getViablePoints(bool isMax)
{
	vector<Point> result;
	int viablePoints[BOARD_SIZE][BOARD_SIZE] = { 0 };
	for (auto &line : points) {
		for (auto point : line) {
			if (point.value != 0) {
				int left = point.x - 2, right = point.x + 2, top = point.y - 2, bottom = point.y + 2;
				left = left >= 0 ? left : 0;
				right = right <= 14 ? right : 14;
				top = top >= 0 ? top : 0;
				bottom = bottom <= 14 ? bottom : 14;
				for (int i = left; i <= right; ++i) {
					for (int j = top; j <= bottom; ++j) {
						if (points[i][j].value == 0) {
							viablePoints[i][j] = 1;
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			if (viablePoints[i][j] == 1) {
				points[i][j].evaluate = getPointEvaluate(points[i][j], isMax);
				result.push_back(points[i][j]);
			}
		}
	}
	bool(*comp)(Point &a, Point &b);
	if (isMax) {
		comp = compMax;
	}
	else {
		comp = compMin;
	}
	sort(result.begin(), result.end(), comp);
	return result;
}
void Board::setPoint(int x, int y, int value) {
	points[x][y].value = value;
}

bool Board::win()
{
	int value;
	for (int x = 0; x < BOARD_SIZE; ++x) {
		for (int y = 0; y < BOARD_SIZE; ++y) {
			if (points[x][y].value != 0) {
				value = points[x][y].value;
				if (points[x][y + 1].value != value) {
					if (computeLeft(x, y, value) == score[4]) {
						return true;
					}
				}

				if (points[x + 1][y + 1].value != value) {
					if (computeTopLeft(x, y, value) == score[4]) {
						return true;
					}
				}

				if (points[x + 1][y].value != value) {
					if (computeTop(x, y, value) == score[4]) {
						return true;
					}
				}

				if (points[x + 1][y - 1].value != value) {
					if (computeTopRight(x, y, value) == score[4]) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

void Board::draw()
{
	system("cls");
	cout << setw(3) << ' ';
	for (int i = 0; i <= 14; ++i) {
		cout << setw(3) << i;
	}
	cout << endl;
	int k = -1;
	for (auto &i : points) {
		cout << setw(3) << ++k;
		for (auto j : i) {
			switch (j.value)
			{
			case 0:{
				cout << setw(3) << '+';
				break;
			}
			case 1:{
				cout << setw(3) << '@';
				break;
			}
			case 2:{
				cout << setw(3) << '%';
				break;
			}
			default:
				break;
			}
		}
		cout << endl;
	}
}

int Board::computeLeft(int x, int y, int value)
{
	int ownCount = 0, enemyCount = 0;
	if (y + 1 > 14 || points[x][y + 1].value != 0) {
		++enemyCount;
	}
	while (y - 1 >= 0 && points[x][y - 1].value == value) {
		--y;
		++ownCount;
	}
	if (ownCount == 4) {
		return  score[4];
	}
	if (y <= 0) {
		++enemyCount;
	} else if (points[x][y - 1].value != 0) {
		++enemyCount;
	}
	return 	enemyCount < 2 ? score[ownCount + enemyCount * 5] : 0;
}

int Board::computeTopLeft(int x, int y, int value)
{
	int ownCount = 0, enemyCount = 0;
	if (x + 1 > 14 || y + 1 > 14 || points[x + 1][y + 1].value != 0) {
		++enemyCount;
	}
	while (x - 1 >= 0 && y - 1 >= 0 && points[x - 1][y - 1].value == value) {
		--x;
		--y;
		++ownCount;
	}
	if (ownCount == 4) {
		return  score[4];
	}
	if (y <= 0 || x <= 0) {
		++enemyCount;
	}
	else if (points[x - 1][y - 1].value != 0) {
		++enemyCount;
	}
	return 	enemyCount < 2 ? score[ownCount + enemyCount * 5] : 0;
}

int Board::computeTop(int x, int y, int value)
{
	int ownCount = 0, enemyCount = 0;
	if (points[x + 1][y].value != 0) {
		++enemyCount;
	}
	while (x - 1 >= 0 && points[x - 1][y].value == value) {
		--x;
		++ownCount;
	}
	if (ownCount == 4) {
		return  score[4];
	}
	if (x <= 0) {
		++enemyCount;
	}
	else if (points[x - 1][y].value != 0) {
		++enemyCount;
	}
	return 	enemyCount < 2 ? score[ownCount + enemyCount * 5] : 0;
}

int Board::computeTopRight(int x, int y, int value)
{
	int ownCount = 0, enemyCount = 0;
	if (points[x + 1][y - 1].value != 0) {
		++enemyCount;
	}
	while (x - 1 >= 0 && y + 1 <= 14 && points[x][y - 1].value == value) {
		++y;
		--x;
		++ownCount;
	}
	if (ownCount == 4) {
		return  score[4];
	}
	if (x <= 0 || y >= 14) {
		++enemyCount;
	}
	else if (points[x + 1][y - 1].value != 0) {
		++enemyCount;
	}

	return 	enemyCount < 2 ? score[ownCount + enemyCount * 5] : 0;
}

int Board::evaluate()
{
	++sum;
	int computerScore = 0;
	int humanScore = 0;
	int x, y, value, pointScore;
	for (auto &line : points) {
		for (auto point : line) {
			if (point.value == 0) {
				continue;
			}
			x = point.x, y = point.y, value = point.value, pointScore = 0;
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

			if (value == 1) {
				humanScore += pointScore;
			} else {
				computerScore += pointScore;
			}
		}
	}
	return  computerScore - humanScore;
}