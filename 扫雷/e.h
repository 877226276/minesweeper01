#pragma once
#include<iostream>
using namespace std;

#include<iomanip>//�Ҷ���
#include<easyx.h>
#define IMGW 40

bool isOVER = false;  //�㵽�׽������
bool isv = false;  //�ж��Ƿ�ʤ��
int num = 0;

void showmap(int map[ROW][COL]);

void initmap(int map[ROW][COL]);

void drawmap(int map[ROW][COL], IMAGE img[]);

//������
void mouseevent(int map[ROW][COL]);

void openNull(int map[ROW][COL], int row, int col);

void judge(int map[ROW][COL], int row, int col);

void victory();