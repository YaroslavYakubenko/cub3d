/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:30:47 by yyakuben          #+#    #+#             */
/*   Updated: 2025/03/03 21:19:53 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_image(t_game *game)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (y < SCREEN_WIDTH)
	{
		x = 0;
		while (x < SCREEN_HEIGHT)
		{
			color = 0;
			my_mlx_pixel_put_v2(game->back, y, x, 0);
			x++;
		}
		y++;
	}
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit_game(game);
	if (keycode == KEY_W)
		game->player->key_up = true;
	if (keycode == KEY_S)
		game->player->key_down = true;
	if (keycode == KEY_A)
		game->player->key_left = true;
	if (keycode ==  KEY_D)
		game->player->key_right = true;
	if (keycode == KEY_LEFT)
		game->player->lef_rotate = true;
	if (keycode == KEY_RIGHT)
		game->player->right_rotate = true;
	return (0);
}

int	key_realese(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player->key_up = false;
	if (keycode == KEY_S)
		game->player->key_down = false;
	if (keycode == KEY_A)
		game->player->key_left = false;
	if (keycode ==  KEY_D)
		game->player->key_right = false;
	if (keycode == KEY_LEFT)
		game->player->lef_rotate = false;
	if (keycode == KEY_RIGHT)
		game->player->right_rotate = false;
	return (0);
}
