#include "ft_schmup.h"

void	reduce_hp(t_entity *entity, t_entity *other_entity)
{
	if (entity->ch == 'P' || entity->ch == 'o')
	{
		if (other_entity->ch == 'V' || other_entity->ch == '|')
		{
			entity->hp--;
			other_entity->hp--;
		}
	}
	else
	{
		if (other_entity->ch == 'P' || other_entity->ch == 'o')
		{
			entity->hp--;
			other->entity->hp--;
		}
	}
}

t_entitylist	*set_type(t_entity *entity, t_game *game)
{
	if (entity->ch == 'V')
		return (&game->enemies);
	else if (entity->ch == 'o')
		return (&game->p_shots);
	else if (entity->ch == '|')
		return (&game->e_shots);
}

int	check_walls(int type, int row, int col)
{
	if (type == 'P' && row <= MAP_LIMIT)
		return (0);
	if (row < WIN_WIDTH || row >= LINES - WIN_WIDTH - 1 || col < WIN_WIDTH || col >= COLS - WIN_WIDTH - 1)
		return (0);
	return (1);
}

void	check_collision(t_entity *entity, int row, int col, t_game *game)
{
	t_entity	*other_entity;
	t_entitylist	*entity_type;

	other_entity = game->map[row][col];
	if (!other_entity)
	{
		if (check_walls(entity->ch, row, col))
		{
			game->map[entity->row][entity->col] = NULL;
			entity->row = row;
			entity->col = col;
			game->map[row][col] = entity;
			return ;
		}
		else if (entity->ch != 'P'
			entity->hp = 0;
	}
	else
		reduce_hp(entity, other_entity);
	entity_type = set_type(entity, game);
	if (entity->hp == 0 && entity->ch != 'P')
		destroy_entity(entity, entity_type, game);
	if (other_entity && other_entity->hp == 0 && entity->ch != 'P')
	{
		entity_type = set_type(other_entity, game);
		destroy_entity(other_entity, entity_type, game);
	}
	return;
}
