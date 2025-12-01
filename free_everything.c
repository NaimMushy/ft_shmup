#include <stdlib.h>
#include "ft_schmup.h"

void	free_all(t_game game)
{
	free_lst(&game.e_shots);
	free_lst(&game.p_shots);
	free_lst(&game.enemies);
	free_map(&game.map);
	werase(game.win);
	wrefresh(game.win);
	erase();
	refresh();
	delwin(game.win);
}

void	free_lst(t_entitylist **ptr_lst)
{	
	if ((*ptr_lst) && (*ptr_lst)->next)
		free_lst(&(*ptr_lst)->next);
	free(*ptr_lst);
	*ptr_lst = NULL;
}

void	free_map(t_entity ****ptr_map)
{
	int	i;

	i = 0;
	while (i < SUB_LINES && (*ptr_map)[i] != NULL)
	{
		free((*ptr_map)[i]);
		++i;
	}
	free(*ptr_map);
	*ptr_map = NULL;
}
