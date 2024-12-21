/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:41:56 by yyakuben          #+#    #+#             */
/*   Updated: 2024/12/21 21:40:55 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_map	*map;
	t_game	*game;

	if (ac != 2)
	{
		ft_printf("Error: Too many arguments.\n");
		return (1);
	}
	map = parse_cub_file(av[1]);
	if (!map)
	{
		ft_printf("Error: Failed to parse the *.cub file.\n");
		return (1);
	}
	game = init_game(map);
	printf("here\n");
	if (!game)
	{
		ft_printf("Error: Failed to initialize the game.\n");
		free_resources(map);
		return (1);
	}
	// init_image(game);
	// load_all_textures(game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_hook(game->win, KEY_PRESS, KEY_PRESS_MASK, handle_input, game);
	// printf("here\n");
	// mlx_key_hook(game->win, handle_input, game);
	// render_scene(game);
	printf("here1\n");
	mlx_loop(game->mlx);
	printf("here2\n");
	free_resources(map);
	return (0);
}
