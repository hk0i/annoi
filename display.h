/* display.h */
#include "menu.h"

/* screen settings, might move these later ?? */
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP    32

/*#define TOWER_POS1    100
#define TOWER_POS2    305
#define TOWER_POS3    510*/

/* old disc positions */
/*#define TOWER_POS1    120
#define TOWER_POS2    290
#define TOWER_POS3    460*/

#define TOWER_STATE_NORMAL  0
#define TOWER_STATE_HOVER   1
#define TOWER_STATE_CLICKED 2

#ifdef DISPLAY

/* surfaces */
SDL_Surface *screen   = NULL;
SDL_Surface *background = NULL;
SDL_Surface *win     = NULL;
SDL_Surface *tower   = NULL;
SDL_Surface *ring    = NULL;
SDL_Surface *menu    = NULL;
SDL_Surface *credits = NULL;

/* tower clipping coordinates */
SDL_Rect towerClip[3];
SDL_Rect ringClip[3];
SDL_Rect menuClip[12];

/* tower positions */
const int towerPos[] = { 100, 305, 510 };
#else
/*extern SDL_Surface *background;*/
extern SDL_Surface *screen;
#endif

void cleanUp(void);
void drawScreen(void);
void drawTower(int, int[]);
void init(void);
void selectRing(void);
void screenshot(void);
void setBackground(SDL_Surface*);

