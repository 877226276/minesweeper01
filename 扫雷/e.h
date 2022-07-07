#pragma once
#include<iostream>
using namespace std;

#include<iomanip>//右对齐
#include<easyx.h>
#define IMGW 40

bool isOVER = false;  //点到雷结束标记
bool isv = false;  //判断是否胜利
int num = 0;

void showmap(int map[ROW][COL]);

void initmap(int map[ROW][COL]);

void drawmap(int map[ROW][COL], IMAGE img[]);

//鼠标操作
void mouseevent(int map[ROW][COL]);

void openNull(int map[ROW][COL], int row, int col);

void judge(int map[ROW][COL], int row, int col);

void victory();