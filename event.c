/* event.c - handles SDL events */
#include "SDL.h"
#include "game.h"
#define  EVENT
#include "event.h"
#include "display.h"
#include "constants.h"

/* sdltomenu: converts SDL keys to menu input */
int sdltomenu(SDLKey sym)
{
    switch (sym)
    {
        case SDLK_i:
        case SDLK_UP:
            return UP;
            break;

        case SDLK_k:
        case SDLK_DOWN:
            return DOWN;
            break;

        case SDLK_RETURN:
        case SDLK_l:
        case SDLK_RIGHT:
            return ENTER;
            break;

        case SDLK_ESCAPE:
        case SDLK_j:
        case SDLK_LEFT:
            return ESCAPE;
            break;

        default: break;
    }
}

/* eventKeyDown: handle key down event */
void eventKeyDown( SDLKey sym )
{
    if (gameMenu)
    {
        machine_input(sdltomenu(sym));
        return;
    }
    switch(sym)
    {
        case SDLK_i:
        case SDLK_UP:
            if (!gameWon)
            {
                /* grab a ring */
                if (!currentRing)
                {
                    srcTower = currentTower;
                    selectRing();
                }
            }
            break;

        case SDLK_k:
        case SDLK_DOWN:
            if (!gameWon)
            {
                /*fprintf(stderr, "srcTower: %d, currentTower: %d, currentRing: %d\n",
                        srcTower, currentTower, currentRing);*/
                /* drop ring */
                if (srcTower >= 0)
                    if (move(srcTower, currentTower))
                    {
                        currentRing = 0;
                        srcTower = -1;
                    }
            }
            break;

        case SDLK_j:
        case SDLK_LEFT:
            if (!gameWon)
            {
                /* move cursor one ring to the left */
                if (currentTower > 0)
                    currentTower--;
            }
            break;

        case SDLK_l:
        case SDLK_RIGHT:
            if (!gameWon)
            {
                /* move cursor one right to the right */
                if (currentTower < 2)
                    currentTower++;
            }
            break;

        case SDLK_s:
            screenshot();
            break;

        case SDLK_RETURN:
            if (gameWon)
            {
                if (maxRing < 10)
                    gameReset(maxRing+1);
            }
            break;


        case SDLK_r:
            if (!gameWon)
            {
                /* reset the current game */
                fprintf(stderr, "Resetting game board...\n");
                gameReset(maxRing);
            }
            break;

        case SDLK_ESCAPE:
            main_menu();
            break;

        default:
            /* default case to avoid warnings */
            break;
    }
}

void eventMainLoop( void )
{
    while (SDL_PollEvent(&event))
    {
        switch( event.type )
        {
            case SDL_QUIT:
                exit( 0 );
                break;

            case SDL_KEYDOWN:
                eventKeyDown(event.key.keysym.sym);
                break;

            default:
                /* default case to avoid compiler warnings */
                break;
        }
    }
} 
