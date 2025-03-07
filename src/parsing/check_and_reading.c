/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_reading.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:06:22 by yyakuben          #+#    #+#             */
/*   Updated: 2025/03/06 21:51:33 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file(const char *file_name)
{
	const char	*dot;

	dot = ft_strrchr(file_name, '.');
	return (dot && ft_strcmp(dot, ".cub") == 0);
}

size_t	count_lines(const char *file_name)
{
	int		fd;
	char	*line;
	size_t	count;

	count = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

size_t	validate_and_count_lines(const char *file_name, t_game *game)
{
	size_t	line_count;

	if (!check_file(file_name))
	{
		ft_printf("Error: invalid file extension.\n");
		free(game->map);
		free(game);
		exit (1);
	}
	line_count = count_lines(file_name);
	if (line_count == 0)
	{
		ft_printf("Error: Invalid or empty file.\n");
		free(game->map);
		free(game);
		exit (1);
	}
	return (line_count);
}

char	**read_file(const char *file_name, t_game *game)
{
	int		fd;
	char	*line;
	char	**lines;
	size_t	i;
	size_t	line_count;

	line = NULL;
	lines = NULL;
	i = 0;
	line_count = validate_and_count_lines(file_name, game);
	fd = open(file_name, O_RDONLY);
	if (fd < 0 || line_count == 0)
		return (printf("Error opening file.\n"), NULL);
	lines = malloc(sizeof(char *) * (line_count + 1));
	if (!lines)
		return (close(fd), printf("Error allocation memory.\n"), NULL);
	line = get_next_line(fd);
	while (line)
	{
		lines[i++] = line;
		line = get_next_line(fd);
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}
