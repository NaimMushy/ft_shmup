#ifndef FT_SCHMUP_H
# define FT_SCHMUP_H

# define WIN_WIDTH 3
# define SUB_LINES (LINES - ((WIN_WIDTH - 1) << 1))
# define SUB_COLS (COLS - ((WIN_WIDTH - 1) << 1))
# define MAP_LIMIT (SUB_LINES >> 1)
# define FPS_CAP 60
# define PLAYER_T 'p'
# define PLAYER_UP '^'
# define PLAYER_DOWN 'v'
# define PLAYER_LEFT '<'
# define PLAYER_RIGHT '>'
# define ENEMY 'W'
# define PLAYER_SHOT '*'
# define ENEMY_SHOT 'o'
# define GREEN 1
# define RED 2
# define YELLOW 3
# define MAGENTA 4
# define WHITE 5
# define BLUE 6
# define CYAN 7

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
	char app;
	char type;
	int hp;
	int row;
	int col;
	int dir_r;
	int dir_c;
}   t_entity;

typedef struct s_entitylist
{
	t_entity			data;
	struct s_entitylist	*prev;
	struct s_entitylist	*next;
}   t_entitylist;

typedef struct s_info
{
	int				*ptr_player_hp;
	int				score;
	struct timeval	t_zero;
}   t_info;

typedef struct s_spawn_info
{
	int	kills;
	int	timer;
	int ppk;
	int	wave_size;
}	t_spawn_info;

typedef struct s_game
{
	WINDOW			*win;
	t_spawn_info	spawn;
	t_info			info;
	struct timeval	frame_time;
	int				f_counter;
	t_entity		player;
	t_entitylist	*enemies;
	t_entitylist	*e_shots;
	t_entitylist	*p_shots;
	t_entity		***map;
}   t_game;

//INITIALIZATION
int		init_all(t_game *game);

//UPDATE
int	update_all(int input, t_game *game);

//CREATION
t_entitylist	*ft_lstnew(int c);
int				add_new_wave(t_game *game, int number);
int				create_new_eshot(t_entitylist *enemies, t_entitylist **e_shots, t_game *game);
void			ft_lstadd_front(t_entitylist **lst, t_entitylist *new);

//COLLISION
void	check_collision(t_entity *entity, int row, int col, t_game *game);

//DISPLAY
int		display_game(t_game game, struct timeval *ptr_curtime);
void	game_over(t_game *game);

//FRAME TIME
void	wait_next_frame(struct timeval *ptr_frametime, struct timeval curtime);

//FREE
void	free_all(t_game game);
void	free_lst(t_entitylist **ptr_lst);
void	free_map(t_entity ****ptr_map);

#endif
