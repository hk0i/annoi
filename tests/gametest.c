#include <stdio.h>
#include "game.h"

void printTowers(void)
{
    int i, j;       /* loop variables */
    i = j = 0;
    for (i = 0; i < 3; ++i)
    {
        printf("tower%d: ", i+1);
        for (j = 0; j < 10; ++j)
            printf("%d\t",towers[i][j]);
        printf("\n");
    }
}

/* makeMove(): makes the move and shows the towers. */
void makeMove(int src, int dest)
{
    move(src, dest);
    printTowers();
}


/* gameWin(): plays out a successful game */
void gameWin()
{
    printTowers();
    makeMove(0,2);
    makeMove(0,1);
    makeMove(2,1);
    makeMove(0,2);
    makeMove(1,0);
    makeMove(1,2);
    makeMove(0,2);
}

int main(int argc, char **argv)
{
    gameInit(3);
    printTowers();
    makeMove(0,2);
    makeMove(0,2);
    makeMove(0,1);
    return 0;
}
