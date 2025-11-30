#include "ft_schmup.h"
#include <ncurses.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    int		ret;
	t_game	game = {0};
	struct timeval	curtime;
	int		input = 0;

	ret = init_all(&game);
	if (ret != SUCCESS)
		return (ret);
	curtime = game.info.t_zero;
	ret = display_game(game, &game.frame_time);
	if (ret != SUCCESS)
	{
		free_all(game);
		return (ret);
	}
	while ((input = getch()) != KEY_F(1))
	{
		ret = gettimeofday(&game.frame_time, NULL);
		if (ret != 0)
		{
			free_all(game);
			break ;
		}
		ret = update_all(input, &game);
		if (ret != SUCCESS || game.player.hp == 0)
		{
			if (ret != SUCCESS)
				free_all(game);
			break ;
		}
		ret = display_game(game, &curtime);
		if (ret != SUCCESS)
		{
			free_all(game);
			break ;
		}
		wait_next_frame(&game.frame_time, curtime);
		if (refresh() == ERR)
		{
			free_all(game);
			ret = ERROR_NCURSES;
			break ;
		}
		if (wrefresh(game.win))
		{
			free_all(game);
			ret = ERROR_NCURSES;
			break ;
		}
		++game.f_counter;
	}
	endwin();
	return (ret);
}	
