/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:41:56 by yyakuben          #+#    #+#             */
/*   Updated: 2024/12/29 18:43:04 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_game *game, float x, float y, int color)
{
	int	i;
	if (!game || !game->back || !game->back->addr)
	{
		printf("Error: game, back or addr is NULL.\n");
		return;
	}
	// printf("x = %f\ny = %f\n", x, y);
	if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT || x < 0 || y < 0)
	{
		// printf("Error: coordinates out of bounds: x=%d, y=%d\n", x, y);
		return;
	}
	i = y * game->back->line_lenght + x * game->back->bpp / 8;
	// printf("Error: coordinates out of bounds: x=%d, y=%d\n", x, y);
	game->back->addr[i] = color & 0xFF;
	// printf("here\n");
	game->back->addr[i + 1] = (color >> 8) & 0xFF;
	game->back->addr[i + 2] = (color >> 16) & 0xFF;
}

void	draw_square(t_game *game, float x, float y, int size, int color)
{
	float	i;

	i = 0;
	printf("x = %f\ny = %f\n", x, y);
	while (i++ < size)
		put_pixel(game, x + i, y, color);
	i = 0;
	while (i++ < size)
		put_pixel(game, x, y + i, color);
	i = 0;
	while (i++ < size)
		put_pixel(game, x + size, y + i, color);
	i = 0;
	while (i++ < size)
		put_pixel(game, x + i, y + size, color);
}

void	init_game(t_game *game)
{
	// game = NULL;
	game->back = malloc(sizeof(t_image));
	// game->player = NULL;
	game->player = malloc(sizeof(t_player));
	// player = ft_calloc(sizeof(t_player), player);

	if (!game->player)
	{
		printf("Error: Failed to allocate memory.\n");
		return ;
	}
	// game->mlx = NULL;
	// game->back->img = NULL;
	init_player(game->player);
	if(game->player == NULL)
		printf("here NULL ->dksmj\n");
	// printf("player->x: %f\n", game->player->x);
	// printf("player->y: %f\n", game->player->y);
	// printf("here_init_game\n");
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	game->back->img = mlx_new_image(game->mlx,SCREEN_WIDTH, SCREEN_HEIGHT);
	game->back->addr = mlx_get_data_addr(game->back->img, &game->back->bpp, &game->back->line_lenght, &game->back->endian);
	// printf("line_lenght: %d, bpp: %d\n", game->back->line_lenght, game->back->bpp);
	if (!game->mlx || !game->win || !game->back->img || !game->back->addr)
	{
    	printf("Error: Initialization failed.\n");
    	exit(1);
	}
	printf("mlx: %p, win: %p, img: %p\n", game->mlx, game->win, game->back->img);

	mlx_put_image_to_window(game->mlx, game->win, game->back->img, 0, 0);
}

int	draw_loop(t_game *game)
{
	// t_player	*player;

	// player = game->player;
	
	// move_player(player);
	// // printf("Draw loop executed\n");
	// draw_square(game, player->x, player->y, 10, 0x00FF00);
	// mlx_put_image_to_window(game->mlx, game->win, game->back->img, 0, 0);
	// return (0);


	// printf("player.x: %f\n", game->player->x);
	// printf("player.y: %f\n", game->player->y);
	// printf("Draw loop executed\n");
	
	draw_square(game, game->player->x, game->player->y, 10, 0x00FF00);
	// printf("player->x = %f\nplayer->y = %f\n", game->player->x, game->player->y);
	move_player(game->player);
	mlx_put_image_to_window(game->mlx, game->win, game->back->img, 0, 0);
	return (0);
}

// int	exit_game(t_game *game)
// {
// 	free_game(game);
// 	exit(0);
// 	return (0);
// }

int	main(int ac, char **av)
{
	t_map	*map;
	t_game	game;

	// (void)av;
	// game = NULL;
	if (ac != 2)
	{
		printf("Error: Too many arguments.\n");
		return (1);
	}
	map = parse_cub_file(av[1]);
	if (!map)
	{
		printf("Error: Failed to parse the *.cub file.\n");
		return (1);
	}
	init_game(&game);
	// printf("player.x: %f\n", game.player->x);
	// printf("player.y: %f\n", game.player->y);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_hook(game.win, KEY_PRESS, KEY_PRESS_MASK, key_press, game.player);
	mlx_hook(game.win, KEY_RELEASE, KEY_RELEASE_MASK, key_realese, game.player);
	// mlx_hook(game->win, DestroyNotify, KEY_PRESS_MASK, exit_game, game);
	printf("here\n");
	mlx_loop(game.mlx);
	// free(game);
	return (0);
}

// int	main(int ac, char **av)
// {
// 	t_map	*map;
// 	t_game	*game;

// 	if (ac != 2)
// 	{
// 		ft_printf("Error: Too many arguments.\n");
// 		return (1);
// 	}
// 	map = parse_cub_file(av[1]);
// 	if (!map)
// 	{
// 		ft_printf("Error: Failed to parse the *.cub file.\n");
// 		return (1);
// 	}
// 	game = init_game(map);
// 	printf("here\n");
// 	if (!game)
// 	{
// 		ft_printf("Error: Failed to initialize the game.\n");
// 		free_resources(map);
// 		return (1);
// 	}
// 	// init_image(game);
// 	// load_all_textures(game);
// 	mlx_loop_hook(game->mlx, game_loop, game);
// 	mlx_hook(game->win, KEY_PRESS, KEY_PRESS_MASK, handle_input, game);
// 	// printf("here\n");
// 	// mlx_key_hook(game->win, handle_input, game);
// 	// render_scene(game);
// 	printf("here1\n");
// 	mlx_loop(game->mlx);
// 	printf("here2\n");
// 	free_resources(map);
// 	return (0);
// }
