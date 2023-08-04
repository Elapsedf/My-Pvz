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
extern char username[200];		//�洢�û�
enum  CURSORFLAG
{
	Chammer,
	CpotatoMine,
	Ciceshroom,
	Cgravebuster
};
extern CURSORFLAG cursor;
void init();		//��ʼ��
void PaintPlantsAndGraves();	//����ֲ����Ĺ��
void PaintZombies();
void PaintNames();
void getFiles(string path);
template <class T>
Node<T>* findno(int i, int j, LinkList<T>& p1);

void readArchive(char name[]);	//����������֮ǰ���û�����
void writeArchive(char name[]);	//�浵

void generateSunshine(int x, int y);		//
void PaintSuns();
void PaintBangs();
void PaintCursor();
void RandomGraves();
void RandomZombies();
void drawHint();
void beginGame();
