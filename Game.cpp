#include"Game.h"
LinkList<Sun> suns;
LinkList<Plant> plants;
LinkList<Zombie> zombies;
LinkList<Bang> bangs;
Lawnmower* lawnmowers[5];
vector<string> files;
ExMessage mousemsg;
RECT rect = { 0, 500, 820, 600 };
char sunshineNum[10];
char username[200];		//�洢�û�
CURSORFLAG cursor;
template <class T>
Node<T>* findno(int i, int j, LinkList<T>& p1)
{
	Node<T>* cur = p1.head;
	while (cur != NULL)
	{
		if (cur->content->x == i && cur->content->y == j)
		{
			break;
		}
		else cur = cur->next;
	}
	return cur;
}
void init()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			mapState[i][j] = GRASS;
		}
	}

	currentSunshine = 0;
	plants.DeleteAllNode();
	zombies.DeleteAllNode();
	suns.DeleteAllNode();
	bangs.DeleteAllNode();

	for (int i = 0; i < 5; i++)
	{
		lawnmowers[i] = new Lawnmower();
	}

	normalfrequency = 0.002;
	coneheadfrequency = 0.0025;
	bucketheadfrequency = 0.0028;
	SunsFrequency = 0.05;
	isNewGame = 1;
	isHitting = 0;
	hammerRadius = 0;
	drawingHint = 0;
	hintCountDown = 70;
	snowCountDown = 0;
	graveNum = 0;
	Win1Lose2 = 0;
}
void PaintPlantsAndGraves()
{
	// ��ֲ���Ĺ��
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			switch (mapState[i][j])
			{
			case GRASS:
				break;
			case GRAVE1:
			{
				transparentImage(NULL, xys[i][j].x - 5, xys[i][j].y, &grave[0]);
				break;
			}
			case GRAVE2:
			{
				transparentImage(NULL, xys[i][j].x - 5, xys[i][j].y, &grave[1]);
				break;
			}
			case GRAVE3:
			{
				transparentImage(NULL, xys[i][j].x - 5, xys[i][j].y, &grave[2]);
				break;
			}
			case GRAVE4:
			{
				transparentImage(NULL, xys[i][j].x - 5, xys[i][j].y, &grave[3]);
				break;
			}
			case GRAVE5:
			{
				transparentImage(NULL, xys[i][j].x - 5, xys[i][j].y, &grave[4]);
				break;
			}
			case GRAVE6:
			{
				transparentImage(NULL, xys[i][j].x - 5, xys[i][j].y, &grave[5]);
				break;
			}
			case GRAVE7:
			{
				transparentImage(NULL, xys[i][j].x - 5, xys[i][j].y, &grave[6]);
				break;
			}
			case GRAVE8:
			{
				transparentImage(NULL, xys[i][j].x - 5, xys[i][j].y, &grave[7]);
				break;
			}
			case POTATO:
			{
				transparentImage(NULL, xys[i][j].x, xys[i][j].y + 37, &potato);	
				Node<Plant>* cur = findno<Plant>(i, j, plants);
				if (cur != NULL)
				{
					PotatoMine* potato = static_cast<PotatoMine*>(cur->content);	//ǿ������ת��
					potato->UnderLand(i,j,mapState);
					//if (potato->underCountDown == 0)
					//{
					//	mapState[i][j] = POTATOMINE;		//¶������
					//	potato->playdirt_rise();
					//}
				}
				break;
			}
			case POTATOMINE:
			{
				Node<Plant>* cur = findno<Plant>(i, j, plants);

				if (cur != NULL)
				{
					PotatoMine* potato = static_cast<PotatoMine*>(cur->content);	//ǿ������ת��
					potato->ChangeFrame(xys[i][j].x, xys[i][j].y + 40, cur);					
				}
				break;
			}
			case POTATOBOOM:
			{
				transparentImage(NULL, xys[i][j].x - 25, xys[i][j].y + 20, &potatoBoom);
				Node<Plant>* cur = findno<Plant>(i, j, plants);
				if (cur != NULL)
				{
					PotatoMine* potato = static_cast<PotatoMine*>(cur->content);//ǿ������ת��
					potato->Boom(i, j, mapState, plants);
				}
				break;
			}
			case GRAVEBUSTER_GRAVE1:
				transparentImage(NULL, xys[i][j].x - 5, xys[i][j].y, &grave[0]);	//�ȼ��س���Ӧ��Ĺ��
				goto label;
			case GRAVEBUSTER_GRAVE2:
				transparentImage(NULL, xys[i][j].x - 5, xys[i][j].y, &grave[1]);
				goto label;
			case GRAVEBUSTER_GRAVE3:
				transparentImage(NULL, xys[i][j].x - 5, xys[i][j].y, &grave[2]);
				goto label;
			case GRAVEBUSTER_GRAVE4:
				transparentImage(NULL, xys[i][j].x - 5, xys[i][j].y, &grave[3]);
				goto label;
			case GRAVEBUSTER_GRAVE5:
				transparentImage(NULL, xys[i][j].x - 5, xys[i][j].y, &grave[4]);
				goto label;
			case GRAVEBUSTER_GRAVE6:
				transparentImage(NULL, xys[i][j].x - 5, xys[i][j].y, &grave[5]);
				goto label;
			case GRAVEBUSTER_GRAVE7:
				transparentImage(NULL, xys[i][j].x - 5, xys[i][j].y, &grave[6]);
				goto label;
			case GRAVEBUSTER_GRAVE8:
				transparentImage(NULL, xys[i][j].x - 5, xys[i][j].y, &grave[7]);	//��������ΪʲôҪ-5��
				goto label;
				{
				label:
					Node<Plant>* cur = findno<Plant>(i, j, plants);
					if (cur != NULL)
					{
						GraveBuster* grave = static_cast<GraveBuster*>(cur->content);
						grave->EatGrave(xys[i][j].x - 10,  xys[i][j].y - 10, cur, plants, i, j, mapState);
					}
					break;
				}
			case ICESHROOM:
			{
				Node<Plant>* cur = findno<Plant>(i, j, plants);
				if (cur != NULL)
				{
					IceShroom* iceshroom = static_cast<IceShroom*>(cur->content);
					iceshroom->Shoop(xys[i][j].x, xys[i][j].y + 15, cur, plants,zombies, i, j, mapState);
				}
				break;
			}
			}
		}
	}
}
void PaintZombies()
{
	// ����ʬ
	Node<Zombie>* cur = zombies.head, * next =NULL;
	while (cur != NULL)
	{
		Zombie* zombieptr = cur->content;
		if (zombieptr->location < -150)		//?
		{
			cur = cur->next;
			zombies.DeleteNode(zombieptr->No);
			continue;
		}

		if (zombieptr->emerge1walk2eat3 == 1)
		{
			if (zombieptr->type == NORMALZOMBIE)		//���ݽ�ʬ�������ɽ�ʬ
				tmpImg = normalZombieEmergePictures[zombieptr->frameNo];
			else if (zombieptr->type == CONEHEADZOMBIE)
				tmpImg = coneheadZombieEmergePictures[zombieptr->frameNo];
			else
				tmpImg = bucketheadZombieEmergePictures[zombieptr->frameNo];

			transparentImage(NULL, zombieptr->location, xys[zombieptr->row][0].y - 40, &tmpImg);
			zombieptr->frameNo--;
			if (zombieptr->frameNo == 0)		//�ڲ����꽩ʬ���ֺ󣬽�ʬ��ǰ�߶�
			{
				zombieptr->emerge1walk2eat3 = 2;
			}
		}
		else if (zombieptr->emerge1walk2eat3 == 2)
		{
			if (zombieptr->type == NORMALZOMBIE)
				tmpImg = normalZombieWalkPictures[zombieptr->frameNo];
			else if (zombieptr->type == CONEHEADZOMBIE)
				tmpImg = coneheadZombieWalkPictures[zombieptr->frameNo];
			else
				tmpImg = bucketheadZombieWalkPictures[zombieptr->frameNo];

			if (zombieptr->isFrozen)		//��ס
			{
				addIce(&tmpImg2, &tmpImg);
				transparentImage(NULL, zombieptr->location, xys[zombieptr->row][0].y - 40, &tmpImg2);
			}
			else if (zombieptr->isSlowed)	//����
			{
				addIce(&tmpImg2, &tmpImg);
				transparentImage(NULL, zombieptr->location, xys[zombieptr->row][0].y - 40, &tmpImg2);
				zombieptr->changeFrameCountDown -= 1;
				if (zombieptr->changeFrameCountDown <= 0)
				{
					zombieptr->changeFrameCountDown = 6;		//ÿ��һ����ʱ��
					zombieptr->location -= 1;
					zombieptr->frameNo++;
					if (zombieptr->frameNo > 46)			//������·ͼƬ
					{
						zombieptr->frameNo = 0;
					}
				}
			}
			else
			{
				transparentImage(NULL, zombieptr->location, xys[zombieptr->row][0].y - 40, &tmpImg);
				zombieptr->changeFrameCountDown -= 2;
				if (zombieptr->changeFrameCountDown <= 0)
				{
					zombieptr->changeFrameCountDown = 6;
					zombieptr->location -= 2;
					zombieptr->frameNo++;
					if (zombieptr->frameNo > 46)
					{
						zombieptr->frameNo = 0;
					}
				}
			}
		}
		else if (zombieptr->emerge1walk2eat3 == 3)
		{
			if (zombieptr->type == NORMALZOMBIE)tmpImg = normalZombieEatPictures[zombieptr->frameNo];
			else if (zombieptr->type == CONEHEADZOMBIE)tmpImg = coneheadZombieEatPictures[zombieptr->frameNo];
			else tmpImg = bucketheadZombieEatPictures[zombieptr->frameNo];	//����ͼƬ
			if (zombieptr->isFrozen) {
				addIce(&tmpImg2, &tmpImg);
				transparentImage(NULL, zombieptr->location, xys[zombieptr->row][0].y - 40, &tmpImg2);	//�ӱ�
			}
			else if (zombieptr->isSlowed) {
				addIce(&tmpImg2, &tmpImg);
				transparentImage(NULL, zombieptr->location, xys[zombieptr->row][0].y - 40, &tmpImg2);
				zombieptr->changeFrameCountDown -= 1;		//��Ϊ�ٶȼ���
				if (zombieptr->changeFrameCountDown <= 0) {
					zombieptr->changeFrameCountDown = 6;
					//zombieptr->location -= 1;
					zombieptr->frameNo++;
					if (zombieptr->frameNo > 9) {
						zombieptr->frameNo = 0;
					}
				}
			}
			else {
				transparentImage(NULL, zombieptr->location, xys[zombieptr->row][0].y - 40, &tmpImg);
				zombieptr->changeFrameCountDown -= 2;		//�����ٶ�
				if (zombieptr->changeFrameCountDown <= 0) {
					zombieptr->changeFrameCountDown = 6;
					zombieptr->frameNo++;
				}
			}
		}
		// �ж��Ƿ�ס
		if (zombieptr->isFrozen > 0)
		{
			zombieptr->isFrozen--;
			if (zombieptr->isFrozen == 0)	zombieptr->isSlowed = 400;
			transparentImage(NULL, zombieptr->location + 100, xys[zombieptr->row][0].y + 70, &iceTrap);
		}
		// �ж��Ƿ����
		if (zombieptr->isSlowed > 0)
		{
			zombieptr->isSlowed--;
		}
		// �����ʬ�ߵ�������Ҵ����г��ݻ�
		if (zombieptr->location < -50 && lawnmowers[zombieptr->row]->isOut == 0)
		{
			lawnmowers[zombieptr->row]->isActivated = 1;
			mciSendString("play lawnmower from 0", 0, 0, 0);
		}
		//// �����ʬǰ����ֲ��
		Node<Plant>* curPlant = plants.head,*pre;
		while (curPlant != NULL)
		{
			Plant* plant = curPlant->content;
			if (zombieptr->row == plant->x
				&& zombieptr->location < xys[plant->x][plant->y].x- 25
				&& zombieptr->location > xys[plant->x][plant->y-1].x-25)		//�ҵ���Ӧ��ֲ��
			{
				if (zombieptr->emerge1walk2eat3 == 2)			//�ı�״̬
				{
					zombieptr->emerge1walk2eat3 = 3;
					zombieptr->frameNo = 0;
					mciSendString("play ./Music/chomp.mp3 from 0", 0, 0, 0);
				}
				if (zombieptr->emerge1walk2eat3 == 3 && zombieptr->frameNo > 9)	//���ŵ��ھ���ͼƬ
				{
					zombieptr->frameNo = 0;
					mciSendString("play ./Music/chomp.mp3 from 0", 0, 0, 0);
					plant->HP-=zombieptr->attack;
					if (plant->HP <= 0)
					{
						pre = curPlant;
						curPlant = curPlant->next;
						int state = mapState[pre->content->x][pre->content->y];		//�ж�ҧ���ǲ���Ĺ��
						if (state >= 12 && state <= 19) {
							mapState[plant->x][plant->y] = state - 11;//��Ӧ��ԭ����Ĺ��
						}
						else {
							mapState[plant->x][plant->y] = GRASS;		//������Ĺ�����������Ϊ�ݵ�
						}
						//mapState[pre->content->x][pre->content->y] = GRASS;
						plants.DeleteNode(pre->content->No);	//û��ɾ��ͼƬ��
						zombieptr->emerge1walk2eat3 = 2;
						continue;
					}
				}
				//curPlant = curPlant->next;
			}
			curPlant = curPlant->next;
		}
		// �����ʬǰ���г��ݻ�
		if (lawnmowers[zombieptr->row]->isOut == 0 && zombieptr->location < lawnmowers[zombieptr->row]->location - 30)
		{
			next = cur->next;
			zombies.DeleteNode(zombieptr->No);
			generateSunshine(zombieptr->location, xys[zombieptr->row][0].y);
			cur = next;		//��
			continue;
		}
		cur = cur->next;
	}
}
void getFiles(string path)

