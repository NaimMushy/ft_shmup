#include "ft_schmup.h"

void	init_player(t_game *game)
{
	game->player.row = LINES - WIN_WIDTH - 1;
	game->player.col = ((COLS - 1) / 2) - 1;
	game->player.hp = 3;
	game->player.ch = 'P';
}

void	update_player(char input)
{
	t_game	game = {0};

    switch (c)
	{
		case 'w' :
			if (row - 1 >= WIN_WIDTH)
				game.player.row -= 1;
			break;
		case 's' : 
			if (row + 1 < LINES - WIN_WIDTH)
				game.player.row += 1;
			break;
		case 'a' :
			if (col - 1 >= WIN_WIDTH)
				game.player.col -= 1;
			break;
		case 'd' : 
			if (col + 1 < COLS - WIN_WIDTH)
				game.player.col += 1;
			break;
		case ' ' :
			ft_lstadd_front(&game.p_shots, ft_lstnew());
			init_shot(&game.p.shots);
	}
	return (0);
}
