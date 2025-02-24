#include "Main.h"


//选择身份
void A_U()
{
    char role='a';
    printf("U旅客/A管理员\n");
    printf("请选择您的身份:\n");
    if(avoid!=0)
    {
       while (getchar() != '\n');
    }
    avoid++;
    scanf("%c",&role);
    switch (role)
    {
    case 'U':
        User();
        break;
    case 'A':
        Admin();
        break;
    case 'u':
        User();
        break;
    case 'a':
        Admin();
        break;    
    default:
    printf("请输入正确的符号!\n");
        break;
    }
}


//管理员菜单栏
void Admin_M()
{
    printf("***********************\n");
    printf("****航班信息管理系统****\n");
    printf("***********************\n");
    printf("*****1.录入航班信息*****\n");
    printf("*****2.删除航班信息*****\n");
    printf("*****3.浏览航班信息*****\n");
    printf("*****4.浏览订单信息*****\n");
    printf("*****5.查看候补信息*****\n");
}


//旅客菜单栏
void User_M()
{
    printf("*********************\n");
    printf("***航班信息管理系统***\n");
    printf("*********************\n");
    printf("******* 1.订票 *******\n");
    printf("******* 2.改签 *******\n");
    printf("******* 3.退票 *******\n");
    printf("****4.浏览航班信息****\n");
    printf("*5.查看自己的航班信息*\n");
}