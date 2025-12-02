#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "ft_shmup.h"

int	start_menu(void)
{
	WINDOW	*start_win;
	int	s_line, s_col;
	int	input = 0;
	bool	underlined = true;
	char	*title = "FT_SHMUP";
	size_t	len = strlen(title);

	s_line = 17;
	s_col = COLS / 3;
	start_win = newwin(s_line, s_col, LINES / 3, s_col);
	wattron(start_win, COLOR_PAIR(BORDER));
	mvwhline(start_win, 0, 1, ' ', s_col - 1);
	mvwhline(start_win, s_line - 1, 1, ' ', s_col - 1);
	wattron(start_win, COLOR_PAIR(WHITE));
	mvwvline(start_win, 0, 0, '|', s_line);
	mvwvline(start_win, 0, s_col - 1, '|', s_line);
	wattron(start_win, COLOR_PAIR(GREEN));
	mvwhline(start_win, 3, (s_col - 8 - len) >> 1, '*', len + 8);
	mvwhline(start_win, 7, (s_col - 8 - len) >> 1, '*', len + 8);
	mvwvline(start_win, 4, (s_col - 8 - len) >> 1, '*', 3);
	mvwvline(start_win, 4, (s_col - ((s_col - 8 - len) >> 1) - 1), '*', 3);
	mvwaddstr(start_win, 5, (s_col - len) >> 1, title);
	wattron(start_win, COLOR_PAIR(YELLOW) | A_UNDERLINE);
	mvwaddstr(start_win, 10, (s_col - strlen("> start")) >> 1, "> start");
	wattroff(start_win, A_UNDERLINE);
	mvwaddstr(start_win, 12, (s_col - strlen("> start")) >> 1, "> exit");
	refresh();
	wrefresh(start_win);
	keypad(start_win, true);
	while ((input = getch()) != ' ')
	{
		if (input == KEY_DOWN && underlined)
		{
			wattron(start_win, A_UNDERLINE);
			mvwaddstr(start_win, 12, (s_col - strlen("> start")) >> 1, "> exit");
			wattroff(start_win, A_UNDERLINE);
			mvwaddstr(start_win, 10, (s_col - strlen("> start")) >> 1, "> start");
			wrefresh(start_win);
			underlined = false;
		}
		if (input == KEY_UP && !underlined)
		{
			wattron(start_win, A_UNDERLINE);
			mvwaddstr(start_win, 10, (s_col - strlen("> start")) >> 1, "> start");
			wattroff(start_win, A_UNDERLINE);
			mvwaddstr(start_win, 12, (s_col - strlen("> start")) >> 1, "> exit");
			wrefresh(start_win);
			underlined = true;
		}
	}
	wattroff(start_win, COLOR_PAIR(YELLOW));
	delwin(start_win);
	if (!underlined)
		return (0);
	return (1);
}

void	game_over(t_game *game)
{
	int	b_cols, txt_col;

	b_cols = COLS >> 1;
	game->win = subwin(stdscr, 13, b_cols, (LINES - 13) >> 1, b_cols >> 1);
	wattron(game->win, COLOR_PAIR(BORDER));
	box(game->win, ' ', ' ');
	txt_col = (b_cols - strlen("---- GAME OVER ----")) >> 1;
	wattron(game->win, COLOR_PAIR(RED));
	mvwaddstr(game->win, 2, txt_col, "---- GAME OVER ----");
	wattron(game->win, COLOR_PAIR(WHITE));
	mvwhline(game->win, 4, 1, '*', b_cols - 2);
	txt_col = (b_cols - (strlen("score : ") + 10)) >> 1;
	wattron(game->win, COLOR_PAIR(CYAN));
	mvwprintw(game->win, 6, txt_col, "score : %010d", game->info.score);
	wattron(game->win, COLOR_PAIR(WHITE));
	mvwhline(game->win, 8, 1, '*', b_cols - 2);
	txt_col = (b_cols - (strlen("PRESS 'e' TO EXIT"))) >> 1;
	wattron(game->win, COLOR_PAIR(BLUE));
	mvwaddstr(game->win, 10, txt_col, "PRESS 'e' TO EXIT");
	wattroff(game->win, COLOR_PAIR(BLUE));
	wrefresh(game->win);
	while (getch() != 'e')
		usleep(1000000 / FPS_CAP);
	delwin(game->win);
	return ;
}

int	pause_game(t_info info, struct timeval *curtime)
{
	WINDOW	*pause_win;
	int p_col;
	int input = 0;
	bool underlined = true;

	p_col = COLS / 3;
	pause_win = newwin(10, p_col, (LINES - 10) >> 1, p_col);
	wattron(pause_win, COLOR_PAIR(BORDER));
	box(pause_win, ' ', ' ');
	wattron(pause_win, COLOR_PAIR(MAGENTA));
	mvwaddstr(pause_win, 3, (p_col - strlen("---- GAME PAUSED ----")) >> 1, "---- GAME PAUSED ----");
	wattron(pause_win, COLOR_PAIR(YELLOW) | A_UNDERLINE);
	mvwaddstr(pause_win, 5, (p_col - strlen("> resume")) >> 1, "> resume");
	wattroff(pause_win, A_UNDERLINE);
	mvwaddstr(pause_win, 6, (p_col - strlen("> resume")) >> 1, "> exit game");
	wrefresh(pause_win);
	while ((input = getch()) != ' ')
	{
		display_info(info, curtime);
		refresh();
		if (input == KEY_DOWN && underlined)
		{
			wattron(pause_win, A_UNDERLINE);
			mvwaddstr(pause_win, 6, (p_col - strlen("> resume")) >> 1, "> exit game");
			wattroff(pause_win, A_UNDERLINE);
			mvwaddstr(pause_win, 5, (p_col - strlen("> resume")) >> 1, "> resume");
			underlined = false;
			wrefresh(pause_win);
		}
		if (input == KEY_UP && !underlined)
		{
			wattron(pause_win, A_UNDERLINE);
			mvwaddstr(pause_win, 5, (p_col - strlen("> resume")) >> 1, "> resume");
			wattroff(pause_win, A_UNDERLINE);
			mvwaddstr(pause_win, 6, (p_col - strlen("> resume")) >> 1, "> exit game");
			underlined = true;
			wrefresh(pause_win);
		}

	}
	wattroff(pause_win, COLOR_PAIR(YELLOW));
	delwin(pause_win);
	refresh();
	if (!underlined)
		return (0);
	return (1);
}
