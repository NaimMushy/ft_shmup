#include "ft_schmup.h"
#include <stdlib.h>

static void	init_player(t_game *game, t_entity *player);
static int	init_info(t_info *ptr_info, t_game *ptr_game);
static int	init_map(t_game *game);

int	init_all(t_game *game)
{
	int	ret;

	initscr();
	curs_set(0);
	cbreak();
	noecho();
	game->win = subwin(stdscr, LINES - ((WIN_WIDTH - 1) << 1), COLS - ((WIN_WIDTH - 1) << 1), WIN_WIDTH, WIN_WIDTH);
	keypad(game->win, TRUE);
	keypad(stdscr, TRUE);
	nodelay(stdscr, true);
	nodelay(game->win, true);
	game->spawn.kills = 0;
	game->spawn.timer = 5;
	game->spawn.ppk = 50;
	game->spawn.wave_size = 3;
	ret = init_map(game);
	if (ret != SUCCESS)
		return (ret);
	init_player(game, &game->player);
	ret = init_info(&game->info, game);
	if (ret != SUCCESS)
		return (ret);
	return (SUCCESS);
}

static void	init_player(t_game *game, t_entity *player)
{
	player->row = LINES - WIN_WIDTH;
	player->col = ((COLS - 1) >> 1);
	player->hp = 3;
	player->ch = PLAYER;
	game->map[player->row][player->col] = player;
}

static int	init_info(t_info *ptr_info, t_game *ptr_game)
{
	int	ret;
	
	ptr_info->ptr_player_hp = &ptr_game->player.hp;
	ptr_info->score = 0;
	ret = gettimeofday(&ptr_info->t_zero, NULL);
	if (ret == -1)
		return (ERROR_SYSCALL);
	return (SUCCESS);
}

static int	init_map(t_game *game)
{
	int	index = 0;

	game->map = malloc(sizeof(t_entity **) * LINES);
	if (!game->map)
		return (ERROR_ALLOC);
	while (index < LINES)
	{
		game->map[index] = calloc(COLS, sizeof(t_entity *));
		if (!game->map[index])
			return (ERROR_ALLOC);
		++index;
	}
	return (SUCCESS);
}
