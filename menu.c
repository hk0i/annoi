/* menu.c */
#include <stdlib.h>
#include "constants.h"
#include "menu.h"

struct state {
    void (*up)();
    void (*down)();
    void (*enter)();
    void (*escape)();
    int data;
};

int gameMenu = TRUE;

void move_up(void);
void move_down(void);
void new_game(void);
void exit_menu(void);
void exit_game(void);
void show_credits(void);

int current_item = 0;
int current_menu = 0;

/* menu */
struct state machine[] = {
    {move_up, move_down, new_game, exit_menu},      /* new game */
    {move_up, move_down, show_credits, exit_menu},  /* credits */
    {move_up, move_down, exit_game, exit_menu},     /* exit */

    /* Game Menu */
    {move_up, move_down, start_game, exit_menu, 3}, /* 3 rings */
    {move_up, move_down, start_game, exit_menu, 4}, /* 4 rings */
    {move_up, move_down, start_game, exit_menu, 5}  /* 5 rings */
};

void move_down(void) { current_item = (current_item + 1) % 3; }
void move_up(void) { 
    current_item --;
    if (current_item < 0)
        current_item = 2;
}
void show_credits(void)
{
    current_menu = MENU_CREDITS;
}
void exit_menu(void)
{
    current_menu--;
    current_item = 0;
    if (current_menu < 0)
    {
        current_menu = 0;
        current_item = 2;
    } 
}
void exit_game(void) { exit(0); }
void new_game(void) { current_menu = MENU_NEWGAME; }
void start_game(void)
{
    gameInit(machine[current_item + (3*current_menu)].data); 
    gameMenu = FALSE;
}

void machine_input(int control)
{
    int item = 0;
    item = current_item + (3 * current_menu);

    if (current_menu == MENU_CREDITS)
    {
        current_menu = 0;
        return;
    }

    switch (control)
    {
        case UP:     machine[item].up(); break;
        case DOWN:   machine[item].down(); break;
        case ENTER:  machine[item].enter(); break;
        case ESCAPE: machine[item].escape(); break;
        default: break;
    }
}

int get_cur_menu_item(void) { return current_item; }
int get_cur_menu(void) { return current_menu; }

void main_menu(void)
{
    current_item = 0;
    current_menu = 0;
    gameMenu = TRUE;
}
