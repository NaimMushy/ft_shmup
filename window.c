#include <ncurses.h>
#include "ft_schmup.h"

int init_window(WINDOW **ptr_win, t_info info)
{
    int ret;
    int i;
    
    ret = mvprintw(0, 0, "Remaning lives : %d\tElapsed time : %d:%d\tCurrent score : %d",
            *info.ptr_player_lives, info.time.tv_sec / 60, info.time.tv_sec % 60, info.score);
    if (ret == ERR)
        return (ERROR_NCURSES);
    i = 0;
    while (i < COLS)
    {
        ret = mvprintw(1, i, "_");
        ++i;
    }
    return (SUCCESS);
}
