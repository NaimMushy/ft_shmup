#include "ft_schmup.h"
#include <ncurses.h>

void	display_win(t_game *game)
{
	clear();
	mvprintw(game->player.row, game->player.col, "%c", game->player.ch);
	ft_lstiter(&game->enemies, &(mvwprintw());
	ft_lstiter(&game->p_shots, &(mvwprintw());
	ft_lstiter(&game->e_shots, &(mvwprintw());
	refresh();
	return ;
}

void	init_enemies(t_listentity *enemies)
{
	t_listentity	*enemy;

	enemy = ft_lstnew(5, 6);
	ft_lstadd_front(&enemies, enemy);
	enemy = ft_lstnew(10, 15);
	ft_lstadd_front(&enemies, enemy);
	enemy = ft_lstnew(3, 70);
	ft_lstadd_front(&enemies, enemy);
	return ;
}

int main(void)
{
    t_game game = {0};
	char	c = 0;

	initscr();
	keypad(game.w, TRUE);
	init_enemies(&game.enemies);
	init_player(&game.player);
	noecho();
	while ((c = getch()) != KEY_F(1))
	{
		update_player(c, &game);
		display_win(&game);
	}
	endwin();
	return (0);
}	
