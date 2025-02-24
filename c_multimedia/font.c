#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "font.h"
#include "font_libs.h"

static int *tmp;
static int lcd_width;
static int lcd_height;

void Font_init(void *fb_addr,int w,int h)
{
	tmp = (int *)fb_addr;
	lcd_width = w;
	lcd_height = h;
}

//画黑色方框，X Y 起点坐标，width宽度，height高度
int  Create_LineEdit(int X,int Y,int width,int height,unsigned long color)
{
	int x,y;

	for(y=Y;y<Y+height && y<lcd_height;y++)
	{
		for(x=X;x<X+width && x<lcd_width;x++)
		{				
			tmp[y*lcd_width+x]  = color;
		}

	}	
	
	return 0;		
}

//区域填充color，X Y 起点坐标，width宽度，height高度
int  Clean_Area(int X,int Y,int width,int height,unsigned long color )
{
	int x,y;

	for(y=Y;y<Y+height && y<lcd_height;y++)
	{
		for(x=X;x<X+width && x<lcd_width;x++)
		{				
			tmp[y*lcd_width+x]  =  color;
		}

	}	
	
	return 0;		
}

/**画点***/
int  Draw_Text16(unsigned int x,unsigned int y,unsigned long color,const unsigned char ch[])
{
	unsigned short int i,j;
	unsigned char mask,buffer;

	for(i=0;i<16;i++)
	{
		mask =0x80;				//掩码
		buffer =ch[i*2];		//提取一行的第一个字节
		for(j=0;j<8;j++)
		{
			if(buffer &mask)
			{
				tmp[(y+i)*lcd_width+x+j]= color;	//为画笔上色
			}
			mask =mask >>1;
		}
		mask =0x80;
		buffer =ch[i*2+1];
		for(j=0;j<8;j++)
		{
			if(buffer &mask)
			{
				tmp[(y+i)*lcd_width+x+j+8]= color;
			}
			mask =mask>>1;	
		}		
	}
	
	return 0;
}

int  Draw_TextX(unsigned int x,unsigned int y,unsigned long color,const unsigned char ch[],int size)
{
	unsigned short int i,j,k,m;
	unsigned char mask,buffer;
	
	for(i=0;i<16;i++)
	{
		mask =0x80;				//掩码
		buffer =ch[i*2];		//提取一行的第一个字节
		for(j=0;j<8;j++)
		{
			if(buffer &mask)
			{
				for(k=0;k<size;k++)	
			  	{
			  		for(m=0;m<size;m++)
			  		{
					  tmp[(y+i*size+m)*lcd_width+x+j*size+k]= color;
			  		}
			  	}
			}
			mask =mask >>1;
		}
		mask =0x80;
		buffer =ch[i*2+1];
		for(j=0;j<8;j++)
		{
			if(buffer &mask)
			{
				for(k=0;k<size;k++)
			  	{	
					for(m=0;m<size;m++)
			  		{	
					   tmp[(y+i*size+m)*lcd_width+x+(j+8)*size+k]= color;
			  		}
			  	}
			}
			mask =mask>>1;	
		}		
	}

	return 0;
}

int  Draw_ASCII(unsigned int x,unsigned int y,unsigned long color,const unsigned char ch[])
{
    unsigned short int i,j;
    unsigned char mask,buffer;
 
    for(i=0;i<16;i++)
    {
        mask=0x80;
        buffer=ch[i];
        for(j=0;j<8;j++)
        {                   
            if(buffer&mask)
            {
                tmp[(y+i)*lcd_width+(x+j)]= color;
            }
            mask=mask>>1;                   
        }
    }

	return 0;
}

