#include "ft_schmup.h"
#include <stdlib.h>

static int	update_player(int input, t_game *game);
static void	update_entities(t_entitylist *entities, int move, t_game *game);

int	update_all(int input, t_game *game)
{
	int	ret;
	
	update_entities(game->p_shots, -1, game);
	ret = update_player(input, game);
	if (ret != SUCCESS)
		return (ret);
	update_entities(game->e_shots, 1, game);
	if (game->f_counter % FPS_CAP == 0)
		update_entities(game->enemies, 1, game);
	if (game->f_counter % FPS_CAP == 0)
	{
		ret = create_new_eshot(game->enemies, &game->e_shots, game);
		if (ret != SUCCESS)
			return (ret);
	}
	if (game->f_counter % (game->spawn.timer * FPS_CAP) == 0)
	{
		if (game->spawn.kills != 0 && game->spawn.kills % 20 == 0 && game->spawn.wave_size < 10)
		{
			++game->spawn.wave_size;
			game->spawn.ppk += 25;
		}
		ret = add_new_wave(game, game->spawn.wave_size);
		if (ret != SUCCESS)
			return (ret);
	}
	return (SUCCESS);
}

static int	update_player(int input, t_game *game)
{
	t_entitylist	*new_shot;

    switch (input)
	{
		case 'z' :
			check_collision(&game->player, game->player.row - 1, game->player.col, game);
			break;
		case 's' : 
			check_collision(&game->player, game->player.row + 1, game->player.col, game);
			break;
		case 'q' :
			check_collision(&game->player, game->player.row, game->player.col - 1, game);
			break;
		case 'd' : 
			check_collision(&game->player, game->player.row, game->player.col + 1, game);
			break;
		case ' ' :
			if (game->player.row - 1 >= WIN_WIDTH)
			{
				new_shot = ft_lstnew(PLAYER_SHOT);
				if (new_shot == NULL)
					return (ERROR_ALLOC);
				ft_lstadd_front(&game->p_shots, new_shot);
				check_collision(&new_shot->data, game->player.row - 1, game->player.col, game);
			}
	}
	return (SUCCESS);
}

static void	update_entities(t_entitylist *entities, int move, t_game *game)
{
	if (entities != NULL)
	{
		if (entities->next != NULL)
			update_entities(entities->next, move, game);
		check_collision(&entities->data, entities->data.row + move, entities->data.col, game);
	}
}
