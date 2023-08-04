#pragma once
#include"Source.h"
int bangNum = 0;
class Bang
{
public:
	int No;
	int x;
	int y;
	int countDown;

	Bang(int x, int y)
	{
		No = bangNum;
		bangNum++;
		this->x = x;
		this->y = y;
		countDown = 20;
	}
};
