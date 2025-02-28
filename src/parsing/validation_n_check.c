/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_n_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:22:43 by yyakuben          #+#    #+#             */
/*   Updated: 2025/02/27 21:01:03 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	first_y_wall(char **map)
// {
// 	int	y;
// 	int	x;
	
// 	y = -1;
// 	while (map[++y])
// 	{
// 		printf("map[%d][0]: %c\n", y , map[y][0]);
// 		if (map[y][0] == '0')
// 		{
// 			printf("Error: problems with walls.\n");
// 			exit (1);
// 		}
// 		x = 0;
// 		while (map[y][x] && (map[y][x] == ' ' || map[y][x] == '\t' || map[y][x] == '1'))
// 		{
			
// 			if (map[y][x] == '0' && (map[y][x - 1] == ' ' || map[y][x] == '\t'))
// 			{
// 				printf("Error: problems with walls.\n");
// 				exit (1);
// 			}
// 			x++;
// 		}
// 	}
// }

// void	firts_x_wall(char **map)
// {
// 	int	x;

// 	first_y_wall(map);
// 	x = 0;
// 	while (map[0][x])
// 	{
// 		if (map[0][x] == '0')
// 		{
// 			printf("Error: problems with walls.\n");
// 			exit (1);
// 		}
// 		x++;
// 	}
// }

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
					printf("map[%d][%d]: %c\n", y, x, map[y][x]);
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
					printf("map[%d][%d]: %c\n", y, x, map[y][x]);
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
					printf("map[%d][%d]: %c\n", y, x, map[y][x]);
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
					printf("map[%d][%d]: %c\n", y, x, map[y][x]);
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
	printf("here_is_validate_walls\n");
	check_spaces(map);
	check_tabs(map);
	check_end(map);
	check_new_line(map);
}
