#pragma once
#include"GameLoad.h"
//游戏道具：锤子和小推车
extern int bangNum;
class Lawnmower	//小推车
{
public:
	int location = -20;		//初始位置
	int isActivated = 0;	//是否启动
	int isOut = 0;			//是否已经开出去
};

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
	void paintbangs(Node<Bang>*& cur, Node<Bang>*& pre, LinkList<Bang>& bangs);
};
