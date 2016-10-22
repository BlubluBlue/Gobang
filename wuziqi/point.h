#ifndef POINT_H
#define POINT_H
#include<vector>
using namespace std;
class Point
{
public:
	void set(int a, int b)
	{
		x = a;
		y = b;
	}
	int evaluate = 0;
	int x;
	int y;
	int value = 0;
	int neighborCount = 0;
};

#endif