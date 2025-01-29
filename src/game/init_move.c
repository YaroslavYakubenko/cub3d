/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:30:47 by yyakuben          #+#    #+#             */
/*   Updated: 2025/01/29 22:36:43 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < SCREEN_WIDTH)
	{
		x = 0;
		while (x < SCREEN_HEIGHT)
		{
			put_pixel(game, y, x, 0);
			x++;
		}
		y++;
	}
	// printf("%s", game->map->north_texture);
}

int	key_press(int keycode, t_player *player, t_game *game)
{
	if (keycode == KEY_ESC)
		exit_game(game);
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
