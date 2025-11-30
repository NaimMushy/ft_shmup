#include "ft_schmup.h"
#include <stdlib.h>

int	init_player(t_entity *player)
{
	player->row = N_LINES - WIN_WIDTH - 1;
	player->col = ((N_COLS - 1) / 2) - 1;
	player->hp = 3;
	player->ch = 'P';
	return (SUCCESS);
}

int	init_info(t_info *ptr_info, t_game *ptr_game)
{
	int	ret;
	
	ptr_info->ptr_player_hp = &ptr_game->player.hp;
	ptr_info->score = 0;
	ret = gettimeofday(&ptr_info->t_zero, NULL);
	if (ret == -1)
	{
		perror("gettimeofday");
		return (ERROR_SYSCALL);
	}
	return (SUCCESS);
}

int	init_map(t_game *game)
{
	int	index;

	game->map = malloc(sizeof(t_entity **) * N_LINES);
	if (!game->map)
		return (ERROR_ALLOC);
	index = 0;
	while (index < N_LINES)
	{
		game->map[index] = malloc(sizeof(t_entity *) * N_COLS);
		if (!game->map[index])
			return (ERROR_ALLOC);
		game->map[index] = (t_entity **){0};
		index++;
	}
	return (SUCCESS);
}

int init_all(t_game *game)
{
	int	ret;

	ret = init_player(&game->player);
	if (ret != SUCCESS)
		return (ret);
	ret = init_info(&game->info, game);
	if (ret != SUCCESS)
		return (ret);
	ret = init_map(game);
	if (ret != SUCCESS)
		return (ret);
	return (SUCCESS);
}
