/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:35:13 by yyakuben          #+#    #+#             */
/*   Updated: 2024/11/28 20:46:38 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_player(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (ft_strchr("NSEW", map->grid[i][j]))
			{
				map->player.x = j + 0.5;
				map->player.y = i + 0.5;
				if (map->grid[i][j] == 'N')
					map->player.angle = 3.14 / 2;
				else if (map->grid[i][j] == 'S')
					map->player.angle = 3 * 3.14 / 2;
				else if (map->grid[i][j] == 'E')
					map->player.angle = 0;
				else if (map->grid[i][j] == 'W')
					map->player.angle = 3.14;
				map->grid[i][j] = '0';
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
