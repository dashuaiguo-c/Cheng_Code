#include <sys/types.h>   
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h> /*perror, errno ,...*/
#include <stdlib.h>/*abs的头文件*/
#include <stdio.h> /*printf*/
#include <sys/mman.h>
#include <linux/input.h>
#include <stdlib.h>
#include <time.h> /*time */
#include <string.h>
#include "../font.h"  //引入font字库

#define LCD_WIDTH 800
#define LCD_HEIGHT 480
#define LCD_BYTESPERPIXEL   4  //每个像素点占几个字节

#define LCD_SIZE   (LCD_WIDTH * LCD_HEIGHT *LCD_BYTESPERPIXEL)

#define MATRIX_X0    0     //整个棋盘的左上角顶点的x轴坐标
#define MATRIX_Y0    0    //整个棋盘的左上角顶点的y轴坐标
#define PIECE_SIZE    100   //棋子的像素点大小

#define BOARDSIZE  4  // 整个棋盘的大小BORADSIZE * BOARDSIZE
#define MOVE_LEFT 1
#define MOVE_RIGHT 2
#define MOVE_UP 3
#define MOVE_DOWN 4

unsigned char bmpdata[LCD_SIZE] ;  //读bmp 图片数据临时数组 
int game_over = 0;//游戏结束的标志，1表示游戏结束
					//0表示游戏不结束

int score=0;  //记录分数
int max_score=0;  //记录最高分
char buf[10]; //存放读取的最高分

int *plcd = NULL;//指向framebuffer(屏幕显存第一个点的内存)

//将所有的图片名保存到一个数组中
const char * bmpfiles[] =	
{
	"./2048/2/military_font_7_2.bmp", 	// 2
	"./2048/2/military_font_7_4.bmp", 	//4
	"./2048/2/military_font_7_8.bmp", 	//8
	"./2048/2/military_font_7_16.bmp",	//16
	"./2048/2/military_font_7_32.bmp",
	"./2048/2/military_font_7_64.bmp",
	"./2048/2/military_font_7_128.bmp",
	"./2048/2/military_font_7_256.bmp",
	"./2048/2/military_font_7_512.bmp",
	"./2048/2/military_font_7_1024.bmp",
	"./2048/2/military_font_7_2048.bmp",
	"./2048/2/military_font_7_4096.bmp",
	"./2048/2/military_font_7_8192.bmp",
	"./2048/2/military_font_7_16384.bmp",
	"./2048/2/military_font_7_32768.bmp",
	"./2048/2/military_font_7_65536.bmp",
};



/*
	get_bmpfiles_index:根据你要显示的数字(2,4,8,,16,...)
		返回你对应的文件名的下标
	返回值:
		返回 x对应的文件名在数组bmpfiles的下标
*/
int get_bmpfiles_index(int x)
{
	if (x == 2)
	{
		return 0;
	} else if (x == 4)
	{
		return 1;
	} else if (x == 8)
	{
		return 2;
	} else if (x == 16)
	{
		return 3;
	}else if (x == 32)
	{
		return 4;
	}else if (x == 64)
	{
		return 5;
	}else if (x == 128)
	{
		return 6;
	}else if (x == 256)
	{
		return 7;
	}else if (x == 512)
	{
		return 8;
	}else if (x == 1024)
	{
		return 9;
	}else if (x == 2048)
	{
		return 10;
	}else if (x == 4096)
	{
		return 11;
	}else if (x == 8192)
	{
		return 12;
	}else if (x == 16384)
	{
		return 13;
	}else if (x == 32768)
	{
		return 14;
	}else if (x == 65536)
	{
		return 15;
	}


}


//棋盘矩阵
int matrix[BOARDSIZE][BOARDSIZE] =
{
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0	
};

/*
	get_zero_num:求棋盘矩阵里面有多少个0
	返回值:
		返回棋盘矩阵中0的个数
*/
int get_zero_num()
{
	int z = 0;//棋盘矩阵中元素为0的个数
	int i, j;

	for (i = 0; i < BOARDSIZE; i++) //BOARDSIZE = 4,整个棋盘大小为BOARDSIZE*BOARDSIZE
	{
		for (j = 0; j < BOARDSIZE; j++)
		{
			if (matrix[i][j] == 0)
			{
				z++;
			}
		}
	}

	return z;
}


/*
	set_matrix:给棋盘矩阵第z个0的位置，填充一个
		值s
*/
void set_matrix(int z,  int s)
{
	int i, j;
	int k = 0 ;//0的个数

	for (i = 0; i < BOARDSIZE ;i++)
	{
		for (j = 0; j < BOARDSIZE; j++)
		{
			if (matrix[i][j] == 0)
			{
				k++;
				if (k == z)
				{
					matrix[i][j] = s;
					return ;
				}
			}
			
		}
	}

}




