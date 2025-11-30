#include "ft_schmup.h"
#include <sys/time.h>

static int	ft_lstiter_display(t_entitylist *lst);
static int	display_info(t_info info, struct timeval *ptr_curtime);

int	display_game(t_game game, struct timeval *ptr_curtime)
{
	int	ret;

	if (werase(game.win) == ERR)
		return (ERROR_NCURSES);
	if (wborder(game.win, '|', '|', '=', '=', '/', '\\', '\\', '/'))
		return (ERROR_NCURSES);
	if (mvaddch(game.player.row, game.player.col, game.player.ch) == ERR)
		return (ERROR_NCURSES);
	ret = ft_lstiter_display(game.enemies);
	if (ret != SUCCESS)
		return (ret);
	ret = ft_lstiter_display(game.p_shots);
	if (ret != SUCCESS)
		return (ret);
	ret = ft_lstiter_display(game.e_shots);
	if (ret != SUCCESS)
		return (ret);
	ret = display_info(game.info, ptr_curtime);
	if (ret != SUCCESS)
		return (ret);
	return (SUCCESS);
}

static int	ft_lstiter_display(t_entitylist *lst)
{
	while (lst)
	{
		if (mvaddch(lst->data.row, lst->data.col, lst->data.ch) == ERR)
			return (ERROR_NCURSES);	
		lst = lst->next;
	}
	return (SUCCESS);
}

static int	display_info(t_info info, struct timeval *ptr_curtime)
{
	int				ret;
	
	ret = gettimeofday(ptr_curtime, NULL);
	if (ret == 1)
		return (ERROR_SYSCALL);
	mvprintw(0, 0, "Remaining lives : %d\tElapsed time : %ld:%02ld\tCurrent score : %010d",
		*info.ptr_player_hp,
		(ptr_curtime->tv_sec - info.t_zero.tv_sec) / 60,
		(ptr_curtime->tv_sec - info.t_zero.tv_sec) % 60,
		info.score);
	return (SUCCESS);
}
