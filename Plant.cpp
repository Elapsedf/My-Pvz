#include"Plant.h"
int PlantNum = 0;		//ֲ��ʵʱ������ע�����ȫ�ֱ�����
int SunNum = 0;			//̫������
void PotatoMine::ChangeFrame(int x, int y, Node<Plant>*&cur)	//ָ���ָ�룬��Ϊ������һ��ָ�������
{		
	transparentImage(NULL, x, y, &potaotoMinePictures[cur->content->frameNo]);
	cur->content->changeFrameCountDown--;		//�ı��Ƶ�ʱ��
	if	(cur->content->changeFrameCountDown == 0)	//
	{
		cur->content->changeFrameCountDown = 20;
		cur->content->frameNo++;
		if	(cur->content->frameNo == 7)
		{
			cur->content->frameNo = 0;		//��˲���ѭ����ֱ���н�ʬ����
		}
	}
}
void PotatoMine::UnderLand(int i, int j, int (&mapState)[32][32])
{
	underCountDown--;		//�ڵص��µ�ʱ��--
	if (underCountDown == 0)
	{
		mapState[i][j] = POTATOMINE;		//¶������
		playdirt_rise();
	}
}
void PotatoMine::Boom(int i, int j, int(&mapState)[32][32], LinkList<Plant>&plants)
{
	boomCountDown--;		//��ը״̬ʱ��
	if (boomCountDown == 0)
	{
		plants.DeleteNode(this->No);
		mapState[i][j] = GRASS;
	}
}
void GraveBuster::EatGrave(int x, int y, Node<Plant>* &cur, LinkList<Plant>& plants, int i, int j, int(&mapState)[32][32])	
{		//��ָ������ã�����ʵҲ������һ��ʵ�ַ�ʽ����ָ���ָ�루ԭ�Ȱ汾�������ǵ�����Ч�ʸ��ߣ����Ǹ���֮
	transparentImage(NULL, x, y, &gravebusterPictures[cur->content->frameNo]);
	cur->content->changeFrameCountDown--;		//
	if (cur->content->changeFrameCountDown == 0)
	{
		cur->content->changeFrameCountDown = 10;
		cur->content->frameNo++;
		if (cur->content->frameNo > 27)		//����Ĺ��
		{
			plants.DeleteNode(cur->content->No);	//ɾ�����
			mapState[i][j] = GRASS;
			graveNum--;
			if (graveNum == 5)		//Ĺ������ԽС�����������Խ��
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
void IceShroom::Shoop(int x, int y, Node<Plant>* & cur, LinkList<Plant>& plants, LinkList<Zombie>& zombies,int i, int j, int(&mapState)[32][32])//ͬ������ָ������ã�����ʵ
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
			Node<Zombie>* cur = zombies.head;		//ʩ�ӱ���Ч��
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
				return flag;		//���ص��ü���continue��
			}
		}
	}
	return flag;
}