/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:35:13 by yyakuben          #+#    #+#             */
/*   Updated: 2025/01/28 20:24:32 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	position_player(t_player *player, t_game *game)
{
	int		x;
	int		y;

	// game->player = malloc(sizeof(t_player));
	// if (!player)
	// 	exit(1);
	y = 0;
	while (game->map->grid[y])
	{
		x = 0;
		while (game->map->grid[y][x])
		{
			if (game->map->grid[y][x] == 'N' || game->map->grid[y][x] == 'E'
				|| game->map->grid[y][x] == 'S' || game->map->grid[y][x] == 'W'
				|| game->map->grid[y][x] == 'P')
			{
				player->x = (float)x * BLOCK;
				player->y = (float)y * BLOCK;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_player(t_player *player, t_game *game)
{
	position_player(player, game);
	// printf("player->x: %f\nplayer->y: %f\n", player->x, player->y);
	player->angle = PI / 2;
	player->key_down = false;
	player->key_up = false;
	player->key_left = false;
	player->key_right = false;
	player->lef_rotate = false;
	player->right_rotate = false;

}
