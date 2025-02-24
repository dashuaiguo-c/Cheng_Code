#include "Main.h"


//验证旅客密码
int User_pwd()
{
    char User_P[10]="12345";
    char *User_Pwd=User_P;
    char U_P[10]="123";
    char *U_Pwd=U_P;
    int i=3; 

    for(i=3;i>0;i--)
    {
        if(i<3)
        {
            printf("密码错误!您还有%d次机会\n",i);
        }
        printf("请输入密码:\n");
        scanf("%s",U_Pwd);
        if(strcmp(User_Pwd,U_Pwd)==0)
        {
            system("clear");
            printf("尊敬的旅客，欢迎您!\n");
            break;
        }
    }
    if(i==0)
    {
        exit(1);
    }
}


//功能1 订票
void U_ONE()
{
    int id=0,k=0;
    printf("请输入航班编号:\n");
    scanf("%d",&id);
    for (int i = 0; i < count; i++)
    {
        if(id==Plane[i].P_ID)
        {
            Travel[num].P_ID =id;
            printf("请输入您的姓名:\n");
            scanf("%s",Travel[num].name);
            num++;
            printf("您已成功购票!\n");
            k++;
        }
    }
    if(k==0)
    {
        printf("该航班未开通!\n");
    }
}


//功能2 改签
void U_TWO()
{
    char a[10];
    int edit=0;
    int y = 0;
    printf("请输入您的姓名:\n");
    scanf("%s",a);
    for(int i=0;i<num;i++)
    {
        if(strcmp(a,Travel[i].name)==0)
        {
            printf("请输入你要改签的航班编号:\n");
            scanf("%d",&edit);
            for(int j=0;j<count;j++)
            {
                if(Plane[j].P_ID==edit)
                {
                    Travel[i].P_ID = edit;
                    y++;
                    printf("改签成功！");
                }
            }
        }
    }
    if(y==0)
    {
        printf("改签失败！\n");
    }
}


//功能3 退票
void U_THREE()
{
    int id=0;
    int y=0;
    printf("请输入您的航班编号:\n");
    scanf("%d",&id);
    for(int i=0;i<num;i++)
    {
        if(id==Travel[i].P_ID)
        {

            bzero(&Travel[i].P_ID,sizeof(Travel[i].P_ID));
            bzero(Travel[i].name,sizeof(Travel[i].name));
            printf("退票成功!!!\n");
            y++;
        }
    }
    if(y==0)
    {
        printf("没有找到您的票!\n");
    }
}


//功能4 浏览航班信息
void  U_FOUR()
{
    if(count==0)
    {
        printf("无航班！\n");
    }
    for ( int i = 0; i < count; i++)
    {
        printf("航班编号:%d\n",Plane[i].P_ID);
        printf("起始地:%s\n",Plane[i].Start);
        printf("目的地:%s\n",Plane[i].End);
        printf("起飞时间:%s\n",Plane[i].Time);
        printf("机票价格:%d\n",Plane[i].Price);
        printf("限载人数:%d\n",Plane[i].Max_P);
        printf("-----------------\n");
    }
}


//功能5 查询自己的航班信息
void U_FIVE()
{
    int k=0;
    for ( int i = 0; i < count; i++)
    {
        for(int j=0;j < num;j++)
        {
            if(Travel[j].P_ID==Plane[i].P_ID)
            {
                printf("航班编号:%d\n",Plane[i].P_ID);
                printf("姓名:%s\n",Travel[j].name);
                printf("起始地:%s\n",Plane[i].Start);
                printf("目的地:%s\n",Plane[i].End);
                printf("起飞时间:%s\n",Plane[i].Time);
                printf("机票价格:%d\n",Plane[i].Price);
                printf("限载人数:%d\n",Plane[i].Max_P);
                printf("-----------------\n");
                k++;
            }
        }
    }
    if(k==0)
    {
        printf("您未订票！");
    }
}


//旅客操作选择
void User_O()
{
    int option=0,k=0;
    if(k>0)
    {
        printf("请输入你要进行的操作:\n");
    }
    scanf("%d",&option);
    k++;

    switch (option)
    {
    case 1:
        U_ONE();
        break;
    case 2:
        U_TWO();
        break;
    case 3:
        U_THREE();
        break;
    case 4:
        U_FOUR();
        Sleep(2000);
        break;
    case 5:
        U_FIVE();
        Sleep(2000);
        break;
    default:
        printf("请输入正确的操作:\n");
        User_O();
        break;
    }
}


//旅客程序流
void User()
{
    char *y="y";
    char *n="n";
    char a[2];
    char b[2];
    User_pwd();

    while (1)
    {
        User_M();
        User_O();
        Sleep(2000);
        system("clear");
        printf("是否继续操作(y/n):\n");
        scanf("%s",a);
        if(strcmp(y,a)==0)
        {
            continue;
        }
        else if(strcmp(n,a)==0)
        {
            break;
        }
    }
    printf("是否退出航班管理系统(y/n):\n");
    scanf("%s",b);
    if(strcmp(y,b)==0)
    {
        Sleep(1000);
        system("clear");
        printf("退出成功!");
        exit(1);
    }
    else if(strcmp(n,b)==0)
    {
        A_U();
    }
}