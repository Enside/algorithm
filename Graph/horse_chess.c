#include <stdio.h>
#include <stdlib.h>

void horse_chess(int chess[8][8], int count, int x, int y)
{
    static int total = 0;
    if (count == 64 && total < 5)
    {
        total++;
        printf("The No.%d Method:\n", total);
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                printf("%-3d", chess[i][j]);
            }
            putchar('\n');
        }
        return;
    }
    else if (total < 5)
    {
        if (chess[y + 1][x + 2] == 0 && y + 1 <= 7 && x + 2 <= 7)
        {
            int chess_next[8][8];
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    chess_next[i][j] = chess[i][j];
                }
            }
            chess_next[y + 1][x + 2] = count + 1;
            horse_chess(chess_next, count + 1, x + 2, y + 1);
        }

        if (chess[y + 2][x + 1] == 0 && y + 2 <= 7 && x + 1 <= 7)
        {
            int chess_next[8][8];
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    chess_next[i][j] = chess[i][j];
                }
            }
            chess_next[y + 2][x + 1] = count + 1;
            horse_chess(chess_next, count + 1, x + 1, y + 2);
        }

        if (chess[y + 2][x - 1] == 0 && y + 2 <= 7 && x - 1 >= 0)
        {
            int chess_next[8][8];
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    chess_next[i][j] = chess[i][j];
                }
            }
            chess_next[y + 2][x - 1] = count + 1;
            horse_chess(chess_next, count + 1, x - 1, y + 2);
        }

        if (chess[y + 1][x - 2] == 0 && y + 1 <= 7 && x - 2 >= 0)
        {
            int chess_next[8][8];
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    chess_next[i][j] = chess[i][j];
                }
            }
            chess_next[y + 1][x - 2] = count + 1;
            horse_chess(chess_next, count + 1, x - 2, y + 1);
        }

        if (chess[y - 1][x - 2] == 0 && y - 1 >= 0 && x - 2 >= 0)
        {
            int chess_next[8][8];
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    chess_next[i][j] = chess[i][j];
                }
            }
            chess_next[y - 1][x - 2] = count + 1;
            horse_chess(chess_next, count + 1, x - 2, y - 1);
        }

        if (chess[y - 2][x - 1] == 0 && y - 2 >= 0 && x - 1 >= 0)
        {
            int chess_next[8][8];
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    chess_next[i][j] = chess[i][j];
                }
            }
            chess_next[y - 2][x - 1] = count + 1;
            horse_chess(chess_next, count + 1, x - 1, y - 2);
        }

        if (chess[y - 2][x + 1] == 0 && y - 2 >= 0 && x + 1 <= 7)
        {
            int chess_next[8][8];
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    chess_next[i][j] = chess[i][j];
                }
            }
            chess_next[y - 2][x + 1] = count + 1;
            horse_chess(chess_next, count + 1, x + 1, y - 2);
        }
        if (chess[y - 1][x + 2] == 0 && y - 1 >= 0 && x + 2 <= 7)
        {
            int chess_next[8][8];
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    chess_next[i][j] = chess[i][j];
                }
            }
            chess_next[y - 1][x + 2] = count + 1;
            horse_chess(chess_next, count + 1, x + 2, y - 1);
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
    chess[0][0] = 1;
    int count = 1;
    horse_chess(chess, count, 0, 0);
    return 0;
}
