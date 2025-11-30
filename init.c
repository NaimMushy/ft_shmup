#include "ft_schmup.h"

void	init_player(t_entity *player)
{
	player->row = LINES - WIN_WIDTH - 1;
	player->col = ((COLS - 1) / 2) - 1;
	player->hp = 3;
	player->ch = 'P';
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
