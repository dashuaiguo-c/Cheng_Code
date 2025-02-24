#include "Main.h"


//验证管理员密码
int Admin_pwd()
{
    char Admin_P[10]="12345";
    char *Admin_Pwd=Admin_P;
    char A_P[10]="123";
    char *A_Pwd=A_P;
    int i=3;

    for(i=3;i>0;i--)
    {
        if(i<3)
        {
            printf("密码错误!您还有%d次机会\n",i);
        }
        printf("请输入管理员密码:\n");
        scanf("%s",A_Pwd);
        if(strcmp(Admin_Pwd,A_Pwd)==0)
        {
            system("clear");
            printf("欢迎最帅的管理员!\n");
            break;
        }
    }
    if(i==0)
    {
        exit(1);
    }
}


//功能1 录入航班信息
void O_ONE()
{
    printf("请输入编号:\n");
    scanf("%d",&Plane[count].ID);
    printf("请输入航班编号:\n");
    scanf("%d",&Plane[count].P_ID);
    printf("请输入航班起始地:\n");
    scanf("%s",Plane[count].Start);
    printf("请输入航班目的地:\n");
    scanf("%s",Plane[count].End);
    printf("请输入航班起飞时间:\n");
    scanf("%s",Plane[count].Time);
    printf("请输入航班机票价格:\n");
    scanf("%d",&Plane[count].Price);
    printf("请输入航班限载人数:\n");
    scanf("%d",&Plane[count].Max_P);
    count++;
    printf("该航班信息已经成功录入!\n");
}


//功能2 删除航班信息
void O_TWO()
{
    int id=0;
    int y=0;
    printf("请选择你要删除的编号:\n");
    scanf("%d",&id);
    for(int i=0;i<count;i++)
    {
        if(id==Plane[i].ID)
        {
            bzero(&Plane[i].ID,sizeof(Plane[i].ID));
            bzero(&Plane[i].P_ID,sizeof(Plane[i].P_ID));
            bzero(Plane[i].Start,sizeof(Plane[i].Start));
            bzero(Plane[i].End,sizeof(Plane[i].End));
            bzero(&Plane[i].Price,sizeof(Plane[i].Price));
            bzero(Plane[i].Time,sizeof(Plane[i].Time));
            bzero(&Plane[i].Max_P,sizeof(Plane[i].Max_P));
            printf("编号:%d删除成功!!!\n",Plane[i].ID);
            y++;
        }
    }
    if(y==0)
    {
        printf("没有找到您要删除的编号!\n");
    }
}


//功能3 浏览航班信息
void  O_THREE()
{
    if(count==0)
    {
        printf("无航班！\n");
    }
    for ( int i = 0; i < count; i++)
    {
        printf("编号:%d\n",Plane[i].ID);
        printf("航班编号:%d\n",Plane[i].P_ID);
        printf("起始地:%s\n",Plane[i].Start);
        printf("目的地:%s\n",Plane[i].End);
        printf("起飞时间:%s\n",Plane[i].Time);
        printf("机票价格:%d\n",Plane[i].Price);
        printf("限载人数:%d\n",Plane[i].Max_P);
        printf("-----------------\n");
    }
}


//功能4 浏览订单信息
void O_FOUR()
{
    int i=0,j=0,k=0;
    for(i=0;i<count;i++)
    {
        for(j=0;j<num;j++)
        {
            if(Travel[j].P_ID==Plane[i].P_ID)
            {
                printf("航班编号:%d\n",Plane[i].ID);
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
        printf("无订单信息!\n");
    }
}


//功能5 查看候补信息
void O_FIVE()
{
    printf("无候补信息!\n");
}


//管理员操作选择
void Admin_O()
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
        O_ONE();
        break;
    case 2:
        O_TWO();
        break;
    case 3:
        O_THREE();
        Sleep(2000);
        break;
    case 4:
        O_FOUR();
        Sleep(2000);
        break;
    case 5:
        O_FIVE();
        break;
    default:
        printf("请输入正确的操作:\n");
        Admin_O();
        break;
    }
}


//管理员程序流
void Admin()
{
    char *y="y";
    char *n="n";
    char a[2];
    char b[2];
    Admin_pwd();

    while (1)
    {
        Admin_M();
        Admin_O();
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