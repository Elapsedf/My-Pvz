#include"Game.h"

int main()
{
	srand((unsigned)time(NULL));
	loading();

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			xys[i][j].x = 40 + j * 82;
			xys[i][j].y = 70 + i * 100;
			//cout << "xys[" << i << "][" << j << "]:" << xys[i][j].x << "," << xys[i][j].y << endl;;
		}
	}

	initgraph(820, 600);
	BeginBatchDraw();

labelBGM:
	mciSendString("open ./Music/Cerebrawl.mp3 alias BGM1", 0, 0, 0);
	mciSendString("play BGM1 repeat", 0, 0, 0);

label2:
	cleardevice();

	//背景
	putimage(0, 0, &background);

	//对话框
	if (Win1Lose2 == 0)
	{
		transparentImage(NULL, 177, 35, &selectID);
		PaintNames();
	}
	else if (Win1Lose2 == 1)
	{
		transparentImage(NULL, 230, 140, &winGame);
	}
	else if (Win1Lose2 == 2)
	{
		transparentImage(NULL, 230, 140, &loseGame);
	}

	FlushBatchDraw();	//用于执行未完成的绘制任务。
	while (1)
	{
		getmessage(&mousemsg, EM_MOUSE);
		if (mousemsg.message == WM_LBUTTONDOWN)
		{
			cout << mousemsg.x << "," << mousemsg.y << endl;
			if (Win1Lose2 == 0)
			{
				if (mousemsg.x > 236 && mousemsg.y > 436 && mousemsg.x < 391 && mousemsg.y < 474)
				{
					//点击了“没有我的名字”
					char s[10];
					InputBox(s, 10, "请输入你的姓名：");
					init();
					writeArchive(s);
					goto label2;
				}
				else if (mousemsg.x > 410 && mousemsg.y > 438 && mousemsg.x < 566 && mousemsg.y < 473)
				{
					//点击了退出，存档
					if (strcmp(username, "") != 0)
						writeArchive(username);
					return 0;
				}
				else if (mousemsg.x > 268 && mousemsg.y > 190 && mousemsg.x < 538 && mousemsg.y < 385)
				{
					//点击了存档位置
					if (190 <= mousemsg.y && mousemsg.y < 229)
					{
						if (0 < files.size() && files.size() < 6)
							strcpy(username, (char*)files[0].c_str());
						else continue;
					}
					else if (229 <= mousemsg.y && mousemsg.y < 268)
					{
						if (1 < files.size() && files.size() < 6)
							strcpy(username, (char*)files[1].c_str());
						else continue;
					}
					else if (268 <= mousemsg.y && mousemsg.y < 307)
					{
						if (2 < files.size() && files.size() < 6)
							strcpy(username, (char*)files[2].c_str());
						else continue;
					}
					else if (307 <= mousemsg.y && mousemsg.y < 346)
					{
						if (3 < files.size() && files.size() < 6)
							strcpy(username, (char*)files[3].c_str());
						else continue;
					}
					else if (346 <= mousemsg.y && mousemsg.y < 385)
					{
						if (4 < files.size() && files.size() < 6)
							strcpy(username, (char*)files[4].c_str());
						else continue;
					}
					readArchive(username);
					mciSendString("close BGM1", 0, 0, 0);
					beginGame();
					if (Win1Lose2 == 0)
						goto labelBGM;
					else goto label2;
				}
			}
			else
			{
				if (mousemsg.x > 297 && mousemsg.y > 331 && mousemsg.x < 500 && mousemsg.y < 369)
				{
					init();
					mciSendString("close BGM1", 0, 0, 0);
					beginGame();
					if (Win1Lose2 == 0)
						goto labelBGM;
					else goto label2;
				}
			}
		}
	}
	getch();
	EndBatchDraw();		//结束绘画
	closegraph();		//关闭窗口

	return 0;
}