#include "media.c"

int main()
{
  Login_Interface(); //登录界面
}

//登录界面
void Login_Interface()
{
    int x=0,y=0;
    
	int flag1=0;
	
    char usr[18] = {0};
    char passwd[18] = {0};
	do
	{
		//主界面
		show_anysizebmp("./images/login.bmp");
		
		//执行 输入账号 和 密码
		printf("请输入账号和密码:\n");
		
		scanf("%s",usr);
		//显示在对应 框框里面---字库
		//显示账号
		Font_Show(278,119,strlen(usr)+1,usr,3,0xFF0000);
		
		scanf("%s",passwd);
		//显示密码
		Font_Show(278,229,strlen(passwd)+1,passwd,3,0xFF0000);
		
		get_xy(&x,&y);//---获取坐标
		if(x>420&&x<497&&y>316&&y<376) //420,316   497,376  
		{
			flag1=1; //注册功能
		}
		if(x>265&&x<341&&y>320&&y<373) //265,320   341,373      
		{
			flag1=2; //登录功能
		}
		switch (flag1)
		{
			case 1:
				//注册功能
                Register(usr,passwd);
                printf("注册成功\n");
				break;
			case 2:
				//登录功能
				Login(usr,passwd);
				break;
            default:
                break;
		}
	}while(1);
}

//注册
void Register(char *usr, char *passwd)
{
    int i = 0;

    //加密
    for (i = 0; i < strlen(usr); i++)
    {
        usr[i] = usr[i] ^ S_KEY;
    }
    for (i = 0; i < strlen(passwd); i++)
    {
        passwd[i] = passwd[i] ^ S_KEY;
    }
    
    //2.写入文件
    int fd = open("./user.txt", O_RDWR | O_CREAT, 0666);
    if (-1 == fd)
    {
        perror("open fail");
        return;
    }

    write(fd, usr, strlen(usr));
    write(fd, passwd, strlen(passwd));
    
    close(fd);

    return;
}


//登录
void Login(char *usr, char *passwd)
{
    char usrold[18] = {0};
    char passwdold[18] = {0};
    char all[36]={0};  //存储登录输入账号和密码  防止长度不一致的错误登录
    sprintf(all,"%s%s",usr,passwd);
    char all_key[36]={0};  //存储文件读取出的账号和密码
    int i = 0;

    //加载文件里面的密码
    int fd = open("./user.txt", O_RDWR);
    if (-1 == fd)
    {
        perror("open fail");
        return;
    }
    
    read(fd, usrold, strlen(usr));
    read(fd, passwdold, strlen(passwd));

    lseek(fd,0,SEEK_SET); //偏移回头部
    read(fd,all_key,36);  //读取密码和账号信息
    
    close(fd);
    
    //解密
    for (i = 0; i < strlen(usr); i++)
    {
        usrold[i] = usrold[i] ^ S_KEY;
    }
    for (i = 0; i < strlen(passwd); i++)
    {
        passwdold[i] = passwdold[i] ^ S_KEY;
    }
    for (i = 0; i < strlen(all_key); i++)
    {
        all_key[i] = all_key[i] ^ S_KEY;
    }
    
    if (strcmp(usr, usrold) != 0)  //对比账号
    {
        printf("账号错误\n");
        printf("请重新输入\n");
    }
    else if (strcmp(passwd, passwdold) != 0)  //对比密码
    {
        printf("密码错误\n");
        printf("请重新输入\n");
    }
    else if (strcmp(all, all_key)!= 0)  //对比所有数据  //防止登录账号较短，只核对短的部分
    {
        printf("账号错误\n");
        printf("请重新输入\n");
    }
    else
    {
        printf("登录成功\n");
        Media_Interface();
    }
}


