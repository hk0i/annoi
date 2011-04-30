/* menu.h - menu control */
enum {UP, DOWN, ENTER, ESCAPE};
enum { MENU_MAIN, MENU_NEWGAME, MENU_CREDITS };
void start_game(void);
void machine_input(int);
int  get_cur_menu_item(void);
int  get_cur_menu(void);
void main_menu(void);
extern int gameMenu;
