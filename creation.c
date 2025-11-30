#include "ft_schmup.h"

void	create_new_eshot(t_entitylist *enemies, t_entitylist *e_shots, t_game *game)
{
	static t_entitylist	*cursor = enemies;
	t_entitylist	*new_shot;

	if (cursor)
	{
		new_shot = ft_lstnew('|');
		ft_lstadd_front(e_shots, new_shot);
		check_collision(&new_shot->data, cursor->data.row + 1, cursor->data.col, game);
		cursor = cursor->next;
	}
	else
		cursor = enemies;
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
		check_collision(&new_enemy->data, WIN_WIDTH, pos, game);
		pos += (COLS - 1) / nb;
	}
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
	return (new);
}

void	ft_lstadd_front(t_entitylist **lst, t_entitylist *new)
{
	new->next = *lst;
	*lst = new;
}
