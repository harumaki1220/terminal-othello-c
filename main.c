#include <stdio.h>

int main(void)
{
    int board[8][8] = {0};

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] == 0)
            {
                printf(".");
            }
            else if (board[i][j] == 1)
            {
                printf("B");
            }
            else if (board[i][j] == 2)
            {
                printf("W");
            }
        }
        printf("\n");
    }

    return 0;
}