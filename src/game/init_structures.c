/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:41:26 by yyakuben          #+#    #+#             */
/*   Updated: 2025/03/07 20:48:06 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_game *game)
{
	game->north_img = NULL;
	game->south_img = NULL;
	game->west_img = NULL;
	game->east_img = NULL;
}
void	init_map(t_game *game)
{
	game->map = malloc(sizeof(t_map));
	game->map->north_texture = NULL;
	game->map->south_texture = NULL;
	game->map->west_texture = NULL;
	game->map->east_texture = NULL;
	game->map->ceiling = NULL;
	game->map->floor = NULL;
	game->map->floor_color = -1;
	game->map->ceiling_color = -1;
	game->map->grid = NULL;
	game->map->liness = NULL;
}

void	init_structures(t_game *game)
{
	init_textures(game);
	init_player(game->player);
	init_raycast(game);
	init_position_charactor(game);
	add_plane_characters(game);
}
