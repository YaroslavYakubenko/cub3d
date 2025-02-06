/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:35:13 by yyakuben          #+#    #+#             */
/*   Updated: 2025/02/06 19:44:35 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void player_angle(t_game *game, int x, int y)
{
	if (game->map->grid[y][x] == 'N')
		game->player->angle = PI / 2;
	if (game->map->grid[y][x] == 'S')
		game->player->angle = 3 * PI / 2;
	if (game->map->grid[y][x] == 'W')
		game->player->angle = PI;
	if (game->map->grid[y][x] == 'E')
		game->player->angle = 0;
	if (game->map->grid[y][x] == 'P')
		game->player->angle = PI / 2;
}

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
				player_angle(game, x, y);
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
	// player->angle = PI / 2;
	// player->angle = PI;
	player->key_down = false;
	player->key_up = false;
	player->key_left = false;
	player->key_right = false;
	player->lef_rotate = false;
	player->right_rotate = false;

}
