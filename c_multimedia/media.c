#include "main.h" 


//功能主界面
void Media_Interface()
{
    int x=0,y=0;
    
	int flag1=0;
	do
	{
		//主界面
		show_anysizebmp("./images/media.bmp");

		get_xy(&x,&y);//---获取坐标
		if(x>100&&x<195&&y>190&&y<291) //100,190   195,291   
		{
			flag1=1; //音乐功能
		}
		if(x>335&&x<450&&y>228&&y<290) //335,228   450,290
		{
			flag1=2; //游戏功能
		}
        if(x>583&&x<688&&y>186&&y<294) //583,186   688,294
		{
			flag1=3; //相册功能
		}
        if(x>732&&x<790&&y>15&&y<80) //732,15   790,80
		{
			flag1=4; //退出
		}
		switch (flag1)
		{
			case 1:
            Music_Interface();  //音乐
				break;
			case 2:
            Game_Controller();  //游戏
				break;
			case 3:
            show_anysizebmp("./images/photo.bmp");
            Photo_Slid();  //相册
				break;
            case 4:
            Login_Interface();  //退出到登录界面
				break;
		}
	}while(1);   
}

//音乐播放器
void Music_Interface()
{
    char *mp3[3]={"madplay /root/mp3/1.mp3 &","madplay /root/mp3/2.mp3 &","madplay /root/mp3/3.mp3 &"};
    int x=0,y=0;
    int n=0;  //循环遍历指针数组
    int m=0; //控制播放 暂停界面的转换
    //主界面
    show_anysizebmp("./images/music.bmp");

    // if(access("/mkfifo",F_OK))  //根目录管道文件 
    // {
    //     mkfifo("/mkfifo",0777);
    // }

    // int fifo_fd = open("/mkfifo/myfifo",O_RDWR);  //打开文件
    // if(fifo_fd == -1)
    // {
    //     perror("open fifo failed");
    //     return;
    // }
	do
	{
        int flag1=0;
        char command[100]={0};  //音量+-命令
        get_xy(&x,&y);//---获取坐标
        if(x>747&&x<791&&y>5&&y<55) //747,5   791,55
        {
            flag1=1; //退出功能
        }
        if(x>387&&x<432&&y>425&&y<475) //387,425   432,474
        {
            flag1=2; //播放功能
        }
        if(x>495&&x<540&&y>426&&y<478) //495,426    540,478
        {
            flag1=3; //下一首功能
        }
        if(x>279&&x<326&&y>424&&y<476) //279,424  326,476
        {
            flag1=4; //上一首功能
        }
        if(x>602&&x<647&&y>426&&y<471) //602,426  647,471
        {
            flag1=5; //结束播放功能
            m=0;  //未播放
        }
        if(x>106&&x<209&&y>434&&y<471) //166,434  209,471
        {
            flag1=6; //播放列表
        }
        if(x>579&&x<654&&y>15&&y<76) //579,15  654,76
        {
            flag1=7; //音量+
        }
        if(x>581&&x<650&&y>144&&y<206) //581,144  650,206
        {
            flag1=8; //音量-
        }
        switch (flag1)
        {
            case 1:  //退出
                Media_Interface(); //多媒体界面
                break;

            case 2:  //播放功能
                if(m==0)  
                {
                    system(mp3[n]);  //播放
                    show_anysizebmp("./images/musics.bmp"); //播放界面 
                }
                else 
                {
                    if(m%2==0)
                    {
                        system("killall -18 madplay");  //继续播放
                        show_anysizebmp("./images/musics.bmp");  //播放界面
                    }
                    else  
                    {
                        system("killall -19 madplay");  //暂停播放
                        show_anysizebmp("./images/music.bmp");   //未播放界面
                    }
                }
                m++;
                break;

            case 3:  //下一首功能
                n++;
                if(n>2)
                {
                    n=0;  
                }
                if(m%2!=0)  //正在播放
                {
                    system("killall -9 madplay");
                }
                system(mp3[n]);
                //播放界面
                show_anysizebmp("./images/musics.bmp");
                m=1;  //播放状态  
                break;

            case 4:  //上一首功能
                n--;
                if(n<0)
                {
                    n=2;
                }
                if(m%2!=0)  //正在播放
                {
                    system("killall -9 madplay");
                }
                system(mp3[n]);
                //播放界面
                show_anysizebmp("./images/musics.bmp");
                m=1;  //播放状态  
                break;

            case 5:  //结束播放功能
                system("killall -9 madplay");

                show_anysizebmp("./images/music.bmp"); //未播放界面
                break;

            case 6:  //查看音乐列表
                File_List();
                break;
            case 7:  //音量+
                    if(m%2!=0)  //正在播放
                    {
                        system("killall -15 madplay"); // 使用SIGTERM信号，更温和地停止madplay
                    }
                    sprintf(command, "madplay -a %d %s",10,mp3[n]);
                    system(command);
                    m=1;              
                break;
            case 8:  //音量-
                    if(m%2!=0)  //正在播放
                    {
                        system("killall -15 madplay"); // 使用SIGTERM信号，更温和地停止madplay
                    }
                    sprintf(command, "madplay -a %d %s",-5,mp3[n]);
                    system(command); 
                    m=1;             
                break;
        }
    }while(1);    
}

