#include "ft_schmup.h"

void	init_player(t_game *game)
{
	game->player.row = LINES - WIN_WIDTH - 1;
	game->player.col = ((COLS - 1) / 2) - 1;
	game->player.hp = 3;
	game->player.ch = 'P';
}

void	update_player(char input, t_game *game)
{
	t_listentity	*new_shot;

    switch (c)
	{
		case 'w' :
			if (row - 1 >= MAP_LIMIT)
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
			if (row - 1 >= WIN_WIDTH)
			{
				new_shot = ft_lstnew(row);
				ft_lstadd_front(&game.p_shots, new_shot);
				init_shot(&game.p.shots);
			}
	}
	return (0);
}
