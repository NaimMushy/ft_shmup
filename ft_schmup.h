#ifndef FT_SCHMUP_H
# define FT_SCHMUP_H

# define WIN_WIDTH 3
# define MAP_LIMIT LINES / 2
# define FPS_CAP 1.0f / 60

#include <ncurses.h>
#include <sys/time.h>

enum ret_val
{
	SUCCESS = 0,
	ERROR_NCURSES,
	ERROR_SYSCALL,
	ERROR_ALLOC
};

typedef struct s_entity
{
	char ch;
	int hp;
	int row;
	int col;
}   t_entity;

typedef struct s_entitylist
{
	t_entity			data;
	struct s_entitylist	*next;
}   t_entitylist;

typedef struct s_info
{
	int				*ptr_player_hp;
	int				score;
	struct timeval	t_zero;
}   t_info;

typedef struct s_game
{
	WINDOW			*win;
	struct timeval	frame_time;
	int				f_counter;
	t_entity		player;
	t_entitylist	*enemies;
	t_entitylist	*e_shots;
	t_entitylist	*p_shots;
	t_entity	map[LINES][COLS];
}   t_game;


void	init_player(t_entity *player);
void	update_player(int input, t_game *game);
void	ft_lstiter_display(t_entitylist *lst);
void	ft_lstadd_front(t_entitylist **lst, t_entitylist *new);
t_entitylist	*ft_lstnew(int c);

int		init_info(t_info *ptr_info, t_game *ptr_game);
int		display_info(t_info info, struct timeval *ptr_curtime);
void	wait_next_frame(struct timeval *ptr_frametime, struct timeval curtime);

#endif
