/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:47:46 by yyakuben          #+#    #+#             */
/*   Updated: 2025/02/17 22:28:32 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_textures_and_colors(t_map *map, char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (ft_strncmp(lines[i], "NO ", 3) == 0)
		{
			map->north_texture = ft_strdup(lines[i] + 3);
			// printf("map->north_texture: %s\n", map->north_texture);
		}
		else if (ft_strncmp(lines[i], "SO ", 3) == 0)
			map->south_texture = ft_strdup(lines[i] + 3);
		else if (ft_strncmp(lines[i], "WE ", 3) == 0)
			map->west_texture = ft_strdup(lines[i] + 3);
		else if (ft_strncmp(lines[i], "EA ", 3) == 0)
			map->east_texture = ft_strdup(lines[i] + 3);
		else if (ft_strncmp(lines[i], "F ", 2) == 0)
			map->floor = ft_strdup(lines[i] + 2);
		else if (ft_strncmp(lines[i], "C ", 2) == 0)
		{
			map->ceiling = ft_strdup(lines[i] + 2);
		}
		else
			break;
		i++;
	}
	i++;
	return (i);
}

unsigned int	init_colors(char *color_string, t_map *map)
{
	char			**rgb;
	unsigned int	colors[3];
	int				i;

	(void)map;
	i = 0;
	if (color_string != NULL)
	{
		rgb = ft_split(color_string, ',');
		while (rgb[i])
		{
			colors[i] = ft_atoi(rgb[i]);
			if (colors[i] > 255)
				printf("Error: The range must be from 0 to 255.\n");
			i++;
		}
		i = 0;
		while (i < 3)
			free(rgb[i++]);
		free(rgb);
		return ((colors[0] << 16) | (colors[1] << 8) | colors[2]);
	}
	return (0);
}

int	validate_map(char **grid)
{
	int	i;
	int	j;

	i = 6;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if (grid[i][j] != '1' && grid[i][j] != '0'
				&& grid[i][j] != 'N' && grid[i][j] != 'S'
				&& grid[i][j] != 'E' && grid[i][j] != 'W'
				&& grid[i][j] != 'P')
				{
					printf("Error: Invalid character in map.\n");
					return (0);	
				}
			j++;
		}
		i++;
	}
	return (1);
}

t_map	*parse_cub_file(const char *file_name)
{
	t_map	*map;
	// char	**lines;
	int		map_start;
	// int		i;

	map = malloc(sizeof(t_map));
	map->liness = read_file(file_name);
	if (!map->liness)
		return (NULL);
	// i = 0;
	// while (i < 15)
	// {
	// 	printf("lines[%d]: %s\n", i, lines[i]);
	// 	i++;
		
	// }
	map->north_texture = NULL;
	map->south_texture = NULL;
	map->west_texture = NULL;
	map->east_texture = NULL;
	map->floor_color = -1;
	map->ceiling_color = -1;
	map->grid = NULL;
	map_start = parse_textures_and_colors(map, map->liness);
	map->ceiling_color = init_colors(map->ceiling, map);
	map->floor_color = init_colors(map->floor, map);
	// i = 0;
	// while (map->liness[i])
	// {
	// 	printf("map->liness[%d]: %s\n", i, map->liness[i]);
	// 	i++;
	// }
	map->grid = &map->liness[map_start];
	// printf("map->grid: %s\n", map->grid[0]);
	// printf("map->grid: %s\n", map->grid[1]);
	// printf("map->grid: %s\n", map->grid[2]);
	// printf("map->grid: %s\n", map->grid[3]);
	// printf("map->grid: %s\n", map->grid[4]);
	// printf("map->grid: %s\n", map->grid[5]);
	// printf("map->grid: %s\n", map->grid[6]);
	if (!validate_map(map->grid))
	{
		printf("Error: Invalid map.\n");
		// free_map(map);
        return (NULL);
	}
	// i = 0;
	// while (lines[i++])
	// 	free(lines[i]);
	// free(lines);
	return (map);
}
