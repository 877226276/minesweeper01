#include"e.h"


void showmap(int map[ROW][COL])
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			cout << setw(2) << map[i][j] << " ";//�Ҷ���  ����leftʱ�����
		}
		cout << endl;
	}
}

void initmap(int map[ROW][COL])
{
	//����map
	memset(map, 0, ROW * COL * sizeof(int));

	//����ͼ��10����   -1��ʾ��
	//�������������
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

	//�����ڵľŹ������еĸ��ӵ���ֵ����һ  �׳���
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j] == -1)
			{
				//����
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
	//�����и��Ӷ�������ͼ��ס  ��ÿ�����Ӷ�����  ���綼����20
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
	//���������������ת���ɶ�Ӧ��ͼƬ  ����ͼ�δ�������
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			//�հ׸��Ӻ�����
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

//������
void mouseevent(int map[ROW][COL])
{
	//������Ϣ�ṹ�壨�����Ϣ �� ������Ϣ �� �ַ���Ϣ��
	ExMessage msg;
	//�������Ϣ�ͷ�����  ���Ҹ�msg����ֵ
	if (peekmessage(&msg, EM_MOUSE))  //EM_MOUSE | EM_KEY | EM_CHAR
	{
		//����������ת��������±�
		int r = msg.y / IMGW;
		int c = msg.x / IMGW;
		if (msg.message == WM_LBUTTONDOWN)  //����������
		{
			if (map[r][c] >= 19 && map[r][c] <= 28)
			{
				map[r][c] -= 20;
				num++;
				openNull(map, r, c);//��ǰ��������  ��Ȼ�Ҳ���
				judge(map, r, c);
				victory();
				showmap(map);
				//����
				//cout << num << endl;
			}
		}
	}
}
void openNull(int map[ROW][COL], int row, int col)
{
	//�ж�һ�µ�ǰ�����ǲ��ǿհ�
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
	//����㵽�ף�����Ϸ����    ����һ����������ȫ��ʾ����
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
	//Ӧ�õ㿪�ĸ��Ӷ��㿪��  ��Ӯ��
	if (ROW * COL - num == 10)
	{
		isv = true;
	}
}