#include "2048Game.h"

//游戏结束
int GameOver()
{
    int i=0,j=0;
    int count=CountEmpty();  //计算空位数量
    if(count !=0)   //有空位
    {
        return -1;
    }
    for(i=0;i<SIZE;i++)   //计算左右是否可以消除
    {
        for(j=0;j<SIZE-1;j++)
        {
            if(Board[i][j] == Board[i][j+1])
            {
                return -1;
            }
        }
    }
    for(j=0;j<SIZE;j++)   //计算上下是否可以消除
    {
        for(i=0;i<SIZE-1;i++)
        {
            if(Board[i][j] == Board[i+1][j])
            {
                return -1;
            }
        }
    }
    printf("Game Over");
    Sleep(2000);
    exit(1);
}
