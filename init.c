#include "ft_shmup.h"
#include <stdlib.h>

static void	init_player(t_game *game, t_entity *player);
static int	init_info(t_info *ptr_info, t_game *ptr_game);
static int	init_map(t_game *game);

int	init_all(t_game *game)
{
	int	ret;

	initscr();
	if (has_colors())
	{
		start_color();
		//init_pair(EMPTY_PAIR, COLOR_BLACK, COLOR_BLACK);
		init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
		init_pair(RED, COLOR_RED, COLOR_BLACK);
		init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
		init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
		init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
		init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
		init_pair(BORDER, COLOR_WHITE, COLOR_WHITE);
		clear();
	}
	curs_set(0);
	cbreak();
	noecho();
	game->win = subwin(stdscr, SUB_LINES, SUB_COLS, WIN_WIDTH, WIN_WIDTH);
	//dprintf(game->fd, "subwin successfully created, SUB_LINES = %d SUB_COLS = %d\n", SUB_LINES, SUB_COLS);
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
	//dprintf(game->fd, "map successfully created\n");
	init_player(game, &game->player);
	ret = init_info(&game->info, game);
	if (ret != SUCCESS)
		return (ret);
	return (SUCCESS);
}

static void	init_player(t_game *game, t_entity *player)
{
	player->row = SUB_LINES - 2;
	player->col = (SUB_COLS - 1) >> 1;
	//dprintf(game->fd, "player row at init : %d\nplayer col at init : %d\n", player->row, player->col);
	player->hp = 3;
	player->app = PLAYER_UP;
	player->type = PLAYER_T;
	player->dir_r = -1;
	player->dir_c = 0;
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

	game->map = malloc(sizeof(t_entity **) * (SUB_LINES + 1));
	if (!game->map)
		return (ERROR_ALLOC);
	while (index < SUB_LINES + 1)
	{
		game->map[index] = calloc(SUB_COLS, sizeof(t_entity *));
		if (!game->map[index])
			return (ERROR_ALLOC);
		++index;
	}
	return (SUCCESS);
}
