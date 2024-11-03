#include <stdio.h>
#include "include.h"

static COORD snake[1024];
static int   snake_body_length = 0;
static COORD last_body_pos;

void draw_init_snake(void)
{
    snake[0].X = WIDTH / 2;
    snake[0].Y = HEIGHT / 2;
    goto_xy(snake[0].X, snake[0].Y);
    putchar('O');
    snake[1].X = WIDTH / 2 - 1;
    snake[1].Y = HEIGHT / 2;
    goto_xy(snake[1].X, snake[1].Y);
    putchar('+');
    snake_body_length++;
}

int get_snake_body_length(void)
{
    return snake_body_length;
}

COORD* get_snake(void)
{
    return snake;
}

COORD get_new_snake_head(Direction dir)
{
    COORD pos; // 记录不同方向，蛇头新的坐标位置
    switch (dir)
    {
        case Right:
            pos.X = snake[0].X + 1;
            pos.Y = snake[0].Y;
            break;
        case Left:
            pos.X = snake[0].X - 1;
            pos.Y = snake[0].Y;
            break;
        case Up:
            pos.X = snake[0].X;
            pos.Y = snake[0].Y - 1;
            break;
        case Down:
            pos.X = snake[0].X;
            pos.Y = snake[0].Y + 1;
            break;
        default:
            pos.X = snake[0].X;
            pos.Y = snake[0].Y;
            break;
    }
    return pos;
}

void snake_move(COORD new_head)
{
    int i = 0;
    last_body_pos.X = snake[snake_body_length].X;
    last_body_pos.Y = snake[snake_body_length].Y;

    // 将蛇移动前最后的一个位置擦除
    goto_xy(snake[snake_body_length].X, snake[snake_body_length].Y);
    putchar(' ');

    // 蛇移动后的坐标绘制
    for (i = snake_body_length; i > 0; i--)
    {
        snake[i].X = snake[i - 1].X;
        snake[i].Y = snake[i - 1].Y;
        goto_xy(snake[i].X, snake[i].Y);
        // 绘制身体
        putchar('+');
    }
    snake[0].X = new_head.X;
    snake[0].Y = new_head.Y;
    goto_xy(snake[0].X, snake[0].Y);
    // 绘制新的蛇头
    putchar('O');
}

/*
【经验提示】
 1 - 代表某种错误，比如此处的结果错误，带一个负号是为了避免和其他的可能的返回某种长度的功能函数的返回值冲突
 0 - 在大多数程序设计中，0值代表返回结果成功或者是正确的
*/

int is_snake_move_to_wall(COORD new_head)
{
    // 判断是否撞墙，此处返回0表示撞墙，返回-1没有撞墙
    if (new_head.X == 0 || new_head.X == WIDTH || new_head.Y == 0 || new_head.Y == HEIGHT)
    {
        goto_xy(0, HEIGHT + 2);
        printf("Game Over!!!\r\n");
        return 0;
    }
    return -1;
}

int is_snake_eat_food(COORD new_head, COORD food_pos)
{
    // 判断新的蛇头是否跟食物重叠，重叠即吃到食物，蛇的生体加上长一节，新的食物出现在合法的位置
    // 吃到食物蛇的身体增长一节，到原来身体最后一节的位置
    // 此处吃到食物返回0，没有吃到食物返回-1
    if (new_head.X == food_pos.X && new_head.Y == food_pos.Y)
    {
        snake_body_length++;
        snake[snake_body_length].X = last_body_pos.X;
        snake[snake_body_length].Y = last_body_pos.Y;
        goto_xy(snake[snake_body_length].X, snake[snake_body_length].Y);
        putchar('*');
        return 0;
    }
    return -1;
}

int is_snake_eat_self(COORD new_head)
{ // 此处撞到自己返回0，没有撞到自己返回-1
    int i = 0;
    for (i = 1; i <= snake_body_length; i++)
    {
        if (new_head.X == snake[i].X && new_head.Y == snake[i].Y)
        {
            goto_xy(0, HEIGHT + 2);
            printf("Game Over!!!\r\n");
            return 0;
        }
    }
    return -1;
}