#ifndef _FONT_H_
#define _FONT_H_

//��ʼ��������Ϊ�Դ���ڵ�ַ����ʾ���Ŀ�͸�
void Font_init(void *fb_addr,int w,int h);

/***�ַ���ʾ***/

/*****
����˵����
X Y �� x y����ʾ�����λ������
width��height����ʾ����Ŀ�Ⱥ͸߶�
color����ʾ����ɫ
string��str����ʾ���ַ�����
len ��string���ݵĳ���
size����ʾ�ı���

*****/
int  Create_LineEdit(int X,int Y,int width,int height,unsigned long color);
int  Clean_Area(int X,int Y,int width,int height,unsigned long color);
int  Display_character(unsigned int x,unsigned int y,unsigned int len,unsigned char *string,unsigned long color);
int  Display_characterX(unsigned int x,unsigned int y,unsigned int len,unsigned char *string,int size,unsigned long color);
int  Display_characterXX(unsigned int x,unsigned int y,unsigned int len,unsigned char *string,int size,unsigned long color);
int  Roll_Dispaly(unsigned char *str);


#endif