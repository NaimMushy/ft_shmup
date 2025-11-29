#ifndef FT_SCHMUP_H
# define FT_SCHMUP_H

# define MAX_ENEMY 300

#include <ncurses.h>
#include <sys/time.h>

enum ret_val
{
	SUCCESS = 0,
	ERROR_NCURSES,
	ERROR_SYSCALL,
	ERROR_ALLOC
};

typedef struct s_listentity
{
	t_entity			data;
	struct s_listentity	*next;
}   t_listentity;

typedef struct s_entity
{
	char ch;
	int hp;
	int row;
	int col;
}   t_entity;

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
	t_listentity	*enemies;
	t_listentity	*e_shots;
	t_listentity	*p_shots;
}   t_game;

#endif