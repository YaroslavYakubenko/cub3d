/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:47:46 by yyakuben          #+#    #+#             */
/*   Updated: 2024/12/21 19:08:35 by yyakuben         ###   ########.fr       */
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
			// printf("n_txtr:%s\n", map->north_texture);
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
		return ((colors[0] << 16) | (colors[1] << 8) | colors[2]);
	}
	return (0);
}

int	validate_map(char **grid)
{
	int	i;
	int	j;

	i = 5;
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
				ft_printf("Error: Invalid character in map.\n");
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
	char	**lines;
	int		map_start;

	map = malloc(sizeof(t_map));
	lines = read_file(file_name);
	if (!lines)
		return (NULL);
	map->north_texture = NULL;
	map->south_texture = NULL;
	map->west_texture = NULL;
	map->east_texture = NULL;
	map->floor_color = -1;
	map->ceiling_color = -1;
	map->grid = NULL;
	map_start = parse_textures_and_colors(map, lines);
	map->ceiling_color = init_colors(map->ceiling, map);
	map->floor_color = init_colors(map->floor, map);
	map->grid = &lines[map_start];
	if (!validate_map(map->grid))
	{
		ft_printf("Error: Invalid map.\n");
		free_map(map);
        return (NULL);
	}
	return (map);
}
