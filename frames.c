#include <sys/time.h>
#include "unistd.h"
#include "ft_schmup.h"

void	wait_next_frame(struct timeval *ptr_frametime, struct timeval curtime)
{
	long	sleeptime;

	sleeptime = (1.0f / FPS_CAP - (curtime.tv_sec - ptr_frametime->tv_sec)) * 1e6
			+ curtime.tv_usec - ptr_frametime->tv_usec;
	if (sleeptime > 0)
		usleep(sleeptime);
}