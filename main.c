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
	//game.fd = open("./log.txt", O_RDWR);
	if (ret != SUCCESS)
	return (ret);
	curtime = game.info.t_zero;
	while ((input = getch()) != KEY_F(1))
	{
		ret = gettimeofday(&game.frame_time, NULL);
		if (ret != 0)
		{
			free_all(game);
			break ;
		}
		ret = update_all(input, &game);
		if (ret != SUCCESS)
		{
			free_all(game);
			break ;
		}
		ret = display_game(game, &curtime);
		if (ret != SUCCESS || game.player.hp == 0)
		{
			free_all(game);
			if (ret == SUCCESS)
				game_over(&game);
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
		if (game.f_counter >= 300)
			game.f_counter = 0;
	}
	endwin();
	return (ret);
}	
