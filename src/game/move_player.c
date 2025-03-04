/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:32:37 by yyakuben          #+#    #+#             */
/*   Updated: 2025/03/03 21:47:20 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_front(t_game *game)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = game->player->x + game->player->dir_x * PLAYER_SPEED;
	new_pos_y = game->player->y + game->player->dir_y * PLAYER_SPEED;
	if (game->map->grid[(int)(new_pos_x + DISTANCE
			* game->player->dir_x)][(int)game->player->y] == '0')
		game->player->x = new_pos_x;
	if (game->map->grid[(int)game->player->x][(int)(new_pos_y + DISTANCE
		* game->player->dir_y)] == '0')
		game->player->y = new_pos_y;
}

void	move_back(t_game *game)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = game->player->x - game->player->dir_x * PLAYER_SPEED;
	new_pos_y = game->player->y - game->player->dir_y * PLAYER_SPEED;
	if (game->map->grid[(int)(new_pos_x - DISTANCE
			* game->player->dir_x)][(int)game->player->y] == '0')
		game->player->x = new_pos_x;
	if (game->map->grid[(int)game->player->x][(int)(new_pos_y - DISTANCE
		* game->player->dir_y)] == '0')
		game->player->y = new_pos_y;
}

void	move_left(t_game *game)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = game->player->x - game->player->plane_x * PLAYER_SPEED;
	new_pos_y = game->player->y - game->player->plane_y * PLAYER_SPEED;
	if (game->map->grid[(int)(new_pos_x - DISTANCE
			* game->player->plane_x)][(int)game->player->y] == '0')
		game->player->x = new_pos_x;
	if (game->map->grid[(int)game->player->x][(int)(new_pos_y - DISTANCE
		* game->player->plane_y)] == '0')
		game->player->y = new_pos_y;
}

void	move_right(t_game *game)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = game->player->x + game->player->plane_x * PLAYER_SPEED;
	new_pos_y = game->player->y + game->player->plane_y * PLAYER_SPEED;
	if (game->map->grid[(int)(new_pos_x + DISTANCE
			* game->player->plane_x)][(int)game->player->y] == '0')
		game->player->x = new_pos_x;
	if (game->map->grid[(int)game->player->x][(int)(new_pos_y + DISTANCE
		* game->player->plane_y)] == '0')
		game->player->y = new_pos_y;
}
