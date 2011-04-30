/* quick SDL test */
#include "SDL.h"
#include "SDL_image.h"

SDL_Surface *screen = NULL;
SDL_Surface *background = NULL;

SDL_Surface *loadImage( char *filename )
{
    SDL_Surface *tmpImage = NULL;
    SDL_Surface *optImage = NULL;

    tmpImage = IMG_Load( filename );

    if (tmpImage)
    {
        optImage = SDL_DisplayFormat( tmpImage );
        SDL_FreeSurface( tmpImage );
    }

    return optImage;
}

void applySurface( int x, int y, SDL_Surface *src, SDL_Surface *dest )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( src, NULL, dest, &offset );
}

int main( int argc, char **argv )
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;
    screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );

    if (!screen)
        return 2;

    SDL_WM_SetCaption( "Testing SDL...", NULL );
    background = loadImage( "images/background.png" );
    applySurface( 0, 0, background, screen );
    if (SDL_Flip(screen) < 0)
        return 3;
    SDL_Delay( 2000 );

    SDL_FreeSurface( background);
    SDL_Quit();
    return 0;
}
