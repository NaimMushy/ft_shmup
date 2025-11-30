#include <sys/time.h>
#include "ft_schmup.h"

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

int	display_info(t_info info, struct timeval *ptr_curtime)
{
	int				ret;
	
	ret = gettimeofday(ptr_curtime, NULL);
	if (ret == 1)
		return (ERROR_SYSCALL);
	mvprintw(0, 0, "Remaning lives : %d\tElapsed time : %ld:%02ld\tCurrent score : %010d",
		*info.ptr_player_hp,
		(ptr_curtime->tv_sec - info.t_zero.tv_sec) / 60,
		(ptr_curtime->tv_sec - info.t_zero.tv_sec) % 60,
		info.score);
	return (SUCCESS);
}
