#include "Init.c"
#include "Move.c"
#include "Put.c"
#include "GameOver.c"


int main()
{
    srand((unsigned int)time(0));  //随机数种子
    Init_B();
    Printf_B();  //游戏初始化完成
    while (1)
    {
        Move();  //选择方向 
        GameOver();  //判断游戏是否结束
    }
}