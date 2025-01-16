/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:35:13 by yyakuben          #+#    #+#             */
/*   Updated: 2025/01/15 21:55:47 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player)
{
	// printf("player->x: %f.2\n", player->x);
	player->x = SCREEN_WIDTH / 2;
	player->y = SCREEN_HEIGHT / 2;
	player->angle = M_PI / 2;
	player->key_down = false;
	player->key_up = false;
	player->key_left = false;
	player->key_right = false;
	player->lef_rotate = false;
	player->right_rotate = false;

}

int	key_press(int keycode, t_player *player)
{
	if (keycode == KEY_W)
		player->key_up = true;
	if (keycode == KEY_S)
		player->key_down = true;
	if (keycode == KEY_A)
		player->key_left = true;
	if (keycode ==  KEY_D)
		player->key_right = true;
	if (keycode == KEY_LEFT)
		player->lef_rotate = true;
	if (keycode == KEY_RIGHT)
		player->right_rotate = true;
	return (0);
}

int	key_realese(int keycode, t_player *player)
{
	// printf("Key realesed: %d\n", keycode);
	if (keycode == KEY_W)
		player->key_up = false;
	if (keycode == KEY_S)
		player->key_down = false;
	if (keycode == KEY_A)
		player->key_left = false;
	if (keycode ==  KEY_D)
		player->key_right = false;
	if (keycode == KEY_LEFT)
		player->lef_rotate = false;
	if (keycode == KEY_RIGHT)
		player->right_rotate = false;
	return (0);
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
	if (player->angle > 2 * M_PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * M_PI;
	if (!player)
	{
		printf("Error: player is NULL.\n");
		return;
	}
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
		player->x += cos_angle * PLAYER_SPEED;
		player->y -= sin_angle * PLAYER_SPEED;
	}
	if (player->key_right)
	{
		player->x -= cos_angle * PLAYER_SPEED;
		player->y += sin_angle * PLAYER_SPEED;
	}
}
