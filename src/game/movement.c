/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:28:26 by yyakuben          #+#    #+#             */
/*   Updated: 2025/03/04 16:32:35 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_player(t_game *game)
{
	if(game->player->lef_rotate)
		rotate_left(game);
	if(game->player->right_rotate)
		rotate_right(game);
	if(game->player->key_up)
		move_front(game);
	if(game->player->key_down)
		move_back(game);
	if(game->player->key_left)
		move_left(game);
	if(game->player->key_right)
		move_right(game);
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(-ROTATION_SPEED)
		- game->player->dir_y * sin(-ROTATION_SPEED);
	game->player->dir_y = old_dir_x * sin(-ROTATION_SPEED) + game->player->dir_y
		* cos(-ROTATION_SPEED);
	old_plane_x = game->player->plane_x;
	game->player->plane_x = game->player->plane_x * cos(-ROTATION_SPEED)
		- game->player->plane_y * sin(-ROTATION_SPEED);
	game->player->plane_y = old_plane_x * sin(-ROTATION_SPEED)
		+ game->player->plane_y * cos(-ROTATION_SPEED);
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(ROTATION_SPEED)
		- game->player->dir_y * sin(ROTATION_SPEED);
	game->player->dir_y = old_dir_x * sin(ROTATION_SPEED) + game->player->dir_y
		* cos(ROTATION_SPEED);
	old_plane_x = game->player->plane_x;
	game->player->plane_x = game->player->plane_x * cos(ROTATION_SPEED)
		- game->player->plane_y * sin(ROTATION_SPEED);
	game->player->plane_y = old_plane_x * sin(ROTATION_SPEED)
		+ game->player->plane_y * cos(ROTATION_SPEED);
}
