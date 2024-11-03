#include <stdlib.h>
#include <stdio.h>
#include "include.h"

static COORD        food_pos;
static unsigned int food_refresh_time = 0;

COORD get_food_position(void)
{
    return food_pos;
}

// 生成食物随机位置
static void generate_food_position(int* outx, int* outy)
{
    int i = 0;
    int length = get_snake_body_length();
    while (1)
    {
        int    isusefull = 1;
        int    rand_x = rand() % WIDTH;
        int    rand_y = rand() % HEIGHT;
        COORD* snake = get_snake();
        for (i = 0; i <= length; i++)
        {
            if (rand_x == snake[i].X && rand_y == snake[i].Y)
            {
                isusefull = 0;
                break;
            }
            else if (rand_x == 0 || rand_y == 0)
            {
                isusefull = 0;
                break;
            }
        }
        if (!isusefull)
        {
            continue;
        }
        *outx = rand_x;
        *outy = rand_y;
        break;
    }
}

// 刷新食物
void refresh_food_position()
{
    int x, y;
    generate_food_position(&x, &y);
    goto_xy(x, y);
    putchar('@');
    food_pos.X = x;
    food_pos.Y = y;
    // 刷新食物之后，food_refresh_time置为0，重新计时
    food_refresh_time = 0;
}

// 周期性刷新食物
void refresh_food_loop()
{
    if (food_refresh_time == 25)
    {
        // 清除原来未被吃掉的食物
        goto_xy(food_pos.X, food_pos.Y);
        putchar(' ');
        // 重新刷新食物
        refresh_food_position();
    }
}

void food_refresh_time_add()
{
    food_refresh_time++;
}