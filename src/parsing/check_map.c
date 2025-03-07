/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:35:23 by yyakuben          #+#    #+#             */
/*   Updated: 2025/03/07 21:09:16 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_last_array(char **map, int i, t_game *game)
{
	int	x;
	int	y;

	y = -1;
	x = 0;
	while (map[y])
		++y;
	if (i == y - 1)
	{
		while (map[y - 1][x])
		{
			x++;
		}
	}
	if ((map[y - 1][x - 2] == '0' || map[y - 1][x - 1] == '0')
		|| map[y - 1][0] == '0')
	{
		printf("Error: problems with walls.\n");
		free_map(game->map);
		free(game);
		exit (1);
	}
}

int	find_last_array(char **map, int x, int y)
{
	int	i;

	(void)map;
	i = 0;
	while (y > 0)
	{
		x = 0;
		while (map[y][x] != '\n' && map[y][x] != '\0')
		{
			if (map[y][x] == '1')
			{
				i = y;
				return (i);
			}
			x++;
		}
		y--;
	}
	return (0);
}

void	go_to_last_array(char **map, t_game *game)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			x++;
		}
		y++;
	}
	i = find_last_array(map, x, y - 1);
	check_last_array(map, i, game);
}

void	double_character(char **map, t_game *game)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = 0;
	while (map[y])
	{
		// printf("map[%d]: %s", y, map[y]);
		x = 0;
		while (map[y][x])
		{
			// printf("X = %d\n", x);
			if (map[y][x] == 'S' || map[y][x] == 'W'
				|| map[y][x] == 'E' || map[y][x] == 'N')
				i++;
			x++;
		}
		y++;
	}
	if (i != 1)
	{
		// printf("map[%d][%d]: %c\n", y, x, map[y][x]);
		printf("i: %d\n", i);
		printf("Error: Invalid player.\n");
		free_map(game->map);
		free(game);
		exit (1);
	}
}
