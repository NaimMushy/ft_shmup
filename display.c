#include "ft_schmup.h"
#include <sys/time.h>

void	display_game(t_game game, struct timeval *ptr_curtime)
{
	//clear();
	//erase();
	mvprintw(game.player.row, game.player.col, "%c", game.player.ch);
	ft_lstiter_display(game.enemies);
	ft_lstiter_display(game.p_shots);
	ft_lstiter_display(game.e_shots);
	display_info(game.info, ptr_curtime);
	werase(game.win);
	wborder(game.win, '|', '|', '_', '_', '/', '\\', '\\', '/');
	//touchwin(stdscr);
	//refresh();
	//wrefresh(game.win);
	return ;
}

void	ft_lstiter_display(t_entitylist *lst)
{
	while (lst)
	{
		mvprintw(lst->data.row, lst->data.col, "%c", lst->data.ch);	
		lst = lst->next;
	}
}

int	display_info(t_info info, struct timeval *ptr_curtime)
{
	int				ret;
	
	ret = gettimeofday(ptr_curtime, NULL);
	if (ret == 1)
		return (ERROR_SYSCALL);
	mvprintw(0, 0, "Remaning lives : %d\tElapsed time : %ld:%02ld\tCurrent score : %010d",
		*info.ptr_player_hp,
		(ptr_curtime->tv_sec - info.t_zero.tv_sec) / 60,
		(ptr_curtime->tv_sec - info.t_zero.tv_sec) % 60,
		info.score);
	return (SUCCESS);
}