//游戏
void Game_Controller()
{
    int x=0,y=0;
    int flag1=0;
    int g=0; //检测游戏是否已经开始
	do
	{
		//主界面
		show_anysizebmp("./images/game.bmp");
		get_xy(&x,&y);//---获取坐标
		if(x>290&&x<501&&y>160&&y<227) //285,157   501,227   
		{
			flag1=1; //开始游戏
		}
		if(x>286&&x<500&&y>274&&y<343) //282,276   500,343
		{
			flag1=2; //结束游戏
		}
		switch (flag1)
		{
			case 1:
                Game_2048();  //开始游戏
				break;
			case 2:
                Media_Interface();  //游戏结束
                    break;
            default:
                    break;
		}
	}while(1);
}    

//相册
int Photo_Slid()
{
    //静态图 
    char *Photos[5]={"./images/1.bmp","./images/2.bmp","./images/3.bmp","./images/4.bmp","./images/5.bmp"};
    //保存动态图的每一帧
    char *Gits[38]={"./images/10 (1).bmp","./images/10 (2).bmp","./images/10 (3).bmp","./images/10 (4).bmp","./images/10 (5).bmp","./images/10 (6).bmp","./images/10 (7).bmp","./images/10 (8).bmp","./images/10 (9).bmp","./images/10 (10).bmp","./images/10 (11).bmp","./images/10 (12).bmp","./images/10 (13).bmp","./images/10 (14).bmp","./images/10 (15).bmp","./images/10 (16).bmp","./images/10 (17).bmp","./images/10 (18).bmp","./images/10 (19).bmp","./images/10 (20).bmp","./images/10 (21).bmp","./images/10 (22).bmp","./images/10 (23).bmp","./images/10 (24).bmp","./images/10 (25).bmp","./images/10 (26).bmp","./images/10 (27).bmp","./images/10 (28).bmp","./images/10 (29).bmp","./images/10 (30).bmp","./images/10 (31).bmp","./images/10 (32).bmp","./images/10 (33).bmp","./images/10 (34).bmp","./images/10 (35).bmp","./images/10 (36).bmp","./images/10 (37).bmp","./images/10 (38).bmp"};
    int x=-1;
    int y=-1;
    int flag=0;  
    int n=0;

    while(1)
    {
        flag=slide_lcd();  //获取滑屏算法得到的结果(上下左右)
        switch(flag)
        {
            case 1:   //右滑
                if(n<0)
                {
                    n=4;
                }
                printf("right\n");
                show_anysizebmp(Photos[n]);
                n--;
                break;
            case 2:  //左滑
                if(n>4)
                {
                    n=0;
                }
                printf("left\n");
                show_anysizebmp(Photos[n]);
                n++;
                break;
            case 3:  //下滑
                printf("down\n");
                Media_Interface();  //退出相册
                break;
            case 4:  //上滑
                printf("up\n");
                for(int i=0;i<38;i++)
                {
                    show_anysizebmp(Gits[i]);  
                    usleep(66667); //15帧动图
                }
                break; 
        }
    }
}


//显示MP3文件名
void File_List()
{
	//打开目录
	DIR * pdir=opendir("/root/mp3");
	if(NULL == pdir)
	{
		perror("opendir fail");
		return;
	}
	
    struct dirent *dirinfo = NULL;  //防止野指针
    int y=295;
    while ((dirinfo = readdir(pdir)) != NULL)  //循环遍历所有文件
    {
        //查找后缀名为mp3的文件
        if(dirinfo->d_name[strlen(dirinfo->d_name) - 3]=='m' && dirinfo->d_name[strlen(dirinfo->d_name) - 2]=='p'&& dirinfo->d_name[strlen(dirinfo->d_name) - 1]=='3')
        {
            Font_Show(6,y+=50,strlen(dirinfo->d_name)+1,dirinfo->d_name,2,0xFF0000);  //将文件名显示在屏幕上
        }
    }
	closedir(pdir);  //关闭目录
}


