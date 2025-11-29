#ifndef FT_SCHMUP_H
# define FT_SCHMUP_H

# define WIN_WIDTH 3
# define MAP_LIMIT LINES / 2

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
	int				score;
	int				*ptr_player_lives;
	struct timeval	time;
}   t_info;

typedef struct s_game
{
	struct timeval	frame;
	int				f_counter;
	t_entity		player;
	t_entitylist	*enemies;
	t_entitylist	*e_shots;
	t_entitylist	*p_shots;
}   t_game;


void	init_player(t_entity *player);
void	update_player(int input, t_game *game);
void	ft_lstiter_display(t_entitylist *lst);
void	ft_lstadd_front(t_entitylist **lst, t_entitylist *new);
t_entitylist	*ft_lstnew(int row, int col, int c);

#endif
