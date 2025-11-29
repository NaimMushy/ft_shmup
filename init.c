#include "ft_schmup.h"

void	init_player(t_entity *player)
{
	player->row = LINES - WIN_WIDTH - 1;
	player->col = ((COLS - 1) / 2) - 1;
	player->hp = 3;
	player->ch = 'P';
}
