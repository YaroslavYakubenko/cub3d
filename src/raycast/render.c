/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:26:18 by yyakuben          #+#    #+#             */
/*   Updated: 2024/12/13 17:17:11 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	pixel = game->back->addr + (y * game->back->line_lenght + x * (game->back->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	render_scene(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			// if (x % 2 == 0 && y % 2 == 0)e
			if ((x & 1) == 0 && (y & 1) == 0)
				put_pixel(game, x, y, 0xFF0000);
			else
				put_pixel(game, x, y, 0x000000);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->back->img, 0, 0);
}
