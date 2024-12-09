/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:10:47 by yyakuben          #+#    #+#             */
/*   Updated: 2024/12/08 21:38:45 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_image(t_game *game)
{
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img)
	{
		// free(game->img);
		exit(1);
	}
	game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->line_len, &game->endian);
}

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
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!game->win)
	{
		free(game);
		return (NULL);
	}
	game->map = map;
	return (game);
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	pixel = game->addr + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	render_scene(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			if (x % 2 == 0 && y % 2 == 0)
				put_pixel(game, x, y, 0xFF0000);
			else
				put_pixel(game, x, y, 0x000000);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int	game_loop(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img);
	init_image(game);
	render_scene(game);
	return (0);
}

void	load_texture(t_game *game, char *path,
	void **texture, int size_texture)
{
	printf("game: %p\npath: %s\nt*texture: %s\nsize_texture: %d\n", game, path, *texture, size_texture);
	ft_printf("Loading texture: %s\n", path);
	*texture = mlx_xpm_file_to_image(game->mlx, path, &size_texture, &size_texture);
	if (!*texture)
	{
		ft_printf("Error: Failed to load texture\n");
		exit(1);
	}
}

void	load_all_textures(t_game *game)
{
	load_texture(game, game->map->north_texture, &game->map->north_img, TEXTUREHEIGHT);
	ft_printf("North texture: %dx%d\n", TEXTUREHEIGHT);
	load_texture(game, game->map->south_texture, &game->map->south_img,TEXTUREHEIGHT);
	ft_printf("South texture: %dx%d\n", TEXTUREHEIGHT);
	load_texture(game, game->map->west_texture, &game->map->west_img, TEXTUREHEIGHT);
	ft_printf("West texture: %dx%d\n", TEXTUREHEIGHT);
	load_texture(game, game->map->east_texture, &game->map->east_img,TEXTUREHEIGHT);
	ft_printf("East texture: %dx%d\n", TEXTUREHEIGHT);
}

// void	mlx_rectangle(void *mlx, void *win, int x0, int y0, int x1, int y1, int color)
// {
// 	int	x;
// 	int	y;

// 	y = y0;
// 	while (y < y1)
// 	{
// 		x = x0;
// 		while (x < x1)
// 		{
// 			mlx_pixel_put(mlx, win, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void	render_map(t_game *game)
// {
// 	int	x;
// 	int	y;
// 	int	block_size;

// 	block_size = 20;
// 	for (y = 0; game->map->grid[y]; y++)
// 	{
// 		for (x = 0; game->map->grid[y][x]; x++)
// 		{
// 			if (game->map->grid[y][x] == '1')
// 				mlx_rectangle(game->mlx, game->win, x * block_size, y * block_size,
// 					(x + 1) * block_size, (y + 1) * block_size, 0xFFFFFF);
// 			else
// 				mlx_rectangle(game->mlx, game->win, x * block_size, y * block_size,
// 					(x + 1) * block_size, (y + 1) * block_size, 0x000000);
// 		}
// 	}
// }

// void	render_player(t_game *game)
// {
// 	int	player_size;

// 	player_size = 5;
// 	mlx_rectangle(game->mlx, game->win, game->map->player.x * 20 - player_size,
// 		game->map->player.y * 20 - player_size,
// 		game->map->player.x * 20 + player_size,
// 		game->map->player.y * 20 + player_size, 0xFF0000);
// }

// void	render_scene(t_game *game)
// {
// 	mlx_clear_window(game->mlx, game->win);
// 	render_map(game);
// 	render_player(game);
// }
