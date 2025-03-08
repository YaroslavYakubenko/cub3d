/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:47:46 by yyakuben          #+#    #+#             */
/*   Updated: 2025/03/08 17:44:58 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_textures_and_colors(t_game *game, char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		
		if (ft_strncmp(lines[i], "NO ", 3) == 0)
		{
			if(!game->map->north_texture)
				game->map->north_texture = ft_strdup(lines[i] + 3);
			else
				error_for_duplicate_texture(game);
			i++;
			continue;
		}
		else if (ft_strncmp(lines[i], "SO ", 3) == 0)
		{
			if(!game->map->south_texture)
				game->map->south_texture = ft_strdup(lines[i] + 3);
			else
				error_for_duplicate_texture(game);
			i++;
			continue;
		}
		else if (ft_strncmp(lines[i], "WE ", 3) == 0)
		{
			if(!game->map->west_texture)
				game->map->west_texture = ft_strdup(lines[i] + 3);
			else
				error_for_duplicate_texture(game);
			i++;
			continue;
		}
		else if (ft_strncmp(lines[i], "EA ", 3) == 0)
		{
			if(!game->map->east_texture)
				game->map->east_texture = ft_strdup(lines[i] + 3);
			else
				error_for_duplicate_texture(game);
			i++;
			continue;
		}
		else if (ft_strncmp(lines[i], "F ", 2) == 0)
		{
			if(!game->map->floor)
				game->map->floor = ft_strdup(lines[i] + 2);
			else
				error_for_duplicate_texture(game);
			i++;
			continue;
		}
		else if (ft_strncmp(lines[i], "C ", 2) == 0)
		{
			if(!game->map->ceiling)
				game->map->ceiling = ft_strdup(lines[i] + 2);
			else
				error_for_duplicate_texture(game);
			i++;
			continue;
		}
		else if (lines[i][0] == '\n'
			|| lines[i][0] == '\t' || lines[i][0] == ' ')
			{
				i++;
				if(game->map->north_texture && game->map->south_texture && game->map->west_texture
					&& game->map->east_texture && game->map->floor && game->map->ceiling)
					break ;
				continue ;
			}
		else if(game->map->north_texture && game->map->south_texture && game->map->west_texture
			&& game->map->east_texture && game->map->floor && game->map->ceiling)
			break ;
		else
			error_for_invalid_line(game);
	}
	return (i);
}

char	*parse_rgb(char *rgb, t_game *game)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * strlen(rgb) + 1);
	while (rgb[i])
	{
		while (rgb[i] == ' ' || rgb[i] == '\t')
			i++;
		if ((rgb[i]) && (rgb[i] < '0' || rgb[i] > '9')
			&& rgb[i] != ',' && rgb[i] != '\n')
			error_exit_for_parse_rgb(game, str);
		if (rgb[i] && (rgb[i] == ',' || (rgb[i] >= '0' && rgb[i] <= '9')))
			str[j++] = rgb[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

void	free_rgb(char **rgb, char *color_string)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
	free(color_string);
}

unsigned int	init_colors(char *color_string, t_game *game)
{
	char			**rgb;
	unsigned int	colors[3];
	int				i;

	i = -1;
	color_string = parse_rgb(color_string, game);
	rgb = ft_split(color_string, ',');
	while (rgb[++i])
	{
		colors[i] = ft_atoi(rgb[i]);
		if (colors[i] > 255 || ft_strlen(rgb[i]) > 3)
		{
			
			printf("Error: The range must be from 0 to 255.\n");
			free_rgb(rgb, color_string);
			free_map(game->map);
			free(game);
			exit (1);
		}
	}
	free_rgb(rgb, color_string);
	return ((colors[0] << 16) | (colors[1] << 8) | colors[2]);
}

int	validate_map(char **grid, t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (grid[++i])
	{
		// printf("grid[%d] = %s", i, grid[i]);
		j = -1;
		while (grid[i][++j])
		{
			if (grid[i][j] != '1' && grid[i][j] != '0'
				&& grid[i][j] != 'N' && grid[i][j] != 'S'
				&& grid[i][j] != 'E' && grid[i][j] != 'W'
				&& grid[i][j] != ' ' && grid[i][j] != '\n'
				&& grid[i][j] != '\t')
			{
				printf("Error: Invalid character in map.\n");
				free_map(game->map);
				free(game);
				exit (1);
			}
		}
	}
	double_character(grid, game);
	return (1);
}

t_map	*parse_cub_file(const char *file_name, t_game *game)
{
	int		map_start;
	
	init_map(game);
	game->map->liness = read_file(file_name, game);
	if (!game->map->liness)
		return (NULL);
	map_start = parse_textures_and_colors(game, game->map->liness);
	game->map->ceiling_color = init_colors(game->map->ceiling, game);
	game->map->floor_color = init_colors(game->map->floor, game);
	game->map->grid = &game->map->liness[map_start];
	if (!validate_map(game->map->grid, game))
	{
		printf("Error: Invalid map.\n");
		return (NULL);
	}
	validate_walls(game->map->grid, game);
	return (game->map);
}
