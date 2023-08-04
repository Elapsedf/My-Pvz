#pragma once
#include<iostream>
#include <graphics.h>		// 引用图形库头文件
#include<vector>
#include<ctime>
#include<string>
#include <stdio.h>
#include <cmath>
#include <mmsystem.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#pragma warning (disable:4996)
#pragma comment( lib, "MSIMG32.LIB")
#pragma comment( lib, "winmm.lib")
using namespace std;
#define GRASS 0

extern IMAGE potatoBoom;		//定义各种图片
extern IMAGE potato;
extern IMAGE grave[8];
extern IMAGE hammer[13];
extern IMAGE tmpImg;
extern IMAGE tmpImg2;
extern IMAGE potaotoMinePictures[8];
extern IMAGE iceshroomPictures[11];
extern IMAGE gravebusterPictures[28];
extern IMAGE sunPictures[22];
extern IMAGE normalZombieWalkPictures[47];
extern IMAGE normalZombieEmergePictures[20];
extern IMAGE normalZombieEatPictures[10];
extern IMAGE coneheadZombieWalkPictures[47];
extern IMAGE coneheadZombieEmergePictures[20];
extern IMAGE coneheadZombieEatPictures[10];
extern IMAGE bucketheadZombieWalkPictures[47];
extern IMAGE bucketheadZombieEmergePictures[20];
extern IMAGE bucketheadZombieEatPictures[10];
extern IMAGE plantsBar;
extern IMAGE menu;
extern IMAGE background;
extern IMAGE selectID;
extern IMAGE iceTrap;
extern IMAGE snow;
extern IMAGE lawnmower;
extern IMAGE loseGame;
extern IMAGE winGame;
extern IMAGE bang;
// 游戏参数
extern int mapState[32][32];		// 地图状态。0：空，1：墓碑，2：地雷（没出土），3：地雷（已出土），4：寒冰菇
struct coordinate			//坐标结构！
{
	int x;
	int y;
};
extern coordinate xys[32][32];	//地图？
extern int currentSunshine;

extern double normalfrequency;
extern double coneheadfrequency;
extern double bucketheadfrequency;
extern double SunsFrequency;
extern int isNewGame;
extern int isHitting;
extern int hammerRadius;
extern int drawingHint;
extern int hintCountDown;
extern int snowCountDown;
extern int graveNum;
extern int Win1Lose2;

void loadImages(IMAGE imgs[], const char path[], int n, int begin);
void loading();
void transparentImage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
void addIce(IMAGE* targetImage, IMAGE* srcImage, int addRed = 0, int addGreen = 0, int addBlue = 50);
void HpSleep(int ms);
template<class T>
class Node
{
public:
	T* content;
	Node* next = NULL;
	Node(T* t)
	{
		content = t;
	}
};

template<class T>
class LinkList
{
public:
	Node<T>* head;
	Node<T>* tail;

	LinkList()
	{
		head = NULL;
		tail = NULL;
	};

	LinkList(Node<T> node)
	{
		head = node;
		tail = node;
	};

	~LinkList()
	{
		DeleteAllNode();
	}

	void InsertNode(T* t)
	{
		Node<T>* node = new Node<T>(t);
		if (head == NULL)
		{
			head = node;
			tail = node;
		}
		else
		{
			tail->next = node;
			tail = node;
		}
	};

	void DeleteNode(int No)
	{
		Node<T>* cur = head, * pre = NULL;
		while (cur != NULL && cur->content->No != No)
		{
			pre = cur;
			cur = cur->next;
		}

		if (pre == NULL)
		{
			head = cur->next;
		}
		else if (cur == NULL)
		{
			cout << "没有找到符合条件的结点！" << endl;
			return;
		}
		else
		{
			pre->next = cur->next;
		}

		if (cur == tail)
		{
			tail = pre;
		}
		delete cur;
	};

	void DeleteAllNode()
	{
		Node<T>* cur = head, * pre = NULL;
		while (tail != NULL)
		{
			pre = cur;
			cur = cur->next;
			DeleteNode(pre->content->No);
		}
	};
};
