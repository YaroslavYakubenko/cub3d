/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:25:22 by yyakuben          #+#    #+#             */
/*   Updated: 2025/03/08 19:17:43 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_exit_for_parse_rgb(t_game *game, char *rgb)
{
	printf("Error: Wrong characters for floors or ceilings color.\n");
	free(rgb);
	free_map(game->map);
	free(game);
	exit (1);
}

void	error_for_duplicate_texture(t_game *game)
{
	printf("Error: Duplicate texture.\n");
	free_map(game->map);
	free(game);
	exit (1);
}

void	error_for_invalid_line(t_game *game)
{
	printf("Error: Invalid line in the map.\n");
	free_map(game->map);
	free(game);
	exit (1);
}

void	error_for_walls(t_game *game)
{
	printf("Error: problems with walls.\n");
	free_map(game->map);
	free(game);
	exit (1);
}