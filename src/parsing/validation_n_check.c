/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_n_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:22:43 by yyakuben          #+#    #+#             */
/*   Updated: 2025/03/04 16:36:05 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_spaces(char **map)
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
				if (map[y - 1][x - 1] == ' ' || map[y - 1][x] == ' '
					|| map[y - 1][x + 1] == ' ' || map[y][x + 1] == ' '
					|| map[y][x - 1] == ' ' || map[y + 1][x - 1] == ' '
					|| map[y + 1][x] == ' ' || map[y + 1][x + 1] == ' ')
				{
					printf("Error: problems with walls.\n");
					exit (1);
				}
			}
			x++;
		}
		y++;
	}
}

void	check_tabs(char **map)
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
				if (map[y - 1][x - 1] == '\t' || map[y - 1][x] == '\t'
					|| map[y - 1][x + 1] == '\t' || map[y][x + 1] == '\t'
					|| map[y][x - 1] == '\t' || map[y + 1][x - 1] == '\t'
					|| map[y + 1][x] == '\t' || map[y + 1][x + 1] == '\t')
				{
					printf("Error: problems with walls.\n");
					exit (1);
				}
			}
			x++;
		}
		y++;
	}
}

void	check_end(char **map)
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
					exit (1);
				}
			}
			x++;
		}
		y++;
	}
}

void	check_new_line(char **map)
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
				if (map[y - 1][x - 1] == '\n' || map[y - 1][x] == '\n'
					|| map[y - 1][x + 1] == '\n' || map[y][x + 1] == '\n'
					|| map[y][x - 1] == '\n' || map[y + 1][x - 1] == '\n'
					|| map[y + 1][x] == '\n' || map[y + 1][x + 1] == '\n')
				{
					printf("Error: problems with walls.\n");
					exit (1);
				}
			}
			x++;
		}
		y++;
	}
}

void	validate_walls(char **map)
{
	go_to_last_array(map);
	check_spaces(map);
	check_tabs(map);
	check_end(map);
	check_new_line(map);
}
