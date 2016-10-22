#include<iostream>
#include<ctime>
#include<vector>
#include"board.h"
using namespace std;

void humanPlay();
void computerPlay();
void play(int player);
Point maxMin(int deep);
int min(int deep, int alpha, int beta);
int max(int deep, int alpha, int beta);


Board *board = Board::getInstance();
const int DEEP = 4;
const int MAX = (*board).score[4] * 10;
const int MIN = -1 * MAX;
double timeForOneStep;
int main()
{
	srand(time(0));
	int player = 1;
	while (!(*board).win()) {
		(*board).draw();
		play(player);
		player *= -1;
	}
	(*board).draw();
	if (player == 1) {
		cout << "电脑已经把你干翻在地" << endl;
	} else {
		cout << "恭喜你击败了强大的电脑" << endl;
	}

	delete board;
	return 0;
}

void humanPlay() 
{
	cout << "电脑花了" << timeForOneStep << "秒来思考" << endl;
	cout << (*board).sum << endl;
	(*board).sum = 0;
	cout << "你的回合: " << endl;
	int x, y;
	cin >> x >> y;
	while (x < 0 || x > 14 || y < 0 || y > 14 || (*board).getPoint(x, y).value != 0) {
		cout << "该位置不可下子，请重新选择!" << endl;
		cin >> x >> y;
	}
	(*board).setPoint(x, y, 1);
}

void computerPlay() 
{
	timeForOneStep = clock();
	cout << "电脑正在思考: " << endl;
	Point point = maxMin(DEEP);
	timeForOneStep = (clock() - timeForOneStep) / 1000;
	int x = point.x, y = point.y;
	(*board).setPoint(x, y, 2);
}

Point maxMin(int deep)
{
	vector<Point> viablePoints = (*board).getViablePoints(true);
	vector<Point> bestPoints;
	int x, y;
	int alpha = MIN, beta = MAX, result;
	for (auto point : viablePoints) {
		x = point.x, y = point.y;
		(*board).setPoint(x, y, 2);
		result = min(deep - 1, alpha, beta);
		if (result >= alpha) {
			if (result > alpha) {
				bestPoints.clear();
				alpha = result;
			}
			bestPoints.push_back(point);
		}
		(*board).setPoint(x, y, 0);
	}
	int size = bestPoints.size();
	return bestPoints[rand() % size];
}

int min(int deep, int alpha, int beta)
{
	if (deep <= 0 || (*board).win()) {
		return (*board).evaluate();
	}
	vector<Point> viablePoints = (*board).getViablePoints(false);
	int x, y;
	int result;
	for (auto point : viablePoints) {
		x = point.x, y = point.y;
		(*board).setPoint(x, y, 1);
		result = max(deep - 1, alpha, beta);
		if (result < beta) {
			beta = result;
		}
		(*board).setPoint(x, y, 0);
		if (alpha > beta) {
			break;
		}
	}
	return beta;
}

int max(int deep, int alpha, int beta)
{
	if (deep <= 0 || (*board).win()) {
		return (*board).evaluate();
	}
	vector<Point> viablePoints = (*board).getViablePoints(true);
	int x, y;
	int result;
	for (auto point : viablePoints) {
		x = point.x, y = point.y;
		(*board).setPoint(x, y, 2);
		result = min(deep - 1, alpha, beta);
		if (result > alpha) {
			alpha = result;
		}
		(*board).setPoint(x, y, 0);
		if (alpha > beta) {
			break;
		}
	}
	return alpha;
}

void play(int player) 
{
	if (player == 1) {
		humanPlay();
	}
	else {
		computerPlay();
	}
}
