#include "2048Game.h"

//计算棋盘上的空位
int CountEmpty()
{
    int i, j=0;
    int counts=0;
    for(i=0;i<SIZE;i++)
    {
        for(j=0;j<SIZE;j++)
        {
            if(Board[i][j] == 0)
            {
                counts++;
            } 
        }
    }
    return counts;  //返回空位数
}

//初始化棋盘
void Init_B()
{
    int i, j=0;
    int c1_num = 0;
    int c2_num = 0;
    int pos1 = 0;      
    int pos2 = 0;      
    int count_e=CountEmpty();   //计算空位数
    c1_num = rand() % 5;   //棋子1在棋子数组的序号
    c2_num = rand() % 5;   //棋子2在棋子数组的序号
    while (1)   //防止随机数出现相同情况
    {
        pos1 = ( rand() %count_e)+1; //确定棋子1位置
        pos2 = ( rand() %count_e)+1; //确定棋子2位置
          if(pos1 !=pos2)
          {
            break;
          }
    }
    Put_C(pos1,c1_num);  //将棋子放入棋盘
    Put_C(pos2,c2_num);
}

//打印棋盘
void Printf_B()
{
    int i,j=0;
    for(i=0;i<SIZE;i++)
    {
     for(j=0;j<SIZE;j++)
       {
        printf("%d",Board[i][j]);
        printf("\t");
       }
       printf("\n");
   }
   printf("积分:%d\n",score);
   printf("请输入移动方的向(w/s/a/d):\n");
}

void Copy_Board()
{
    int i,j=0;
    for(i=0;i<SIZE;i++)
    {
     for(j=0;j<SIZE;j++)
       {
        Board_C[i][j]=Board[i][j];
       }
   }
}