/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:14:37 by yyakuben          #+#    #+#             */
/*   Updated: 2025/02/20 21:26:56 by yyakuben         ###   ########.fr       */
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
	// printf("px: %f\npy: %f\n", px, py);
	// x = (int)px;
	// y = (int)py;
	printf("x: %d\ny: %d\n", x, y);
	if(y > 6 || y < 0) // Костыль убрать!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		return true;
	if (game->map->grid[y][x] == '1')
	{
		// printf("Wall hit at (%d, %d)\n", x, y);
		return (true);
	}
	return (false);
}

double	distance(double x, double y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(t_game *game, double x1, double y1, double x2, double y2)
{
	double	delta_x;
	double	delta_y;
	double	angle;
	double	fix_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - game->player->angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}
