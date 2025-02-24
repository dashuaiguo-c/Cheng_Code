#ifndef __2048_H__
#define __2048_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define SIZE 4

//布局
int score = 0; //积分
int chess[5] ={2,2,2,2,4}; //使棋盘刷新棋子时出现2的概率更高
int Board[SIZE][SIZE]=   //创建棋盘
{
{0,0,0,0},
{0,0,0,0},
{0,0,0,0},
{0,0,0,0}
};

int Board_C[SIZE][SIZE];
extern int CountEmpty();  //函数的声明
extern int GameOver();
extern void Init_B();
extern void Copy_Board();
extern void Move();
extern void MoveLeft();
extern void MoveRight();
extern void MoveUp();
extern void MoveDown();
extern void Printf_B();
extern void Put_Auto();
extern void Put_C();
extern void C_Move();

#endif