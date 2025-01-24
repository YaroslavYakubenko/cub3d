/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:35:13 by yyakuben          #+#    #+#             */
/*   Updated: 2025/01/24 18:40:50 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	position_player(t_player *player, t_game *game)
{
	int		x;
	int		y;

	// game = NULL;
	// if (!game)
	// 	printf("Error: Invalid game.\n");
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
				player->x = (float)x;
				player->y = (float)y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_player(t_player *player, t_game *game)
{
	player->x = SCREEN_WIDTH / 2;
	player->y = SCREEN_HEIGHT / 2;
	position_player(player, game);
	printf("player->x: %f\nplayer->y: %f\n", player->x, player->y);
	player->angle = PI / 2;
	player->key_down = false;
	player->key_up = false;
	player->key_left = false;
	player->key_right = false;
	player->lef_rotate = false;
	player->right_rotate = false;

}
