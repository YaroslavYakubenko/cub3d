/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:10:47 by yyakuben          #+#    #+#             */
/*   Updated: 2025/03/04 16:12:25 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	game->back = malloc(sizeof(t_image));
	game->player = malloc(sizeof(t_player));
	if (!game->back || !game->player)
	{
		printf("Error: Failed to allocate memory.\n");
		free(game->player);
		free(game->back);
		return ;
	}
	init_player(game->player);
	init_position_charactor(game);
	add_plane_characters(game);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	game->back->img = mlx_new_image(game->mlx,SCREEN_WIDTH, SCREEN_HEIGHT);
	game->back->addr = mlx_get_data_addr(game->back->img, &game->back->bpp,
		&game->back->line_lenght, &game->back->endian);
		if (!game->mlx || !game->win || !game->back->img || !game->back->addr)
		{
			printf("Error: Initialization failed.\n");
			exit(1);
		}
	load_all_textures(game);
	mlx_put_image_to_window(game->mlx, game->win, game->back->img, 0, 0);
}

int	exit_game(t_game *game)
{
	if (game->back)
	{
		if (game->back)
		{
			mlx_destroy_image(game->mlx, game->back->img);
			free(game->back);
			free(game->player);
		}
	}
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_map(game->map, game);
	free(game);
	exit(0);
	return (0);
}

void	load_texture(t_game *game, char *path,
	t_image **texture, int size_texture)
{
	int	size;
	
	size = size_texture;
	*texture = malloc(sizeof(t_image));
	if (!(*texture))
	{
		printf("Error: Failed to allocate memory for texture.");
		free(texture);
		exit (1);
	}
	(*texture)->img = mlx_xpm_file_to_image(game->mlx, path, &size, &size);
	if (!(*texture)->img)
	{
		printf("Error: Failed to load texture.\n");
		free((*texture)->img);
		exit(1);
	}
	(*texture)->addr = mlx_get_data_addr((*texture)->img, &(*texture)->bpp,
		&(*texture)->line_lenght, &(*texture)->endian);
	if (!(*texture)->addr)
	{
		printf("Error: Failed to get image address.\n");
		free((*texture)->addr);
		exit(1);
	}
}

void	rm_newline(char *str)
{
	int	len;

	if (!str)
		return ;
	len = 0;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
	
}

void	load_all_textures(t_game *game)
{
	rm_newline(game->map->north_texture);
	rm_newline(game->map->south_texture);
	rm_newline(game->map->west_texture);
	rm_newline(game->map->east_texture);
	load_texture(game, game->map->north_texture, &game->north_img, TEXTUREHEIGHT);
	load_texture(game, game->map->south_texture, &game->south_img,TEXTUREHEIGHT);
	load_texture(game, game->map->west_texture, &game->west_img, TEXTUREHEIGHT);
	load_texture(game, game->map->east_texture, &game->east_img,TEXTUREHEIGHT);
}
