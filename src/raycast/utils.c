/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:14:37 by yyakuben          #+#    #+#             */
/*   Updated: 2025/03/04 17:00:06 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	touch(t_game *game, float px, float py)
{
	int	x;
	int	y;

	if (DEBUG)
	{
		x = (int)px / BLOCK;
		y = (int)py / BLOCK;
	}
	else
	{
		x = (int)px - 0.5;
		y = (int)py - 0.5;
	}
	if (game->map->grid[y][x] == '1')
		return (true);
	return (false);
}

void	my_mlx_pixel_put_v2(t_image *image, int x, int y, int color)
{
	char	*dst;

	// MAYBE CHANGE floor and ceiling here

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		dst = image->addr + (y * image->line_lenght + x * (image->bpp
					/ 8));
		*(unsigned int *)dst = color;
	}
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
