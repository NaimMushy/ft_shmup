#include "ft_schmup.h"
#include <ncurses.h>
#include <unistd.h>

int main(void)
{
    int		ret;
	t_game	game = {0};
	struct timeval	curtime;
	int		input = 0;

	initscr();
	curs_set(0);
	cbreak();
	noecho();
	game.win = subwin(stdscr, N_LINES - (WIN_WIDTH - 1) * 2, N_COLS - (WIN_WIDTH - 1) * 2, 2, 2);
	keypad(game.win, TRUE);
	keypad(stdscr, TRUE);
	nodelay(stdscr, true);
	nodelay(game.win, true);
	ret = init_all(&game);
	if (ret != SUCCESS)
		return (ret);
	curtime = game.info.t_zero;
	display_game(game, &game.frame_time);
	//display_info(game->info, &game.frame_time);
	while ((input = getch()) != KEY_F(1))
	{
		ret = gettimeofday(&game.frame_time, NULL);
		if (ret != 0)
			return (ERROR_SYSCALL);
		update_all(input, &game);
		display_game(game, &curtime);
		//ret = display_info(game.info, &curtime);
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
