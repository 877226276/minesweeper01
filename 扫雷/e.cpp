#include"e.h"


void showmap(int map[ROW][COL])
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			cout << setw(2) << map[i][j] << " ";//右对齐  加上left时左对齐
		}
		cout << endl;
	}
}

void initmap(int map[ROW][COL])
{
	//清零map
	memset(map, 0, ROW * COL * sizeof(int));

	//给地图埋10个雷   -1表示雷
	//设置随机数种子
	srand((unsigned)time(NULL));
	for (int i = 0; i < 10;)
	{
		int r = rand() % ROW;
		int c = rand() % COL;
		if (map[r][c] == 0)
		{
			map[r][c] = -1;
			i++;
		}
	}

	//雷所在的九宫格所有的格子的数值都加一  雷除外
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j] == -1)
			{
				//遍历
				for (int num1 = i - 1; num1 <= i + 1; num1++)
				{
					for (int num2 = j - 1; num2 <= j + 1; num2++)
					{
						if (num1 >= 0 && num1 < ROW && num2 >= 0 && num2 < COL && map[num1][num2] != -1)
						{
							map[num1][num2]++;
						}
					}
				}
				/*map[i - 1][j - 1]++;
				map[i - 1][j]++;
				map[i - 1][j + 1]++;
				map[i][j - 1]++;
				map[i][j + 1]++;
				map[i + 1][j - 1]++;
				map[i + 1][j]++;
				map[i + 1][j + 1]++;*/
			}

		}
	}
	//把所有格子都用遮罩图盖住  给每个格子都加密  比如都加上20
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			map[i][j] += 20;
		}
	}
}
void drawmap(int map[ROW][COL], IMAGE img[])
{
	//把数组里面的数据转换成对应的图片  贴到图形窗口上面
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			//空白格子和数字
			if (map[i][j] >= 0 && map[i][j] <= 8)
			{
				putimage(j * IMGW, i * IMGW, img + map[i][j]);
			}
			else if (map[i][j] == -1)
			{
				putimage(j * IMGW, i * IMGW, img + 9);
			}
			else if (map[i][j] >= 19 && map[i][j] <= 28)
			{
				putimage(j * IMGW, i * IMGW, img + 10);
			}
		}
	}
}

//鼠标操作
void mouseevent(int map[ROW][COL])
{
	//定义消息结构体（鼠标消息 ， 按键消息 ， 字符消息）
	ExMessage msg;
	//如果有消息就返回真  并且给msg设置值
	if (peekmessage(&msg, EM_MOUSE))  //EM_MOUSE | EM_KEY | EM_CHAR
	{
		//把鼠标的坐标转成数组的下标
		int r = msg.y / IMGW;
		int c = msg.x / IMGW;
		if (msg.message == WM_LBUTTONDOWN)  //鼠标左键按下
		{
			if (map[r][c] >= 19 && map[r][c] <= 28)
			{
				map[r][c] -= 20;
				num++;
				openNull(map, r, c);//在前面做声明  不然找不到
				judge(map, r, c);
				victory();
				showmap(map);
				//测试
				//cout << num << endl;
			}
		}
	}
}
void openNull(int map[ROW][COL], int row, int col)
{
	//判断一下当前点解的是不是空白
	if (map[row][col] == 0)
	{
		for (int i = row - 1; i <= row + 1; i++)
		{
			for (int j = col - 1; j <= col + 1; j++)
			{
				if ((i >= 0 && i < ROW && j >= 0 && j < COL) && map[i][j] >= 19 && map[i][j] <= 28)
				{
					num++;
					map[i][j] -= 20;
					openNull(map, i, j);
				}
			}
		}
	}
}

void judge(int map[ROW][COL], int row, int col)
{
	//如果点到雷，就游戏结束    带你一个雷其他雷全显示出来
	if (map[row][col] == -1)
	{
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				if (map[i][j] == 19)
				{
					map[i][j] -= 20;
				}
			}
		}
		isOVER = true;
	}
}

void victory()
{
	//应该点开的格子都点开了  就赢了
	if (ROW * COL - num == 10)
	{
		isv = true;
	}
}