/*
	lcd_draw_point:在屏幕坐为(x, y)这个点，填充color
	这个颜色值。
	@x: x轴坐标
	@y:y轴坐标
	@color:要填充的辨色值

	返回值:
		无返回值。

*/
void lcd_draw_point(int x, int y, int color)
{
	int *p = plcd;

	if (x >= 0 && x < LCD_WIDTH && y>=0 && y <LCD_HEIGHT)
	{
		*(p +LCD_WIDTH*y + x) = color;
	}
}


/*
	lcd_draw_dect: 在屏幕上画一个矩形，并且用
		color这种颜色填充该矩形。
	@x0: 该矩形的左上角的那个点x轴坐标
	@y0:该矩形的左上角的那个点y轴坐标
	@w:该矩形的宽
	@h:该矩形的高
	@color:该矩形要填充的辨色值

	返回值:
		无返回值。
		
*/
void lcd_draw_dect(int x0, int y0, int w, int h, int color)
{
	if (x0 < 0 || y0 < 0 || w < 0 || h <0)
		return;

	if ((x0 + w >LCD_WIDTH) || (y0+h) > LCD_HEIGHT)
	{
		return;
	}

	int x, y;

	for (y = y0; y < y0 + h; y++)
	{
		for (x = x0; x < x0 + w; x++)
		{
			lcd_draw_point(x, y  ,  color);
		}
	}

}

/*
	draw_bmp_byname:把一张bmp图片显示在屏幕上特定的位置
	@bmpfile:要显示的bmp图片的文件名
	@x0: 在屏幕上显示的左上角顶点的x轴坐标
	@y0: 在屏幕上显示的左上角顶点的y轴坐标
	@w: 位图宽度
	@h: 位图高度
	返回值:
		无返回值.
*/
void draw_bmp_byname(const char *bmpfile, int x0, int y0, int w, int h)
{
	int fd;
	int x, y;
	
	fd = open(bmpfile, O_RDONLY);
	if (fd == -1)
	{
		perror("open bmpfile error:");
		return ;
	}
		
	lseek(fd, 54, SEEK_SET);
	
	read(fd, bmpdata, w*h*3);

	close(fd);

	int i = 0;
	for (y = 0; y < h; y++)
	{
		unsigned char r,g ,b;
		int color;

		for (x = 0; x < w; x++)
		{
			b = bmpdata[i++];
			g = bmpdata[i++];
			r = bmpdata[i++];
			color = (r << 16) | (g << 8) | b;

			lcd_draw_point(x0+ x, y0 + (h -1 - y) ,color);
		}
	}

}



/*
	draw_matrix:把棋盘矩阵在屏幕上显示出来
*/
void draw_matrix()
{
	int i, j;
	for (i = 0; i < BOARDSIZE; i++)
	{
		for (j = 0; j < BOARDSIZE;j++)
		{
			int x0, y0;
			x0 = 185;//棋盘矩阵左上角那个点的x轴坐标
			y0 = 25;//棋盘矩阵左上角那个点的y轴坐标
			if (matrix[i][j] == 0)
			{
				lcd_draw_dect(x0+j*110,  y0+i*110,  PIECE_SIZE, PIECE_SIZE, 
						0xb4eeb4);//如果此处元素的值为0，那么
								//就显示
			}
			else
			{
				int f_index = get_bmpfiles_index(matrix[i][j]);
				draw_bmp_byname(bmpfiles[f_index],
						x0+j*110,  y0+i*110,
						PIECE_SIZE,PIECE_SIZE);
			}
		}
	}
}

/*
	init_matrix:初始化棋盘矩阵
			在任意x个位置，填充x个数字(2,4,8)
*/

void init_matrix()
{
	//规则x >= 1,x <= 3
	int x = (random() % 3) + 1;

	int i;

	/*
		step1:随机产生x个数字，并填充到棋盘矩阵中去
	*/

	for(i = 0; i < x; i++)
	{
		int pos = (random() % get_zero_num()) + 1;

		int s[] = {2, 4, 8, 2};
		int s_i = (random() % 3);

		set_matrix(pos, s[s_i]);
	}

	/*
		step 2: 绘制棋盘矩阵
	*/
	draw_matrix();

}

