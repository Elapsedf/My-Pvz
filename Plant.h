#pragma once

#include"Zombie.h"
#define POTATO 9	//δ����
#define POTATOMINE 10	//����
#define POTATOBOOM 11	//��ը
#define GRAVEBUSTER_GRAVE1 12
#define GRAVEBUSTER_GRAVE2 13
#define GRAVEBUSTER_GRAVE3 14
#define GRAVEBUSTER_GRAVE4 15
#define GRAVEBUSTER_GRAVE5 16
#define GRAVEBUSTER_GRAVE6 17
#define GRAVEBUSTER_GRAVE7 18
#define GRAVEBUSTER_GRAVE8 19
#define ICESHROOM 20
extern int PlantNum;		//ֲ��ʵʱ������ע�����ȫ�ֱ�����
extern int SunNum;
class Plant {
public:
	int type;
	int HP;				//����ֲ���в�ͬѪ����
	int frameNo;		//ͬ��ֲ���е���ʼ��㣨ͼƬ��λ��
	int SunCost;
	int No;				//ֲ����plant�е�λ��
	int x;	
	int y;
	int changeFrameCountDown;	//�ı���̬��ʱ��

	Plant()
	{
		No = PlantNum;		
		PlantNum++;
		
		//HP = 6;
	}
	~Plant() {}
	//virtual void ChangeFrame(int x, int y, Node<Plant>*& cur) = 0;
	void playplant()
	{
		mciSendString("play ./Music/plant.mp3 from 0", 0, 0, 0);
	}
};
class PotatoMine : public Plant
{
public:
	int underCountDown = 400;
	int boomCountDown = 50;

	PotatoMine()
	{
		SunCost = 25;
		HP = 6;
		frameNo = 0;
		changeFrameCountDown = 5;
		type = POTATOMINE;
	}
	void ChangeFrame(int x, int y, Node<Plant>*&cur);
	void playdirt_rise()
	{
		mciSendString("play ./Music/dirt_rise.mp3 from 0 ", 0, 0, 0);
	}
	void UnderLand(int i, int j, int (&mapState)[32][32]);
	void Boom(int i, int j, int(&mapState)[32][32], LinkList<Plant>&plants);
};

// Ĺ��������
class GraveBuster : public Plant
{
public:
	GraveBuster()
	{
		SunCost = 75;
		HP = 12;
		frameNo = 1;
		changeFrameCountDown = 5;
		type = GRAVEBUSTER_GRAVE1;
	}
	void EatGrave(int x, int y, Node<Plant>*& cur, LinkList<Plant>& plants, int i, int j, int(&mapState)[32][32]);
};

// ������
class IceShroom : public Plant
{
public:
	int frozenCountDown = 200;
	int slowingCountDown = 1000;

	IceShroom()
	{
		HP = 12;
		SunCost = 75;
		frameNo = 0;
		changeFrameCountDown = 5;
		type = ICESHROOM;
	}
	void playshoop()
	{
		mciSendString("play ./Music/shoop.mp3 from 0 ", 0, 0, 0);
	}
	void Shoop(int x, int y, Node<Plant>*& cur, LinkList<Plant>& plants, LinkList<Zombie>& zombies, int i, int j, int(&mapState)[32][32]);
};
class Sun
{
public:
	int x;
	int y;
	int frame;			//��Ӧ��Ƭ�Ľ��
	int No;				//��Ӧ�����еĽ��
	int changeFrameCountDown;	//�ı�״̬�ļ�ʱ��
	int goToCount;
	int goToCountFrame;
	int tempX;
	int tempY;

	Sun(int x, int y)
	{
		frame = 0;
		No = SunNum;
		SunNum++;
		this->x = x;
		this->y = y;
		this->tempX = x;
		this->tempY = y;
		changeFrameCountDown = 5;
		goToCount = 0;
		goToCountFrame = 10;
	}
	int paintsun(Node<Sun>*& cur, Node<Sun>*& next, LinkList<Sun>&suns);
	void playsunshine()
	{
		mciSendString("play ./Music/sunshine.mp3 from 0", 0, 0, 0);
	}
};