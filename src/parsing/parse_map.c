/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:47:46 by yyakuben          #+#    #+#             */
/*   Updated: 2025/02/27 16:53:40 by yyakuben         ###   ########.fr       */
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
			map->north_texture = ft_strdup(lines[i] + 3);
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

char	*parse_rgb(char *rgb)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * 11);
	while (rgb[i])
	{
		if (rgb[i] && (rgb[i] == ',' || (rgb[i] >= '0' && rgb[i] <= '9')))
		{
			str[j] = rgb[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

unsigned int	init_colors(char *color_string, t_map *map)
{
	char			**rgb;
	unsigned int	colors[3];
	int				i;

	(void)map;
	i = 0;
	color_string = parse_rgb(color_string);
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
		free(color_string);
		return ((colors[0] << 16) | (colors[1] << 8) | colors[2]);
	}
	return (0);
}

int	validate_map(char **grid)
{
	int	i;
	int	j;

	i = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if (grid[i][j] != '1' && grid[i][j] != '0'
				&& grid[i][j] != 'N' && grid[i][j] != 'S'
				&& grid[i][j] != 'E' && grid[i][j] != 'W'
				&& grid[i][j] != ' ' && grid[i][j] != '\n' && grid[i][j] != '\t')
				{
					printf("Error: Invalid character in map.\n");
					exit (1);	
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
	int		map_start;

	map = malloc(sizeof(t_map));
	map->liness = read_file(file_name);
	if (!map->liness)
		return (NULL);
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
	map->grid = &map->liness[map_start];
	if (!validate_map(map->grid))
	{
		printf("Error: Invalid map.\n");
        return (NULL);
	}
	validate_walls(map->grid);
	return (map);
}
