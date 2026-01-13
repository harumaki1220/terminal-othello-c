#include <stdio.h>

#define EMPTY 0
#define BLACK 1
#define WHITE 2

void print_board(int board[8][8])
{
    printf("  0 1 2 3 4 5 6 7\n");

    for (int i = 0; i < 8; i++)
    {
        printf("%d ", i);

        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] == EMPTY)
            {
                printf(". ");
            }
            else if (board[i][j] == BLACK)
            {
                printf("B ");
            }
            else if (board[i][j] == WHITE)
            {
                printf("W ");
            }
        }
        printf("\n");
    }
}

int main(void)
{
    int board[8][8] = {EMPTY};

    board[3][3] = WHITE;
    board[3][4] = BLACK;
    board[4][3] = BLACK;
    board[4][4] = WHITE;

    print_board(board);

    return 0;
}