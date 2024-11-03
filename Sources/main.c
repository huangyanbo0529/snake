#include <stdlib.h>
#include <conio.h>
#include "include.h"


void goto_xy(int x, int y)
{
    COORD  pos = { .X = x, .Y = y };
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, pos);
}

int main(int argc, char* argv[])
{
    draw_wall();
    draw_menu();
    int menu = select_menu();
    if (menu)
    {
        draw_wall();
        draw_init_snake();
        refresh_food_position();
    }
    else
    {
        return 0;
    }

    int direction = Right;
    while (1)
    {
        int new_dir = get_key();
        if (new_dir == 0 || new_dir == Center)
        {
            direction = direction;
        }
        else if (new_dir == Up && direction == Down)
        {
            direction = direction;
        }
        else if (new_dir == Down && direction == Up)
        {
            direction = direction;
        }
        else if (new_dir == Left && direction == Right)
        {
            direction = direction;
        }
        else if (new_dir == Right && direction == Left)
        {
            direction = direction;
        }
        else
        {
            direction = new_dir;
        }

        COORD new_snake_head = get_new_snake_head(direction);
        snake_move(new_snake_head);

        // 判断是否撞墙
        int ret = is_snake_move_to_wall(new_snake_head);
        if (ret == 0)
        {
            break;
        }


        // 判断是否吃到食物
        COORD food_pos = get_food_position();
        ret = is_snake_eat_food(new_snake_head, food_pos);
        if (ret == 0)
        {
            refresh_food_position();
        }

        // 判断是否撞到自身
        ret = is_snake_eat_self(new_snake_head);
        if (ret == 0)
        {
            break;
        }

        // 周期性刷新食物
        refresh_food_loop();
        Sleep(200);
        food_refresh_time_add();
    }
    system("pause");
    return 0;
}
