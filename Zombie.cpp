#include"Zombie.h"
int ZombieNum = 0;
double GroanFrequency = 0.0005;	//��ϢƵ��
//void Zombie::paintzombies(Node<Zombie>*& cur, Node<Zombie>*& next, LinkList<Zombie>zombies, Lawnmower*& lawnmowers)
//{
//	
//	if (location < -150)		//?
//	{
//		cur = cur->next;
//		zombies.DeleteNode(No);
//		return;
//	}
//	
//	if (emerge1walk2eat3 == 1)
//	{	
//		if (type == NORMALZOMBIE)		//���ݽ�ʬ�������ɽ�ʬ
//			tmpImg = normalZombieEmergePictures[frameNo];
//		else if (type == CONEHEADZOMBIE)
//			tmpImg = coneheadZombieEmergePictures[frameNo];
//		else
//			tmpImg = bucketheadZombieEmergePictures[frameNo];
//
//		transparentImage(NULL, location, xys[row][0].y - 40, &tmpImg);
//		frameNo--;
//		if (frameNo == 0)		//�ڲ����꽩ʬ���ֺ󣬽�ʬ��ǰ�߶�
//		{
//			emerge1walk2eat3 = 2;
//		}
//	}
//	else if (emerge1walk2eat3 == 2)
//	{
//		if (type == NORMALZOMBIE)
//			tmpImg = normalZombieWalkPictures[frameNo];
//		else if (type == CONEHEADZOMBIE)
//			tmpImg = coneheadZombieWalkPictures[frameNo];
//		else
//			tmpImg = bucketheadZombieWalkPictures[frameNo];
//
//		if (isFrozen)		//��ס
//		{
//			addIce(&tmpImg2, &tmpImg);
//			transparentImage(NULL, location, xys[row][0].y - 40, &tmpImg2);
//		}
//		else if (isSlowed)	//����
//		{
//			addIce(&tmpImg2, &tmpImg);
//			transparentImage(NULL, location, xys[row][0].y - 40, &tmpImg2);
//			changeFrameCountDown -= 1;
//			if (changeFrameCountDown <= 0)
//			{
//				changeFrameCountDown = 6;		//ÿ��һ����ʱ��
//				location -= 1;
//				frameNo++;
//				if (frameNo > 46)			//������·ͼƬ
//				{
//					frameNo = 0;
//				}
//			}
//		}
//		else
//		{
//			transparentImage(NULL, location, xys[row][0].y - 40, &tmpImg);
//			changeFrameCountDown -= 2;
//			if (changeFrameCountDown <= 0)
//			{
//				changeFrameCountDown = 6;
//				location -= 2;
//				frameNo++;
//				if (frameNo > 46)
//				{
//					frameNo = 0;
//				}
//			}
//		}
//	}
//	else if (emerge1walk2eat3 == 3)
//	{
//		/*if (type == NORMALZOMBIE)tmpImg = normalZombieEatPictures[frameNo];
//		else if (type == CONEHEADZOMBIE)tmpImg = coneheadZombieEatPictures[frameNo];
//		else tmpImg = bucketheadZombieEatPictures[frameNo];
//		if (isFrozen) {
//			addIce(&tmpImg2, &tmpImg);
//			transparentImage(NULL, location, xys[row][0].y - 40, &tmpImg2);
//		}
//		else if (isSlowed) {
//			addIce(&tmpImg2, &tmpImg);
//			transparentImage(NULL, location, xys[row][0].y - 40, &tmpImg2);
//			changeFrameCountDown -= 1;
//			if (changeFrameCountDown <= 0) {
//				changeFrameCountDown = 6;
//				location -= 1;
//				frameNo++;
//				if (frameNo > 46) {
//					frameNo = 0;
//				}
//			}
//		}
//		else {
//			transparentImage(NULL, location, xys[row][0].y - 40, &tmpImg);
//			changeFrameCountDown -= 2;
//			if (changeFrameCountDown <= 0) {
//				changeFrameCountDown = 25;
//				frameNo++;
//			}
//		}*/
//	}
//	// �ж��Ƿ�ס
//	if (isFrozen > 0)
//	{
//		isFrozen--;
//		if (isFrozen == 0)	isSlowed = 400;
//		transparentImage(NULL, location + 100, xys[row][0].y + 70, &iceTrap);
//	}
//	// �ж��Ƿ����
//	if (isSlowed > 0)
//	{
//		isSlowed--;
//	}
//	// �����ʬ�ߵ�������Ҵ����г��ݻ�
//	if (location < -50 && lawnmowers[row]->isOut == 0)
//	{
//		lawnmowers[row]->isActivated = 1;
//		mciSendString("play lawnmower from 0", 0, 0, 0);
//	}
//	//// �����ʬǰ����ֲ��
//	//Node<Plant>* curPlant = plants.head,*pre;
//	//while (curPlant != NULL)
//	//{
//	//	Plant* plant = curPlant->content;
//	//	if (row == plant->x
//	//		&& location < xys[plant->x][plant->y].x- 25
//	//		&& location > xys[plant->x][plant->y-1].x-25)
//	//	{
//	//		if (emerge1walk2eat3 == 2)
//	//		{
//	//			emerge1walk2eat3 = 3;
//	//			frameNo = 0;
//	//			mciSendString("play ./Music/chomp.mp3 from 0", 0, 0, 0);
//	//		}
//	//		if (emerge1walk2eat3 == 3 && frameNo > 9)
//	//		{
//	//			frameNo = 0;
//	//			mciSendString("play ./Music/chomp.mp3 from 0", 0, 0, 0);
//	//			plant->HP--;
//	//			if (plant->HP == 0)
//	//			{
//	//				pre = curPlant;
//	//				curPlant = curPlant->next;
//	//				plants.DeleteNode(pre->content->No);
//	//				emerge1walk2eat3 = 2;
//	//				continue;
//	//			}
//	//		}
//	//	}
//	//	curPlant = curPlant->next;
//	//}
//	// �����ʬǰ���г��ݻ�
//	if (lawnmowers[row]->isOut == 0 && location < lawnmowers[row]->location - 30)
//	{
//		next = cur->next;
//		zombies.DeleteNode(No);
//		generateSunshine(location, xys[row][0].y);
//		cur = next;		//��
//		return;
//	}
//}