/*
	rand1_matrix:移动之后随机产生一个数字填充到
	任意一个0的位置上
*/
void rand_matrix()
{
	int pos = (random() % get_zero_num()) + 1;

	int s[] = {2, 4, 8, 2};
	int s_i = (random() % 4);

	set_matrix(pos, s[s_i]);
	draw_matrix();

}

/*
	get_finger_direction:获取手指在触摸屏上面的滑动方向
	返回值:
		MOVE_LEFT:手指向左移动
		MOVE_RIGHT:手指向右移动
		MOVE_UP:手指向上移动
		MOVE_DOWN:手指向下移动
*/
int get_finger_direction()
{
	int ret;
	int fd = open("/dev/input/event0", O_RDONLY); //打开触摸屏
	if (fd == -1)
	{
		perror("open event failed:");
		return -1;
	}
	struct input_event ev;

	int  x1 = -1; //在滑动过程中第一个点的x轴坐标
	int x2; //在滑动过程中最后一个点的x轴坐标
	int y1 = -1;//在滑动过程中第一个点的y轴坐标
	int y2;//在滑动过程中最后一个点的y轴坐标

	while (1)
	{
		ret = read(fd, &ev, sizeof(ev));
		if(ret != sizeof(ev))
		{
			continue;
		}
		
		if (ev.type == EV_ABS && ev.code == ABS_X)//是x轴坐标
		{
			if (x1 == -1)//x1重来没有赋过值，那么肯定是第一个点
			{
				x1 = ev.value;
			}
			x2 = ev.value;
		}
		if (ev.type == EV_ABS && ev.code == ABS_Y)//是y轴坐标
		{
			if ( y1 == -1)//y1重来没有赋过值，那么肯定是第一个点
			{
				y1 = ev.value;
			}
			y2 = ev.value;
		}


		//if (ev.type == EV_ABS && ev.code == ABS_PRESSURE//手指弹起，再计算滑动方向
		//	&& ev.value == 0)//触摸屏压力值为0, press up
		if(ev.type == EV_KEY && ev.code ==  BTN_TOUCH && ev.value == 0)
		{
			int x_cz;//x轴的位移
			int y_cz;//y轴的位移
			int abs_x;
			int abs_y;
			x_cz = x2 - x1;
			y_cz = y2 - y1;
			abs_x = abs(x_cz);
			abs_y = abs(y_cz);
			
			if((x_cz > 30) && (abs_x > 2 * abs_y))
			{
				close(fd);
				return MOVE_RIGHT;
			}
			else if((x_cz < -30) && (abs_x > 2 * abs_y))
			{
				close(fd);
				return MOVE_LEFT;
			}
			else if((y_cz > 30) && (abs_y > 2 * abs_x))
			{
				close(fd);
				return MOVE_DOWN;
			}
			else if((y_cz < -30) && (abs_y > 2 * abs_x))
			{
				close(fd);
				return MOVE_UP;
			}	
			else	
			{
				x1 = y1 = -1;
				continue;
			}
		}
	}


	close(fd);

}

/*
	fin_left:手指左划后棋子移动及合并的方式
*/
void fin_left()
{
	int i, j;//i为矩阵行下标，j为矩阵列下标
	int value, save_zero;
	for(i = 0; i < BOARDSIZE; i++)
	{
		value = 0;
		save_zero= 0;
		for(j = 0; j < BOARDSIZE ; j++)
		{
			if (matrix[i][j] == 0)
				continue;
			
			if (value == 0)
				value = matrix[i][j];
			else
			{
				if (value == matrix[i][j])
				{
					matrix[i][save_zero++] = value * 2;
					score+=value;
					value = 0;
				} else {
					matrix[i][save_zero++] = value;
					value = matrix[i][j];
				}
			}
			matrix[i][j] = 0;
		}

		if (value != 0)
			matrix[i][save_zero] = value;

	}
		
}
	//draw_matrix();
