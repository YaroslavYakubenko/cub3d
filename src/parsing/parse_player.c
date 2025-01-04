/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:35:13 by yyakuben          #+#    #+#             */
/*   Updated: 2025/01/04 19:32:53 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player)
{
	printf("player->x: %f.2\n", player->x);
	player->x = SCREEN_WIDTH / 2;
	player->y = SCREEN_HEIGHT / 2;
	player->key_down = false;
	player->key_up = false;
	player->key_left = false;
	player->key_right = false;

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
	return (0);
}

int	key_realese(int keycode, t_player *player)
{
	printf("Key realesed: %d\n", keycode);
	if (keycode == KEY_W)
		player->key_up = false;
	if (keycode == KEY_S)
		player->key_down = false;
	if (keycode == KEY_A)
		player->key_left = false;
	if (keycode ==  KEY_D)
		player->key_right = false;
	return (0);
}

void	move_player(t_player *player)
{
	if (!player)
	{
		printf("Error: player is NULL.\n");
		return;
	}
	if (player->key_up)
		player->y -= PLAYER_SPEED;
	if (player->key_down)
		player->y += PLAYER_SPEED;
	if (player->key_left)
		player->x -= PLAYER_SPEED;
	if (player->key_right)
		player->x += PLAYER_SPEED;
}
