#include "ft_schmup.h"
#include <stdlib.h>

int	init_player(t_game *game, t_entity *player)
{
	player->row = LINES - WIN_WIDTH - 1;
	player->col = ((COLS - 1) / 2) - 1;
	player->hp = 3;
	player->ch = 'P';
	game->map[player->row][player->col] = 'P';
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
	int	index = 0;

	game->map = malloc(sizeof(char *) * LINES);
	if (!game->map)
		return (ERROR_ALLOC);
	while (index < LINES)
	{
		game->map[index] = calloc(COLS, sizeof(char));
		if (!game->map[index])
			return (ERROR_ALLOC);
		++index;
	}
	return (SUCCESS);
}

int init_all(t_game *game)
{
	int	ret;

	initscr();
	curs_set(0);
	cbreak();
	noecho();
	game->win = subwin(stdscr, LINES - (WIN_WIDTH - 1) * 2, COLS - (WIN_WIDTH - 1) * 2, 2, 2);
	keypad(game->win, TRUE);
	keypad(stdscr, TRUE);
	nodelay(stdscr, true);
	nodelay(game->win, true);
	ret = init_player(game, &game->player);
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
