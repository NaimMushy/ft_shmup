#ifndef FT_SCHMUP_H
# define FT_SCHMUP_H

# define WIN_WIDTH 3
# define MAP_LIMIT LINES / 2

#include <ncurses.h>
#include <time.h>

typedef struct s_listentity
{
    t_entity    data;
    struct s_listentity    *next;
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
    int score;
    int *ptr_player_lives;
    timeval time;
}   t_info;

typedef struct s_game
{
    WINDOW  *win;
    timeval frame;
    int f_counter;
    t_entity player;
    t_listentity enemies;
    t_listentity e_shots;
    t_listentity p_shots;
}   t_game;


void	init_player(t_game *game);
void	update_player(char input, t_game *game);
void	ft_lstiter(t_entitylist *lst, void	(*f)())
void	ft_lstdelone(t_entitylist *lst, void (*del)(void *))
void	ft_lstadd_front(t_entitylist **lst, t_entitylist *new)
t_entitylist	*ft_lstnew(int row, int col)
#endif
