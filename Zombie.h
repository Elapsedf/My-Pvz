#pragma once
#include"tools.h"
#define GRAVE1 1
#define GRAVE2 2
#define GRAVE3 3
#define GRAVE4 4
#define GRAVE5 5
#define GRAVE6 6
#define GRAVE7 7
#define GRAVE8 8
#define BUCKETHEADZOMBIE 16
#define NORMALZOMBIE 21
#define CONEHEADZOMBIE 22
extern int ZombieNum;
extern double GroanFrequency;	//��ϢƵ��
extern void generateSunshine(int x, int y);
class Zombie
{
public:
	int HP;
	int row;
	int location;
	int emerge1walk2eat3;
	int frameNo;
	int height;
	int No;		//node������ֹ��node���� 
	int changeFrameCountDown;
	int isFrozen;
	int isSlowed;
	int type;
	int attack;	//�˺�

	Zombie()
	{
		No = ZombieNum;			//��ǰĩ���
		ZombieNum++;	
		isFrozen = 0;		//�Ƿ񱻱���
		isSlowed = 0;
		height = 115;			// ��ʬͼ��߶�
		frameNo = 19;			// ��ʾ���ŵ��ڼ�֡
		emerge1walk2eat3 = 1;	// ����ð������ 1 ��ʾ������������ 2 ��ʾ�����ڳ�ֲ���� 3 ��ʾ
		HP = 6;
		changeFrameCountDown = 10;
	}
	void playdirt_rise()
	{
		mciSendString("play ./Music/dirt_rise.mp3 from 0", 0, 0, 0);
	}
	//void paintzombies(Node<Zombie>*&cur, Node<Zombie>*&next, LinkList<Zombie>zombies, Lawnmower *&lawnmowers);
};
class NormalZombie : public Zombie			//��ͨ��ʬ
{
public:
	NormalZombie()
	{
		HP = 1;
		attack = 2;
		type = NORMALZOMBIE;
	}
};

class ConeheadZombie : public Zombie		//·�Ͻ�ʬ
{
public:
	ConeheadZombie()
	{
		HP = 2;
		attack = 4;
		type = CONEHEADZOMBIE;
	}
};

class BucketheadZombie : public Zombie		//��Ͱ��ʬ
{
public:
	BucketheadZombie()
	{
		HP = 3;
		attack = 6;
		type = BUCKETHEADZOMBIE;
	}
};