/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:41:56 by yyakuben          #+#    #+#             */
/*   Updated: 2025/02/24 21:06:43 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;
	
	game = malloc(sizeof(t_game));
	if (!game)
		return (0);
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
	init_raycast(game);
	mlx_loop_hook(game->mlx, draw_loop, (void *)game);
	mlx_hook(game->win, KEY_PRESS, KEY_PRESS_MASK, key_press, (void *)game);
	mlx_hook(game->win, KEY_RELEASE, KEY_RELEASE_MASK, key_realese, (void *)game);
	mlx_hook(game->win, DESTROY, KEY_PRESS_MASK, exit_game, (void *)game);
	printf("here_is_main\n");
	mlx_loop(game->mlx);
	return (0);
}
