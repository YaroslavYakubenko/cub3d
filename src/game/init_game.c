/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:10:47 by yyakuben          #+#    #+#             */
/*   Updated: 2024/12/14 20:39:22 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_image(t_game *game)
{
	game->back->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->back->img)
	{
		// free(game->img);
		exit(1);
	}
	game->back->addr = mlx_get_data_addr(game->back->img, &game->back->bpp,
		&game->back->line_lenght, &game->back->endian);
	if (!game->back->addr)
		exit(1);
}

t_game	*init_game(t_map *map)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->map = map;
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
	load_all_textures(game);
	init_image(game);
	
	return (game);
}


int	game_loop(t_game *game)
{
	mlx_destroy_image(game->mlx, game->back->img);
	init_image(game);
	render_scene(game);
	return (0);
}

void	load_texture(t_game *game, char *path,
	t_image **texture, int size_texture)
{
	*texture = malloc(sizeof(t_image));
	(*texture)->img = mlx_xpm_file_to_image(game->mlx, path, &size_texture, &size_texture);
	if (!(*texture)->img)
	{
		ft_printf("Error: Failed to load texture.\n");
		exit(1);
	}
	(*texture)->addr = mlx_get_data_addr((*texture)->img, &(*texture)->bpp,
		&(*texture)->bpp, &(*texture)->endian);
	if (!(*texture)->addr)
	{
		ft_printf("Error: Failed to get image address.\n");
		exit(1);
	}
}

void	load_all_textures(t_game *game)
{
	load_texture(game, game->map->north_texture, &game->north_img, TEXTUREHEIGHT);
	load_texture(game, game->map->south_texture, &game->south_img,TEXTUREHEIGHT);
	load_texture(game, game->map->west_texture, &game->west_img, TEXTUREHEIGHT);
	load_texture(game, game->map->east_texture, &game->east_img,TEXTUREHEIGHT);
}

