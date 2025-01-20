/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:10:47 by yyakuben          #+#    #+#             */
/*   Updated: 2025/01/20 20:40:09 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	int	i;
	if (!game || !game->back || !game->back->addr)
	{
		printf("Error: game, back or addr is NULL.\n");
		return;
	}
	if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT || x < 0 || y < 0)
		return;
	i = y * game->back->line_lenght + x * game->back->bpp / 8;
	game->back->addr[i] = color & 0xFF;
	game->back->addr[i + 1] = (color >> 8) & 0xFF;
	game->back->addr[i + 2] = (color >> 16) & 0xFF;
}

void	init_image(t_game *game)
{
	game->back = malloc(sizeof(t_image));
	if (!game->back)
		{
			printf("Error: Failed to allocate memory for back image.\n");
			free(game->back);
			exit(1);
		}
	game->back->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->back->img)
	{
		printf("Error: Failed to create new image.\n");
		free(game->back);
		exit(1);
	}
	game->back->addr = mlx_get_data_addr(game->back->img, &game->back->bpp,
		&game->back->line_lenght, &game->back->endian);
	if (!game->back->addr)
		exit(1);
}

void	draw_map(t_game *game)
{
	char	**map;
	int		color;
	int		x;
	int		y;

	y = 0;
	color = 0x0000FF;
	// game = malloc(sizeof(t_game));
	// printf("here\n");
	// printf("game->map->grid: %s\n", game->map->grid[0]);
	map = game->map->grid;
	// printf("map: %s\n", map[0]);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(game, x * BLOCK, y * BLOCK, BLOCK, color);
			x++;
		}
		y++;
	}
}

void	draw_square(t_game *game, int x, int y, int size, int color)
{
	float	i;

	i = 0;
	// printf("x = %f\ny = %f\n", x, y);
	while (i++ < size)
		put_pixel(game, x + i, y, color);
	i = 0;
	while (i++ < size)
		put_pixel(game, x, y + i, color);
	i = 0;
	while (i++ < size)
		put_pixel(game, x + size, y + i, color);
	i = 0;
	while (i++ < size)
		put_pixel(game, x + i, y + size, color);
}


void	init_game(t_game *game)
{
	game->back = malloc(sizeof(t_image));
	game->player = malloc(sizeof(t_player));

	if (!game->player || !game->back)
	{
		printf("Error: Failed to allocate memory.\n");
		return ;
	}
	init_player(game->player);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	game->back->img = mlx_new_image(game->mlx,SCREEN_WIDTH, SCREEN_HEIGHT);
	game->back->addr = mlx_get_data_addr(game->back->img, &game->back->bpp, &game->back->line_lenght, &game->back->endian);
	if (!game->mlx || !game->win || !game->back->img || !game->back->addr)
	{
    	printf("Error: Initialization failed.\n");
    	exit(1);
	}

	mlx_put_image_to_window(game->mlx, game->win, game->back->img, 0, 0);
}

bool	touch(t_game *game, float px, float py)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map->grid[y][x] == '1')
		return (true);
	return (false);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(t_game *game, float x1, float y1, float x2, float y2)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_y) - game->player->angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;
	float	dist;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = player->x;
	ray_y = player->y;
	while (!touch(game, ray_x, ray_y))
	{
		if (DEBUG)
			put_pixel(game, ray_x, ray_y, 0xFF0000);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if (!DEBUG)
	{
		dist = fixed_dist(game, player->x, player->y, ray_x, ray_y);
		float	height = (BLOCK / dist) * (SCREEN_WIDTH / 2);
		int	start_y = (SCREEN_HEIGHT - height) / 2;
		int	end = start_y + height;
		while (start_y < end)
		{
			put_pixel(game, i, start_y, 255);
			start_y++;
		}
	}
}

int	draw_loop(t_game *game)
{
	t_player	*player;

	player = game->player;
	move_player(game->player);
	clear_image(game);
	if (DEBUG)
	{	
		draw_square(game, game->player->x, game->player->y, 10, 0x00FF00);
		draw_map(game);
	}
	float	fraction = PI / 3 / SCREEN_WIDTH;
	float	start_x = game->player->angle - PI / 6;
	int		i = 0;
	while (i < SCREEN_WIDTH)
	{
		printf("i: %d\n", i);
		draw_line(player, game, start_x, i);
		printf("start-x before: %f\n", start_x);
		start_x += fraction;
		printf("start-x after: %f\n", start_x);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->back->img, 0, 0);
	return (0);
}



// int	game_loop(t_game *game)
// {
// 	render_scene(game);
// 	printf("here_is_game_loop\n");
// 	return (0);
// }

// void	load_texture(t_game *game, char *path,
// 	t_image **texture, int size_texture)
// {
// 	int	size;
	
// 	size = size_texture;
// 	*texture = malloc(sizeof(t_image));
// 	if (!(*texture))
// 	{
// 		printf("Error: Failed to allocate memory for texture.");
// 		exit (1);
// 	}
// 	(*texture)->img = mlx_xpm_file_to_image(game->mlx, path, &size, &size);
// 	if (!(*texture)->img)
// 	{
// 		printf("path: %s\nsize_texture: %d\n", path, size_texture);
// 		ft_printf("Error: Failed to load texture.\n");
// 		exit(1);
// 	}
// 	(*texture)->addr = mlx_get_data_addr((*texture)->img, &(*texture)->bpp,
// 		&(*texture)->bpp, &(*texture)->endian);
// 	if (!(*texture)->addr)
// 	{
// 		ft_printf("Error: Failed to get image address.\n");
// 		exit(1);
// 	}
// }

// void	rm_newline(char *str)
// {
// 	int	len;

// 	if (!str)
// 		return ;
// 	len = 0;
// 	len = ft_strlen(str);
// 	if (len > 0 && str[len - 1] == '\n')
// 		str[len - 1] = '\0';
	
// }

// void	load_all_textures(t_game *game)
// {
// 	rm_newline(game->map->north_texture);
// 	rm_newline(game->map->south_texture);
// 	rm_newline(game->map->west_texture);
// 	rm_newline(game->map->east_texture);
// 	load_texture(game, game->map->north_texture, &game->north_img, TEXTUREHEIGHT);
// 	load_texture(game, game->map->south_texture, &game->south_img,TEXTUREHEIGHT);
// 	load_texture(game, game->map->west_texture, &game->west_img, TEXTUREHEIGHT);
// 	load_texture(game, game->map->east_texture, &game->east_img,TEXTUREHEIGHT);
// }
