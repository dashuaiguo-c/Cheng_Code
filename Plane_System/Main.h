#ifndef __Plane_H__
#define __Plane_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct Plane     //航班信息
{
    int ID;
    int P_ID;
    char Start[20];
    char End[20];
    char Time[20];
    int Price;
    int Max_P;
};

 struct Travel   //机票信息
{
    int P_ID;
    char name[10];
};

struct Plane Plane[10];
struct Travel Travel[10];
int count=0;
int num=0;
int avoid=0;

extern void A_U();      //函数的声明
extern int Admin_pwd();
extern void Admin_M();
extern void Admin_O();
extern void O_ONE();
extern void O_TWO();
extern void O_THREE();
extern void O_FOUR();
extern void O_FIVE();
extern void Admin();
extern int User_pwd();
extern void User_M();
extern void U_ONE();
extern void U_TWO();
extern void U_THREE();
extern void U_FOUR();
extern void U_FIVE();
extern void User_O();
extern void User();
#endif