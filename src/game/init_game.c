/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:10:47 by yyakuben          #+#    #+#             */
/*   Updated: 2024/12/01 18:02:25 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*init_game(t_map *map)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		free(game);
		return (NULL);
	}
	game->win = mlx_new_window(game->mlx, 800, 600, "Cub3D");
	if (!game->win)
	{
		free(game);
		return (NULL);
	}
	game->map = map;
	return (game);
}

void	mlx_rectangle(void *mlx, void *win, int x0, int y0, int x1, int y1, int color)
{
	int	x;
	int	y;

	y = y0;
	while (y < y1)
	{
		x = x0;
		while (x < x1)
		{
			mlx_pixel_put(mlx, win, x, y, color);
			x++;
		}
		y++;
	}
}

void	render_map(t_game *game)
{
	int	x;
	int	y;
	int	block_size;

	block_size = 20;
	for (y = 0; game->map->grid[y]; y++)
	{
		for (x = 0; game->map->grid[y][x]; x++)
		{
			if (game->map->grid[y][x] == '1')
				mlx_rectangle(game->mlx, game->win, x * block_size, y * block_size,
					(x + 1) * block_size, (y + 1) * block_size, 0xFFFFFF);
			else
				mlx_rectangle(game->mlx, game->win, x * block_size, y * block_size,
					(x + 1) * block_size, (y + 1) * block_size, 0x000000);
		}
	}
}

void	render_player(t_game *game)
{
	int	player_size;

	player_size = 5;
	mlx_rectangle(game->mlx, game->win, game->map->player.x * 20 - player_size,
		game->map->player.y * 20 - player_size,
		game->map->player.x * 20 + player_size,
		game->map->player.y * 20 + player_size, 0xFF0000);
}

void	render_scene(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	render_map(game);
	render_player(game);
}
