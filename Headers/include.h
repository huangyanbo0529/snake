#ifndef INCLUDE_H_INCLUDE
#define INCLUDE_H_INCLUDE

#include <windows.h>

#define HEIGHT 20
#define WIDTH 30

typedef enum MyEnum {
    Up = 1,
    Down,
    Left,
    Right,
    Center
} Direction;

int    get_key(void);
void   goto_xy(int x, int y);

void   draw_wall(void);
void   draw_menu(void);
int    select_menu(void);

void   draw_init_snake(void);
int    get_snake_body_length(void);
COORD* get_snake(void);
COORD  get_new_snake_head(Direction dir);
void   sname_move(COORD new_head);
int    is_snake_move_to_wall(COORD new_head);
int    is_snake_eat_food(COORD new_head, COORD food_pos);
int    is_snake_eat_self(COORD new_head);

COORD  get_food_position(void);
void   refresh_food_position();
void   refresh_food_loop();
void food_refresh_time_add();

#endif // INCLUDE_H_INCLUDE