#include "ft_schmup.h"
#include <sys/time.h>

static int	ft_lstiter_display(t_entitylist *lst, t_game *game, int c_pair);
static int	display_info(t_info info, struct timeval *ptr_curtime);

int	display_game(t_game game, struct timeval *ptr_curtime)
{
	int	ret;

	if (werase(game.win) == ERR)
		return (ERROR_NCURSES);
	wattron(game.win, COLOR_PAIR(CYAN));
	if (wborder(game.win, '|', '|', ' ', ' ', ' ', ' ', ' ', ' '))
		return (ERROR_NCURSES);
	wattroff(game.win, COLOR_PAIR(CYAN));
	wattron(game.win, COLOR_PAIR(GREEN));
	if (mvwaddch(game.win, game.player.row, game.player.col, game.player.app) == ERR)
		return (ERROR_NCURSES);
	wattroff(game.win, COLOR_PAIR(GREEN));
	ret = ft_lstiter_display(game.enemies, &game, RED);
	if (ret != SUCCESS)
		return (ret);
	ret = ft_lstiter_display(game.p_shots, &game, YELLOW);
	if (ret != SUCCESS)
		return (ret);
	ret = ft_lstiter_display(game.e_shots, &game, MAGENTA);
	if (ret != SUCCESS)
		return (ret);
	ret = display_info(game.info, ptr_curtime);
	if (ret != SUCCESS)
		return (ret);
	return (SUCCESS);
}

static int	ft_lstiter_display(t_entitylist *lst, t_game *game, int c_pair)
{
	wattron(game->win, COLOR_PAIR(c_pair));
	while (lst)
	{
		if (mvwaddch(game->win, lst->data.row, lst->data.col, lst->data.app) == ERR)
		{
			wattroff(game->win, COLOR_PAIR(c_pair));
			return (ERROR_NCURSES);
		}
		lst = lst->next;
	}
	wattroff(game->win, COLOR_PAIR(c_pair));
	return (SUCCESS);
}

static int	display_info(t_info info, struct timeval *ptr_curtime)
{
	int				ret;
	
	ret = gettimeofday(ptr_curtime, NULL);
	if (ret == 1)
		return (ERROR_SYSCALL);
	attron(COLOR_PAIR(WHITE));
	mvprintw(0, 0, "Remaining lives : %d\tElapsed time : %ld:%02ld\tCurrent score : %010d",
		*info.ptr_player_hp,
		(ptr_curtime->tv_sec - info.t_zero.tv_sec) / 60,
		(ptr_curtime->tv_sec - info.t_zero.tv_sec) % 60,
		info.score);
	attroff(COLOR_PAIR(WHITE));
	return (SUCCESS);
}
