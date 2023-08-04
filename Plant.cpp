#include"Plant.h"
int PlantNum = 0;		//植物实时数量，注意设成全局变量！
int SunNum = 0;			//太阳数量
void PotatoMine::ChangeFrame(int x, int y, Node<Plant>*&cur)	//指针的指针，因为传的是一个指针进来！
{		
	transparentImage(NULL, x, y, &potaotoMinePictures[cur->content->frameNo]);
	cur->content->changeFrameCountDown--;		//改变红灯的时间
	if	(cur->content->changeFrameCountDown == 0)	//
	{
		cur->content->changeFrameCountDown = 20;
		cur->content->frameNo++;
		if	(cur->content->frameNo == 7)
		{
			cur->content->frameNo = 0;		//如此不断循环，直至有僵尸触碰
		}
	}
}
void PotatoMine::UnderLand(int i, int j, int (&mapState)[32][32])
{
	underCountDown--;		//在地底下的时间--
	if (underCountDown == 0)
	{
		mapState[i][j] = POTATOMINE;		//露出地面
		playdirt_rise();
	}
}
void PotatoMine::Boom(int i, int j, int(&mapState)[32][32], LinkList<Plant>&plants)
{
	boomCountDown--;		//爆炸状态时间
	if (boomCountDown == 0)
	{
		plants.DeleteNode(this->No);
		mapState[i][j] = GRASS;
	}
}
void GraveBuster::EatGrave(int x, int y, Node<Plant>* &cur, LinkList<Plant>& plants, int i, int j, int(&mapState)[32][32])	
{		//对指针的引用！但其实也有另外一种实现方式，即指针的指针（原先版本）但考虑到引用效率更高，于是更改之
	transparentImage(NULL, x, y, &gravebusterPictures[cur->content->frameNo]);
	cur->content->changeFrameCountDown--;		//
	if (cur->content->changeFrameCountDown == 0)
	{
		cur->content->changeFrameCountDown = 10;
		cur->content->frameNo++;
		if (cur->content->frameNo > 27)		//吃完墓碑
		{
			plants.DeleteNode(cur->content->No);	//删除结点
			mapState[i][j] = GRASS;
			graveNum--;
			if (graveNum == 5)		//墓碑数量越小，爆阳光概率越大
			{
				SunsFrequency = 0.2;
				normalfrequency = 0.003;
				coneheadfrequency = 0.0035;
				bucketheadfrequency = 0.0038;
			}
			else if (graveNum == 3)
			{
				SunsFrequency = 0.4;
				normalfrequency = 0.006;
				coneheadfrequency = 0.0065;
				bucketheadfrequency = 0.0068;
			}
		}
	}
}
void IceShroom::Shoop(int x, int y, Node<Plant>* & cur, LinkList<Plant>& plants, LinkList<Zombie>& zombies,int i, int j, int(&mapState)[32][32])//同样，对指针的引用，但其实
{
	transparentImage(NULL, x, y, &iceshroomPictures[cur->content->frameNo]);
	cur->content->changeFrameCountDown--;
	if (cur->content->changeFrameCountDown == 0)
	{
		cur->content->changeFrameCountDown = 8;
		cur->content->frameNo++;
		if (cur->content->frameNo > 10)
		{
			plants.DeleteNode(cur->content->No);
			mapState[i][j] = 0;
			snowCountDown = 20;
			Node<Zombie>* cur = zombies.head;		//施加冰冻效果
			while (cur != NULL)
			{
				cur->content->isFrozen = 200;
				cur = cur->next;
			}
		}
	}
}
int Sun::paintsun(Node<Sun>* &cur, Node<Sun>* & next, LinkList<Sun>&suns)
{
	int flag = 0;
	transparentImage(NULL, x, y, &sunPictures[frame]);
	changeFrameCountDown--;
	if (changeFrameCountDown == 0)
	{
		changeFrameCountDown = 5;
		frame++;
		if (frame == 22)frame = 0;
		if (goToCount == 1)
		{
			x = tempX / 10 * goToCountFrame;
			y = tempY / 10 * goToCountFrame;
			goToCountFrame--;
			if (goToCountFrame == 0)
			{
				next = cur->next;
				suns.DeleteNode(No);
				cur = next;
				currentSunshine += 25;
				flag = 1;
				return flag;		//返回调用继续continue；
			}
		}
	}
	return flag;
}