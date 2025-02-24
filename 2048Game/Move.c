#include "2048Game.h"


//移动选择
void Move()
{
    Copy_Board();
    char move = 'a';
    system("stty -icanon");
    scanf("%c",&move);

    switch (move)
    {
    case 'w':   //上
        MoveUp();
        break;
    case 's':   //下
        MoveDown();
        break;
    case 'a':   //左
        MoveLeft();
        break;
    case 'd':   //右
        MoveRight();;
        break;
    default:
        break;
    }
    C_Move();
}

//左移
void MoveLeft()
{
    int i=0, j=0;
    int temp = 0;
    int flag = 0;
    for(i=0;i<SIZE;i++)  //每行
    {
        temp = 0;        //下一行洗手
        flag = 0;
        for(j=0;j<SIZE;j++)  //固定行的每列
        {
            if(Board[i][j] ==0)  //空位置，不拿
            {
                continue;
            }
            if(temp == 0) //第一次拿
            {
                temp = Board[i][j];  
            }
            else
            {
                if (temp == Board[i][j]) //与下一个棋子相等
                {
                    Board[i][flag++] = temp*2;
                    score+=temp;        //积分累加
                    temp = 0;           //棋子已经给Board[i][flag++]
                }
                else
                {
                    Board[i][flag++] = temp;  //放下棋子
                    temp = Board[i][j];  //拿起该位置棋子
                }
            }

            Board[i][j] = 0;   //被拿位置无棋子
        }
        if(temp != 0)
        {
            Board[i][flag++] = temp;   //若最后手上还有棋子则跟随放入
        }
    }
}


//右移
void MoveRight()
{
    int i=0, j=0;
    int temp = 0;
    int flag = SIZE-1;
    for(i=SIZE-1;i>=0;i--)  //逆向每行
    {
        int temp = 0;
        int flag = SIZE-1;
        for(j=SIZE-1;j>=0;j--) 
        {
        if(Board[i][j] == 0) //固定行的逆向每列
        {
            continue;
        }
        if(temp ==0)
        {
            temp = Board[i][j];
        }
        else
        {
            if(temp == Board[i][j])
            {
                Board[i][flag--] = temp*2;
                score+=temp;
                temp =0;
            }
            else
            {
                Board[i][flag--] = temp;
                temp = Board[i][j];
            }
        }
        Board[i][j] = 0;
        }
      if(temp !=0)
      {
        Board[i][flag--] =temp;
      }
    }
}

//上移
void MoveUp()
{
    int i=0, j=0;
    int temp = 0;
    int flag = 0;
    for(j=0;j<SIZE;j++)
    {
        temp = 0;
        flag = 0;
        for(i=0;i<SIZE;i++)
        {
            if(Board[i][j] == 0)
            {
                continue;
            }
            if(temp ==0)
            {
                temp = Board[i][j];
            }
            else
            {
                if(temp == Board[i][j])
                {
                    Board[flag++][j] = temp*2;
                    score+=temp;
                    temp = 0;
                }
                else
                {
                    Board[flag++][j] = temp;
                    temp = Board[i][j];
                }
            }
            Board[i][j] = 0; 
        }
        if(temp != 0)
        {
            Board[flag++][j] = temp;
        }
    }
}


//下移
void MoveDown()
{
    int i=0,j=0;
    int temp = 0;
    int flag = 0;
    for (j = SIZE-1;j>=0;j--)
    {
        temp = 0;
        flag = SIZE -1;
        for (i = SIZE-1;i>=0;i--)
        {
            if(Board[i][j] ==0)
            {
                continue;
            }
            if(temp ==0)
            {
                temp = Board[i][j];
            }
            else
            {
                if(temp == Board[i][j])
                {
                    Board[flag--][j] = temp*2;
                    score+=temp;
                    temp = 0;
                }
                else
                {
                    Board[flag--][j] = temp;
                    temp = Board[i][j];
                }
            }
            Board[i][j] = 0;
        }
        if(temp != 0)
        {
            Board[flag--][j] = temp; 
        }
    }
}

void C_Move()  //判断是否是有效移动
{
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            if(Board[i][j]!=Board_C[i][j])
            {
                Put_Auto();
                system("clear");
                Printf_B();
                i=j=SIZE;
            }
        }
    }
}