/*
	fin_right:手指上划后棋子移动及合并的方式
*/
void fin_right()
{
	int i, j;//i为矩阵行下标，j为矩阵列下标
	int value;
	int save_zero;
	for (i = 0; i < BOARDSIZE; i++)
	{
		value = 0;
		save_zero = BOARDSIZE -1;
		for (j = BOARDSIZE - 1; j >= 0 ; j--)
		{
			if(matrix[i][j] == 0)
			{
				continue;
			}
			if(value == 0)
			{
				value = matrix[i][j];
			}
			else
			{
				if(value == matrix[i][j])
				{
					matrix[i][save_zero--] = 2 * value;
					score+=value;
					value = 0;
				}
				else
				{
					matrix[i][save_zero--] = value;
					value = matrix[i][j];
				}
			}
			matrix[i][j] = 0;
		}
		if(value != 0)
		{
			matrix[i][save_zero] = value;
		}
	
	}
}
/*
	fin_up:手指上划后棋子移动及合并的方式
*/
void fin_up()
{

	int i, j;//i为矩阵行下标，j为矩阵列下标
	int value;
	int save_zero;

	for(j = 0; j < BOARDSIZE; j++)
	{
		value = 0;
		save_zero= 0;
		for(i = 0; i < BOARDSIZE ; i++)
		{
		
			if(matrix[i][j] == 0)
			{
				continue;
			}
			if(value == 0)
			{
				value = matrix[i][j];
			}
			else
			{
				if(value == matrix[i][j])
				{
					matrix[save_zero++][j] =2 * value;
					score+=value;
					value = 0;
				}
				else
				{
					matrix[save_zero++][j] = value;
					value = matrix[i][j];
				}
			}
			matrix[i][j] = 0;
		}
		if(value != 0)
		{
			matrix[save_zero][j] = value;
		}
	}

}
	
	//draw_matrix();
/*
	fin_down:手指上划后棋子移动及合并的方式
*/
void fin_down()
{
	int i, j;//i为矩阵行下标，j为矩阵列下标
	int value;
	int save_zero;
	
	for(j = 0; j < BOARDSIZE; j++)
	{
		value = 0;
		save_zero = BOARDSIZE - 1;
		for(i = BOARDSIZE - 1; i >= 0 ; i--)
		{
			if(matrix[i][j] == 0)
			{
				continue;
			}
			if(value == 0)
			{
				value = matrix[i][j];
			}
			else
			{
				if(value == matrix[i][j])
				{
					matrix[save_zero--][j] = 2 * value;
					score+=value;
					value = 0;
				}
				else
				{
					matrix[save_zero--][j] = value;
					value = matrix[i][j];
				}
			}
			matrix[i][j] = 0;
		}
		if(value != 0)
		{
			matrix[save_zero][j] = value;
		}	
	}
	
}
/*
	move_judge:判断是否还能移动
	return value:
		1 game over
		0 continue
*/
int move_judge()
{
	int i, j;
	if(get_zero_num() != 0)
	{
		return 0;
	}

	for(i = 0; i < BOARDSIZE; i++)
	{
		for(j = 0; j < BOARDSIZE ; j++)
		{
			if (j != BOARDSIZE -1)
			{
				if (matrix[i][j] == matrix[i][j+1])
				{
					return 0;
				}
			}

			if (i != BOARDSIZE - 1)
			{
				if (matrix[i][j] == matrix[i+1][j])
				{
					return 0;
				}
			}
		}
	}
	
	
	return 1;

}


/*
	change_matrix:根据手指滑动(direction)，
		变换棋盘矩阵
*/
int change_matrix()
{
	
	int direction = get_finger_direction();
	if (direction == MOVE_LEFT)
	{
		fin_left();
	}
	else if (direction == MOVE_RIGHT)
	{
		fin_right();
	}
	else if (direction == MOVE_UP)
	{
		fin_up();
	}
	else
	{
		fin_down();
	}
}

//获取x,y坐标
void get_xy(int *x,int *y)
{
    struct input_event ts;
    int count=0;
    //打开
    int tsfd=open("/dev/input/event0",O_RDWR);
    if(-1==tsfd)
    {
        perror("open ts fail");
        return;
    }
    
    //读取
    while(1)
    {
        read(tsfd,&ts,sizeof(ts));
        if(ts.type==EV_ABS && ts.code==ABS_X)  // 触摸 x轴
        {
            *x=800*ts.value/1024;//黑色板 
      
            count++;
        }
        
        if(ts.type==EV_ABS && ts.code==ABS_Y)  // 触摸 y轴
        {
            *y=480*ts.value/600;//黑色板 

            count++;
        }
        if(count == 2)
        {
            printf("(%d,%d)\n",*x,*y);  //获取到x,y轴则打印
            count=0;
            break;
        }
    }
    close(tsfd);
}

//显示文字
int Font_Show(int x0,int y0,int size,char *buf,int Fsize,unsigned int color)
{
	//1.打开屏幕
	int fd = open("/dev/fb0",O_RDWR);
	if(fd == -1)
	{
		perror("open fail");
		return -1; //出错直接结束
	}
	unsigned int *lcd=mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(lcd == MAP_FAILED)
	{
		perror("mmap fail");
	}

	Font_init(lcd,800,480);
	                  //指定位置  内容长度   内容  字号  颜色
	Display_characterX(x0,y0,size,buf,Fsize,color);
	
	munmap(lcd, 800*480*4);
	close(fd);
}

