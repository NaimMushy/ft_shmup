#include "ft_schmup.h"

void	update_player(int input, t_game *game)
{
	t_entitylist	*new_shot;

    	switch (input)
	{
		case 'w' :
			check_collision(game->player, game->player.row - 1, game->player.col, game);
			break;
		case 's' : 
			check_collision(game->player, game->player.row + 1, game->player.col, game);
			break;
		case 'a' :
			check_collision(game->player, game->player.row, game->player.col - 1, game);
			break;
		case 'd' : 
			check_collision(game->player, game->player.row, game->player.col + 1, game);
			break;
		case ' ' :
			if (game->player.row - 1 >= WIN_WIDTH)
			{
				new_shot = ft_lstnew('*');
				ft_lstadd_front(&game->p_shots, new_shot);
				check_collision(&new_shot->data, game->player.row - 1, game->player.col, game)
			}
	}
	//if (!game->player.hp)
	//	game_over(game);
	return ;
}

void	update_entities(t_entitylist *entities, int move, t_game *game)
{
	t_entitylist	*cursor;

	cursor = entities;
	while (cursor)
	{
		check_collision(&cursor->data, cursor->data.row + move, cursor->data.col, game)
		cursor = cursor->next;
	}
}

void	update_all(int input, t_game *game, int f_counter)
{
	update_player(input, game);
	if (f_counter % 300 == 0)
		add_new_wave(game);
	if (f_counter % 60 == 0)
		update_entities(&game->enemies, 1, game);
	if (f_counter % 30 == 0)
	{
		create_new_eshot(&game->enemies, &game->e_shots, game);
		update_entities(&game->p_shots, -1, game);
		update_entities(&game->e_shots, 1, game);
	}
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
		if (cur->data == *entity)
		{
			prev->next = cur->next;
			free(cur);
			break;
		}
		prev = cur;
		cur = cur->next;
	}
}
