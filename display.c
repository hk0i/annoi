/* display.c - graphic functions for hanoi */
#include <stdlib.h>     /* for atexit() */
#include "SDL.h"
#include "SDL_image.h"
#define DISPLAY
#include "game.h"
#include "display.h"
#include "constants.h"

/* screenshot: takes a screenshot of the game.
 *
 * TODO:  Do something sensible involving file numbering of screenshots */
void screenshot(void)
{
    SDL_SaveBMP(screen, "screenshot.bmp");
    fprintf(stderr, "Screenshot recorded.\n");
}

SDL_Surface *loadImage( char *filename )
{
    SDL_Surface *tmpImg = NULL;
    SDL_Surface *optImg = NULL;

    /* load the image to a temporary surface */
    tmpImg = IMG_Load( filename );

    if (tmpImg)
    {
        /* optimize it by changing it to display format */
        optImg = SDL_DisplayFormat( tmpImg );
        /* free the temporary surface */
        SDL_FreeSurface( tmpImg );

        if (optImg)
        {
            /* once we have an optimized image, we'll create and apply a
             * colorkey */
            Uint32 colorkey = SDL_MapRGB( optImg->format, 0, 0xFF, 0xFF);
            /* apply the colorkey */
            SDL_SetColorKey( optImg, SDL_SRCCOLORKEY, colorkey );
        }
    }
    return optImg;
}

/* loadSurf: takes a (pointer to) a (pointer to) a surface, and a file name,
 *           then loads the file and points the pointer to the newly made
 *           image. Returns TRUE on success, FALSE on failure */
int loadSurf( SDL_Surface **surf, char *filename )
{
    /* output message */
    fprintf(stderr, "Loading %s...", filename);
    *surf = loadImage( filename );
    if (!surf)
    {
        fprintf(stderr,"\tERROR LOADING IMAGE: %s\n", filename);
        return FALSE;
    }
    fprintf(stderr, "\tImage loaded!\n");
    return TRUE;
}

/* spriteCut: sets clip rects up for the appropriate sprites */
void spriteCut(void)
{
    int i = 0;  /* loop counter */
    /* fill the towerClip array with appropriate values */
    towerClip[TOWER_STATE_NORMAL].x = 0;
    towerClip[TOWER_STATE_NORMAL].y = 0;
    towerClip[TOWER_STATE_NORMAL].w = 30;
    towerClip[TOWER_STATE_NORMAL].h = 300;

    towerClip[TOWER_STATE_HOVER].x = 60;
    towerClip[TOWER_STATE_HOVER].y = 0;
    towerClip[TOWER_STATE_HOVER].w = 30;
    towerClip[TOWER_STATE_HOVER].h = 300;

    towerClip[TOWER_STATE_CLICKED].x = 120;
    towerClip[TOWER_STATE_CLICKED].y = 0;
    towerClip[TOWER_STATE_CLICKED].w = 30;
    towerClip[TOWER_STATE_CLICKED].h = 300;

    /* clip the ring sprite */
    ringClip[TOWER_STATE_HOVER].x = 0;
    ringClip[TOWER_STATE_HOVER].y = 0;
    ringClip[TOWER_STATE_HOVER].w = 200;
    ringClip[TOWER_STATE_HOVER].h = 30;

    ringClip[TOWER_STATE_CLICKED].x = 0;
    ringClip[TOWER_STATE_CLICKED].y = 30;
    ringClip[TOWER_STATE_CLICKED].w = 200;
    ringClip[TOWER_STATE_CLICKED].h = 30;

    ringClip[TOWER_STATE_NORMAL].x = 0;
    ringClip[TOWER_STATE_NORMAL].y = 60;
    ringClip[TOWER_STATE_NORMAL].w = 200;
    ringClip[TOWER_STATE_NORMAL].h = 30;

    /* normal menu states */
    for (i = 0; i < 6; ++i)
    {
        menuClip[i].x = 0;
        menuClip[i].y = 40 * i;
        menuClip[i].w = 640;
        menuClip[i].h = 40;
    }
    for (i = 6; i < 12; ++i)
    {
        menuClip[i].x = 640;
        menuClip[i].y = 40 * (i-6);
        menuClip[i].w = 640;
        menuClip[i].h = 40;
    }

}

void loadImages(void)
{
    fprintf( stderr, "Loading all images...\n");
    if (!loadSurf(&background, "images/background.png"))
        exit(EXIT_FAILED_IMAGE_LOAD);
    if (!loadSurf(&tower, "images/tower.png"))
        exit(EXIT_FAILED_IMAGE_LOAD);
    if (!loadSurf(&ring, "images/ring.png"))
        exit(EXIT_FAILED_IMAGE_LOAD);
    if (!loadSurf(&win, "images/win.png"))
        exit(EXIT_FAILED_IMAGE_LOAD);
    if (!loadSurf(&menu, "images/menu.png"))
        exit(EXIT_FAILED_IMAGE_LOAD);
    if (!loadSurf(&credits, "images/credits.png"))
        exit(EXIT_FAILED_IMAGE_LOAD);

    /* cut sprites up */
    spriteCut();

    fprintf( stderr, "All images loaded successfully!\n" );
}

