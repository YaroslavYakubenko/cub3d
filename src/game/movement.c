/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:28:26 by yyakuben          #+#    #+#             */
/*   Updated: 2025/01/23 18:14:18 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	movement_player(t_player *player)
{
	float	cos_angle;
	float	sin_angle;
	
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->key_up)
	{
		player->x += cos_angle * PLAYER_SPEED;
		player->y += sin_angle * PLAYER_SPEED;
	}
	if (player->key_down)
	{
		player->x -= cos_angle * PLAYER_SPEED;
		player->y -= sin_angle * PLAYER_SPEED;
	}
	if (player->key_left)
	{
		player->x += sin_angle * PLAYER_SPEED;
		player->y -= cos_angle * PLAYER_SPEED;
	}
	if (player->key_right)
	{
		player->x -= sin_angle * PLAYER_SPEED;
		player->y += cos_angle * PLAYER_SPEED;
	}
}

void	move_player(t_player *player)
{
	float	cos_angle;
	float	sin_angle;
	
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->lef_rotate)
		player->angle -= ROTATION_SPEED;
	if (player->right_rotate)
		player->angle += ROTATION_SPEED;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	movement_player(player);
}
