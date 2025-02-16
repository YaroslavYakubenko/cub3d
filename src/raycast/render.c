/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:26:18 by yyakuben          #+#    #+#             */
/*   Updated: 2025/02/16 22:20:55 by yyakuben         ###   ########.fr       */
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

void	draw_line(t_player *player, t_game *game, double start_x, int i)
{
	double	cos_angle = cos(start_x);
	double	sin_angle = sin(start_x);
	double	ray_x = player->x;
	double	ray_y = player->y;

	(void)i;
	// Ищем, где луч ударяется в стену
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

	x = 0;
	player = game->player;
	movement_player(game);
	clear_image(game);
	if (DEBUG)
	{	
		draw_square(game, game->player->x * BLOCK, game->player->y * BLOCK, 10, 0x00FF00);
		draw_map(game);
	}
	if (!DEBUG)
	{
		while (x < SCREEN_WIDTH)
		{
			init_raycast(game);
			calculate_ray_direction(game, x);
			calculate_ray_step(game);
			find_wall_hit(game);
			calculate_wall_dimensions(game);
			calculate_texture_position(game);
			draw_wall_segment(game, x);
			// printf("here_is_draw_loop\n");
			x++;
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->back->img, 0, 0);
	return (0);
}
