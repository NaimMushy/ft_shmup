#include "ft_schmup.h"

void	init_player(t_entity *player)
{
	player->row = LINES - WIN_WIDTH - 1;
	player->col = ((COLS - 1) / 2) - 1;
	player->hp = 3;
	player->ch = 'P';
}

void	update_player(int input, t_game *game)
{
	t_entitylist	*new_shot;

    switch (input)
	{
		case 'w' :
			if (game->player.row - 1 >= MAP_LIMIT)
				game->player.row -= 1;
			break;
		case 's' : 
			if (game->player.row + 1 < LINES - WIN_WIDTH)
				game->player.row += 1;
			break;
		case 'a' :
			if (game->player.col - 1 >= WIN_WIDTH)
				game->player.col -= 1;
			break;
		case 'd' : 
			if (game->player.col + 1 < COLS - WIN_WIDTH)
				game->player.col += 1;
			break;
		case ' ' :
			if (game->player.row - 1 >= WIN_WIDTH)
			{
				new_shot = ft_lstnew(game->player.row - 1, game->player.col, '*');
				ft_lstadd_front(&game->p_shots, new_shot);
			}
	}
	return ;
}