{
	files.clear();
	//�ļ����  
	intptr_t hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			files.push_back(fileinfo.name);
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	files.erase(files.begin());
	files.erase(files.begin());
}
void readArchive(char name[])	//����������֮ǰ���û��������޸����ڱ�������˴�Ҫ���ģ�
{
	init();
	char path[] = "./archives/", tmppath[200] = { 0 };
	strcat(strcat(tmppath, path), name);
	FILE* fp = fopen(tmppath, "rb");
	::fread(&mapState, sizeof(mapState), 1, fp);

	for (int i = 0; i < 5; i++)
	{
		lawnmowers[i] = new Lawnmower();
		::fread(&lawnmowers[i]->location, sizeof(int), 1, fp);
		::fread(&lawnmowers[i]->isActivated, sizeof(int), 1, fp);
		::fread(&lawnmowers[i]->isOut, sizeof(int), 1, fp);
	}
	//��Ϸ����
	fread(&currentSunshine, sizeof(int), 1, fp);
	fread(&normalfrequency, sizeof(double), 1, fp);
	fread(&coneheadfrequency, sizeof(double), 1, fp);
	fread(&bucketheadfrequency, sizeof(double), 1, fp);
	fread(&SunsFrequency, sizeof(double), 1, fp);
	fread(&isNewGame, sizeof(int), 1, fp);
	fread(&isHitting, sizeof(int), 1, fp);
	fread(&hammerRadius, sizeof(int), 1, fp);
	fread(&drawingHint, sizeof(int), 1, fp);
	fread(&hintCountDown, sizeof(int), 1, fp);
	fread(&snowCountDown, sizeof(int), 1, fp);
	fread(&graveNum, sizeof(int), 1, fp);
	fread(&Win1Lose2, sizeof(int), 1, fp);

	int separator;
	while (1)
	{
		fread(&separator, sizeof(int), 1, fp);
		if (separator != 1234567)
		{
			//��ȡ��ʬ
			Zombie* tmpZombie = new Zombie();
			fseek(fp, -(int)sizeof(int), SEEK_CUR);
			fread(&tmpZombie->HP, sizeof(int), 1, fp);
			fread(&tmpZombie->row, sizeof(int), 1, fp);
			fread(&tmpZombie->location, sizeof(int), 1, fp);
			fread(&tmpZombie->emerge1walk2eat3, sizeof(int), 1, fp);
			fread(&tmpZombie->frameNo, sizeof(int), 1, fp);
			fread(&tmpZombie->height, sizeof(int), 1, fp);
			fread(&tmpZombie->No, sizeof(int), 1, fp);
			fread(&tmpZombie->changeFrameCountDown, sizeof(int), 1, fp);
			fread(&tmpZombie->isFrozen, sizeof(int), 1, fp);
			fread(&tmpZombie->isSlowed, sizeof(int), 1, fp);
			fread(&tmpZombie->type, sizeof(int), 1, fp);
			fread(&tmpZombie->attack, sizeof(int), 1, fp);
			zombies.InsertNode(tmpZombie);
		}
		else break;
	}

	int tmpPlantType;
	while (1)
	{
		fread(&separator, sizeof(int), 1, fp);
		if (separator != 7654321)
		{
			fseek(fp, -(int)sizeof(int), SEEK_CUR);
			fread(&tmpPlantType, sizeof(int), 1, fp);
			switch (tmpPlantType)
			{
			case POTATOMINE:
			{
				PotatoMine* tmpPotatoMine = new PotatoMine();//?
				tmpPotatoMine->type = tmpPlantType;
				fread(&tmpPotatoMine->frameNo, sizeof(int), 1, fp);
				fread(&tmpPotatoMine->No, sizeof(int), 1, fp);
				fread(&tmpPotatoMine->x, sizeof(int), 1, fp);
				fread(&tmpPotatoMine->y, sizeof(int), 1, fp);
				fread(&tmpPotatoMine->changeFrameCountDown, sizeof(int), 1, fp);
				fread(&tmpPotatoMine->underCountDown, sizeof(int), 1, fp);
				fread(&tmpPotatoMine->boomCountDown, sizeof(int), 1, fp);
				fread(&tmpPotatoMine->HP, sizeof(int), 1, fp);
				fread(&tmpPotatoMine->SunCost, sizeof(int), 1, fp);
				plants.InsertNode(tmpPotatoMine);
				break;
			}
			case GRAVEBUSTER_GRAVE1:
			{
				GraveBuster* tmpGraveBuster = new GraveBuster();
				tmpGraveBuster->type = tmpPlantType;
				fread(&tmpGraveBuster->frameNo, sizeof(int), 1, fp);
				fread(&tmpGraveBuster->No, sizeof(int), 1, fp);
				fread(&tmpGraveBuster->x, sizeof(int), 1, fp);
				fread(&tmpGraveBuster->y, sizeof(int), 1, fp);
				fread(&tmpGraveBuster->HP, sizeof(int), 1, fp);
				fread(&tmpGraveBuster->SunCost, sizeof(int), 1, fp);
				fread(&tmpGraveBuster->changeFrameCountDown, sizeof(int), 1, fp);
				plants.InsertNode(tmpGraveBuster);
				break;
			}
			case ICESHROOM:
			{
				IceShroom* tmpIceShroom = new IceShroom();
				tmpIceShroom->type = tmpPlantType;
				fread(&tmpIceShroom->frameNo, sizeof(int), 1, fp);
				fread(&tmpIceShroom->No, sizeof(int), 1, fp);
				fread(&tmpIceShroom->x, sizeof(int), 1, fp);
				fread(&tmpIceShroom->y, sizeof(int), 1, fp);
				fread(&tmpIceShroom->changeFrameCountDown, sizeof(int), 1, fp);
				fread(&tmpIceShroom->frozenCountDown, sizeof(int), 1, fp);
				fread(&tmpIceShroom->slowingCountDown, sizeof(int), 1, fp);
				fread(&tmpIceShroom->HP, sizeof(int), 1, fp);
				fread(&tmpIceShroom->SunCost, sizeof(int), 1, fp);
				plants.InsertNode(tmpIceShroom);
				break;
			}
			}
		}
		else break;
	}

	while (1)
	{
		fread(&separator, sizeof(int), 1, fp);
		if (separator != 357421)
		{
			Bang* tmpBang = new Bang(0, 0);
			fseek(fp, -(int)sizeof(int), SEEK_CUR);
			fread(&tmpBang->No, sizeof(int), 1, fp);
			fread(&tmpBang->x, sizeof(int), 1, fp);
			fread(&tmpBang->y, sizeof(int), 1, fp);
			fread(&tmpBang->countDown, sizeof(int), 1, fp);
			bangs.InsertNode(tmpBang);
		}
		else
			break;
	}

	while (fread(&separator, sizeof(int), 1, fp))
	{
		Sun* tmpSun = new Sun(0, 0);
		fread(&tmpSun->x, sizeof(int), 1, fp);
		fread(&tmpSun->y, sizeof(int), 1, fp);
		fread(&tmpSun->frame, sizeof(int), 1, fp);
		fread(&tmpSun->No, sizeof(int), 1, fp);
		fread(&tmpSun->changeFrameCountDown, sizeof(int), 1, fp);
		fread(&tmpSun->goToCount, sizeof(int), 1, fp);
		fread(&tmpSun->goToCountFrame, sizeof(int), 1, fp);
		fread(&tmpSun->tempX, sizeof(int), 1, fp);
		fread(&tmpSun->tempY, sizeof(int), 1, fp);
		suns.InsertNode(tmpSun);
	}
	fclose(fp);
}

