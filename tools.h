#pragma once
#include"GameLoad.h"
//��Ϸ���ߣ����Ӻ�С�Ƴ�
extern int bangNum;
class Lawnmower	//С�Ƴ�
{
public:
	int location = -20;		//��ʼλ��
	int isActivated = 0;	//�Ƿ�����
	int isOut = 0;			//�Ƿ��Ѿ�����ȥ
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