//显示任意大小的图片
int show_anysizebmp(char *bmpname)
{
    int fd=open("/dev/fb0",O_RDWR); // 读写
    if(fd==-1)
    {
        perror("fail to open the dev");
		return -1;
    }
    
	unsigned int* lcd= mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(lcd == MAP_FAILED)
	{
		perror("mmap fail");
		return -1;
	}	
	
	//打开图片
	FILE * bmpfp = fopen(bmpname,"r");
	if(bmpfp==NULL)
	{
		perror("fopen bmp fail");
		return -1;
	}
	
	//读取像素数据
	
	fseek(bmpfp,18,SEEK_SET); //从头开始偏移18字节到宽
	//从信息头 读取 宽和高
	int w=0;
	int h=0;
	fread(&w,4,1,bmpfp);
	fread(&h,4,1,bmpfp);

	fseek(bmpfp,54,SEEK_SET); //从头开始偏移54字节
	
	unsigned char bmpbuf[w*h*3];
	
	fread(bmpbuf,sizeof(bmpbuf),1,bmpfp);
	
	//数据处理
	int i=0;
	int j=0;
	
	for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			if(h<=480 && w<= 800) //只放 屏幕部分
			{
				 //屏幕     =  图片  行--i
				lcd[800*(h-1-i)+j]=bmpbuf[3*(w*i+j)+2]<<16|bmpbuf[3*(w*i+j)+1]<<8|bmpbuf[3*(w*i+j)];
			}

		}
	}
	fclose(bmpfp);	
	munmap(lcd,800*480*4);
	close(fd);
}


//滑屏算法
int slide_lcd()
{
    struct input_event ts;  //创建结构体变量
    int count=0;
    
    int x1=0; //按下时
    int x2=0; //松开时
    
    int y1=0;
    int y2=0;
    
    int x_sub;  //差值
    int y_sub;

    int x_abs;  //绝对值
    int y_abs;
    
    //打开
    int tsfd=open("/dev/input/event0",O_RDWR);
    if(-1==tsfd)
    {
        perror("open ts fail");
        return -1;
    }
    
    //读取
    while(1)
    {
        read(tsfd,&ts,sizeof(ts));
        
        //记录按下时候的坐标
        if(x1==0)
        {
            if(ts.type==EV_ABS && ts.code==ABS_X)
            {
                x1=ts.value;  //第一次按下
            }
        }
        if(y1==0)
        {
            if(ts.type==EV_ABS && ts.code==ABS_Y)
            {
                y1=ts.value;  //第一次按下
            }
        }
        
        if(ts.type==EV_ABS && ts.code==ABS_X)
        {
            x2=ts.value;  //松手

        }
        if(ts.type==EV_ABS && ts.code==ABS_Y)
        {
            y2=ts.value;  //松手
  
        }
        
        if(ts.type==EV_KEY && ts.code==BTN_TOUCH && ts.value==0) //编码类型0x01  触摸松开时
        {
            x_sub=x2-x1;
            y_sub=y2-y1;
            
            x_abs=abs(x_sub);
            y_abs=abs(y_sub);
            
            if(x_abs > y_abs) //产生在x轴上的移动
            {
                if(x_sub>30) //够30才是有效滑动
                {
                    close(tsfd);
                    return 1; //右滑
                }
                if(x_sub < -30)
                {
                    close(tsfd);
                    return 2; //左滑
                }
            }
            else //产生在y轴上的移动
            {
                if(y_sub>30) //够30才是有效滑动
                {
                    close(tsfd);
                    return 3; //下滑 
                }
                if(y_sub < -30)
                {
                    close(tsfd);
                    return 4; //上滑
                }
            }
            
            x1=0; //按下时
            x2=0; //松开时
            
            y1=0;
            y2=0;
            continue;
        }
        
    }
    
}

//清屏--映射白色
int clear_lcd()
{
	//1.打开屏幕
	int fd = open("/dev/fb0",O_RDWR);
	if(fd == -1)
	{
		perror("open fail");
		return -1; //出错直接结束
	}
	
	//2.建立映射 lcd--内存的起始地址
	unsigned int *lcd=mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(lcd == MAP_FAILED)
	{
		perror("mmap fail");
	}
	
	//3.填充
	int i=0;
	int j=0;
	
	for(i=0;i<800*480;i++)
	{
		lcd[i]=0xFFFFFF; //白色
	}
	
	//解除映射
	munmap(lcd, 800*480*4);
	//关闭屏幕
	close(fd);
	
}


                        //移动至2048_v3.c
/* //获取x,y坐标
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
} */