void writeArchive(char name[])
{
	char path[] = "./archives/", tmppath[200] = { 0 };
	strcat(strcat(tmppath, path), name);
	FILE* fp = fopen(tmppath, "wb");
	::fwrite(mapState, sizeof(mapState), 1, fp);

	for (int i = 0; i < 5; i++)
	{
		::fwrite(&lawnmowers[i]->location, sizeof(int), 1, fp);
		::fwrite(&lawnmowers[i]->isActivated, sizeof(int), 1, fp);
		::fwrite(&lawnmowers[i]->isOut, sizeof(int), 1, fp);
	}
	//��Ϸ����
	::fwrite(&currentSunshine, sizeof(int), 1, fp);
	::fwrite(&normalfrequency, sizeof(double), 1, fp);
	::fwrite(&coneheadfrequency, sizeof(double), 1, fp);
	::fwrite(&bucketheadfrequency, sizeof(double), 1, fp);
	::fwrite(&SunsFrequency, sizeof(double), 1, fp);
	::fwrite(&isNewGame, sizeof(int), 1, fp);
	::fwrite(&isHitting, sizeof(int), 1, fp);
	::fwrite(&hammerRadius, sizeof(int), 1, fp);
	::fwrite(&drawingHint, sizeof(int), 1, fp);
	::fwrite(&hintCountDown, sizeof(int), 1, fp);
	::fwrite(&snowCountDown, sizeof(int), 1, fp);
	::fwrite(&graveNum, sizeof(int), 1, fp);
	::fwrite(&Win1Lose2, sizeof(int), 1, fp);

	Node<Zombie>* curZombie = zombies.head;
	while (curZombie != NULL)
	{
		Zombie* zombie = curZombie->content;
		::fwrite(&zombie->HP, sizeof(int), 1, fp);
		::fwrite(&zombie->row, sizeof(int), 1, fp);
		::fwrite(&zombie->location, sizeof(int), 1, fp);
		::fwrite(&zombie->emerge1walk2eat3, sizeof(int), 1, fp);
		::fwrite(&zombie->frameNo, sizeof(int), 1, fp);
		::fwrite(&zombie->height, sizeof(int), 1, fp);
		::fwrite(&zombie->No, sizeof(int), 1, fp);
		::fwrite(&zombie->changeFrameCountDown, sizeof(int), 1, fp);
		::fwrite(&zombie->isFrozen, sizeof(int), 1, fp);
		::fwrite(&zombie->isSlowed, sizeof(int), 1, fp);
		::fwrite(&zombie->type, sizeof(int), 1, fp);
		::fwrite(&zombie->attack, sizeof(int), 1, fp);
		curZombie = curZombie->next;
	}

	int separator1 = 1234567;
	::fwrite(&separator1, sizeof(int), 1, fp);
	Node<Plant>* curPlant = plants.head;
	while (curPlant != NULL)
	{
		switch (curPlant->content->type)
		{
		case POTATOMINE:
		{
			PotatoMine* potatoMine = static_cast<PotatoMine*>(curPlant->content);
			::fwrite(&potatoMine->type, sizeof(int), 1, fp);
			::fwrite(&potatoMine->frameNo, sizeof(int), 1, fp);
			::fwrite(&potatoMine->No, sizeof(int), 1, fp);
			::fwrite(&potatoMine->x, sizeof(int), 1, fp);
			::fwrite(&potatoMine->y, sizeof(int), 1, fp);
			::fwrite(&potatoMine->HP, sizeof(int), 1, fp);
			::fwrite(&potatoMine->SunCost, sizeof(int), 1, fp);
			::fwrite(&potatoMine->changeFrameCountDown, sizeof(int), 1, fp);
			::fwrite(&potatoMine->underCountDown, sizeof(int), 1, fp);
			::fwrite(&potatoMine->boomCountDown, sizeof(int), 1, fp);
			break;
		}
		case ICESHROOM:
		{
			IceShroom* iceShroom = static_cast<IceShroom*>(curPlant->content);
			::fwrite(&iceShroom->type, sizeof(int), 1, fp);
			::fwrite(&iceShroom->frameNo, sizeof(int), 1, fp);
			::fwrite(&iceShroom->No, sizeof(int), 1, fp);
			::fwrite(&iceShroom->x, sizeof(int), 1, fp);
			::fwrite(&iceShroom->y, sizeof(int), 1, fp);
			::fwrite(&iceShroom->HP, sizeof(int), 1, fp);
			::fwrite(&iceShroom->SunCost, sizeof(int), 1, fp);
			::fwrite(&iceShroom->changeFrameCountDown, sizeof(int), 1, fp);
			::fwrite(&iceShroom->frozenCountDown, sizeof(int), 1, fp);
			::fwrite(&iceShroom->slowingCountDown, sizeof(int), 1, fp);
			break;
		}
		case GRAVEBUSTER_GRAVE1:
		{
			GraveBuster* graveBuster = static_cast<GraveBuster*>(curPlant->content);
			::fwrite(&graveBuster->type, sizeof(int), 1, fp);
			::fwrite(&graveBuster->frameNo, sizeof(int), 1, fp);
			::fwrite(&graveBuster->No, sizeof(int), 1, fp);
			::fwrite(&graveBuster->x, sizeof(int), 1, fp);
			::fwrite(&graveBuster->HP, sizeof(int), 1, fp);
			::fwrite(&graveBuster->SunCost, sizeof(int), 1, fp);
			::fwrite(&graveBuster->y, sizeof(int), 1, fp);
			::fwrite(&graveBuster->changeFrameCountDown, sizeof(int), 1, fp);
			break;
		}
		}
		curPlant = curPlant->next;
	}

	int separator2 = 7654321;
	::fwrite(&separator2, sizeof(int), 1, fp);
	Node<Bang>* curBang = bangs.head;
	while (curBang != NULL)
	{
		Bang* bang = curBang->content;
		::fwrite(&bang->No, sizeof(int), 1, fp);
		::fwrite(&bang->x, sizeof(int), 1, fp);
		::fwrite(&bang->y, sizeof(int), 1, fp);
		::fwrite(&bang->countDown, sizeof(int), 1, fp);
		curBang = curBang->next;
	}

	int separator3 = 357421;
	::fwrite(&separator3, sizeof(int), 1, fp);
	Node<Sun>* curSun = suns.head;
	while (curSun != NULL)
	{
		Sun* sun = curSun->content;
		::fwrite(&sun->x, sizeof(int), 1, fp);
		::fwrite(&sun->y, sizeof(int), 1, fp);
		::fwrite(&sun->frame, sizeof(int), 1, fp);
		::fwrite(&sun->No, sizeof(int), 1, fp);
		::fwrite(&sun->changeFrameCountDown, sizeof(int), 1, fp);
		::fwrite(&sun->goToCount, sizeof(int), 1, fp);
		::fwrite(&sun->goToCountFrame, sizeof(int), 1, fp);
		::fwrite(&sun->tempX, sizeof(int), 1, fp);
		::fwrite(&sun->tempY, sizeof(int), 1, fp);
		curSun = curSun->next;
	}

	fclose(fp);
}

