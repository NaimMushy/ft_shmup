#include <ncurses.h>

int main(void)
{
    int ch = 'P';
	int row, col;

	initscr();
    keypad(stdscr, TRUE);
    noecho();
	row = 1;
	col = 0;
	mvprintw(row, col, "%c", ch);
    	mvprintw(0, 0, "position : %d ; %d", row, col);
	refresh();
    while ((ch = getch()) != 'q')
    {
    	mvprintw(0, 0, "position : %d ; %d", row, col);
        switch (ch)
		{
		case 'w' :
			if (row - 1 >= 0)
			{
				mvprintw(row, col, "%c", ' ');
				row -= 1;
				mvprintw(row, col, "%c", 'P');
			}
			break;
		case 's' : 
			if (row + 1 < LINES)
			{
				mvprintw(row, col, "%c", ' ');
				row += 1;
				mvprintw(row, col, "%c", 'P');
			}
			break;
		case 'a' :
			if (col - 1 >= 0)
			{
				mvprintw(row, col, "%c", ' ');
				col -= 1;
				mvprintw(row, col, "%c", 'P');
			}
			break;
		case 'd' : 
			if (col + 1 < COLS)
			{
				mvprintw(row, col, "%c", ' ');
				col += 1;
				mvprintw(row, col, "%c", 'P');
			}
			break;
		}
		refresh();
    }
	endwin();
	return (0);
}
