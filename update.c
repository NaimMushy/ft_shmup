#include "ft_schmup.h"

void	update_player(int input, t_game *game)
{
	t_entitylist	*new_shot;

    	switch (input)
	{
		case 'w' :
			check_collision(game->player, game->player.row - 1, game->player.col);
			break;
		case 's' : 
			check_collision(game->player, game->player.row + 1, game->player.col);
			break;
		case 'a' :
			check_collision(game->player, game->player.row, game->player.col - 1);
			break;
		case 'd' : 
			check_collision(game->player, game->player.row, game->player.col + 1);
			break;
		case ' ' :
			if (game->player.row - 1 >= WIN_WIDTH)
			{
				new_shot = ft_lstnew('*');
				ft_lstadd_front(&game->p_shots, new_shot);
				check_collision(&new_shot->data, game->player.row - 1, game->player.col)
			}
	}
	return ;
}

void	update_entities(t_entitylist *entities, int move, t_game *game)
{
	t_entitylist	*cursor;

	cursor = entities;
	while (cursor)
	{
		check_collision(&cursor->data, cursor->data.row + move, cursor->data.col)
		cursor = cursor->next;
	}
}

void	add_new_wave(t_game *game, int number)
{
	t_entitylist	*new_enemy;
	int	pos;
	int	nb = number;

	new_enemy = NULL;
	pos = (COLS - 1) / (number * 2);
	while (number--)
	{
		new_enemy = ft_lstnew('V');
		ft_lstadd_front(&game->enemies, new_enemy);
		check_collision(&new_enemy->data, WIN_WIDTH, pos);
		pos += (COLS - 1) / nb;
	}
}

void	update_all(t_game *game, int input)
{
	update_player(input, game);
	if (e_timer == 3)
		add_new_wave(game);
	if (s_timer == 1)
	{
		update_entities(&game->enemies, 1, game);
		update_entities(&game->p_shots, -1, game);
		update_entities(&game->e_shots, 1, game);
	}
}
