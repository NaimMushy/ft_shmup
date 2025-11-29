#include "ft_schmup.h"
#include <ncurses.h>
#include <unistd.h>

void	display_game(t_game game)
{	
	//clear();
	werase(game.win);
	wborder(game.win, '|', '|', '_', '_', '/', '\\', '\\', '/');
	mvprintw(game.player.row, game.player.col, "%c", game.player.ch);
	ft_lstiter_display(game.enemies);
	ft_lstiter_display(game.p_shots);
	ft_lstiter_display(game.e_shots);
	//touchwin(stdscr);
	//refresh();
	//wrefresh(game.win);
	return ;
}

void	init_enemies(t_entitylist **enemies)
{
	t_entitylist	*enemy;

	enemy = ft_lstnew(5, 6, 'V');
	ft_lstadd_front(enemies, enemy);
	enemy = ft_lstnew(10, 15, 'V');
	ft_lstadd_front(enemies, enemy);
	enemy = ft_lstnew(3, 70, 'V');
	ft_lstadd_front(enemies, enemy);
	return ;
}

int main(void)
{
    int		ret;
	t_game	game = {0};
	t_info	info = {0};
	struct timeval	curtime;
	int		c = 0;

	initscr();
	curs_set(0);
	cbreak();
	game.win = subwin(stdscr, LINES - (WIN_WIDTH - 1) * 2, COLS - (WIN_WIDTH - 1) * 2, 2, 2);
	keypad(game.win, TRUE);
	keypad(stdscr, TRUE);
	nodelay(stdscr, true);
	nodelay(game.win, true);
	init_enemies(&game.enemies);
	init_player(&game.player);
	noecho();
	ret = init_info(&info, &game);
	if (ret != SUCCESS)
		return (ret);
	curtime = info.t_zero;
	display_game(game);
	display_info(info, &game.frame_time);
	while ((c = getch()) != KEY_F(1))
	{
		ret = gettimeofday(&game.frame_time, NULL);
		if (ret != 0)
			return (ERROR_SYSCALL);
		update_player(c, &game);
		display_game(game);
		ret = display_info(info, &curtime);
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
