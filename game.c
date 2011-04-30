/* game.c - handles game routines and datastructures */
#include <stdio.h>
#define GAME
#include "game.h"
#include "constants.h"

/* towerEmpty(): returns TRUE if the tower is empty. */
int towerEmpty(int tower)
{
    if (towers[tower][0] == 0)
        return TRUE;
    return FALSE;
}

/* checkWin(): checks to see if player won the game yet, returns true if
 *             he did */
int checkWin(void)
{
    int i;  /* loop counter */
    i = 0;
    /* if tower 1 and 2 (0 and 1) are empty... */
    if (towerEmpty(0) && towerEmpty(1))
    {
        for (i = 0; i < maxRing; ++i)
            if (towers[2][i] != 10-i)
                return FALSE;
        gameWon = TRUE;
        return TRUE;
    }
    return FALSE;
}
/* gameInit(): initialize all the variables we need to their defaults */
void gameInit(int max)
{
    int i;          /* loop counter */

    fprintf(stderr, "Initializing game variables...");

    /* set number of turns used to 0. */
    turns = 0;
    /* set maxRing, a variable used to check if we won or not :p */
    maxRing = max;
    /* obviously it's a new game, we didn't win yet */
    gameWon = FALSE;
    /* set current tower and current ring to initial values */
    currentTower = 0;
    currentRing  = 0; 
    srcTower = -1;

    /* initialize arrays */
    for (i = 0; i < 10; ++i)
    {
        if (i < max)
            towers[0][i] = 10-i;
        else
            towers[0][i] = 0;
        towers[1][i] = 0;
        towers[2][i] = 0;
    }
    /* reset the top values */
    top[0] = max;
    top[1] = 0;
    top[2] = 0;

    fprintf(stderr, "\tdone!\n");
}

/* gameReset: resets the game (same as gameInit()) */
void gameReset(int max)
{
    gameInit(max);
}

/* pop(): remove top-most ring from (tower) and return it. */
int pop(int tower)
{
    /* get ring value */
    int tmp = towers[tower][--TOPMOST_RING];
    /* remove the ring */
    towers[tower][TOPMOST_RING] = 0;
    return tmp;
}

/* peek(): return top-most ring from (tower), but leave it. */
int peek(int tower)
{
    return (TOPMOST_RING >= 0) ? towers[tower][TOPMOST_RING-1] : 0;
}

/* push(): add (disc) to (tower) */
void push(int tower, int disc)
{
    towers[tower][TOPMOST_RING++] = disc;
}

/* move: move top element from tower (src) to tower (dest)
 *       returns TRUE on a successful move */
int move(int src, int dest)
{
    int disc, pDisc;
    disc = pop(src);
    pDisc = peek(dest);

    /* check here if it's okay to move it!! */
    if (pDisc == 0 || disc < pDisc)
    {
        if (src != dest)
            fprintf(stderr, "Turn %d: Move disc %d from tower%d to tower%d.\n",
                    ++turns, disc, src+1, dest+1);
        push(dest, disc);
        if (checkWin())
            printf("You won!\n");
        return TRUE;
    }
    else
    {
        fprintf(stderr, "Invalid move! (D%d T%d>T%d D%d)\n",
                disc, src+1, dest+1, pDisc);
        push(src, disc);
        return FALSE;
    }
    
}

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
