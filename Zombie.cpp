#include"Zombie.h"
int ZombieNum = 0;
double GroanFrequency = 0.0005;	//喘息频率
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
//		if (type == NORMALZOMBIE)		//根据僵尸类型生成僵尸
//			tmpImg = normalZombieEmergePictures[frameNo];
//		else if (type == CONEHEADZOMBIE)
//			tmpImg = coneheadZombieEmergePictures[frameNo];
//		else
//			tmpImg = bucketheadZombieEmergePictures[frameNo];
//
//		transparentImage(NULL, location, xys[row][0].y - 40, &tmpImg);
//		frameNo--;
//		if (frameNo == 0)		//在播放完僵尸出现后，僵尸往前走动
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
//		if (isFrozen)		//冻住
//		{
//			addIce(&tmpImg2, &tmpImg);
//			transparentImage(NULL, location, xys[row][0].y - 40, &tmpImg2);
//		}
//		else if (isSlowed)	//减速
//		{
//			addIce(&tmpImg2, &tmpImg);
//			transparentImage(NULL, location, xys[row][0].y - 40, &tmpImg2);
//			changeFrameCountDown -= 1;
//			if (changeFrameCountDown <= 0)
//			{
//				changeFrameCountDown = 6;		//每走一步的时间
//				location -= 1;
//				frameNo++;
//				if (frameNo > 46)			//播放走路图片
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
//	// 判断是否冻住
//	if (isFrozen > 0)
//	{
//		isFrozen--;
//		if (isFrozen == 0)	isSlowed = 400;
//		transparentImage(NULL, location + 100, xys[row][0].y + 70, &iceTrap);
//	}
//	// 判断是否减速
//	if (isSlowed > 0)
//	{
//		isSlowed--;
//	}
//	// 如果僵尸走到最左边且此行有除草机
//	if (location < -50 && lawnmowers[row]->isOut == 0)
//	{
//		lawnmowers[row]->isActivated = 1;
//		mciSendString("play lawnmower from 0", 0, 0, 0);
//	}
//	//// 如果僵尸前面有植物
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
//	// 如果僵尸前面有除草机
//	if (lawnmowers[row]->isOut == 0 && location < lawnmowers[row]->location - 30)
//	{
//		next = cur->next;
//		zombies.DeleteNode(No);
//		generateSunshine(location, xys[row][0].y);
//		cur = next;		//？
//		return;
//	}
//}