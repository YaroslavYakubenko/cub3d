/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:26:18 by yyakuben          #+#    #+#             */
/*   Updated: 2025/02/27 16:55:30 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel(t_image *texture, int tex_x, int tex_y)
{
	int				offset;
	unsigned int	*pixel;

	// printf("tex_x: %d\ntex_y: %d\n", tex_x, tex_y);
	if (!texture || !texture->addr || tex_x < 0 || tex_y < 0
		|| tex_x >= TEXTUREWIDTH || tex_y >= TEXTUREHEIGHT)
		return (0);
	offset = tex_y * (texture->line_lenght / (texture->bpp / 8)) + tex_x;
	pixel = (unsigned int *)(texture->addr + offset * (texture->bpp / 8));
	return (*pixel);
}

// int	get_pixel(t_image *texture, int x, int y)
// {
// 	int	i;

// 	// printf("x: %d\ny: %d\n", x, y);
// 	if (!texture || !texture->addr)
// 		return (0x000000);
// 	i = (y * texture->line_lenght) + (x * (texture->bpp / 8));
// 	return (texture->addr[i] | (texture->addr[i + 1] << 8) | (texture->addr[i + 2] << 16));
// }

void	draw_line(t_player *player, t_game *game, double start_x, int i)
{
	double	cos_angle = cos(start_x);
	double	sin_angle = sin(start_x);
	double	ray_x = player->x;
	double	ray_y = player->y;

	(void)i;
	while (!touch(game, ray_x, ray_y))
	{
		if (DEBUG)
			put_pixel(game, ray_x, ray_y, 0xFF0000);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	int			x;
	int			y;

	x = -1;
	player = game->player;
	
	clear_image(game);
	if (DEBUG)
	{	
		draw_square(game, game->player->x, game->player->y, 10, 0x00FF00);
		draw_map(game);
		float fraction = PI / 3 / SCREEN_WIDTH;
		float start_x = player->angle - PI / 6;
		int i = 0;
		while(i < SCREEN_WIDTH)
		{
			draw_line(player, game, start_x, i);
			start_x += fraction;
			i++;
		}
	}
	// float fraction = PI / 3 / SCREEN_WIDTH;
	// float start_x = player->angle - PI / 6;
	// floor_and_ceiling(game);
	// while (++x < SCREEN_WIDTH)
	// {
	// 	draw_line(player, game, start_x, ++x);
	// 	start_x += fraction;
	// }
	if (!DEBUG)
	{
		floor_and_ceiling(game);
		x = -1;
		while (++x < SCREEN_WIDTH)
		{
			calculate_ray_direction(game, x);
			calculate_ray_step(game);
			find_wall_hit(game);
			calculate_wall_dimensions(game);
			calculate_texture_position(game);
			y = game->rc->draw_start - 1;
			while( ++y < game->rc->draw_end)
			{
				draw_wall_segment(game, x, y);
				// printf("here_is_draw_loop\n");
			}
			// start_x += fraction;
			// x++;
		}
	}
	movement_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->back->img, 0, 0);
	return (0);
}

void	floor_and_ceiling(t_game *game)
{
	unsigned int	*dst;
	int				i;

	dst = (unsigned int *)game->back->addr;
	i = SCREEN_WIDTH * SCREEN_HEIGHT / 2 + 1;
	while (--i > 0)
	{
		*dst++ = game->map->ceiling_color;
		
	}
	i = SCREEN_WIDTH * SCREEN_HEIGHT / 2 + 1;
	while (--i > 0)
		*dst++ = game->map->floor_color;
}
