/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:41:56 by yyakuben          #+#    #+#             */
/*   Updated: 2025/02/05 20:26:09 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game = malloc(sizeof(t_game));

	if (ac != 2)
	{
		printf("Error: Too many arguments.\n");
		return (1);
	}
	game->map = parse_cub_file(av[1]);
	if (!game->map)
	{
		printf("Error: Failed to parse the *.cub file.\n");
		return (1);
	}
	init_game(game);
	mlx_loop_hook(game->mlx, draw_loop, (void *)game);
	mlx_hook(game->win, KEY_PRESS, KEY_PRESS_MASK, key_press, (void *)game);
	mlx_hook(game->win, KEY_RELEASE, KEY_RELEASE_MASK, key_realese, (void *)game);
	// printf("2map->north_texture: %s\n", game->map->north_texture);
	mlx_hook(game->win, DESTROY, KEY_PRESS_MASK, exit_game, (void *)game);
	printf("here_is_main\n");
	// printf("4map->north_texture: %s\n", game->map->north_texture);

	// if (game->mlx)
	mlx_loop(game->mlx);
	// printf("here we are in the main loop\n");
	// if (game.back)
		// mlx_destroy_image(game->mlx, game->back);
	// if (game.win)
		// mlx_destroy_window(game->mlx, game->win);
	// if (game.mlx)
	// {
		// mlx_destroy_display(game->mlx);
		// free(game->mlx);
	// }
	// free_map(game->map, game);
	// free(&game);
	return (0);
}
