#include "ft_schmup.h"
#include <stdlib.h>

int	create_new_eshot(t_entitylist *enemies, t_entitylist **e_shots, t_game *game)
{
	t_entitylist	*cursor;
	t_entitylist	*new_shot;

	cursor = enemies;
	while (cursor)
	{
		new_shot = ft_lstnew(ENEMY_SHOT);
		if (new_shot == NULL)
			return (ERROR_ALLOC);
		ft_lstadd_front(e_shots, new_shot);
		check_collision(&new_shot->data, cursor->data.row + 1, cursor->data.col, game);
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
	while (final < COLS && lst_i)
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

int	add_new_wave(t_game *game, int number)
{
	t_entitylist	*new_enemy;
	int	pos;
	int	nb = number;

	new_enemy = NULL;
	pos = (COLS - 1 - (WIN_WIDTH << 1)) / (number << 1);
	while (number--)
	{
		new_enemy = ft_lstnew(ENEMY);
		if (new_enemy == NULL)
			return (ERROR_ALLOC);
		pos = get_free_col(pos, game->enemies);
		if (pos >= COLS)
		{
			free(new_enemy);
			return (SUCCESS);
		}
		ft_lstadd_front(&game->enemies, new_enemy);
		check_collision(&new_enemy->data, WIN_WIDTH + 1, pos, game);
		pos += (COLS - 1 - (WIN_WIDTH << 1)) / nb;
	}
	return (SUCCESS);
}

t_entitylist	*ft_lstnew(int c)
{
	t_entitylist	*new;

	new = malloc(sizeof(t_entitylist));
	if (!new)
		return (NULL);
	new->data.row = 0;
	new->data.col = 0;
	new->data.ch = c;
	new->data.hp = 1;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_front(t_entitylist **lst, t_entitylist *new)
{
	new->next = *lst;
	*lst = new;
}
