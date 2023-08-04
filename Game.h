#pragma once

#include"Plant.h"
#include<io.h>
extern LinkList<Sun> suns;
extern LinkList<Plant> plants;
extern LinkList<Zombie> zombies;
extern LinkList<Bang> bangs;
extern Lawnmower* lawnmowers[5];
extern vector<string> files;
extern ExMessage mousemsg;
extern RECT rect;
extern char sunshineNum[10];
extern char username[200];		//存储用户
enum  CURSORFLAG
{
	Chammer,
	CpotatoMine,
	Ciceshroom,
	Cgravebuster
};
extern CURSORFLAG cursor;
void init();		//初始化
void PaintPlantsAndGraves();	//画出植物与墓碑
void PaintZombies();
void PaintNames();
void getFiles(string path);
template <class T>
Node<T>* findno(int i, int j, LinkList<T>& p1);

void readArchive(char name[]);	//读档案！即之前的用户！！
void writeArchive(char name[]);	//存档

void generateSunshine(int x, int y);		//
void PaintSuns();
void PaintBangs();
void PaintCursor();
void RandomGraves();
void RandomZombies();
void drawHint();
void beginGame();
