#include <ncurses.h>
#include "ft_schmup.h"

int init_window(WINDOW **ptr_win, t_info info)
{
    *ptr_win = newwin(0,0,0,0);
    if (*ptr_win == NULL)
        return (ERROR_NCURSES);
    mvprintw(0, 0, "Remaning lives : %d\tElapsed time : %d:%d\tCurrent score : %d",
            *info.ptr_player_lives, time.se);
    return (SUCCESS);
}