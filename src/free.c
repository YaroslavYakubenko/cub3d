/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:33:50 by yyakuben          #+#    #+#             */
/*   Updated: 2025/02/03 19:23:58 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_resources(t_map *map)
{
	if (map)
	{
		if (map->grid)
			free(map->grid);
		free(map);
	}
}

void	free_map(t_map *map, t_game *game)
{
	size_t	i;

	if (!map || !game)
		return ;
	printf("here_is_free_map\n");
	printf("is it %p?\n", map->north_texture);
	if (map->north_texture)
		free(map->north_texture);
	if (map->south_texture)
	{
		free(map->south_texture);
	}
	if (map->west_texture)
		free(map->west_texture);
	if (map->east_texture)
		free(map->east_texture);
	if (map->floor)
		free(map->floor);
	if (map->ceiling)
		free(map->ceiling);
	if (map->liness)
	{
		i = 0;
		while (map->liness[i])
			free(map->liness[i++]);
		free(map->liness);
	}
	free(map);
}

void	free_image(void *mlx, t_image *image)
{
	if (!image)
		return ;
	if (image->img)
	{
		mlx_destroy_image(mlx, image->img);
		image->img = NULL;
	}
	free(image);
}

void	free_all_textures(t_game *game)
{
	free_image(game->mlx, game->north_img);
	free_image(game->mlx, game->west_img);
	free_image(game->mlx, game->east_img);
	free_image(game->mlx, game->south_img);
}

void	free_game(t_game *game)
{
	// printf("1map->north_texture: %s\n", game->map->north_texture);
	if (!game)
		return ;
	// printf("game->mlx before: %p\n", &game->mlx);
	// if (game->mlx)
	// {
	// 	printf("here_is_free_game\n");
	// 	free_all_textures(game);
	// 	if (game->back)
	// 	{
	// 		free_image(game->mlx, game->back);
	// 		game->back = NULL;
	// 	}
	// 	if (game->win)
	// 	{
	// 		mlx_destroy_window(game->mlx,game->win);
	// 		game->win = NULL;
	// 	}
	// 	free(game->mlx);
	// }
	// printf("game->mlx  after: %p\n", &game->mlx);
	// free_map(game->map, game);
	// free(game);
}