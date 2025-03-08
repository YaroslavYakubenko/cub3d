/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_n_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:22:43 by yyakuben          #+#    #+#             */
/*   Updated: 2025/03/08 19:42:28 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_spaces(char **map, t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '0')
			{
				if ((int)ft_strlen(map[y - 1]) <= x
					|| (int)ft_strlen(map[y]) <= x
					|| (int)ft_strlen(map[y + 1]) <= x)
					error_for_walls(game);
				if (map[y - 1][x - 1] == ' ' || map[y - 1][x] == ' '
					|| map[y - 1][x + 1] == ' ' || map[y][x + 1] == ' '
					|| map[y][x - 1] == ' ' || map[y + 1][x - 1] == ' '
					|| map[y + 1][x] == ' ' || map[y + 1][x + 1] == ' ')
					error_for_walls(game);
			}
		}
	}
}

void	check_tabs(char **map, t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '0')
			{
				if (map[y - 1][x - 1] == '\t' || map[y - 1][x] == '\t'
					|| map[y - 1][x + 1] == '\t' || map[y][x + 1] == '\t'
					|| map[y][x - 1] == '\t' || map[y + 1][x - 1] == '\t'
					|| map[y + 1][x] == '\t' || map[y + 1][x + 1] == '\t')
				{
					printf("Error: problems with walls.\n");
					free_map(game->map);
					free(game);
					exit(1);
				}
			}
		}
	}
}

void	check_end(char **map, t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
			{
				if (map[y - 1][x + 1] == '\0' || map[y][x + 1] == '\0'
					|| map[y + 1][x + 1] == '\0')
				{
					printf("Error: problems with walls.\n");
					free_map(game->map);
					free(game);
					exit(1);
				}
			}
			x++;
		}
		y++;
	}
}

void	check_new_line(char **map, t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '0')
			{
				if (map[y - 1][x - 1] == '\n' || map[y - 1][x] == '\n'
					|| map[y - 1][x + 1] == '\n' || map[y][x + 1] == '\n'
					|| map[y][x - 1] == '\n' || map[y + 1][x - 1] == '\n'
					|| map[y + 1][x] == '\n' || map[y + 1][x + 1] == '\n')
				{
					printf("Error: problems with walls.\n");
					free_map(game->map);
					free(game);
					exit(1);
				}
			}
		}
	}
}

void	validate_walls(char **map, t_game *game)
{
	go_to_last_array(map, game);
	check_spaces(map, game);
	check_tabs(map, game);
	check_end(map, game);
	check_new_line(map, game);
}