void generateSunshine(int x, int y)
{
	// һ�����ʲ���3������
	double p = rand() / (double)RAND_MAX;
	if (p < SunsFrequency)
	{
		Sun* sunshine[3];
		for (int i = 0; i < 3; i++)
		{
			sunshine[i] = new Sun(x + 80 + rand() % 100 - 50, y + 60 + rand() % 50 - 25);
			suns.InsertNode(sunshine[i]);
		}
	}
}
void PaintSuns()
{
	Node<Sun>* cur = suns.head, * next;
	while (cur != NULL)
	{
		Sun* sun = cur->content;
		int flag=sun->paintsun(cur, next, suns);
		if (flag)
		{
			continue;
		}
		else {
			cur = cur->next;
		}
		//Sun* sun = cur->content;
		//transparentImage(NULL, sun->x, sun->y, &sunPictures[sun->frame]);
		//sun->changeFrameCountDown--;
		//if (sun->changeFrameCountDown == 0)
		//{
		//	sun->changeFrameCountDown = 5;
		//	sun->frame++;
		//	if (sun->frame == 22)sun->frame = 0;
		//	if (sun->goToCount == 1)
		//	{
		//		sun->x = sun->tempX / 10 * sun->goToCountFrame;		//��ͬλ��
		//		sun->y = sun->tempY / 10 * sun->goToCountFrame;		
		//		sun->goToCountFrame--;
		//		if (sun->goToCountFrame == 0)
		//		{
		//			next = cur->next;
		//			suns.DeleteNode(sun->No);
		//			cur = next;
		//			currentSunshine += 25;
		//			continue;
		//		}
		//	}
		//}
		//cur = cur->next;
	}
}
void PaintBangs()
{
	Node<Bang>* cur = bangs.head, * pre;
	while (cur != NULL)
	{
		/*Bang* bang = cur->content;
		bang->paintbangs(cur, pre,bangs);*/
		if (cur->content->countDown > 0)
		{
			cur->content->countDown--;
			transparentImage(NULL, cur->content->x, cur->content->y, &bang);
		}
		pre = cur;
		cur = cur->next;
		if (pre->content->countDown <= 0)
			bangs.DeleteNode(pre->content->No);
	}
}
void PaintCursor()
{
	if (cursor == Chammer)
	{
		// ���û�����������Ƕȴ���
		if (!isHitting)
			transparentImage(NULL, mousemsg.x - 45, mousemsg.y - 45, &hammer[0]);
		else
		{
			// ����ת����
			transparentImage(NULL, mousemsg.x - 45, mousemsg.y - 45, &hammer[hammerRadius]);
			hammerRadius++;
			if (hammerRadius == 13)
			{
				hammerRadius = 0;
				isHitting = 0;
			}
		}
	}
	else if (cursor == CpotatoMine)
		transparentImage(NULL, mousemsg.x - 45, mousemsg.y - 45, &potaotoMinePictures[0]);
	else if (cursor == Ciceshroom)
		transparentImage(NULL, mousemsg.x - 45, mousemsg.y - 45, &iceshroomPictures[0]);
	else
		transparentImage(NULL, mousemsg.x - 45, mousemsg.y - 45, &gravebusterPictures[0]);
}
void RandomGraves()
{
	// �������Ĺ��
	while (graveNum < 6 || graveNum>13)
	{
		graveNum = 0;
		for (int i = 0; i < 5; i++)
		{
			int num = rand() % 4;
			for (int j = 0; j < num; j++)
			{
				int column = rand() % 6 + 3;
				if (mapState[i][column] == 0)
				{
					mapState[i][column] = rand() % 8 + 1;
					graveNum++;
				}
				else j--;
			}
		}
	}
}
void RandomZombies()
{
	// ���������ʬ
	//�˴����÷�װ������ֱ��д�����ú���
	for (int i = 0; i < 5; i++)
	{
		for (int j = 3; j < 9; j++)
		{
			if (1 <= mapState[i][j] && mapState[i][j] <= 8)
			{
				double p = rand() / (double)RAND_MAX;
				if (p < normalfrequency)
				{
					NormalZombie* normalZombie = new NormalZombie();
					normalZombie->row = i;
					normalZombie->location = xys[i][j].x - 75;
					zombies.InsertNode(normalZombie);
					//mciSendString("play ./Music/dirt_rise.mp3 from 0", 0, 0, 0);
				}
				else if (normalfrequency <= p && p < coneheadfrequency)
				{
					ConeheadZombie* coneheadZombie = new ConeheadZombie();
					coneheadZombie->row = i;
					coneheadZombie->location = xys[i][j].x - 75;
					zombies.InsertNode(coneheadZombie);
					//mciSendString("play ./Music/dirt_rise.mp3 from 0", 0, 0, 0);
				}
				else if (coneheadfrequency <= p && p < bucketheadfrequency)
				{
					BucketheadZombie* bucketheadZombie = new BucketheadZombie();
					bucketheadZombie->row = i;
					bucketheadZombie->location = xys[i][j].x - 75;
					zombies.InsertNode(bucketheadZombie);
					//mciSendString("play ./Music/dirt_rise.mp3 from 0", 0, 0, 0);
				}
			}
		}
	}
	// ���������
	double p = rand() / (double)RAND_MAX;
	if (p < GroanFrequency)
	{
		int px = rand() % 6 + 1;
		switch (px)
		{
		case 1:
			mciSendString("play ./Music/groan.mp3 from 0", 0, 0, 0);
			break;
		case 2:
			mciSendString("play ./Music/groan2.mp3 from 0", 0, 0, 0);
			break;
		case 3:
			mciSendString("play ./Music/groan3.mp3 from 0", 0, 0, 0);
			break;
		case 4:
			mciSendString("play ./Music/groan4.mp3 from 0", 0, 0, 0);
			break;
		case 5:
			mciSendString("play ./Music/groan5.mp3 from 0", 0, 0, 0);
			break;
		case 6:
			mciSendString("play ./Music/groan6.mp3 from 0", 0, 0, 0);
			break;
		}
	}
}
void drawHint()		//����ʾ��
{
	if (drawingHint != 0)
	{
		settextcolor(WHITE);
		settextstyle(40, 0, "����");
		if (drawingHint == 1)
		{
			drawtext("�˴�������ֲ�", &rect, DT_CENTER);
		}
		else if (drawingHint == 2)
			drawtext("���ⲻ�㣡", &rect, DT_CENTER);
		else if (drawingHint == 3)
			drawtext("Ŀ�꣺��������Ĺ��", &rect, DT_CENTER);

		hintCountDown--;
		if (hintCountDown == 0)
		{
			hintCountDown = 70;
			drawingHint = 0;
		}
	}
}
void beginGame()	//��ʼ��Ϸ
{
	drawingHint = 3;	//��Ϸָ��

	// ���������Ϸ

	if (isNewGame)
	{
		// �������Ĺ��
		RandomGraves();
		isNewGame = 0;
		cursor = Chammer;
	}
	mciSendString("open ./Music/Loonboon.mp3 alias BGM2", 0, 0, 0);
	mciSendString("play BGM2 repeat", 0, 0, 0);
	mciSendString("play ./Music/theZombiesareComing.mp3 from 0", 0, 0, 0);
	while (1)
	{
		// ��ͼ
		cleardevice();
		// ��������ֲ�������˵���������
		putimage(0, 0, &background);
		putimage(0, 0, &plantsBar);
		transparentImage(NULL, 685, 0, &menu);
		RECT r = { 8, 63, 68, 85 };		// 12, 62, 68, 84
		settextstyle(20, 0, "΢���ź�", 0, 0, FW_BOLD, false, false, false);
		settextcolor(BLACK);
		drawtext(itoa(currentSunshine, sunshineNum, 10), &r, DT_CENTER);
		// ��ֲ���Ĺ��
		PaintPlantsAndGraves();
		// ����ʬ
		PaintZombies();
		// �����ݻ�
		for (int i = 0; i < 5; i++)
		{
			if (lawnmowers[i]->isOut == 0)
			{
				transparentImage(NULL, lawnmowers[i]->location, xys[i][0].y + 45, &lawnmower);
			}
		}

		drawHint();		// ����ʾ

		PaintSuns();		// ��̫��

		PaintBangs();		// �� bang

		PaintCursor();		// �����

		// ��ѩ��
		if (snowCountDown > 0)
		{
			snowCountDown--;
			transparentImage(NULL, 0, 0, &snow);
		}
		FlushBatchDraw();

		// ����
		// ���ݻ�״̬
		for (int i = 0; i < 5; i++)
		{
			if (lawnmowers[i]->isActivated == 1)
			{
				lawnmowers[i]->location += 5;
				if (lawnmowers[i]->location > 800)
				{
					lawnmowers[i]->isOut = 1;
				}
			}
		}
		Node<Zombie>* cur;
		// ����������
		while (peekmessage(&mousemsg, EM_MOUSE))
		{

			if (mousemsg.message == WM_LBUTTONDOWN)	//����������
			{
				if (mousemsg.x > 692 && mousemsg.y > 0 && mousemsg.x < 815 && mousemsg.y < 44)
				{
					// �������˲˵�,�浵�˳�
					writeArchive(username);
					goto stopGame;
				}
				if (cursor == Chammer)
				{
					// �������Ǵ���
					// �������������
					if (mousemsg.x > 86 && mousemsg.y > 10 && mousemsg.x < 133 && mousemsg.y < 79)
					{
						if (currentSunshine >= 25)
							cursor = CpotatoMine;
						else
							drawingHint = 2;
					}
					// �������Ĺ��������
					else if (mousemsg.x > 145 && mousemsg.y > 10 && mousemsg.x < 191 && mousemsg.y < 79)
					{
						if (currentSunshine >= 75)
							cursor = Cgravebuster;
						else
							drawingHint = 2;
					}
					// ������˺�����
					else if (mousemsg.x > 204 && mousemsg.y > 10 && mousemsg.x < 253 && mousemsg.y < 79)
					{
						if (currentSunshine >= 75)
							cursor = Ciceshroom;
						else
							drawingHint = 2;
					}
					else
					{
						hammerRadius = 0;
						isHitting = 1;
						mciSendString("play ./Music/hit.mp3 from 0", 0, 0, 0);
						Node<Zombie>* cur = zombies.head;
						while (cur != NULL)
						{
							Zombie* zombie = cur->content;
							if (mousemsg.x > zombie->location + 97 && mousemsg.y > xys[zombie->row][0].y - 40
								&& mousemsg.x < zombie->location + 164 && mousemsg.y < xys[zombie->row][0].y + zombie->height)
							{
								// ��������˽�ʬ����ʬ��Ѫ������ 
								bangs.InsertNode(new Bang(mousemsg.x - 70, mousemsg.y - 30));
								zombie->HP--;
								if (zombie->HP == 0)
								{
									zombies.DeleteNode(zombie->No);
									generateSunshine(zombie->location, xys[zombie->row][0].y);
								}
								else if (zombie->HP == 1)
									zombie->type = NORMALZOMBIE;

								goto skipLittleWhile;
							}
							cur = cur->next;
						}
						Node<Sun>* curSun = suns.head;
						while (curSun != NULL)
						{
							Sun* sun = curSun->content;
							if (mousemsg.x > sun->x + 20 && mousemsg.y > sun->y - 18 && mousemsg.x < sun->x + 108 && mousemsg.y < sun->y + 80)
							{
								// �������̫��
								curSun->content->goToCount = 1;
								//mciSendString("play ./Music/sunshine.mp3 from 0", 0, 0, 0);
								sun->playsunshine();
								goto skipLittleWhile;
							}
							curSun = curSun->next;
						}
					}
				}
				// ��������ֲ��
				else
				{
					int i, j, isInPlantZone = 0;
					for (i = 0; i < 5; i++)
					{
						for (j = 0; j < 9; j++)
						{
							if (mousemsg.x > xys[i][j].x && mousemsg.y > xys[i][j].y
								&& mousemsg.x < xys[i][j].x + 80 && mousemsg.y < xys[i][j].y + 100)	//�ҵ�Ҫ���µ�λ�ã���i��j
							{
								isInPlantZone = 1;
								break;
							}
						}
						if (isInPlantZone)break;
					}

					if ((cursor != Cgravebuster && mapState[i][j] != GRASS) || isInPlantZone == 0)	//�������Ĺ������Ҫ���ڲݵ���
					{
						drawingHint = 1;
						continue;
					}

					switch (cursor)	//����ֲ��		
					{
					case CpotatoMine:
					{
						mapState[i][j] = POTATO;
						PotatoMine* potatoMine = new PotatoMine();
						currentSunshine -= potatoMine->SunCost;
						potatoMine->x = i;
						potatoMine->y = j;
						plants.InsertNode(potatoMine);		//������
						//mciSendString("play ./Music/plant.mp3 from 0", 0, 0, 0);	//���Է�װ��
						potatoMine->playplant();
						break;
					}
					case Ciceshroom:
					{

						mapState[i][j] = ICESHROOM;
						IceShroom* iceshroom = new IceShroom();
						currentSunshine -= iceshroom->SunCost;
						iceshroom->x = i;
						iceshroom->y = j;
						plants.InsertNode(iceshroom);
						//mciSendString("play ./Music/plant.mp3 from 0", 0, 0, 0);
						iceshroom->playplant();

						break;
					}
					case Cgravebuster:
					{
						if (mapState[i][j] < 1 || mapState[i][j]>8)		//Ĺ��������Ҫ����Ĺ���ϣ�����ֵ�����ݵ�״̬
						{
							drawingHint = 1;
							continue;
						}

						switch (mapState[i][j])
						{
						case GRAVE1:
							mapState[i][j] = GRAVEBUSTER_GRAVE1;
							break;
						case GRAVE2:
							mapState[i][j] = GRAVEBUSTER_GRAVE2;
							break;
						case GRAVE3:
							mapState[i][j] = GRAVEBUSTER_GRAVE3;
							break;
						case GRAVE4:
							mapState[i][j] = GRAVEBUSTER_GRAVE4;
							break;
						case GRAVE5:
							mapState[i][j] = GRAVEBUSTER_GRAVE5;
							break;
						case GRAVE6:
							mapState[i][j] = GRAVEBUSTER_GRAVE6;
							break;
						case GRAVE7:
							mapState[i][j] = GRAVEBUSTER_GRAVE7;
							break;
						case GRAVE8:
							mapState[i][j] = GRAVEBUSTER_GRAVE8;
							break;
						default:
							continue;
							break;
						}
						GraveBuster* gravebuster = new GraveBuster();
						currentSunshine -= gravebuster->SunCost;
						gravebuster->x = i;
						gravebuster->y = j;
						plants.InsertNode(gravebuster);	//����ڵ�
						//mciSendString("play ./Music/gravebusterchomp.mp3 from 0", 0, 0, 0);
						gravebuster->playplant();
						break;
						}
					}
					cursor = Chammer;		//���º󷵻ش���
				}
			}
			else if (mousemsg.message == WM_RBUTTONDOWN)
			{
				cursor = Chammer;
			}
		}

		//�ж��������Ƿ񱻴���
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (mapState[i][j] == POTATOMINE)
				{
					Node<Zombie>* curZombie = zombies.head, * pre = NULL;
					while (curZombie != NULL)
					{
						pre = curZombie;
						curZombie = curZombie->next;
						if (pre->content->row == i && pre->content->location > xys[i][j].x - 135 && pre->content->location < xys[i][j].x - 20)
						{
							mapState[i][j] = POTATOBOOM;
							mciSendString("play ./Music/potato_mine.mp3 from 0", 0, 0, 0);
							zombies.DeleteNode(pre->content->No);
						}
					}
				}
			}
		}

		//���������ʬ
		RandomZombies();

		//�ж���Ӯ
		if (graveNum == 0 && zombies.head == NULL)
		{
			Win1Lose2 = 1;
			mciSendString("play ./Music/trophy.mp3 from 0", 0, 0, 0);
			goto stopGame;
		}
		//Node<Zombie>* cur = zombies.head;
		cur = zombies.head;
		while (cur != NULL)
		{
			if (cur->content->location < -150)
			{
				Win1Lose2 = 2;
				mciSendString("play ./Music/losemusic.mp3 from 0", 0, 0, 0);
				goto stopGame;
			}
			cur = cur->next;
		}

	skipLittleWhile:
		//��ʱ
		HpSleep(15);
	}
stopGame:
	mciSendString("close BGM2", 0, 0, 0);
}
void PaintNames()
{
	// �����浵����
	getFiles("./archives");
	RECT rect;
	setbkmode(TRANSPARENT);
	settextcolor(RGB(222, 186, 97));
	if (files.size() > 5)
	{
		settextstyle(20, 0, "��������");
		rect = { 268, 135, 538, 335 };
		drawtext("�浵���࣬��ɾ��archives", &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		rect = { 268, 175, 538, 375 };
		drawtext("�ļ����µĴ浵������!", &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else if (files.size() == 0)
	{
		settextstyle(40, 0, "��������");
		rect = { 268, 159, 538, 360 };
		drawtext("û�д浵!", &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else
	{
		int h = 189;
		settextstyle(35, 0, "��������");
		for (int i = 0; i < files.size(); ++i)
		{
			rect = { 268, h, 538, h + 40 };
			drawtext(files[i].c_str(), &rect, DT_CENTER);
			h += 40;
		}
	}
}