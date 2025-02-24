#ifndef _FONT_H_
#define _FONT_H_

//初始化，参数为显存入口地址，显示屏的宽和高
void Font_init(void *fb_addr,int w,int h);

/***字符显示***/

/*****
参数说明：
X Y 或 x y：显示的起点位置坐标
width和height：显示区域的宽度和高度
color：显示的颜色
string或str：显示的字符内容
len ：string内容的长度
size：显示的倍数

*****/
int  Create_LineEdit(int X,int Y,int width,int height,unsigned long color);
int  Clean_Area(int X,int Y,int width,int height,unsigned long color);
int  Display_character(unsigned int x,unsigned int y,unsigned int len,unsigned char *string,unsigned long color);
int  Display_characterX(unsigned int x,unsigned int y,unsigned int len,unsigned char *string,int size,unsigned long color);
int  Display_characterXX(unsigned int x,unsigned int y,unsigned int len,unsigned char *string,int size,unsigned long color);
int  Roll_Dispaly(unsigned char *str);


#endif