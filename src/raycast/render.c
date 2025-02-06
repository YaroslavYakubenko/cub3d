/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:26:18 by yyakuben          #+#    #+#             */
/*   Updated: 2025/02/06 21:11:32 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel(t_image *texture, int x, int y)
{
	int	i;

	if (!texture || !texture->addr)
		return (0x000000);
	i = (y * texture->line_lenght) + (x * (texture->bpp / 8));
	return (texture->addr[i] | (texture->addr[i + 1] << 8) | (texture->addr[i + 2] << 16));
}


void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;
	float	dist;
	t_image *texture;
	int		tex_x, tex_y;
	float	tex_step;
	float	tex_pos;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = player->x;
	ray_y = player->y;

	// Ищем, где луч ударяется в стену
	while (!touch(game, ray_x, ray_y))
	{
		if (DEBUG)
			put_pixel(game, ray_x, ray_y, 0xFF0000);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}

	// Определяем дистанцию до стены
	if (!DEBUG)
	{	
		dist = fixed_dist(game, player->x, player->y, ray_x, ray_y);
	
		// Вычисляем высоту стены на экране
		float height = (BLOCK / dist) * (SCREEN_WIDTH / 2);
		int start_y = (SCREEN_HEIGHT - height) / 2;
		int end_y = start_y + height;
	
		// Определяем направление удара в стену
		if (fabs(sin_angle) > fabs(cos_angle)) // Вертикальное пересечение
		{
			if (sin_angle > 0)
				texture = game->south_img; // Игрок смотрит на юг
			else
				texture = game->north_img; // Игрок смотрит на север
			tex_x = (int)ray_x % BLOCK;
		}
		else // Горизонтальное пересечение
		{
			if (cos_angle > 0)
				texture = game->east_img; // Игрок смотрит на восток
			else
				texture = game->west_img; // Игрок смотрит на запад
			tex_x = (int)ray_y % BLOCK;
		}
	
		// Шаг по текстуре
		tex_step = (float)TEXTUREHEIGHT / height;
		tex_pos = 0;
	
		// Рисуем текстурированную стену
		while (start_y < end_y)
		{
			tex_y = (int)tex_pos & (TEXTUREHEIGHT - 1); // Ограничение в границах текстуры
			int color = get_pixel(texture, tex_x, tex_y);
			put_pixel(game, i, start_y, color);
			tex_pos += tex_step;
			start_y++;
		}
	}
}


// void	draw_line(t_player *player, t_game *game, float start_x, int i)
// {
// 	float	cos_angle;
// 	float	sin_angle;
// 	float	ray_x;
// 	float	ray_y;
// 	float	dist;

// 	cos_angle = cos(start_x);
// 	sin_angle = sin(start_x);
// 	ray_x = player->x;
// 	ray_y = player->y;
// 	while (!touch(game, ray_x, ray_y))
// 	{
// 		if (DEBUG)
// 			put_pixel(game, ray_x, ray_y, 0xFF0000);
// 		ray_x += cos_angle;
// 		ray_y += sin_angle;
// 	}
// 	if (!DEBUG)
// 	{
// 		dist = fixed_dist(game, player->x, player->y, ray_x, ray_y);
// 		float	height = (BLOCK / dist) * (SCREEN_WIDTH / 2);
// 		int	start_y = (SCREEN_HEIGHT - height) / 2;
// 		int	end = start_y + height;
// 		while (start_y < end)
// 		{
// 			put_pixel(game, i, start_y, 0x11FFF0);
// 			start_y++;
// 		}
// 	}
// }

int	draw_loop(t_game *game)
{
	t_player	*player;

	player = game->player;
	movement_player(game);
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
		// printf("i: %d\n", i);
		draw_line(player, game, start_x, i);
		// printf("start-x before: %f\n", start_x);
		start_x += fraction;
		// printf("start-x after: %f\n", start_x);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->back->img, 0, 0);
	return (0);
}

// void	put_pixel(t_game *game, int x, int y, int color)
// {
// 	char	*pixel;

// 	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
// 		return ;
// 	pixel = game->back->addr + (y * game->back->line_lenght + x * (game->back->bpp / 8));
// 	*(unsigned int *)pixel = color;
// }

// void	calculate_ray_direction(t_ray *ray, t_game *game, float ray_angle)
// {
// 	ray->ray_x = game->player->x;
// 	ray->ray_y = game->player->y;
// 	ray->ray_dir_x = cos(ray_angle);
// 	ray->ray_dir_y = -sin(ray_angle);
// }

// void	calculate_init_steps(t_ray *ray, int map_x, int map_y,
// 	float delta_dist_x, float delta_dist_y)
// {
// 	if (ray->ray_dir_x < 0)
// 	{
// 		ray->step_x = -1;
// 		ray->side_dist_x = (ray->ray_x - map_x) * delta_dist_x;
// 	}
// 	else
// 	{
// 		ray->step_x = 1;
// 		ray->side_dist_x = (map_x + 1.0 - ray->ray_x);
// 	}
// 	if (ray->ray_dir_y < 0)
// 	{
// 		ray->step_y = -1;
// 		ray->side_dist_y = (ray->ray_y - map_y) * delta_dist_y;
// 	}
// 	else
// 	{
// 		ray->step_y = 1;
// 		ray->side_dist_y = (map_y + 1.0 - ray->ray_y);
// 	}
// }

// float	calculate_wall_distance(t_ray *ray, int map_x, int map_y)
// {
// 	if (ray->side == 0)
// 		return ((map_x - ray->ray_x + (1 - ray->step_x) / 2) / ray->ray_dir_x);
// 	else
// 		return ((map_y - ray->ray_y + (1 - ray->step_y) / 2) / ray->ray_dir_y);
// }

// float	perform_dda(t_ray *ray, t_game *game)
// {
// 	int		map_x;
// 	int		map_y;
// 	float	delta_dist_x;
// 	float	delta_dist_y;

// 	map_x = (int)ray->ray_x;
// 	map_y = (int)ray->ray_y;
// 	delta_dist_x = fabs(1 / ray->ray_dir_x);
// 	delta_dist_y = fabs(1 / ray->ray_dir_y);
// 	calculate_init_steps(ray, map_x, map_y, delta_dist_x, delta_dist_y);
// 	while (1)
// 	{
// 		if (ray->side_dist_x < ray->side_dist_y)
// 		{
// 			ray->side_dist_x += ray->side_dist_x;
// 			map_x += ray->step_x;
// 			ray->side = 0;
// 		}
// 		else
// 		{
// 			ray->side_dist_y += ray->side_dist_y;
// 			map_y += ray->step_y;
// 			ray->side = 1;
// 		}
// 		if (map_x < 0 || map_x > SCREEN_WIDTH || map_y < 0 || map_y > SCREEN_HEIGHT)
// 		{
// 			printf("Out of bounds: map_x=%d, map_y=%d\n", map_x, map_y);
// 			return (-1);
// 		}
// 		if (game->map->grid[map_y][map_x] == '1')
// 			break;
// 	}
// 	return (calculate_wall_distance(ray, map_x, map_y));
// }

// void	draw_wall(t_game *game, int x, float dist_to_wall, int side)
// {
// 	int	wall_height;
// 	int	wall_start;
// 	int	wall_end;
// 	int	y;
	
// 	wall_height = (int)(SCREEN_HEIGHT / (dist_to_wall + 0.0001));
// 	wall_start = SCREEN_HEIGHT / 2 - wall_height / 2;
// 	wall_end = SCREEN_HEIGHT / 2 + wall_height / 2;
// 	y = wall_start;
// 	while (y < wall_end)
// 	{
// 		if (side == 0)
// 			side = 0xAAAAAA;
// 		else
// 			side = 0x888888;
// 		put_pixel(game, x, y, side);
// 		y++;
// 	}
// }

// void	cast_rays(t_game *game)
// {
// 	int		x;
// 	float	ray_angle;
// 	float	dist_to_wall;
// 	t_ray	ray;

// 	x = 0;
// 	while (x < SCREEN_WIDTH)
// 	{
// 		ray_angle = game->player->angle - (FOV / 2) + (FOV / SCREEN_WIDTH) * x;
// 		calculate_ray_direction(&ray, game, ray_angle);
// 		dist_to_wall = perform_dda(&ray, game);
// 		draw_wall(game, x, dist_to_wall, ray.side);
// 		x++;
// 		printf("ray_angle: %f\n", ray_angle);
// 	}
// }

// void	render_scene(t_game *game)
// {
// 	cast_rays(game);
// 	printf("here_is_render_scene\n");
// 	mlx_put_image_to_window(game->mlx, game->win, game->back->img, 0, 0);
// }