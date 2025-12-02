#include "ft_shmup.h"
#include <sys/time.h>

static int	ft_lstiter_display(t_entitylist *lst, t_game *game, int c_pair);

int	display_game(t_game game, struct timeval *curtime)
{
	int	ret;

	if (werase(game.win) == ERR)
		return (ERROR_NCURSES);
	wattron(game.win, COLOR_PAIR(WHITE));
	if (wborder(game.win, '|', '|', '=', '=', '=', '=', '=', '='))
		return (ERROR_NCURSES);
	wattroff(game.win, COLOR_PAIR(WHITE));
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
	ret = display_info(game.info, curtime);
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

int	display_info(t_info info, struct timeval *curtime)
{
	int				ret;
	
	ret = gettimeofday(curtime, NULL);
	if (ret == 1)
		return (ERROR_SYSCALL);
	attron(COLOR_PAIR(CYAN));
	mvprintw(0, 0, "Remaining lives : %d\tElapsed time : %ld:%02ld\tCurrent score : %010d",
		*info.ptr_player_hp,
		(curtime->tv_sec - info.t_zero.tv_sec) / 60,
		(curtime->tv_sec - info.t_zero.tv_sec) % 60,
		info.score);
	attroff(COLOR_PAIR(CYAN));
	return (SUCCESS);
}
