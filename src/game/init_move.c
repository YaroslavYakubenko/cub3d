/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:30:47 by yyakuben          #+#    #+#             */
/*   Updated: 2024/12/01 19:03:35 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_map *map)
{
	float	new_x;
	float	new_y;

	new_x = map->player.x + cos(map->player.angle) * PLAYER_SPEED;
	new_y = map->player.y - sin(map->player.angle) * PLAYER_SPEED;
	if (map->grid[(int)new_y][(int)new_x] != '1')
	{
		map->player.x = new_x;
		map->player.y = new_y;
	}
}

void	move_backward(t_map *map)
{
	float	new_x;
	float	new_y;

	new_x = map->player.x - cos(map->player.angle) * PLAYER_SPEED;
	new_y = map->player.y + sin(map->player.angle) * PLAYER_SPEED;
	if (map->grid[(int)new_y][(int)new_x] != '1')
	{
		map->player.x = new_x;
		map->player.y = new_y;
	}
}

void	turn_left(t_map *map)
{
	map->player.angle += ROTATION_SPEED;
	if (map->player.angle > 2 * 3.14)
		map->player.angle -= 2 * 3.14;
}

void turn_right(t_map *map)
{
	map->player.angle -= ROTATION_SPEED;
	if (map->player.angle < 0)
		map->player.angle += 2 * 3.14;
}

void	print_player_position(t_map *map)
{
	printf("player position: (%.2f, %.2f), angle: %.2f radians\n",
		map->player.x, map->player.y, map->player.angle);
}

void	move_player(t_player *player, char **grid, int keycode)
{
	double	new_x;
	double	new_y;

	new_x = 0.0;
	new_y = 0.0;
	if (keycode == KEY_A)
	{
		new_x = player->x + cos(player->angle) * PLAYER_SPEED;
		new_y = player->y + sin(player->angle) * PLAYER_SPEED;
	}
	else if (keycode == KEY_S)
	{
		new_x = player->x - cos(player->angle) * PLAYER_SPEED;
		new_y = player->y - sin(player->angle) * PLAYER_SPEED;
	}
	else if (keycode == KEY_A)
		player->angle += ROTATION_SPEED;
	else if (keycode == KEY_D)
		player->angle -= ROTATION_SPEED;
	else
	{
		new_x = player->x;
		new_y = player->y;
	}
	if (grid[(int)new_y][(int)new_x] != '1')
	{
		player->x = new_x;
		player->y = new_y;
	}
}

int	handle_input(int keycode, t_game *game)
{	
	// printf("here\n");
	if (keycode == KEY_ESC)
	{
		ft_printf("Exiting the program...\n");
		free_resources(game->map);
		mlx_destroy_window(game->mlx, game->win);
		free(game);
		exit(0);
	}
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A || keycode == KEY_D)
		move_player(&game->map->player, game->map->grid, keycode);
	render_scene(game);
	return (0);
}

