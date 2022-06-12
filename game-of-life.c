#include <stdio.h>
#include <unistd.h>

#define UPDATE_TIME 500000  /* 0.5 seconds */
#define MAXCOLS 80
#define MAXROWS 80
#define OFF 0
#define ON 1

static int ROWS, COLS;
int board[MAXROWS][MAXCOLS] = { OFF };
int next_board[MAXROWS][MAXCOLS] = { OFF };

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
            vx = (x+i);
            vy = (y+j);
            if (vx < 0) vx += ROWS;
            else if (vx >= ROWS) vx -= ROWS;
            if (vy < 0) vy += COLS; 
            else if (vy >= COLS) vy -= COLS; 
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
    scanf("%d %d", &ROWS, &COLS);
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
        usleep(UPDATE_TIME);
        clear_screen();
    }
    return 0;
}
