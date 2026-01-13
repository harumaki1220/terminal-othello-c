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
    int row, col;
    int current_player = BLACK;

    board[3][3] = WHITE;
    board[3][4] = BLACK;
    board[4][3] = BLACK;
    board[4][4] = WHITE;

    while (1)
    {
        print_board(board);
        printf("%sの番です。\n", (current_player == BLACK) ? "黒(B)" : "白(W)");

        printf("どこに置きますか？ (行 列): ");
        scanf("%d %d", &row, &col);

        if (row >= 0 && row <= 7 && col >= 0 && col <= 7)
        {
            if (board[row][col] == EMPTY)
            {
                board[row][col] = current_player;
                printf("%d行 %d列に置きました。\n", row, col);
                if (current_player == BLACK)
                {
                    current_player = WHITE;
                }
                else
                {
                    current_player = BLACK;
                }
            }
            else
            {
                printf("そこにはすでに石があります！\n");
            }
        }
        else
        {
            printf("範囲外の入力です。\n");
        }
    }

    return 0;
}