/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:35:13 by yyakuben          #+#    #+#             */
/*   Updated: 2024/12/25 22:04:16 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player)
{
	player->x = SCREEN_WIDTH / 2;
	printf("here_is_init_player\n");
	player->y = SCREEN_HEIGHT / 2;
	player->key_down = false;
	player->key_up = false;
	player->key_left = false;
	player->key_right = false;
}

// void	find_player(t_game *game)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	printf("here_is_find_player\n");
// 	printf("map_grid: %s\n", game->map->grid[i]);
// 	while (game->map->grid[i])
// 	{
// 		j = 0;
// 		while (game->map->grid[i][j])
// 		{
// 			if (ft_strchr("NSEW", game->map->grid[i][j]))
// 			{
// 				game->map->player.x = j + 0.5;
// 				game->map->player.y = i + 0.5;
// 				if (game->map->grid[i][j] == 'N')
// 					game->map->player.angle = M_PI / 2;
// 				else if (game->map->grid[i][j] == 'S')
// 					game->map->player.angle = 3 * M_PI / 2;
// 				else if (game->map->grid[i][j] == 'E')
// 					game->map->player.angle = 0;
// 				else if (game->map->grid[i][j] == 'W')
// 					game->map->player.angle = M_PI;
// 				game->map->grid[i][j] = '0';
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	init_player(&game->map->player);
// }

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
	int	speed;

	speed = 5;
	if (player->key_up)
		player->y -= speed;
	if (player->key_down)
		player->y += speed;
	if (player->key_left)
		player->x -= speed;
	if (player->key_right)
		player->x += speed;
}
