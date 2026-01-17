#include <stdio.h>

#define EMPTY 0
#define BLACK 1
#define WHITE 2
#define SIZE 8

void print_board(int board[SIZE][SIZE])
{
    printf("  ");
    for (int j = 0; j < SIZE; j++)
    {
        printf("%d ", j);
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", i);

        for (int j = 0; j < SIZE; j++)
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

int can_flip(int board[SIZE][SIZE], int r, int c, int player)
{
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int opponent = (player == BLACK) ? WHITE : BLACK;

    for (int i = 0; i < 8; i++)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];
        int found_opponent = 0;

        while (nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE && board[nr][nc] == opponent)
        {
            nr += dr[i];
            nc += dc[i];
            found_opponent = 1;
        }

        if (found_opponent && nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE && board[nr][nc] == player)
        {
            return 1;
        }
    }

    return 0;
}

void flip_stones(int board[SIZE][SIZE], int r, int c, int player)
{
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int opponent = (player == BLACK) ? WHITE : BLACK;

    for (int i = 0; i < 8; i++)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];
        int found_opponent = 0;

        while (nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE && board[nr][nc] == opponent)
        {
            nr += dr[i];
            nc += dc[i];
            found_opponent = 1;
        }

        if (found_opponent && nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE && board[nr][nc] == player)
        {
            int fr = r + dr[i];
            int fc = c + dc[i];

            while (board[fr][fc] == opponent)
            {
                board[fr][fc] = player;
                fr += dr[i];
                fc += dc[i];
            }
        }
    }
}

void count_stones(int board[SIZE][SIZE], int is_game_over)
{
    int black = 0;
    int white = 0;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == BLACK)
            {
                black++;
            }
            else if (board[i][j] == WHITE)
            {
                white++;
            }
        }
    }

    printf("黒: %d, 白: %d\n", black, white);

    if (is_game_over)
    {
        printf("\n=== 最終結果 ===\n");
        if (black < white)
        {
            printf("白の勝ち！");
        }
        else if (white < black)
        {
            printf("黒の勝ち！");
        }
        else
        {
            printf("引き分け！");
        }
    }
}

int has_valid_move(int board[SIZE][SIZE], int player)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == EMPTY && can_flip(board, i, j, player))
            {
                return 1;
            }
        }
    }
    return 0;
}

int main(void)
{
    int board[SIZE][SIZE] = {EMPTY};
    int row, col;
    int current_player = BLACK;

    int mid = SIZE / 2;
    board[mid - 1][mid - 1] = WHITE;
    board[mid - 1][mid] = BLACK;
    board[mid][mid - 1] = BLACK;
    board[mid][mid] = WHITE;

    while (1)
    {
        count_stones(board, 0);
        print_board(board);

        if (!has_valid_move(board, current_player))
        {
            printf("%sは置ける場所がありません。パスします。\n", (current_player == BLACK) ? "黒" : "白");
            current_player = (current_player == BLACK) ? WHITE : BLACK;

            if (!has_valid_move(board, current_player))
            {
                printf("両者置ける場所がありません。ゲーム終了です\n");
                count_stones(board, 1);
                break;
            }
            continue;
        }

        printf("%sの番です。\n", (current_player == BLACK) ? "黒(B)" : "白(W)");

        printf("どこに置きますか？ (行 列): ");
        if (scanf("%d %d", &row, &col) != 2)
        {
            printf("エラー：数字（0～%d）を2つ入力してください。\n", SIZE - 1);
            while (getchar() != '\n')
            {
            }
            continue;
        }

        if (row >= 0 && row < SIZE && col >= 0 && col < SIZE)
        {
            if (board[row][col] != EMPTY)
            {
                printf("そこにはすでに石があります！\n");
            }
            else if (!can_flip(board, row, col, current_player))
            {
                printf("そこには置けません（相手の石を挟めません）！\n");
            }

            else
            {
                board[row][col] = current_player;
                flip_stones(board, row, col, current_player);
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
        }
        else
        {
            printf("範囲外の入力です。\n");
        }
    }

    return 0;
}