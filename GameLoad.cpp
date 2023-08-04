#include"GameLoad.h"
IMAGE potatoBoom;		//�������ͼƬ
IMAGE potato;
IMAGE grave[8];
IMAGE hammer[13];
IMAGE tmpImg;
IMAGE tmpImg2;
IMAGE potaotoMinePictures[8];
IMAGE iceshroomPictures[11];
IMAGE gravebusterPictures[28];
IMAGE sunPictures[22];
IMAGE normalZombieWalkPictures[47];
IMAGE normalZombieEmergePictures[20];
IMAGE normalZombieEatPictures[10];
IMAGE coneheadZombieWalkPictures[47];
IMAGE coneheadZombieEmergePictures[20];
IMAGE coneheadZombieEatPictures[10];
IMAGE bucketheadZombieWalkPictures[47];
IMAGE bucketheadZombieEmergePictures[20];
IMAGE bucketheadZombieEatPictures[10];
IMAGE plantsBar;
IMAGE menu;
IMAGE background;
IMAGE selectID;
IMAGE iceTrap;
IMAGE snow;
IMAGE lawnmower;
IMAGE loseGame;
IMAGE winGame;
IMAGE bang;
// ��Ϸ����
int mapState[32][32];		// ��ͼ״̬��0���գ�1��Ĺ����2�����ף�û��������3�����ף��ѳ�������4��������
coordinate xys[32][32];
int currentSunshine;

