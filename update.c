#include "ft_shmup.h"
#include <stdlib.h>

static int	update_player(int input, t_game *game);
static void	update_entities(t_entitylist *entities, t_game *game);

int	update_all(int input, t_game *game)
{
	int	ret;
	
	ret = update_player(input, game);
	//dprintf(game->fd, "updated player\n");
	update_entities(game->p_shots, game);
	//dprintf(game->fd, "updated player shots\n");
	if (ret != SUCCESS)
		return (ret);
	if (game->f_counter % FPS_CAP == 0)
		update_entities(game->enemies, game);
	//dprintf(game->fd, "updated enemies\n");
	if (game->f_counter % FPS_CAP == 0)
	{
		ret = create_new_eshot(game->enemies, &game->e_shots, game);
		//dprintf(game->fd, "created new e shots\n");
		if (ret != SUCCESS)
			return (ret);
	}
	if (game->f_counter % (game->spawn.timer * FPS_CAP) == 0)
	{
		if (game->spawn.kills != 0 && game->spawn.kills % 20 == 0 && game->spawn.wave_size < 10)
		{
			++game->spawn.wave_size;
			game->spawn.ppk += 25;
		}
		ret = add_new_wave(game, game->spawn.wave_size, 1, 0);
		//dprintf(game->fd, "added a new enemy wave\n");
		if (ret != SUCCESS)
			return (ret);
	}
	update_entities(game->e_shots, game);
	//dprintf(game->fd, "updated enemy shots\n");
	return (SUCCESS);
}

static void	set_pos(t_game *game, char appearance, int move_r, int move_c)
{
	if (game->player.app != appearance)
	{
		game->player.app = appearance;
		game->player.dir_r = move_r;
		game->player.dir_c = move_c;
	}
	check_collision(&game->player, game->player.row + game->player.dir_r, game->player.col + game->player.dir_c, game); 
}

static int	update_player(int input, t_game *game)
{
	t_entitylist	*new_shot;

    switch (input)
	{
		case KEY_UP :
			set_pos(game, PLAYER_UP, -1, 0);
			break;
		case KEY_DOWN : 
			set_pos(game, PLAYER_DOWN, 1, 0);
			break;
		case KEY_LEFT :
			set_pos(game, PLAYER_LEFT, 0, -1);
			break;
		case KEY_RIGHT : 
			set_pos(game, PLAYER_RIGHT, 0, 1);
			break;
		case ' ' :
			new_shot = ft_lstnew(PLAYER_SHOT, game->player.dir_r, game->player.dir_c);
			if (new_shot == NULL)
				return (ERROR_ALLOC);
			ft_lstadd_front(&game->p_shots, new_shot);
			check_collision(&new_shot->data, game->player.row + game->player.dir_r, game->player.col + game->player.dir_c, game);
	}
	return (SUCCESS);
}

static void	update_entities(t_entitylist *entities, t_game *game)
{
	if (entities != NULL)
	{
		if (entities->next != NULL)
			update_entities(entities->next, game);
		check_collision(&entities->data, entities->data.row + entities->data.dir_r, entities->data.col + entities->data.dir_c, game);
	}
}
