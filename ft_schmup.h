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
	t_info			info;
	struct timeval	frame_time;
	int				f_counter;
	int				fd;
	t_entity		player;
	t_entitylist	*enemies;
	t_entitylist	*e_shots;
	t_entitylist	*p_shots;
	char			**map;
}   t_game;

//INITIALIZATION FUNCTIONS
int		init_player(t_game *game, t_entity *player);
int		init_info(t_info *ptr_info, t_game *ptr_game);
int		init_map(t_game *game);
int		init_all(t_game *game);

//UPDATE FUNCTIONS
void	update_player(int input, t_game *game);
void	update_entities(t_entitylist *entities, int move, t_game *game);
void	update_all(int input, t_game *game);
void	destroy_entity(t_entity *entity, t_entitylist *e_list, t_game *game);

//CREATION FUNCTIONS
void			add_new_wave(t_game *game, int number);
void			create_new_eshot(t_entitylist *enemies, t_entitylist *e_shots, t_game *game);
t_entitylist	*ft_lstnew(int c);
void			ft_lstadd_front(t_entitylist **lst, t_entitylist *new);

//COLLISION FUNCTIONS
void			reduce_hp(t_entity *entity, t_entity *other_entity);
t_entitylist	*set_type(t_entity *entity, t_game *game);
int				check_walls(int type, int row, int col);
void			check_collision(t_entity *entity, int row, int col, t_game *game);

//DISPLAY FUNCTIONS
void	display_game(t_game game, struct timeval *ptr_curtime);
void	ft_lstiter_display(t_entitylist *lst);
int		display_info(t_info info, struct timeval *ptr_curtime);

//FRAME TIME FUNCTIONS
void	wait_next_frame(struct timeval *ptr_frametime, struct timeval curtime);

#endif
