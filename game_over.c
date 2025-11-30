#include <string.h>
#include "ft_schmup.h"

void	game_over(t_game *game)
{
	int	b_lines, b_cols, txt_lines, txt_cols;
	int		input = 0;

	b_lines = LINES >> 2;
	b_cols = COLS / 3;
	game->win = subwin(stdscr, b_lines, b_cols, b_lines, b_cols >> 1);
	wborder(game->win, '|', '|', '_', '_', '/', '\\', '\\', '/');
	txt_lines = b_lines + b_lines / 3;
	txt_cols = (b_cols - strlen("GAME OVER")) >> 1;
	mvwprintw(game->win, txt_lines, txt_cols, "%s", "GAME OVER");
	mvwhline(game->win, txt_lines + 2, b_cols >> 1, '_', b_cols);
	txt_lines += b_lines / 3;
	txt_cols = (b_cols - (strlen("score : ") + 10)) / 2;
	mvwprintw(game->win, txt_lines, txt_cols, "score : %010d", game->info.score);
	mvwhline(game->win, txt_lines + 2, b_cols >> 1, '_', b_cols);
	txt_lines += b_lines / 3;
	txt_cols = (b_cols - (strlen("PRESS F1 TO EXIT"))) >> 1;
	mvwprintw(game->win, txt_lines, txt_cols, "%s", "PRESS F1 TO EXIT");
	wrefresh(game->win);
	while ((input = getch()) != KEY_F(1))
		usleep(1000000 / FPS_CAP);
	delwin(game->win);
	return ;
}
