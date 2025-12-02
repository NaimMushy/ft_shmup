#include <stdlib.h>
#include "ft_schmup.h"

static t_entitylist	**set_type(t_entity *entity, t_game *game);
static int			check_walls(int type, int row, int col);
static void			destroy_entity(t_entity *entity, t_game *game);
static void			move_entity(t_entity *entity, int row, int col, t_game *game);

void	check_collision(t_entity *entity, int row, int col, t_game *game)
{
	t_entity		*other;

	other = game->map[row][col];
	if (other != NULL)
	{
		--entity->hp;
		--other->hp;
		if (other->type != PLAYER_T && other->hp <= 0)
			destroy_entity(other, game);
		if (entity->type != PLAYER_T && entity->hp <= 0)
			destroy_entity(entity, game);
		else
			move_entity(entity, row, col, game);
		return ;
	}
	else if (check_walls(entity->type, row, col) == TRUE)
	{
		if (entity->type != PLAYER_T)
			destroy_entity(entity, game);
		return ;
	}
	move_entity(entity, row, col, game);
}

static t_entitylist	**set_type(t_entity *entity, t_game *game)
{
	if (entity->type == ENEMY)
		return (&game->enemies);
	else if (entity->type == PLAYER_SHOT)
		return (&game->p_shots);
	else if (entity->type == ENEMY_SHOT)
		return (&game->e_shots);
	return (NULL);
}

static int	check_walls(int type, int row, int col)
{
	if (type == PLAYER_T && row <= MAP_LIMIT)
		return (TRUE);
	if (row <= 0 || row >= SUB_LINES - 1 || col <= 0 || col >= SUB_COLS - 1)
		return (TRUE);
	return (FALSE);
}

static void	destroy_entity(t_entity *entity, t_game *game)
{
	t_entitylist	**head;
	t_entitylist	*prev;
	t_entitylist	*cur;
	
	if (entity->type == ENEMY)
		game->info.score += game->spawn.ppk;
	head = set_type(entity, game);
	cur = *head;
	while (cur)
	{
		if (&cur->data == entity)
		{
			if (cur == *head)
			{
				*head = (*head)->next;
			}
			else
				prev->next = cur->next;
			game->map[entity->row][entity->col] = NULL;
			free(cur);
			cur = NULL;
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

static void	move_entity(t_entity *entity, int row, int col, t_game *game)
{
	game->map[entity->row][entity->col] = NULL;
	entity->row = row;
	entity->col = col;
	game->map[row][col] = entity;
}
