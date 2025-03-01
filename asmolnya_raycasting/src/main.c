#include "../includes/game.h"

// void put_pixel(int x, int y, int color, t_game *game)
// {
// 	if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
// 		return;
// 	int index = y * game->size_line + x * game->bpp / 8; // counting index
// 	game->data[index] = color & 0xFF;  // set blue component
// 	game->data[index + 1] = (color >> 8) & 0xFF; //  set green
// 	game->data[index + 2] = (color >> 16) & 0xFF; // set red
// }

// void draw_square(int x, int y, int size, int color, t_game *game)
// {
// 	for(int i = 0; i < size; i++)
// 		put_pixel(x + i, y, color, game);
// 	for(int i = 0; i < size; i++)
// 		put_pixel(x, y + i, color, game);
// 	for(int i = 0; i < size; i++)
// 		put_pixel(x + size, y + i, color, game);
// 	for(int i = 0; i < size; i++)
// 		put_pixel(x + i, y + size, color, game);
// }

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

void	ft_bzero(void *p, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		*(unsigned char *)(p + i++) = '\0';
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = (void *)malloc(size * count);
	if (!p)
		return (NULL);
	ft_bzero(p, (count * size));
	return (p);
}

void	init_texture(t_game *game, t_image **texture, char *path_texture,
	int size_texture)
{
int	size;

size = size_texture;
*texture = ft_calloc(1, sizeof(t_image));
printf("INIT TEXTURES: game->mlx = %p,\n path_texture = %s,\n size = %d\n", game->mlx, path_texture, size);
(*texture)->img = mlx_xpm_file_to_image(game->mlx, path_texture, &size,
		&size);
printf("(*texture)->img = %p\n", (*texture)->img);
printf("INIT TEXTURES HERE 1\n");
if (!(*texture)->img)
	exit(1);
	// error_exit_game("Problem with loading image", game);
printf("INIT TEXTURES HERE 2\n");
(*texture)->addr = mlx_get_data_addr((*texture)->img,
		&(*texture)->bits_per_pixel, &(*texture)->line_length,
		&(*texture)->endian);
if (!(*texture)->addr)
	exit(1);
printf("INIT TEXTURES HERE 3\n");
	// error_exit_game("Problem with getting image address", game);
}

void	init_walls(t_game *game)
{
	game->map->ea = "../textures/wallE.xpm";
	game->map->so = "../textures/wallS.xpm";
	game->map->no = "../textures/wallN.xpm";
	game->map->we = "../textures/wallW.xpm";

	game->so_img = NULL;
	game->ea_img = NULL;
	game->no_img = NULL;
	game->we_img = NULL;

	// printf("INIT WALLS HERE 1\n");

	init_texture(game, &game->ea_img, game->map->ea, TEXHEIGHT);
	// printf("INIT WALLS HERE 2\n");
	init_texture(game, &game->so_img, game->map->so, TEXHEIGHT);
	init_texture(game, &game->no_img, game->map->no, TEXHEIGHT);
	init_texture(game, &game->we_img, game->map->we, TEXHEIGHT);
}

static void	init_background(t_game *game)
{
	game->back = malloc(sizeof(t_image));
	if (!game->back)
		exit(1);
		// error_exit_game("Failed to allocate memory for background", game);
	game->back->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->back->img)
		exit(1);
		// error_exit_game("Failed to create background image", game);
	game->back->addr = mlx_get_data_addr(game->back->img,
			&game->back->bits_per_pixel, &game->back->line_length,
			&game->back->endian);
	if (!game->back->addr)
		exit(1);
		// error_exit_game("Failed to get background image address", game);
}

static void	init_mlx_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit(1);
		// error_exit_game("Failed to initialize mlx", game);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT,
			"cub3D");
	if (!game->win)
		exit(1);
		// error_exit_game("Failed to create mlx window", game);
}

void init_game(t_game *game)
{
	init_player(&game->player);
	init_rc(&game->rc);
	// printf("INIT GAME HERE 1\n");
	game->map = malloc(sizeof(t_map));
	game->map->map = get_map();
	// printf("INIT GAME HERE 2\n");
	init_mlx_window(game);
	// printf("INIT GAME HERE 3\n");
	init_background(game);
	// printf("INIT GAME HERE 4\n");
	init_walls(game);
	// printf("INIT GAME HERE 5\n");
	init_position_charactor(game);
	add_plane_characters(game);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	// game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	// mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	
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

// int draw_map(t_game *game)
// {
// 	char **map = game->map->map;
// 	int color = 0x0000FF;
// 	for(int y = 0; map[y]; y++)
// 		for(int x = 0; map[y][x]; x++)
// 			if(map[y][x] == '1')
// 				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
// 	return 0;
// }

// void clear_image(t_game *game)
// {
// 	int color;
// 	for(int y = 0; y < HEIGHT; y++)
// 		for(int x = 0; x < WIDTH; x++)
// 		{
// 			color = 220001000;
// 			if(y < HEIGHT / 2)
// 				color = 225030000;
// 			put_pixel(x, y, color, game);
// 		}
// }

bool touch(float px, float py, t_game *game)
{
	int x = px / BLOCK;
	int y = py / BLOCK;
	if(game->map->map[y][x] == '1')
		return true;
	return false;
}

// int distance(float x, float y)
// {
// 	return sqrt(x * x + y * y);
// }

// float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
// {
// 	float delta_x = x2 - x1;
// 	float delta_y = y2 - y1;
// 	float angle = atan2(delta_y, delta_x) - game->player.angle;
// 	float fix_dist = distance(delta_x, delta_y) * cos(angle);
// 	return fix_dist;

// }

// void draw_line(t_player *player, t_game *game, float start_x, int i)
// {
// 	float cos_angle = cos(start_x);
// 	float sin_angle = sin(start_x);

// 	float ray_x = player->x;
// 	float ray_y = player->y;

// 	while(!touch(ray_x, ray_y, game))
// 	{
// 		if(DEBUG)
// 			put_pixel(ray_x, ray_y, 0xFF0000, game);
// 		ray_x += cos_angle;
// 		ray_y += sin_angle;
// 	}
// 	if(!DEBUG)
// 	{
// 		float dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
// 		float height = (BLOCK / dist) * (WIDTH / 2);
// 		int start_y = (HEIGHT - height) / 2;
// 		int end = start_y + height;
// 		while(start_y < end)
// 		{
// 			put_pixel(i, start_y, 255, game);
// 			start_y++;
// 		}
// 	}

// }



// int draw_loop(t_game *game)
// {
// 	t_player *player = &game->player;
// 	move_player(player);
// 	clear_image(game);
// 	if(DEBUG)
// 	{
// 		draw_square(player->x, player->y, 10, 0x00FF00, game);
// 		draw_map(game);
// 	}

// 	float fraction = PI / 3 / WIDTH;
// 	float start_x = player->angle - PI / 6;
// 	render(game);
// 	// delete when finish
// 	int i = 0;
// 	while(i < WIDTH)
// 	{
// 		draw_line(player, game, start_x, i);
// 		start_x += fraction;
// 		i++;
// 	}
// 	// delete when finish
// 	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
// 	return 0;
// }

int main()
{
	t_game game;
	init_game(&game);
	// printf("MAIN HERE\n");
	mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
	
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);

	return 0;
}
