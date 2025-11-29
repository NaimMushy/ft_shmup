#include "ft_schmup.h"
#include <ncurses.h>

void	display_win(t_game *game)
{
	clear();
	mvprintw(game->player.row, game->player.col, "%c", game->player.ch);
	ft_lstiter_display(game->enemies);
	ft_lstiter_display(game->p_shots);
	ft_lstiter_display(game->e_shots);
	refresh();
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
	int	c = 0;

	initscr();
	keypad(stdscr, TRUE);
	init_enemies(&game.enemies);
	init_player(&game.player);
	noecho();
	display_win(&game);
	while ((c = getch()) != KEY_F(1))
	{
		update_player(c, &game);
		display_win(&game);
	}
	endwin();
	return (0);
}	
