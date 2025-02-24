#ifndef __Media_H__
#define __Media_H__

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fb.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <dirent.h> 
#include "./2048/2048_v3.c"   //直接引入2048游戏库
#define S_KEY 0x5A

             //函数的声明
//音乐播放器
void Music_Interface();

//游戏
void Game_Controller();

//相册
int Photo_Slid();

//登录界面
void Login_Interface();

//功能界面
void Media_Interface();

//注册
void Register();

//登录
void Login();

//多媒体菜单
void Media_Order();

//滑屏算法
int slide_lcd();

//显示任意大小的图片
int show_anysizebmp(char *bmpname);

//显示文字
int Font_Show(int x0,int y0,int size,char *buf,int Fsize,unsigned int color);

//显示MP3文件名
void File_List();

//2048Game
int Game_2048();

//清屏
int clear_lcd(void);
#endif