/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:26:51 by yyakuben          #+#    #+#             */
/*   Updated: 2025/03/08 19:31:33 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void parse_texture(char **texture, char *line, t_game *game)
{
	if (!*texture)
		*texture = ft_strdup(line);
	else
		error_for_duplicate_texture(game);
}

void parse_color(char **color, char *line, t_game *game)
{
	if (!*color)
		*color = ft_strdup(line);
	else
		error_for_duplicate_texture(game);
}

int parse_line(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		parse_texture(&game->map->north_texture, line + 3, game);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		parse_texture(&game->map->south_texture, line + 3, game);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		parse_texture(&game->map->west_texture, line + 3, game);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		parse_texture(&game->map->east_texture, line + 3, game);
	else if (ft_strncmp(line, "F ", 2) == 0)
		parse_color(&game->map->floor, line + 2, game);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_color(&game->map->ceiling, line + 2, game);
	else if (line[0] == '\n' || line[0] == '\t' || line[0] == ' ')
		return (1);
	else
		error_for_invalid_line(game);
	return (0);
}
