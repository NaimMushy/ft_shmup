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
	t_entitylist	*cursor;

	cursor = entities;
	if (cursor)
		dprintf(game->fd, "start of entity list is not null\n");
	while (cursor)
	{
		dprintf(game->fd, "row of entity : %d\ncol of entity : %d\n", cursor->data.row, cursor->data.col);
		check_collision(&cursor->data, cursor->data.row + move, cursor->data.col, game);
		cursor = cursor->next;
	}
}

void	update_all(int input, t_game *game)
{
	update_player(input, game);
	//if (game->f_counter % 60 == 0)
		//update_entities(game->enemies, 1, game);
	//create_new_eshot(game->enemies, game->e_shots, game);
	update_entities(game->p_shots, -1, game);
	update_entities(game->e_shots, 1, game);
	//if (game->f_counter && game->f_counter % 300 == 0)
		//add_new_wave(game, 5);
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
