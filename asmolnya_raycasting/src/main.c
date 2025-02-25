#include "../includes/game.h"

void put_pixel(int x, int y, int color, t_game *game)
{
	if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return;
	int index = y * game->size_line + x * game->bpp / 8; // counting index
	game->data[index] = color & 0xFF;  // set blue component
	game->data[index + 1] = (color >> 8) & 0xFF; //  set green
	game->data[index + 2] = (color >> 16) & 0xFF; // set red
}

void draw_square(int x, int y, int size, int color, t_game *game)
{
	for(int i = 0; i < size; i++)
		put_pixel(x + i, y, color, game);
	for(int i = 0; i < size; i++)
		put_pixel(x, y + i, color, game);
	for(int i = 0; i < size; i++)
		put_pixel(x + size, y + i, color, game);
	for(int i = 0; i < size; i++)
		put_pixel(x + i, y + size, color, game);
}

void init_rc(t_raycast *rc)
{
	rc->raydir_x = 0.0;
    rc->raydir_y = 0.0;
    rc->map_x = 0;
    rc->map_y = 0;
    rc->side_dist_x = 0.0;
    rc->side_dist_y = 0.0;
    rc->delta_dist_x = 0.0;
    rc->delta_dist_y = 0.0;
    rc->perp_wall_dist = 0.0;
    rc->step_x = 0;
    rc->step_y = 0;
    rc->hit = 0;
    rc->side = 0;
    rc->line_height = 0;
    rc->draw_start = 0;
    rc->draw_end = 0;
    rc->wall_x = 0.0;
    rc->step = 0.0;
    rc->tex_pos = 0.0;
    rc->tex_x = 0;
    rc->tex_y = 0;
    rc->color = 0;
}

void init_game(t_game *game)
{
	init_player(&game->player);
	init_rc(&game->rc);
	game->map = malloc(sizeof(t_map));
	game->map->map = get_map();
	init_position_charactor(game);
	add_plane_characters(game);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	
}

char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = strdup("111111111111111"); // CHANGE FOR FT
    map[1] = strdup("100000000000001");
    map[2] = strdup("100000000000001");
    map[3] = strdup("100000100000001");
    map[4] = strdup("100000000000001");
    map[5] = strdup("100000010000001");
    map[6] = strdup("100001000000001");
    map[7] = strdup("100000000000001");
    map[8] = strdup("10000N000000001");
    map[9] = strdup("111111111111111");
    map[10] = NULL;
    return (map);
}

int draw_map(t_game *game)
{
	char **map = game->map->map;
	int color = 0x0000FF;
	for(int y = 0; map[y]; y++)
		for(int x = 0; map[y][x]; x++)
			if(map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
	return 0;
}

void clear_image(t_game *game)
{
	int color;
	for(int y = 0; y < HEIGHT; y++)
		for(int x = 0; x < WIDTH; x++)
		{
			color = 220001000;
			if(y < HEIGHT / 2)
				color = 225030000;
			put_pixel(x, y, color, game);
		}
}

bool touch(float px, float py, t_game *game)
{
	int x = px / BLOCK;
	int y = py / BLOCK;
	if(game->map->map[y][x] == '1')
		return true;
	return false;
}

int distance(float x, float y)
{
	return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float delta_x = x2 - x1;
	float delta_y = y2 - y1;
	float angle = atan2(delta_y, delta_x) - game->player.angle;
	float fix_dist = distance(delta_x, delta_y) * cos(angle);
	return fix_dist;

}

void draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);

	float ray_x = player->x;
	float ray_y = player->y;

	while(!touch(ray_x, ray_y, game))
	{
		if(DEBUG)
			put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if(!DEBUG)
	{
		float dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
		float height = (BLOCK / dist) * (WIDTH / 2);
		int start_y = (HEIGHT - height) / 2;
		int end = start_y + height;
		while(start_y < end)
		{
			put_pixel(i, start_y, 255, game);
			start_y++;
		}
	}

}



int draw_loop(t_game *game)
{
	t_player *player = &game->player;
	move_player(player);
	clear_image(game);
	if(DEBUG)
	{
		draw_square(player->x, player->y, 10, 0x00FF00, game);
		draw_map(game);
	}

	float fraction = PI / 3 / WIDTH;
	float start_x = player->angle - PI / 6;
	render(game);
	// delete when finish
	int i = 0;
	while(i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	// delete when finish
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return 0;
}

int main()
{
	t_game game;
	init_game(&game);
	mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
	
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return 0;
}
