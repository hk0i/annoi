#include <stdio.h>
#include <stdlib.h>
#include "../menu.h"

char menuitems[][32] = {
    "0 New Game",
    "0 Credits",
    "0 Exit",
    "1 3 Rings - Easy",
    "1 4 Rings - Normal",
    "1 5 Rings - Difficult?"
};

void display_menu(int tier)
{
    int i = 0;
    int menu_num = 0;
    printf("get_cur_menu_item() == %d\n", get_cur_menu_item());
    printf("tier: %d\n", tier);
    for (i = 0; i < 6; ++i)
    {
        if (atoi(&menuitems[i][0]) == tier)
        {
            printf("%s", menuitems[i]+2);
            if (get_cur_menu_item() == menu_num)
                printf(" *");
            putc('\n', stdout);
            ++menu_num;
        }
    }
}

int convert_input(int in)
{
    switch (in)
    {
        case 'k':
        case 'K':
            return DOWN;
            break;

        case 'i':
        case 'I':
            return UP;
            break;

        case 'l':
        case 'L':
            return ENTER;
            break;

        case 'j':
        case 'J':
            return ESCAPE;
            break;
    }
}

int main(int argc, char **argv)
{
    int ch;
    int tier = 0;
    do
    {
        if (ch != '\n')
        {
            machine_input(convert_input(ch));
            display_menu(get_cur_menu());
            printf("---\n");
        }
    }
    while( (ch = getchar()) != EOF );
    return 0;
}
