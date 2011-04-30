/* game.h - handles the game routines and structures. */
/* macro for getting the topmost element of current tower. assumes current tower
 * variable name is 'tower' */
#define TOPMOST_RING top[tower]
#ifdef GAME
/* this is the backend representation of our towers, which are 3 stacks */
int towers[3][10];

/* top stores the number of elements in each tower */
int top[3];

/* maxRing represents the amount of rings we're using (so in a sense, the
 * difficulty level of the game */
int maxRing;

/* turns represents the amount of turns we've used so far */
int turns;
/* tells us if they won yet */
int gameWon;

unsigned int currentRing;
unsigned int currentTower;
/* the tower that the currentRing came from */
int srcTower;
#else
extern int towers[3][10];
extern int turns;
extern int gameWon;
extern int maxRing;
extern unsigned int currentRing;
extern unsigned int currentTower;
extern int srcTower;
#endif

int checkWin(void);
int move(int,int);
int peek(int);
void gameInit(int);
void gameReset(int);
void printTowers(void);
