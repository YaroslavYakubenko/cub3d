/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:41:56 by yyakuben          #+#    #+#             */
/*   Updated: 2025/03/07 17:26:40 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_fuctions(t_game *game)
{
	mlx_hook(game->win, KEY_PRESS, (1L << 0), key_press, (void *)game);
	mlx_hook(game->win, KEY_RELEASE, (1L << 1),
		key_realese, (void *)game);
	mlx_loop_hook(game->mlx, render, (void *)game);
	mlx_hook(game->win, DESTROY, (1L << 0), exit_game, (void *)game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
	{
		free(game);
		return (1);
	}
	if (ac != 2)
	{
		printf("Error: Too many arguments.\n");
		free(game);
		return (1);
	}
	game->map = parse_cub_file(av[1], game);
	if (!game->map)
	{
		printf("Error: Failed to parse the *.cub file.\n");
		free(game->map);
		return (1);
	}
	init_game(game);
	mlx_fuctions(game);
	free(game);
	return (0);
}
