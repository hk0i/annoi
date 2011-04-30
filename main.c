#include "SDL.h"
#include "constants.h"
#include "display.h"
#include "event.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>     /* for atoi() */
#include "SDL_mixer.h"  /* handle background music in this file */

Mix_Music *bgm = NULL;

void musicInit(void)
{
    fprintf(stderr, "(Music) Initializing audio...");
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        fprintf(stderr, "\tFailed.\n"
                "(Music) Error initializing audio: %s\n", Mix_GetError());
        return;
    }
    fprintf(stderr, "\tSuccess!\n(Music) Loading music...");
    bgm = Mix_LoadMUS("bgm.mp3");
    if (!bgm)
    {
        fprintf(stderr, "\tLoad failed, proceeding without music.\n"
                "(Music) Error was: %s\n", Mix_GetError());
        return;
    }
    fprintf(stderr, "\tSuccess!\nStarting music...");
    if (Mix_FadeInMusic(bgm, -1, 500) < 0)
    {
        fprintf(stderr, "\tError Mix_FadeInMusic: %s\n", Mix_GetError());
        return;
    }
    fprintf(stderr, "\tSuccess!\n");

}

void freeMusic(void)
{
    Mix_FreeMusic(bgm);
    Mix_CloseAudio();
}

int main(int argc, char **argv)
{
    int setting;    /* number of rings */
    if (argc > 1)
        setting = atoi(argv[1]);
    else
        setting = 3;
    if (setting > 10)
        setting = 10;
    else if (setting < 3)
        setting = 3;
    /* init display */
    init();
    /* init game variables */

    gameInit(setting);
    musicInit();
    atexit(freeMusic);

    while (1)
    {
        /* eventMainLoop handles all SDL events, when an SDL_QUIT is received,
         * the program will exit */
        eventMainLoop();
        drawScreen();
        if (SDL_Flip(screen) < 0)
        {
            fprintf(stderr, "SDL_Flip() failed to flip screen: %s\n",
                    SDL_GetError());
            return EXIT_FAILED_FLIP;
        }
    }

    return 0;

}
