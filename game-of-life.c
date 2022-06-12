#include <stdio.h>
#include <unistd.h>

#define COLS 24
#define ROWS 20
#define OFF 0
#define ON 1
#define UPDATE_TIME 1

int board[ROWS][COLS] = { OFF };
int next_board[ROWS][COLS] = { OFF };

void print_board()
{
    int i, j;
    for (i = 0; i < ROWS; i+=1)
    {
        for (j = 0; j < COLS; j+=1)
        {
            printf("%d", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void setup_board()
{
    int i, j;
    for (i = 0; i < ROWS; i+=1)
    {
        for (j = 0; j < COLS; j+=1)
        {
            board[i][j] = OFF;
        }
    }
}

int next_cell_state(int x, int y)
{
    int i, j;
    int vx, vy;
    int current_state = board[x][y];
    int living = 0;
    for (i = -1; i <= 1; i+=1)
    {
        for (j = -1; j <= 1; j+=1)
        {
            if (i == 0 && j == 0)
                continue;
            vx = x+i;
            vy = y+j;
            if (vx < 0 || vy < 0 || vx >= COLS || vy >= ROWS)
                continue;
            if (board[vx][vy] == ON)
                living += 1;
        }
    }
    if (current_state == ON && (living == 2 || living == 3))
        return ON;
    if (current_state == OFF && living == 3)
        return ON;
    return OFF;
}

void update_board()
{
    int i, j;
    for (i = 0; i < ROWS; i+=1)
    {
        for (j = 0; j < COLS; j+=1)
        {
            next_board[i][j] = next_cell_state(i, j);
        }
    }
    for (i = 0; i < ROWS; i+=1)
    {
        for (j = 0; j < COLS; j+=1)
        {
            board[i][j] = next_board[i][j];
        }
    }
}

void clear_screen()
{
    /* +1 is because we print extra line after the board */
    printf("\e[%dA\e[K", ROWS+1);
}

int main()
{
    int n, x, y;
    scanf("%d", &n);
    while (n > 0)
    {
        scanf("%d %d", &x, &y);
        board[x-1][y-1] = ON;
        n -= 1;
    }
    while (1)
    {
        print_board();
        update_board();
        sleep(UPDATE_TIME);
        clear_screen();
    }
    return 0;
}
