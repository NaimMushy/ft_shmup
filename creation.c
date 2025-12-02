#include "ft_shmup.h"
#include <stdlib.h>

int	create_new_eshot(t_entitylist *enemies, t_entitylist **e_shots, t_game *game)
{
	t_entitylist	*cursor;
	t_entitylist	*new_shot;

	cursor = enemies;
	while (cursor)
	{
		new_shot = ft_lstnew(ENEMY_SHOT, enemies->data.dir_r, enemies->data.dir_c);
		if (new_shot == NULL)
			return (ERROR_ALLOC);
		ft_lstadd_front(e_shots, new_shot);
		check_collision(&new_shot->data, cursor->data.row + new_shot->data.dir_r, cursor->data.col + new_shot->data.dir_c, game);
		cursor = cursor->next;
	}
	return (SUCCESS);
}

static int get_free_col(int start, t_entitylist *enemies)
{
	t_entitylist	*lst_i;
	int				final;

	lst_i = enemies;
	final = start;
	while (final < SUB_COLS && lst_i)
	{
		if (lst_i->data.col == final)
		{
			++final;
			lst_i = enemies;
		}
		else
			lst_i = lst_i->next;
	}
	return (final);
}

int	add_new_wave(t_game *game, int number, int dir_r, int dir_c)
{
	t_entitylist	*new_enemy;
	int	pos;
	int	nb = number;

	new_enemy = NULL;
	pos = (SUB_COLS - 1) / (number << 1);
	while (number--)
	{
		new_enemy = ft_lstnew(ENEMY, dir_r, dir_c);
		if (new_enemy == NULL)
			return (ERROR_ALLOC);
		pos = get_free_col(pos, game->enemies);
		if (pos >= SUB_COLS)
		{
			free(new_enemy);
			return (SUCCESS);
		}
		ft_lstadd_front(&game->enemies, new_enemy);
		check_collision(&new_enemy->data, 1, pos + dir_c, game);
		pos += (SUB_COLS - 1) / nb;
	}
	return (SUCCESS);
}

t_entitylist	*ft_lstnew(int c, int dir_r, int dir_c)
{
	t_entitylist	*new;

	new = malloc(sizeof(t_entitylist));
	if (!new)
		return (NULL);
	new->data.row = 0;
	new->data.col = 0;
	new->data.app = c;
	new->data.type = c;
	new->data.hp = 1;
	new->data.dir_r = dir_r;
	new->data.dir_c = dir_c;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_front(t_entitylist **lst, t_entitylist *new)
{
	new->next = *lst;
	*lst = new;
}
