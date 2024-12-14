/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:35:13 by yyakuben          #+#    #+#             */
/*   Updated: 2024/12/14 20:00:19 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map->grid[i])
	{
		j = 0;
		while (game->map->grid[i][j])
		{
			if (ft_strchr("NSEW", game->map->grid[i][j]))
			{
				game->map->player.x = j + 0.5;
				game->map->player.y = i + 0.5;
				if (game->map->grid[i][j] == 'N')
					game->map->player.angle = 3.14 / 2;
				else if (game->map->grid[i][j] == 'S')
					game->map->player.angle = 3 * 3.14 / 2;
				else if (game->map->grid[i][j] == 'E')
					game->map->player.angle = 0;
				else if (game->map->grid[i][j] == 'W')
					game->map->player.angle = 3.14;
				game->map->grid[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}