int  Draw_ASCIIX(unsigned int x,unsigned int y,unsigned long color,const unsigned char ch[],int size)
{
	unsigned short int i,j,k,m;
	unsigned char mask,buffer;

	for(i=0;i<16;i++)
	{
		mask=0x80;
		buffer=ch[i];
		for(j=0;j<8;j++)
		{                   
			if(buffer&mask)
			{
				for(k=0;k<size;k++)
				{
					for(m=0;m<size;m++)
					{
						tmp[(y+i*size+m)*lcd_width+(x+j*size+k)]= color;
					}
				}
	
			}
			mask=mask>>1;                   
		}
	}
	
	return 0;
}

//显示字符，中文的函数
int  Display_character(unsigned int x,unsigned int y,unsigned int len,unsigned char *string,unsigned long color)
{
	int k, xx;
	unsigned char qh,wh;
	const unsigned char *mould;
	unsigned int length =len;
	
	for(k=0,xx=x;k<length-1;k++)
	{
		if(string[k]&0x80)   //中文字符
		{
			qh =string[k]-0xa0;			//区号
			wh =string[k+1]-0xa0;		//位号
			mould =&__CHS[((qh-1)*94+wh-1)*32];
			Draw_Text16(4+xx,y,color,mould);
			xx+=16;
			k++;
		}
		else
		{
			mould =&__ASCII[string[k]*16];
			Draw_ASCII(4+xx,y,color,mould);
			xx+=8;
		}
	}
	
	return 0;
}

int  Display_characterX(unsigned int x,unsigned int y,unsigned int len,unsigned char *string,int size,unsigned long color)
{
	int k, xx;
	unsigned char qh,wh;
	const unsigned char *mould;
	unsigned int length =len;
	
	for(k=0,xx=x;k<length-1;k++)
	{
		if(string[k]&0x80)   //中文字符
		{
			qh =string[k]-0xa0;			//区号
			wh =string[k+1]-0xa0;		//位号
			mould =&__CHS[((qh-1)*94+wh-1)*32];
			Draw_TextX(4*size+xx,y,color,mould,size); //加4为了让每个中文之间有一定的间隙
			xx+=16*size;//当前的中文字模为32*32,每次显示下一个中文时横向偏移32个bit
			k++; //加载下一个中文，两次++操作，偏移2个字节
		}
		else
		{
			mould =&__ASCII[string[k]*16];
			Draw_ASCIIX(4*size+xx,y,color,mould,size);
			xx+=8*size;//当前的ASCII字模显示为8*16,每次显示下一个中文时横向偏移8个bit
		}
	}
	return 0;
}

int  Display_characterXX(unsigned int x,unsigned int y,unsigned int len,unsigned char *string,int size,unsigned long color)
{
	int k, xx;
	unsigned char qh,wh;
	const unsigned char *mould;
	unsigned int length =len;
	
	for(k=0,xx=x;k<length-1;k++)
	{
		if(string[k]&0x80)   //中文字符
		{
			qh =string[k]-0xa0;			//区号
			wh =string[k+1]-0xa0;		//位号
			mould =&__CHS[((qh-1)*94+wh-1)*32];
			Draw_TextX(4*size+xx,y,color,mould,size); //加4为了让每个中文之间有一定的间隙
			xx+=16*size;//当前的中文字模为32*32,每次显示下一个中文时横向偏移32个bit
			k++; //加载下一个中文，两次++操作，偏移2个字节
		}
		else
		{
			mould =&__ASCII[string[k]*16];
			Draw_ASCIIX(4*size+xx,y,color,mould,size);
			xx+=8*size;//当前的ASCII字模显示为8*16,每次显示下一个中文时横向偏移8个bit
		}
	}
	return 0;
}

/*
int Roll_Dispaly(unsigned char *str)
{
	int x;
	
	for(x=600;x>20;x--)
	{
	  Display_characterXX(x,45,strlen(str)+1,str,4,0xFF0000);
	  usleep(50000);
	  Display_characterXX(x+1,45,strlen(str)+1,str,4,0xFFFFFFFF); 
    }
	
	Display_characterXX(x+1,45,strlen(str)+1,str,4,0xFFFFFFFF);
	
	return 0;
}

*/