//保存最高分
void Save_Max_Score(int score)
{
	char score_M[10]={0};
	FILE *fp=fopen("./score.txt","w+");
	if(NULL == fp)
	{
		perror("open fail");
		return;
	}
	
    //写入最高分
	sprintf(score_M,"%d",score);
	fwrite(score_M,strlen(score_M)+1,1,fp);

	fclose(fp);
}

//读取最高分
char *Read_Max_Score()
{	FILE *fp=fopen("./score.txt","a+");
	if(NULL == fp)
	{
		perror("open fail");
		return NULL;
	}

	//读取最高积分
	fread(buf,10,1,fp);

	fclose(fp);

	return buf;
}


void reset_game() 
{
    // 重置棋盘矩阵
    memset(matrix, 0, sizeof(matrix));

    // 重置游戏结束标志
    game_over = 0;

    // 清屏
    lcd_draw_dect(0, 0, LCD_WIDTH, LCD_HEIGHT, 0xffffff);

    // 重新设置随机数种子
    srandom((unsigned)time(NULL));

    // 重新初始化棋盘
    init_matrix();
}
		
int Game_2048()
{
	int fd;
	score=0;  //刷新分数
	int r_score=0;  //记录读取的最高分
	/*step 1: 打开屏幕*/
	fd = open("/dev/fb0", O_RDWR);
	if (fd == -1)
	{
		perror("open fb0 failed:");
		return -1;
	}
	
	/*step 2: mmap*/
	plcd = mmap(
			NULL, //第一个参数，为映射后的内存地址，
				 //为NULL,表示让操作系统自行分配
				 
			800*480*4, //第二个参数，为映射的长度。

			PROT_WRITE, //第三个参数，为映射内存区域的权限


			MAP_SHARED, //第四个参数，为映射标志，shared

			fd, //第五个参数，为文件描述符，表示您要
				//映射哪个文件

			0 //第六个参数为偏移量，表示您要从文件的
				//哪个位置开始映射
	
	);

	lcd_draw_dect(0, 0, 800, 480, 0xffffff);//清屏
	
	srandom( time(NULL) ); //设置随机数种子，种子一样，产生的
						//随机数是一样的

	init_matrix();
	

	while (game_over == 0) //游戏没结束
	{
		draw_bmp_byname("./2048/2/ESC.bmp",650,0, 150, 40);
		int x=0,y=0;  //获取点击屏幕的位置
		get_xy(&x,&y);
		char c_score[100]={0};  //记录当前分数
		char t_score[100]={0};

		if(x>650&&x<800&&y>0&&y<40)
		{
			break;
		}
		//用来保存原来的矩阵值
		int matrix_v1[BOARDSIZE][BOARDSIZE];
		int i, j, flag = 0;
		for (i = 0; i < BOARDSIZE; ++i)
		{
			for (j = 0; j < BOARDSIZE; ++j)
			{
				matrix_v1[i][j] = matrix[i][j];
			}
		}
		/*
			step 1: 变换矩阵
		*/
		change_matrix();

		//核对是不是有效变换
		for (i = 0; i < BOARDSIZE; ++i)
		{
			for (j = 0; j < BOARDSIZE; ++j)
			{
				if (matrix_v1[i][j] != matrix[i][j])
				{
					flag = 1;
					i = j = BOARDSIZE;
				}
			}
		}
		if (flag)
		{
			rand_matrix();
			draw_matrix();
		} 
		else 
		{
			draw_matrix();
		}
		game_over = move_judge();

		//积分数据处理
		r_score=atoi(Read_Max_Score());  //将读取的数据转化为整形数
		if(score>r_score)   //比较取得最高分
		{

			Save_Max_Score(score);
		}
		r_score=atoi(Read_Max_Score());
		sprintf(c_score,"Current Score:%d",score);
		sprintf(t_score,"Top Score:%d",r_score);
		lcd_draw_dect(0, 0,180,50, 0xffffff);//清屏
		Font_Show(0,0,strlen(c_score)+1,c_score,1,0xFF0000);  //显示当前分数
		Font_Show(0,20,strlen(t_score)+1,t_score,1,0xFF0000);  //显示最高分
	}
	if(game_over==1)
	{
		draw_bmp_byname("./2048/2/game_over.bmp",250, 165, 300, 150);
		printf("Game Over\n");
		sleep(2);
	}
	reset_game();
	munmap(plcd, 800*480*4);
	close(fd);
}


