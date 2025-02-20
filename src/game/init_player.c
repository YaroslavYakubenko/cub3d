/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:35:13 by yyakuben          #+#    #+#             */
/*   Updated: 2025/02/20 18:30:06 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_direction(t_game *game, int x, int y)
{
	// printf("10 grid: %s\n", game->map->grid[0]);
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
	// printf("10 grid: %s\n", game->map->grid[0]);
	// printf("plane_x: %f\nplane_y: %f\ndir-x: %f\ndir_y: %f\n", game->player->plane_x, game->player->plane_y, game->player->dir_x, game->player->dir_x);
}

// void	player_direction(t_game *game)
// {
// 	game->player->dir_x = 0;
// 	game->player->dir_y = 1;
// 	game->player->plane_x = 0.66;
// 	game->player->plane_y = 0;
// 	// printf("plane_x: %f\nplane_y: %f\ndir-x: %f\ndir_y: %f\n", game->player->plane_x,
// 	// 		game->player->plane_y, game->player->dir_x, game->player->dir_x);
// }

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

// void	position_player(t_game *game)
// {
// 	int			x;
// 	int			y;
	
// 	y = 0;
// 	while (game->map->grid[y])
// 	{
// 		x = 0;
// 		while (game->map->grid[y][x])
// 		{
// 			if (game->map->grid[y][x] == 'N' || game->map->grid[y][x] == 'E'
// 				|| game->map->grid[y][x] == 'S' || game->map->grid[y][x] == 'W'
// 				|| game->map->grid[y][x] == 'P')
// 			{
// 				game->map->grid[y][x] = '0';
// 				game->player->x = ((double)x + 0.5);
// 				game->player->y = ((double)y + 0.5);
// 				printf("1 grid: %s\n", game->map->grid[0]);
// 				player_angle(game, x, y);
// 				printf("2 grid: %s\n", game->map->grid[0]);
// 				player_direction(game);
// 				printf("3 grid: %s\n", game->map->grid[0]);
// 				return ;
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

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

// void	init_player(t_game *game)
// {
// 	game->player->plane_x = 0;
// 	game->player->plane_y = 0;
// 	game->player->dir_x = 0;
// 	game->player->dir_y = 0;
// 	position_player(game);
// 	game->player->key_down = false;
// 	game->player->key_up = false;
// 	game->player->key_left = false;
// 	game->player->key_right = false;
// 	game->player->lef_rotate = false;
// 	game->player->right_rotate = false;
// }
	