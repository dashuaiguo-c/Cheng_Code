#include "2048Game.h"

//移动后自动在空位随机补棋
void Put_Auto()
{
    int counts=0,count=0;  //counts当前空位数量，count计算位置
    int i=0, j=0;
    counts=CountEmpty();
    int A[counts];
    int *p =A;
    int C_auto=0;
    int c_num=0;

    for(i=0;i<SIZE;i++)
    {
        for(j=0;j<SIZE;j++)
        {
            count++;
            if(Board[i][j] ==0)  //将空位位置存入数组A
            {
                *p=count;
                 p++;
            }
        }
    }
    C_auto=rand()%counts;

    c_num = rand() % 5;
    Put_C(A[C_auto],c_num); 
}


//将随机数为2或4的棋子随机放入棋盘空位中
void Put_C(int pos,int c_num)
{
    int i, j=0;
    int count_P=0;
    for(i=0;i<SIZE;i++)
    {
        for(j=0;j<SIZE;j++)
        {
            count_P+=1;
            if(count_P == pos)
            {
                Board[i][j] = chess[c_num];
                break;
            }
        }
    }
}