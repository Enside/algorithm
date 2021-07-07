#include <stdio.h>
#include <stdlib.h>

int count = 1;

//判断危险时不遍历这一行，只遍历两条斜方向和列方向
int danger(int row, int column, int chess[8][8])
{
    int flag_column = 0, flag_left_down = 0, flag_right_dwon = 0, flag_left_up = 0, flag_right_up = 0;

    for (int i = 0; i < 8; i++)//列是否安全
    {
        if (chess[i][column] != 0)
        {
            flag_column = 1;
            break;
        }
    }
    for (int i = row, j = column; i < 8 && j >= 0; i++, j--)//左下是否安全
    {
        if (chess[i][j] != 0)
        {
            flag_left_down = 1;
            break;
        }
    }
    for (int i = row, j = column; i >= 0 && j >= 0; i--, j--)//左上是否安全
    {
        if (chess[i][j] != 0)
        {
            flag_left_up = 1;
            break;
        }
    }
    for (int i = row, j = column; i < 8 && j < 8; i++, j++)//右下是否安全
    {
        if (chess[i][j] != 0)
        {
            flag_right_dwon = 1;
            break;
        }
    }
    for (int i = row, j = column; i >= 0 && j < 8; i--, j++)//右上是否安全
    {
        if (chess[i][j] != 0)
        {
            flag_right_up = 1;
            break;
        }
    }
    if (flag_column || flag_left_down || flag_left_up || flag_right_dwon || flag_right_up)//如果危险返回1
    {
        return 1;
    }
    else//如果不危险返回0
    {
        return 0;
    }
}

void eight_queen(int row, int input[8][8])
{
    int chess[8][8];
    for (int i = 0; i < 8; i++)//复制一个新棋盘
    {
        for (int j = 0; j < 8; j++)
        {
            chess[i][j]=input[i][j];
        }
    }

    if (row == 8)//如果某一分支满足条件并且递归到row=8，则打印这一分支的棋盘
    {
        printf("第%d种方法：\n", count);
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                printf("%d ", chess[i][j]);
            }
            putchar('\n');
        }
        count++;
    }
    else//如果某一分支没有遍历完所有行，则继续遍历
    {
        for (int i = 0; i < 8; i++)//遍历这一行所有位置
        {
            if (!danger(row, i, chess))//如果两条斜方向和列方向安全，则产生一个分支
            {
                for (int j = 0; j < 8; j++)//把这一行全部归零，在新的位置上产生皇后
                {
                    chess[row][j] = 0;
                }
                chess[row][i] = 1;
                eight_queen(row + 1, chess);
                //递归函数复制包含当前皇后的棋盘，作为新的分支层层遍历
                //当函数在某一行没有找到安全位置，则不会递归到row==8,不会打印这一分支
            }
            //一个大分支结束后，会返回到首层函数，继续首行遍历，直到首行遍历完
        }
    }
}

int main(int argc, char const *argv[])
{
    int chess[8][8];
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            chess[i][j] = 0;
        }
    }
    eight_queen(0, chess);
    return 0;
}
