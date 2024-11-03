#include <string.h>
#include <stdio.h>
#include "include.h"

const char start_game[] = "Start Game";
const char exit_game[] = "Exit Game";


COORD exit_pos = {
    .X = WIDTH / 2 - strlen(start_game) / 2,
    .Y = HEIGHT / 2 + 2
};

COORD start_pos = {
    .X = WIDTH / 2 - strlen(start_game) / 2,
    .Y = HEIGHT / 2
};

void draw_wall(void)
{
    int x, y = 0;
    goto_xy(0, 0);
    for (y = 0; y <= HEIGHT; y++)
    {
        for (x = 0; x <= WIDTH; x++)
        {
            if (y == 0 || y == HEIGHT)
            {
                putchar('*');
            }
            else if (x == 0 || x == WIDTH)
            {
                putchar('*');
            }
            else
            {
                putchar(' ');
            }
        }
        puts("");
    }
}


void draw_menu(void)
{
    goto_xy(start_pos.X, start_pos.Y);
    puts(start_game);
    goto_xy(exit_pos.X, exit_pos.Y);
    puts(exit_game);
}

int select_menu(void)
{
    COORD menu_init_pos = start_pos;
    goto_xy(start_pos.X - 2, start_pos.Y);
    putchar('O');
    while (1)
    {
        int key = get_key();
        if (key == Up || key == Down)
        {
            if (menu_init_pos.X == start_pos.X && menu_init_pos.Y == start_pos.Y)
            {
                goto_xy(start_pos.X - 2, start_pos.Y);
                putchar(' ');
                goto_xy(exit_pos.X - 2, exit_pos.Y);
                putchar('O');
                menu_init_pos = exit_pos;
            }
            else if (menu_init_pos.X == exit_pos.X && menu_init_pos.Y == exit_pos.Y)
            {
                goto_xy(exit_pos.X - 2, exit_pos.Y);
                putchar(' ');
                goto_xy(start_pos.X - 2, start_pos.Y);
                putchar('O');
                menu_init_pos = start_pos;
            }
        }
        if (key == Center)
        {
            goto_xy(start_pos.X, 2 * start_pos.Y + 2);
            if (menu_init_pos.X == start_pos.X && menu_init_pos.Y == start_pos.Y)
            {
                return 1;
            }
            else if (menu_init_pos.X == exit_pos.X && menu_init_pos.Y == exit_pos.Y)
            {
                return 0;
            }
        }
    }
}