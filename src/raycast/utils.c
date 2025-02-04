/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:14:37 by yyakuben          #+#    #+#             */
/*   Updated: 2025/02/04 19:04:50 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	touch(t_game *game, float px, float py)
{
	int	x;
	int	y;

	x = (int)px / BLOCK;
	y = (int)py / BLOCK;
	// printf("px: %f\npy: %f\n", px, py);
	// if (x < 0 || y < 0 || y >= SCREEN_HEIGHT || x >= SCREEN_WIDTH)
	// 	return (true);
	if (y - 1 < 0 || x - 1 < 0 || !game->map->grid[y - 1] || !game->map->grid[y + 1])
	{
		return (true);
	}
	if ((int)ft_strlen(game->map->grid[y - 1]) <= x || (int)ft_strlen(game->map->grid[y + 1]) <= x || x
		- 1 < 0 || x + 1 >= (int)ft_strlen(game->map->grid[y]))
	{
		return (true);
	}
	if (game->map->grid[y][x + 1] == ' ' || game->map->grid[y + 1][x] == ' ' || game->map->grid[y][x - 1] == ' '
		|| game->map->grid[y - 1][x] == ' ')
	{
		return (true);
	}
	// if (game->map->grid[y][x] == '1')
	// 	return (true);
	return (false);
	// return (game->map->grid[y][x] == '1');
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
	angle = atan2(delta_y, delta_x) - game->player->angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}
