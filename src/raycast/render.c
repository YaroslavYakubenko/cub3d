/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:26:18 by yyakuben          #+#    #+#             */
/*   Updated: 2024/12/24 18:55:42 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	put_pixel(t_game *game, int x, int y, int color)
// {
// 	char	*pixel;

// 	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
// 		return ;
// 	pixel = game->back->addr + (y * game->back->line_lenght + x * (game->back->bpp / 8));
// 	*(unsigned int *)pixel = color;
// }

void	calculate_ray_direction(t_ray *ray, t_game *game, float ray_angle)
{
	ray->ray_x = game->map->player.x;
	ray->ray_y = game->map->player.y;
	ray->ray_dir_x = cos(ray_angle);
	ray->ray_dir_y = -sin(ray_angle);
}

void	calculate_init_steps(t_ray *ray, int map_x, int map_y,
	float delta_dist_x, float delta_dist_y)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->ray_x - map_x) * delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (map_x + 1.0 - ray->ray_x);
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->ray_y - map_y) * delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (map_y + 1.0 - ray->ray_y);
	}
}

float	calculate_wall_distance(t_ray *ray, int map_x, int map_y)
{
	if (ray->side == 0)
		return ((map_x - ray->ray_x + (1 - ray->step_x) / 2) / ray->ray_dir_x);
	else
		return ((map_y - ray->ray_y + (1 - ray->step_y) / 2) / ray->ray_dir_y);
}

float	perform_dda(t_ray *ray, t_game *game)
{
	int		map_x;
	int		map_y;
	float	delta_dist_x;
	float	delta_dist_y;

	map_x = (int)ray->ray_x;
	map_y = (int)ray->ray_y;
	delta_dist_x = fabs(1 / ray->ray_dir_x);
	delta_dist_y = fabs(1 / ray->ray_dir_y);
	calculate_init_steps(ray, map_x, map_y, delta_dist_x, delta_dist_y);
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->side_dist_x;
			map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->side_dist_y;
			map_y += ray->step_y;
			ray->side = 1;
		}
		if (map_x < 0 || map_x > SCREEN_WIDTH || map_y < 0 || map_y > SCREEN_HEIGHT)
		{
			printf("Out of bounds: map_x=%d, map_y=%d\n", map_x, map_y);
			return (-1);
		}
		if (game->map->grid[map_y][map_x] == '1')
			break;
	}
	return (calculate_wall_distance(ray, map_x, map_y));
}

void	draw_wall(t_game *game, int x, float dist_to_wall, int side)
{
	int	wall_height;
	int	wall_start;
	int	wall_end;
	int	y;
	
	wall_height = (int)(SCREEN_HEIGHT / (dist_to_wall + 0.0001));
	wall_start = SCREEN_HEIGHT / 2 - wall_height / 2;
	wall_end = SCREEN_HEIGHT / 2 + wall_height / 2;
	y = wall_start;
	while (y < wall_end)
	{
		if (side == 0)
			side = 0xAAAAAA;
		else
			side = 0x888888;
		put_pixel(game, x, y, side);
		y++;
	}
}

void	cast_rays(t_game *game)
{
	int		x;
	float	ray_angle;
	float	dist_to_wall;
	t_ray	ray;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ray_angle = game->map->player.angle - (FOV / 2) + (FOV / SCREEN_WIDTH) * x;
		// if (ray_angle < 0)
		// 	ray_angle += 2 * M_PI;
		// else if (ray_angle >= 2)
		// 	ray_angle -= 2 * M_PI;
		calculate_ray_direction(&ray, game, ray_angle);
		dist_to_wall = perform_dda(&ray, game);
		draw_wall(game, x, dist_to_wall, ray.side);
		x++;
		// printf("here_is_cast_rays\n");
		// printf("x: %d\n", x);
		printf("ray_angle: %f\n", ray_angle);
	}
}

void	render_scene(t_game *game)
{
	cast_rays(game);
	printf("here_is_render_scene\n");
	mlx_put_image_to_window(game->mlx, game->win, game->back->img, 0, 0);
}