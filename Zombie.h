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
extern double GroanFrequency;	//喘息频率
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
	int No;		//node，但防止与node混淆 
	int changeFrameCountDown;
	int isFrozen;
	int isSlowed;
	int type;
	int attack;	//伤害

	Zombie()
	{
		No = ZombieNum;			//当前末结点
		ZombieNum++;	
		isFrozen = 0;		//是否被冰冻
		isSlowed = 0;
		height = 115;			// 僵尸图像高度
		frameNo = 19;			// 表示播放到第几帧
		emerge1walk2eat3 = 1;	// 正在冒出来用 1 表示，正在行走用 2 表示，正在吃植物用 3 表示
		HP = 6;
		changeFrameCountDown = 10;
	}
	void playdirt_rise()
	{
		mciSendString("play ./Music/dirt_rise.mp3 from 0", 0, 0, 0);
	}
	//void paintzombies(Node<Zombie>*&cur, Node<Zombie>*&next, LinkList<Zombie>zombies, Lawnmower *&lawnmowers);
};
class NormalZombie : public Zombie			//普通僵尸
{
public:
	NormalZombie()
	{
		HP = 1;
		attack = 2;
		type = NORMALZOMBIE;
	}
};

class ConeheadZombie : public Zombie		//路障僵尸
{
public:
	ConeheadZombie()
	{
		HP = 2;
		attack = 4;
		type = CONEHEADZOMBIE;
	}
};

class BucketheadZombie : public Zombie		//铁桶僵尸
{
public:
	BucketheadZombie()
	{
		HP = 3;
		attack = 6;
		type = BUCKETHEADZOMBIE;
	}
};