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
			other_entity->hp--;
		}
	}
}

t_entitylist	*set_type(t_entity *entity, t_game *game)
{
	if (entity->ch == 'V')
		return (game->enemies);
	else if (entity->ch == 'o')
		return (game->p_shots);
	else if (entity->ch == '|')
		return (game->e_shots);
	return (NULL);
}

int	check_walls(int type, int row, int col)
{
	if (type == 'P' && row <= MAP_LIMIT)
		return (0);
	if (row < WIN_WIDTH || row >= LINES - WIN_WIDTH - 1 || col < WIN_WIDTH || col >= COLS - WIN_WIDTH - 1)
		return (0);
	return (1);
}

/*
void	check_collision(t_entity *entity, int row, int col, t_game *game)
{
	t_entity	*other_entity;
	t_entitylist	*entity_type;
	int	ret = 0;

	other_entity = game->map[row][col];
	if (!other_entity)
	{
		ret = check_walls(entity->ch, row, col);
		game->map[entity->row][entity->col] = NULL;
		if (ret)
		{
			dprintf(game->fd, "case unoccupied, updating coordinates\n");
			entity->row = row;
			entity->col = col;
			game->map[row][col] = entity;
			return ;
		}
		else if (!ret && entity->ch != 'P')
			entity->hp = 0;
	}
	else
		reduce_hp(entity, other_entity);
	dprintf(game->fd, "case occupied, reducing hp\n");
	entity_type = set_type(entity, game);
	if (entity_type && entity->hp <= 0 && entity->ch != 'P')
		destroy_entity(entity, entity_type, game);
	if (other_entity && other_entity->hp <= 0 && entity->ch != 'P')
	{
		entity_type = set_type(other_entity, game);
		destroy_entity(other_entity, entity_type, game);
	}
	return;
}
*/

void	check_collision(t_entity *entity, int row, int col, t_game *game)
{
	t_entitylist	*type;

	if (game->map[row][col] != 0)
	{
		entity->hp--;
		if (entity->hp <= 0)
		{
			type = set_type(entity->ch);
			find_entity(entity->row, entity->col, type, game);
			destroy_entity

		find_entity(row, col, game->map[row][col], game);
		return ;
	}
	if (check_walls
}

void	destroy_entity(t_entity *entity, t_entitylist *e_list, t_game *game)
{
	t_entitylist	*prev;
	t_entitylist	*cur;

	if (entity->ch == 'V')
		game->info.score += 50;
	prev = e_list;
	cur = e_list;
	while (cur)
	{
		if (&cur->data == entity)
		{
			prev->next = cur->next;
			free(entity);
			entity = NULL;
			break;
		}
		prev = cur;
		cur = cur->next;
	}
	dprintf(game->fd, "succeeded in destroying entity at frame : %d\n", game->f_counter);
}
