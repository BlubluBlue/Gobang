#include<iomanip>
#include<iostream>
#include"Board.h"

using namespace std;
bool Board::win()
{
	int value, counts, a, b;
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			if (points[i][j].value != 0) {
				value = points[i][j].value;
				counts = 1, a = i, b = j;
				while (a >= 0 && b >= 0 && points[a][b].neighbors[leftNeighbor] == value) {
					counts++;
					if (counts == 5) {
						return true;
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