#include "../includes/game.h"

void init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 2;

	player->key_down = false;
	player->key_up = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
}

bool	valid_symbol_character(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	init_position_charactor(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map->map[i])
	{
		j = 0;
		while (game->map->map[i][j])
		{
			if (valid_symbol_character(game->map->map[i][j]))
			{
				game->player.direction = game->map->map[i][j];
				game->map->map[i][j] = '0';
				game->player.pos_x = i + 0.5;
				game->player.pos_y = j + 0.5;
			}
			j++;
		}
		i++;
	}
}

void	add_plane_characters(t_game *game)
{
	char	plane;

	plane = game->player.direction;
	if (plane == 'S')
	{
		game->player.dir_x = 1;
		game->player.plane_y = -0.66;
	}
	else if (plane == 'N')
	{
		game->player.dir_x = -1;
		game->player.plane_y = 0.66;
	}
	else if (plane == 'E')
	{
		game->player.dir_y = 1;
		game->player.plane_x = 0.66;
	}
	else if (plane == 'W')
	{
		game->player.dir_y = -1;
		game->player.plane_x = -0.66;
	}
}

int key_press(int keycode, t_player *player)
{
	printf("pressed KEYCODE:%d\n", keycode);
	if(keycode == W)
		player->key_up = true;
	if(keycode == S)
		player->key_down = true;
	if(keycode == A)
		player->key_left = true;
	if(keycode == D)
		player->key_right = true;
	if(keycode == LEFT)
		player->left_rotate = true;
	if(keycode == RIGHT)
		player->right_rotate = true;
	return 0;
}

int key_release(int keycode, t_player *player)
{
	printf("released KEYCODE:%d\n", keycode);
	if(keycode == W)
		player->key_up = false;
	if(keycode == S)
		player->key_down = false;
	if(keycode == A)
		player->key_left = false;
	if(keycode == D)
		player->key_right = false;
	if(keycode == LEFT)
		player->left_rotate = false;
	if(keycode == RIGHT)
		player->right_rotate = false;
	return 0;
}

void move_player(t_game *game)
{
	// int speed = 3;
	// float angle_speed = 0.03;
	// float cos_angle = cos(player->angle);
	// float sin_angle = sin(player->angle);

	if(game->player.left_rotate)
		rotate_left(game);
		// player.angle -= angle_speed;
	if(game->player.right_rotate)
		rotate_right(game);
		// player.angle += angle_speed;
	// if(game->player.angle > 2 * PI)
	// 	player.angle = 0;
	// if(game->player.angle < 0)
	// 	player.angle = 2 * PI;
	if(game->player.key_up)
	{
		// printf("KEY UP\n");
		// player->pos_x += cos_angle * speed;
		// player->pos_y += sin_angle * speed;
		move_front(game);
	}
	if(game->player.key_down)
	{
		// printf("KEY DOWN\n");
		// player->pos_x -= cos_angle * speed;
		// player->pos_y -= sin_angle * speed;
		move_back(game);
	}
	if(game->player.key_left)
	{
		// printf("KEY LEFT\n");
		// player->pos_x += sin_angle * speed;
		// player->pos_y -= cos_angle * speed;
		move_left(game);
	}
	if(game->player.key_right)
	{
		// printf("KEY RIGHT\n");
		// player->pos_x -= sin_angle * speed;
		// player->pos_y += cos_angle * speed;
		move_right(game);
	}
}