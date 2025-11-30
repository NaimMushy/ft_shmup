#include "ft_schmup.h"
#include <stdlib.h>

void	update_player(int input, t_game *game)
{
	t_entitylist	*new_shot;

    switch (input)
	{
		case 'w' :
			check_collision(&game->player, game->player.row - 1, game->player.col, game);
			break;
		case 's' : 
			check_collision(&game->player, game->player.row + 1, game->player.col, game);
			break;
		case 'a' :
			check_collision(&game->player, game->player.row, game->player.col - 1, game);
			break;
		case 'd' : 
			check_collision(&game->player, game->player.row, game->player.col + 1, game);
			break;
		case ' ' :
			if (game->player.row - 1 >= WIN_WIDTH)
			{
				new_shot = ft_lstnew('o');
				ft_lstadd_front(&game->p_shots, new_shot);
				check_collision(&new_shot->data, game->player.row - 1, game->player.col, game);
			}
	}
	//if (!game->player.hp)
	//	game_over(game);
	return ;
}

void	update_entities(t_entitylist *entities, int move, t_game *game)
{
	if (entities != NULL)
	{
		if (entities->next != NULL)
			update_entities(entities->next, move, game);
		check_collision(&entities->data, entities->data.row + move, entities->data.col, game);
	}
}

void	update_all(int input, t_game *game)
{
	update_entities(game->p_shots, -1, game);
	update_player(input, game);
	update_entities(game->e_shots, 1, game);
	if (game->f_counter % 60 == 0)
		update_entities(game->enemies, 1, game);
	create_new_eshot(game->enemies, &game->e_shots, game);
	if (game->f_counter && game->f_counter % 300 == 0)
		add_new_wave(game, 1);
}
