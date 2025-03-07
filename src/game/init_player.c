/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:35:13 by yyakuben          #+#    #+#             */
/*   Updated: 2025/03/07 20:43:14 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player)
{
	player->x = SCREEN_WIDTH / 2;
	player->y = SCREEN_HEIGHT / 2;
	player->angle = PI / 2;
	player->key_down = false;
	player->key_up = false;
	player->key_left = false;
	player->key_right = false;
	player->lef_rotate = false;
	player->right_rotate = false;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
}

bool	valid_symbol_character(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	init_position_charactor(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map->grid[i])
	{
		j = 0;
		while (game->map->grid[i][j])
		{
			if (valid_symbol_character(game->map->grid[i][j]))
			{
				game->player->direction = game->map->grid[i][j];
				game->map->grid[i][j] = '0';
				game->player->x = i + 0.5;
				game->player->y = j + 0.5;
			}
			j++;
		}
		i++;
	}
}

void	add_plane_characters(t_game *game)
{
	char	plane;

	plane = game->player->direction;
	if (plane == 'S')
	{
		game->player->dir_x = 1;
		game->player->plane_y = -0.66;
	}
	else if (plane == 'N')
	{
		game->player->dir_x = -1;
		game->player->plane_y = 0.66;
	}
	else if (plane == 'E')
	{
		game->player->dir_y = 1;
		game->player->plane_x = 0.66;
	}
	else if (plane == 'W')
	{
		game->player->dir_y = -1;
		game->player->plane_x = -0.66;
	}
}
