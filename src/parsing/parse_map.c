/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:47:46 by yyakuben          #+#    #+#             */
/*   Updated: 2025/03/07 21:49:45 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_first_syms(char *line)
{
	int res;

	res = 0;
	if (ft_strncmp(line, "NO ", 3) == 0)
		res = 1;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		res = 1;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		res = 1;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		res = 1;
	else if (ft_strncmp(line, "F ", 2) == 0)
		res = 1;
	else if (ft_strncmp(line, "C ", 2) == 0)
		res = 1;
	else if (line[0] == '\n'
		|| line[0] == '\t' || line[0] == ' ')
		res = 1;
	return (res);
}

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
			{
				printf("Error: Duplicate texture.\n");
				free_map(game->map);
				free(game);
				exit (1);
			}
			i++;
			continue;
		}
		else if (ft_strncmp(lines[i], "SO ", 3) == 0)
		{
			if(!game->map->south_texture)
				game->map->south_texture = ft_strdup(lines[i] + 3);
			else
			{
				printf("Error: Duplicate texture.\n");
				free_map(game->map);
				free(game);
				exit (1);
			}
			i++;
			continue;
		}
		else if (ft_strncmp(lines[i], "WE ", 3) == 0)
		{
			if(!game->map->west_texture)
				game->map->west_texture = ft_strdup(lines[i] + 3);
			else
			{
				printf("Error: Duplicate texture.\n");
				free_map(game->map);
				free(game);
				exit (1);
			}
			i++;
			continue;
		}
		else if (ft_strncmp(lines[i], "EA ", 3) == 0)
		{
			if(!game->map->east_texture)
				game->map->east_texture = ft_strdup(lines[i] + 3);
			else
			{
				printf("Error: Duplicate texture.\n");
				free_map(game->map);
				free(game);
				exit (1);
			}
			i++;
			continue;
		}
		else if (ft_strncmp(lines[i], "F ", 2) == 0)
		{
			if(!game->map->floor)
				game->map->floor = ft_strdup(lines[i] + 2);
			else
			{
				printf("Error: Duplicate texture.\n");
				free_map(game->map);
				free(game);
				exit (1);
			}
			i++;
			continue;
		}
		else if (ft_strncmp(lines[i], "C ", 2) == 0)
		{
			if(!game->map->ceiling)
				game->map->ceiling = ft_strdup(lines[i] + 2);
			else
			{
				printf("Error: Duplicate texture.\n");
				free_map(game->map);
				free(game);
				exit (1);
			}
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
				// i++;
				continue ;
			}
		else if(game->map->north_texture && game->map->south_texture && game->map->west_texture
			&& game->map->east_texture && game->map->floor && game->map->ceiling)
			break ;
		else
		{
			printf("Error: Invalid line in the map.\n");
			free_map(game->map);
			free(game);
			exit (1);
		}
	}
	printf("iiq = %d\n", i);
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
		if ((rgb[i]) && (rgb[i] < '0' || rgb[i] > '9')
			&& rgb[i] != ',' && rgb[i] != '\n')
		{
			printf("Error: wrong characters for floors or ceilings color.\n");
			free(str);
			free_map(game->map);
			free(game);
			exit (1);
		}
		if (rgb[i] && (rgb[i] == ',' || (rgb[i] >= '0' && rgb[i] <= '9')))
			str[j++] = rgb[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

void	free_rgb(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
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
			free_map(game->map);
			free_rgb(rgb);
			free(color_string);
			free(game);
			exit (1);
		}
	}
	free_rgb(rgb);
	free(color_string);
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
	int		i;
	
	i = 0;
	init_map(game);
	// game->map = malloc(sizeof(t_map));
	game->map->liness = read_file(file_name, game);
	if (!game->map->liness)
		return (NULL);
	// game->map->north_texture = NULL;
	// game->map->south_texture = NULL;
	// game->map->west_texture = NULL;
	// game->map->east_texture = NULL;
	// game->map->ceiling = NULL;
	// game->map->floor = NULL;
	// game->map->floor_color = -1;
	// game->map->ceiling_color = -1;
	// game->map->grid = NULL;
	map_start = parse_textures_and_colors(game, game->map->liness);
	game->map->ceiling_color = init_colors(game->map->ceiling, game);
	game->map->floor_color = init_colors(game->map->floor, game);
	game->map->grid = &game->map->liness[map_start];
	while(game->map->grid[i])
	{
		// printf("game->map->grid[%d]: %s", i, game->map->grid[i]);
		i++;
	}
	if (!validate_map(game->map->grid, game))
	{
		printf("Error: Invalid map.\n");
		return (NULL);
	}
	validate_walls(game->map->grid, game);
	return (game->map);
}