void cleanUp(void)
{
    /* free all surface */
    SDL_FreeSurface( background );
    SDL_FreeSurface( win );
    SDL_FreeSurface( tower );
    SDL_FreeSurface( ring );

    /* quit SDL */
    SDL_Quit();
}

void applySurface( int x, int y, SDL_Surface *src, SDL_Surface *dest,
                   SDL_Rect *clip )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( src, clip, dest, &offset );
}

/* setBackground: applies provided surface to screen a the origin (0,0)
 *                with no clipping */
void setBackground (SDL_Surface *bgsurf)
{
    applySurface (0, 0, bgsurf, screen, NULL);
}

/* drawRing(): draws (ring) on (towNum) with (ringTop) height offset */
void drawRing(int towNum, int ringNum, int ringTop)
{    
    int x;              /* x coordinate for ring */
    int ringDiff;       /* difference in ring size */
    SDL_Rect offset;    /* new offset, this changes the size of the ring */
    x = 0;

    ringDiff = (10-ringNum) * 20;
    /* copy original offset */
    offset.x = ringClip[TOWER_STATE_NORMAL].x;
    offset.y = ringClip[TOWER_STATE_NORMAL].y;
    offset.w = ringClip[TOWER_STATE_NORMAL].w - ringDiff;
    offset.h = ringClip[TOWER_STATE_NORMAL].h;

    //x = towerPos[towNum];
    if (ringNum == currentRing)
        x = towerPos[currentTower] - (offset.w/2) + 15;
    else
        x = towerPos[towNum] - (offset.w/2) + 15;

    applySurface(x, ringTop, ring, screen, &offset);
}

/* drawTower: draws tower sprite and appropriate number of rings,
 *            according to the values in rings array. */
void drawTower(int towNum, int rings[])
{
    int i;      /* loop counter */
    int state;  /* current tower state */
    i = 0;
    /* set current tower state */
    if (towNum == currentTower)
        state = TOWER_STATE_HOVER;
    else
        state = TOWER_STATE_NORMAL;
    /* draw the tower first */
    applySurface(towerPos[towNum], SCREEN_HEIGHT-320, tower, screen,
                 &towerClip[state]);
    /* then draw the appropriate number of rings */
    for (i = 0; rings[i] != 0; ++i)
        if (rings[i] != currentRing)
            drawRing(towNum, rings[i],SCREEN_HEIGHT - 50 - (30*i));
        else
            drawRing(towNum, rings[i],SCREEN_HEIGHT - 380);
}

void drawMenu(int which)
{
    int low = 0, high = 0;
    int i = 0; /* loop counter */
    int useClip = 0;

    if (which == MENU_CREDITS)
    {
        /* draw credits screen and LEAVE! */
        applySurface(0, 0, credits, screen, NULL);
        return;
    }

    if (which == MENU_MAIN)
    {
        low = 0;
        high = 3;
    }
    else
    {
        low = 3;
        high = 6;
    }
    for (i = low; i < high; ++i)
    {
        useClip = i;
        if (get_cur_menu_item() == (i-low))
            useClip += 6;

        applySurface(0, (SCREEN_HEIGHT / 2) - (40 * (high-i)),
                     menu, screen, &menuClip[useClip]);
    }
}

/* drawScreen(): draws current game state to screen */
void drawScreen(void)
{
    if (gameWon)
    {
        setBackground(win);
        return;
    }
    /* setBackground sets the background image using applySurface() */
    setBackground(background);
    /* debug: print towers 
    printTowers(); /**/
    /* draw towers */
    drawTower(0,towers[0]);
    drawTower(1,towers[1]);
    drawTower(2,towers[2]);

    if (gameMenu)
        drawMenu(get_cur_menu());
}



void init(void)
{
    fprintf(stderr, "Initializing SDL...");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        fprintf(stderr, "\tERROR INITIALIZING SDL AUDIO AND VIDEO: %s\n",
                SDL_GetError());
        exit( EXIT_FAILED_INIT_SDL );
    }
    else
        fprintf( stderr, "\n" );

    fprintf( stderr, "Initializing the screen...\n" );
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
                           SDL_SWSURFACE );
    if (!screen)
    {
        fprintf(stderr, "Could not set video mode %dx%dx%d: %s",
                SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
                SDL_GetError());
        exit( EXIT_FAILED_VIDEO_MODE );
    }


    SDL_WM_SetCaption( APP_TITLE, NULL );

    /* set up clean shut down routine */
    atexit(cleanUp);
    /* load images */
    loadImages();

    fprintf(stderr, "Init completed successfully!\n");

    currentRing = 0;
    currentTower = 0;
}

/* selectRing(): selects the current ring. */
void selectRing(void)
{
    currentRing = peek(currentTower);
    if (currentRing)
        fprintf(stderr, "selectRing() ring selected: %d.\n", currentRing);
}
