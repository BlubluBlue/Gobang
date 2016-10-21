#include<iostream>
#include<vector>
#include"Board.h"
using namespace std;

void humanPlay();
void computerPlay();
void play(int player);

Board board;
int main()
{
	int player = 1;
	while (!board.win()) {
		board.draw();
		play(player);
		player *= -1;
	}
	if (player == 1) {
		cout << "电脑已经把你干翻在地" << endl;
	} else {
		cout << "恭喜你击败了强大的电脑" << endl;
	}
}

void humanPlay() 
{
	int x, y;
	do{
		cin >> x >> y;
		int a;
	} while (board.getPoint(x, y).value != 0);
	board.setPoint(x, y, 1);
}

void computerPlay() 
{
	
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

/*#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;

#define depth = 4;
void drawBoard();
void playerPlay();
void computerPlay();
void maxMin();
bool hasNeighbor(int x, int y, int gap);
int evaluate();
vector<point> getPoints();
bool win();
int board[15][15] = { 0 };
enum role{
	null,
	player,
	computer
};
struct {
	int one = 10;
	int two = 100;
	int three = 1000;
	int four = 100000;
	int five = 1000000;
	int block_one = 1;
	int block_two = 10;
	int block_three = 100;
	int block_four = 10000;
} score;

int MAX = score.five * 10;
int MIN = -1 * MAX;
struct point
{
	point(int a, int b) :x(a), y(b){}
	int x;
	int y;
};
int winner = role::null;
int main()
{
	drawBoard();
	while (winner == role::null) {
		playerPlay();
		computerPlay();
	}
}

void computerPlay()
{
	maxMin();
}

point maxMin(int deep)
{
	int best = MIN;
	int value;
	vector<point> bestPoints;
	vector<point> points = getPoints();
	for (auto p : points) {
		board[p.x][p.y] = 2;
		value = min(deep - 1);
		if (value = best) {
			bestPoints.push_back(p);
		}
		if (value > best) {
			bestPoints.clear();
			bestPoints.push_back(p);
		}
		board[p.x][p.y] = 0;
	}

	int size = bestPoints.size();
	return bestPoints[rand() % size];
}

int min(int deep)
{
	int value = evaluate();	
	if (deep <= 0 || win()) {
		return value;
	}
	int best = MAX;
	vector<point> points = getPoints();
	for (auto p : points) {
		board[p.x][p.y] = 1;
		value = max(deep - 1);
		if (value < best) {
			best = value;
		}
		board[p.x][p.y] = 0;
	}

	return best;
}


int max(int deep)
{
	int value = evaluate();
	if (deep <= 0 || win()) {
		return value;
	}
	int best = MIN;
	vector<point> points = getPoints();
	for (auto p : points) {
		board[p.x][p.y] = 1;
		value = min(deep - 1);
		if (value > best) {
			best = value;
		}
		board[p.x][p.y] = 0;
	}

	return best;
}

int evaluate()
{

}

vector<point> getPoints()
{
	vector<point> neighbor;
	vector<point> nextNeightbor;
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			if (board[x][y] != 0) {
				continue;
			}
			if (hasNeighbor(x, y, 1)) {
				neighbor.push_back(point(x, y));
				continue;
			} else if (hasNeighbor(x, y, 2)){
				nextNeightbor.push_back(point(x, y));
			}
		}
	}
	for (auto point : nextNeightbor) {
		neighbor.push_back(point);
	}
	return neighbor;
}

bool hasNeighbor(int x, int y, int gap)
{
	int left = x - gap >= 0 ? x - gap : 0;
	int right = x + gap < 15 ? x + gap : 14;
	int top = y - gap >= 0 ? y - gap : 0;
	int bottom = y + gap < 15 ? y + gap : 14;
	for (int i = top; i <= bottom; ++i) {
		for (int j = left; j <= right; ++j) {
			if (board[x][y] != 0) {
				return true;
			}
		}
	}
	return false;
}

void playerPlay()
{
	int x, y;
	do{
		cin >> x >> y;
	} while (board[x][y] != 0);
	board[x][y] = 1;
	drawBoard();
}

void drawBoard()
{
	system("cls");
	cout << setw(3) << ' ';
	for (int i = 0; i <= 14; ++i) {
		cout << setw(3) << i;
	}
	cout << endl;
	int k = -1;
	for (auto &i: board) {
		cout << setw(3) << ++k;
		for (auto j : i) {
			switch (j)
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
}*/