#include "ft_schmup.h"
#include <ncurses.h>
#include <unistd.h>

void	display_win(t_game game, t_info info)
{
	//clear();
	wclear(game.win);
	wborder(game.win, '|', '|', '_', '_', '/', '\\', '\\', '/');
	//mvprintw(0, 0, "Remaning lives : %d\tElapsed time : %ld:%ld\tCurrent score : %d",
            //*info.ptr_player_lives, info.time.tv_sec / 60, info.time.tv_sec % 60, info.score);
	mvprintw(game.player.row, game.player.col, "%c", game.player.ch);
	ft_lstiter_display(game.enemies);
	ft_lstiter_display(game.p_shots);
	ft_lstiter_display(game.e_shots);
	//touchwin(stdscr);
	//refresh();
	wrefresh(game.win);
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
    t_game game = {0};
	t_info info = {0};
	int	c = 0;

	initscr();
	curs_set(0);
	cbreak();
	game.win = subwin(stdscr, LINES - (WIN_WIDTH - 1) * 2, COLS - (WIN_WIDTH - 1) * 2, 2, 2);
	keypad(game.win, TRUE);
	keypad(stdscr, TRUE);
	//halfdelay(10);
	nodelay(stdscr, true);
	init_enemies(&game.enemies);
	init_player(&game.player);
	noecho();
	display_win(game, info);
	while ((c = getch()) != KEY_F(1))
	{
		update_player(c, &game);
		display_win(game, info);
		usleep(100000000 / 60);
	}
	endwin();
	return (0);
}	
