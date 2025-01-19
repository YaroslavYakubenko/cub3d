/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaroslav <yaroslav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:30:47 by yyakuben          #+#    #+#             */
/*   Updated: 2025/01/17 17:59:24 by yaroslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < SCREEN_WIDTH)
	{
		x = 0;
		while (x < SCREEN_HEIGHT)
		{
			put_pixel(game, y, x, 0);
			x++;
		}
		y++;
	}
}