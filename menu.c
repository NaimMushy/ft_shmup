#include <string.h>
#include <unistd.h>
#include "ft_schmup.h"

void	game_over(t_game *game)
{
	int	b_lines, b_cols, txt_line, txt_col, range;
	int		input = 0;

	b_lines = LINES / 3;
	while (!b_lines || b_lines % 3 != 0)
		++b_lines;
	b_cols = COLS >> 1;
	range = (b_lines / 3 + 1) >> 1;
	game->win = subwin(stdscr, b_lines, b_cols, LINES / 3, b_cols >> 1);
	wattron(game->win, COLOR_PAIR(MAGENTA));
	wborder(game->win, '|', '|', '=', '=', '/', '\\', '\\', '/');
	txt_line = range;
	txt_col = (b_cols - strlen("---- GAME OVER ----")) >> 1;
	wattron(game->win, COLOR_PAIR(RED));
	mvwprintw(game->win, txt_line, txt_col, "%s", "---- GAME OVER ----");
	wattron(game->win, COLOR_PAIR(MAGENTA));
	mvwhline(game->win, txt_line + range, 1, '*', b_cols - 1);
	txt_line += range << 1;
	txt_col = (b_cols - (strlen("score : ") + 10)) >> 1;
	wattron(game->win, COLOR_PAIR(CYAN));
	mvwprintw(game->win, txt_line, txt_col, "score : %010d", game->info.score);
	wattron(game->win, COLOR_PAIR(MAGENTA));
	mvwhline(game->win, txt_line + range, 1, '*', b_cols - 1);
	txt_line += range << 1;
	txt_col = (b_cols - (strlen("PRESS F1 TO EXIT"))) >> 1;
	wattron(game->win, COLOR_PAIR(BLUE));
	mvwprintw(game->win, txt_line, txt_col, "%s", "PRESS F1 TO EXIT");
	wattroff(game->win, COLOR_PAIR(BLUE));
	wrefresh(game->win);
	while ((input = getch()) != KEY_F(1))
		usleep(1000000 / FPS_CAP);
	delwin(game->win);
	return ;
}
