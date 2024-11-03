#include <windows.h>
#include <conio.h>

#include "include.h"


int get_key(void)
{
    int kb = kbhit();
    if (kb == 0)
        return 0;
    int key = getch();
    if (key == 224)
    {
        key = getch();
    }
    switch (key)
    {
        case 'w':
        case 'W':
        case 72:
            return Up;
        case 's':
        case 'S':
        case 80:
            return Down;
        case 'a':
        case 'A':
        case 75:
            return Left;
        case 'd':
        case 'D':
        case 77:
            return Right;
        case 13:
            return Center;
        default:
            return 0;
    }
}
