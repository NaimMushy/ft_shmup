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
	game.fd = open("./log.txt", O_CREAT | O_RDWR);
	if (ret != SUCCESS)
		return (ret);
	curtime = game.info.t_zero;
	display_game(game, &game.frame_time);
	while ((input = getch()) != KEY_F(1))
	{
		ret = gettimeofday(&game.frame_time, NULL);
		if (ret != 0)
			return (ERROR_SYSCALL);
		update_all(input, &game);
		display_game(game, &curtime);
		if (ret != SUCCESS)
			break ;
		wait_next_frame(&game.frame_time, curtime);
		refresh();
		wrefresh(game.win);
		++game.f_counter;
	}
	endwin();
	return (ret);
}	