double normalfrequency;
double coneheadfrequency;
double bucketheadfrequency;
double SunsFrequency;
int isNewGame;
int isHitting;
int hammerRadius;
int drawingHint;
int hintCountDown;
int snowCountDown;
int graveNum;
int Win1Lose2;
void loadImages(IMAGE imgs[], const char path[], int n, int begin)
{
	for (int i = 0; i < n; i++)
	{
		char tmpPath[200], frameNo[4];			//·���������Ϊ200��ͼƬ�����Ϊ4λ��
		strcpy_s(tmpPath, 200, path);
		strcat(strcat(tmpPath, itoa(i + begin, frameNo, 10)), ".png");		//itoa������תΪ�ַ���
		loadimage(&imgs[i], tmpPath);
	}
}
void loading()
{
	loadImages(grave, "./graphics/GraveStones/", 8, 1);
	loadImages(hammer, "./graphics/Screen/hammer/hammer", 13, 1);
	loadImages(sunPictures, "./graphics/Plants/Sun/Sun_", 22, 0);
	loadImages(potaotoMinePictures, "./graphics/Plants/PotatoMine/PotatoMine/PotatoMine_", 8, 0);
	loadImages(iceshroomPictures, "./graphics/Plants/IceShroom/IceShroom/IceShroom_", 11, 0);
	loadImages(gravebusterPictures, "./graphics/Plants/GraveBuster/GraveBuster-", 28, 1);

	loadImages(normalZombieWalkPictures, "./graphics/Zombies/NormalZombie/Zombie/Zombie-", 47, 1);
	loadImages(coneheadZombieWalkPictures, "./graphics/Zombies/ConeheadZombie/ConeheadZombie/ConeheadZombie-", 47, 1);
	loadImages(bucketheadZombieWalkPictures, "./graphics/Zombies/BucketheadZombie/BucketheadZombie/BucketheadZombie-", 47, 1);

	loadImages(normalZombieEmergePictures, "./graphics/Zombies/NormalZombie/ZombieEmerge/Zombie-", 20, 1);
	loadImages(coneheadZombieEmergePictures, "./graphics/Zombies/ConeheadZombie/ConeheadZombieEmerge/Zombie-", 20, 1);
	loadImages(bucketheadZombieEmergePictures, "./graphics/Zombies/BucketheadZombie/BucketheadZombieEmerge/Zombie-", 20, 1);

	loadImages(normalZombieEatPictures, "./graphics/Zombies/NormalZombie/ZombieAttack/ZombieAttack_", 10, 0);
	loadImages(coneheadZombieEatPictures, "./graphics/Zombies/ConeheadZombie/ConeheadZombieAttack/ConeheadZombieAttack_", 10, 0);
	loadImages(bucketheadZombieEatPictures, "./graphics/Zombies/BucketheadZombie/BucketheadZombieAttack/BucketheadZombieAttack_", 10, 0);

	loadimage(&potatoBoom, "./graphics/Plants/PotatoMine/PotatoMineExplode/PotatoMineExplode_0.png");
	loadimage(&potato, "./graphics/Plants/PotatoMine/PotatoMineInit/PotatoMineInit_0.png");
	loadimage(&plantsBar, "./graphics/Screen/ChooserBackground.png");
	loadimage(&background, "./graphics/Screen/Background.jpg");
	loadimage(&selectID, "./graphics/Screen/selectID.png");
	loadimage(&iceTrap, "./graphics/Plants/IceShroom/IceShroomTrap_0.png");
	loadimage(&snow, "./graphics/Plants/IceShroom/IceShroomSnow_0.png");
	loadimage(&menu, "./graphics/Screen/menu.png");
	loadimage(&lawnmower, "./graphics/Screen/lawnmower.png");
	loadimage(&loseGame, "./graphics/Screen/lose.png");
	loadimage(&winGame, "./graphics/Screen/win.png");
	loadimage(&bang, "./graphics/Screen/bang.png");

	mciSendString("open ./Music/chomp.mp3", 0, 0, 0);
	mciSendString("open ./Music/dirt_rise.mp3", 0, 0, 0);
	mciSendString("open ./Music/gravebusterchomp.mp3", 0, 0, 0);
	mciSendString("open ./Music/groan.mp3", 0, 0, 0);
	mciSendString("open ./Music/groan2.mp3", 0, 0, 0);
	mciSendString("open ./Music/groan3.mp3", 0, 0, 0);
	mciSendString("open ./Music/groan4.mp3", 0, 0, 0);
	mciSendString("open ./Music/groan5.mp3", 0, 0, 0);
	mciSendString("open ./Music/groan6.mp3", 0, 0, 0);
	mciSendString("open ./Music/hit.mp3", 0, 0, 0);
	mciSendString("open ./Music/lawnmower.mp3 alias lawnmower", 0, 0, 0);
	mciSendString("open ./Music/losemusic.mp3", 0, 0, 0);
	mciSendString("open ./Music/plant.mp3", 0, 0, 0);
	mciSendString("open ./Music/potato_mine.mp3", 0, 0, 0);
	mciSendString("open ./Music/shoop.mp3", 0, 0, 0);
	mciSendString("open ./Music/theZombiesareComing.mp3", 0, 0, 0);
	mciSendString("open ./Music/trophy.mp3", 0, 0, 0);
	mciSendString("open ./Music/sunshine.mp3", 0, 0, 0);
}
void transparentImage(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	HDC dstDC = GetImageHDC(dstimg);	//����������ڻ�ȡ��ͼ�豸���(HDC)��
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);	//�ú���������ʾ����ָ��͸���ȵ�ͼ��
}
void addIce(IMAGE* targetImage, IMAGE* srcImage, int addRed , int addGreen , int addBlue )		//��������ըʱЧ�����֣���ͼƬ�ӱ�
{
	int srcImgWidth = srcImage->getwidth(), srcImgHeight = srcImage->getheight();
	targetImage->Resize(srcImgWidth, srcImgHeight);
	DWORD* pTargetBuffer = GetImageBuffer(targetImage);
	DWORD* pSrcBuffer = GetImageBuffer(srcImage);
	int allPixel = srcImgHeight * srcImgWidth;

#define RGBA(r, g, b, a) ((b) + (g << 8) + (r << 16) + (a << 24))
	for (int i = 0; i < allPixel; ++i)
	{
		UCHAR r = (UCHAR)GetRValue(pSrcBuffer[i]);
		UCHAR g = (UCHAR)GetGValue(pSrcBuffer[i]);
		UCHAR b = (UCHAR)GetBValue(pSrcBuffer[i]);
		r = r + addRed;
		r = r > 255 ? 255 : r;
		g = g + addGreen;
		g = g > 255 ? 255 : g;
		b = b + addBlue;
		b = b > 255 ? 255 : b;
		pTargetBuffer[i] = (DWORD)RGBA(r, g, b, pSrcBuffer[i] >> 24);
	}
}
void HpSleep(int ms)
{
	static clock_t oldclock = clock();		// ��̬��������¼��һ�� tick

	oldclock += ms * CLOCKS_PER_SEC / 1000;	// ���� tick

	if (clock() > oldclock)					// ����Ѿ���ʱ��������ʱ
		oldclock = clock();
	else
		while (clock() < oldclock)			// ��ʱ
			Sleep(1);						// �ͷ� CPU ����Ȩ������ CPU ռ����
	//			Sleep(0);						// ���߾��ȡ����� CPU ռ����
}