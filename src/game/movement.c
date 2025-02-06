/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:28:26 by yyakuben          #+#    #+#             */
/*   Updated: 2025/02/06 19:59:12 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_game *game, float move_x, float move_y)
{
	t_player	*player;
	float	new_x;
	float	new_y;
	
	player = game->player;
	new_x = player->x + move_x;
	new_y = player->y + move_y;
	if (player->lef_rotate)
		player->angle -= ROTATION_SPEED;
	if (player->right_rotate)
		player->angle += ROTATION_SPEED;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;

	if(!touch(game, player->x, new_y))
	{
		player->y = new_y;
	}
	if(!touch(game, new_x, player->y))
	{
		player->x = new_x;	
	}
	
}

void	movement_player(t_game *game)
{
	t_player	*player;
	float		move_x;
	float		move_y;
	
	move_x = 0;
	move_y = 0;
	player = game->player;
	if (player->key_up)
	{
		move_x += cos(player->angle) * PLAYER_SPEED;
		move_y += sin(player->angle) * PLAYER_SPEED;
	}
	if (player->key_down)
	{
		move_x -= cos(player->angle) * PLAYER_SPEED;
		move_y -= sin(player->angle) * PLAYER_SPEED;
	}
	if (player->key_left)
	{
		move_x += sin(player->angle) * PLAYER_SPEED;
		move_y -= cos(player->angle) * PLAYER_SPEED;
	}
	if (player->key_right)
	{
		move_x -= sin(player->angle) * PLAYER_SPEED;
		move_y += cos(player->angle) * PLAYER_SPEED;
	}
	move_player(game, move_x, move_y);
}
