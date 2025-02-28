/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:35:13 by yyakuben          #+#    #+#             */
/*   Updated: 2025/02/27 16:41:41 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_direction(t_game *game, int x, int y)
{
	if (game->map->grid[y][x] == 'S')
	{
		game->player->dir_x = 1;
		game->player->plane_y = -0.66;
	}
	if (game->map->grid[y][x] == 'N')
	{
		game->player->dir_x = -1;
		game->player->plane_y = 0.66;
	}
	if (game->map->grid[y][x] == 'W')
	{
		game->player->dir_y = -1;
		game->player->plane_x = -0.66;
	}
	if (game->map->grid[y][x] == 'E')
	{
		game->player->dir_y = 1;
		game->player->plane_x = 0.66;
	}
}

void	player_angle(t_game *game, int x, int y)
{
	if (game->map->grid[y][x] == 'S')
		game->player->angle = PI / 2;
	if (game->map->grid[y][x] == 'N')
		game->player->angle = 3 * PI / 2;
	if (game->map->grid[y][x] == 'W')
		game->player->angle = PI;
	if (game->map->grid[y][x] == 'E')
		game->player->angle = 0;
}

void	position_player(t_player *player, t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (game->map->grid[y])
	{
		x = 0;
		while (game->map->grid[y][x])
		{
			if (game->map->grid[y][x] == 'N' || game->map->grid[y][x] == 'E'
				|| game->map->grid[y][x] == 'S' || game->map->grid[y][x] == 'W')
			{
				if (DEBUG)
				{					
					player->x = (double)x * BLOCK;
					player->y = (double)y * BLOCK;
				}
				else
				{
					player->x = (double)y + 0.5;
					player->y = (double)x + 0.5;
				}
				player_angle(game, x, y);
				player_direction(game, x, y);
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
	player->key_down = false;
	player->key_up = false;
	player->key_left = false;
	player->key_right = false;
	player->lef_rotate = false;
	player->right_rotate = false;

}
