#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define EMPTY 0
#define BLACK 1
#define WHITE 2
#define SIZE 8

void print_board(int board[SIZE][SIZE]);
int can_flip(int board[SIZE][SIZE], int r, int c, int player);
void flip_stones(int board[SIZE][SIZE], int r, int c, int player);
void count_stones(int board[SIZE][SIZE], int is_game_over);
int has_valid_move(int board[SIZE][SIZE], int player);
void cpu_move(int board[SIZE][SIZE], int player, int *r, int *c);

// 盤面表示
void print_board(int board[SIZE][SIZE])
{
    printf("  ");
    for (int j = 0; j < SIZE; j++)
        printf("%d ", j);
    printf("\n");

    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", i);
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == EMPTY)
                printf(". ");
            else if (board[i][j] == BLACK)
                printf("B ");
            else if (board[i][j] == WHITE)
                printf("W ");
        }
        printf("\n");
    }
}

// 挟めるか判定
int can_flip(int board[SIZE][SIZE], int r, int c, int player)
{
    if (board[r][c] != EMPTY)
        return 0;
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1}, dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int opponent = (player == BLACK) ? WHITE : BLACK;

    for (int i = 0; i < 8; i++)
    {
        int nr = r + dr[i], nc = c + dc[i];
        int found_opponent = 0;
        while (nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE &&
               board[nr][nc] == opponent)
        {
            nr += dr[i];
            nc += dc[i];
            found_opponent = 1;
        }
        if (found_opponent && nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE &&
            board[nr][nc] == player)
            return 1;
    }
    return 0;
}

// 石をひっくり返す
void flip_stones(int board[SIZE][SIZE], int r, int c, int player)
{
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1}, dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int opponent = (player == BLACK) ? WHITE : BLACK;

    for (int i = 0; i < 8; i++)
    {
        int nr = r + dr[i], nc = c + dc[i];
        int found_opponent = 0;
        while (nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE &&
               board[nr][nc] == opponent)
        {
            nr += dr[i];
            nc += dc[i];
            found_opponent = 1;
        }
        if (found_opponent && nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE &&
            board[nr][nc] == player)
        {
            int fr = r + dr[i], fc = c + dc[i];
            while (board[fr][fc] == opponent)
            {
                board[fr][fc] = player;
                fr += dr[i];
                fc += dc[i];
            }
        }
    }
}

// 石のカウントと勝敗表示
void count_stones(int board[SIZE][SIZE], int is_game_over)
{
    int black = 0, white = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == BLACK)
                black++;
            else if (board[i][j] == WHITE)
                white++;
        }
    }
    printf("黒(B): %d, 白(W): %d\n", black, white);
    if (is_game_over)
    {
        printf("\n=== 最終結果 ===\n");
        if (black > white)
            printf("黒の勝ち！\n");
        else if (white > black)
            printf("白の勝ち！\n");
        else
            printf("引き分け！\n");
    }
}

// 置ける場所があるか判定
int has_valid_move(int board[SIZE][SIZE], int player)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (can_flip(board, i, j, player))
                return 1;
        }
    }
    return 0;
}

// CPU
void cpu_move(int board[SIZE][SIZE], int player, int *r, int *c)
{
    int valid_moves[SIZE * SIZE][2];
    int count = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (can_flip(board, i, j, player))
            {
                valid_moves[count][0] = i;
                valid_moves[count][1] = j;
                count++;
            }
        }
    }
    if (count > 0)
    {
        int idx = rand() % count;
        *r = valid_moves[idx][0];
        *c = valid_moves[idx][1];
    }
}

int main(void)
{
    srand((unsigned int)time(NULL));
    int board[SIZE][SIZE] = {EMPTY};
    int row, col, current_player = BLACK;

    int mid = SIZE / 2;
    board[mid - 1][mid - 1] = WHITE;
    board[mid - 1][mid] = BLACK;
    board[mid][mid - 1] = BLACK;
    board[mid][mid] = WHITE;

    while (1)
    {
        count_stones(board, 0);
        print_board(board);

        // パス判定
        if (!has_valid_move(board, current_player))
        {
            printf("%sは置ける場所がありません。パスします。\n",
                   (current_player == BLACK) ? "黒" : "白");
            current_player = (current_player == BLACK) ? WHITE : BLACK;
            if (!has_valid_move(board, current_player))
            {
                printf("両者置ける場所がありません。ゲーム終了です！\n");
                count_stones(board, 1);
                break;
            }
            continue;
        }

        // ターン実行
        if (current_player == BLACK)
        {
            printf("あなたの番(黒)です。どこに置きますか？ (行 列): ");
            if (scanf("%d %d", &row, &col) != 2)
            {
                printf("エラー: 数字を入力してください。\n");
                while (getchar() != '\n')
                    ;
                continue;
            }
        }
        else
        {
            printf("CPUの番です。考えています...\n");
            fflush(stdout);
            sleep(1);
            cpu_move(board, current_player, &row, &col);
            printf("CPUは %d %d に置きました。\n", row, col);
            sleep(1);
        }

        if (row >= 0 && row < SIZE && col >= 0 && col < SIZE &&
            can_flip(board, row, col, current_player))
        {
            board[row][col] = current_player;
            flip_stones(board, row, col, current_player);
            current_player = (current_player == BLACK) ? WHITE : BLACK;
        }
        else if (current_player == BLACK)
        {
            printf("そこには置けません！\n");
        }
    }
    return 0;
}
