/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:51:06 by yyakuben          #+#    #+#             */
/*   Updated: 2025/02/15 23:07:41 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	int	i;

	if (!game || !game->back || !game->back->addr)
	{
		printf("Error: game, back or addr is NULL.\n");
		return;
	}
	if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT || x < 0 || y < 0)
		return;
	i = (y * game->back->line_lenght) + (x * (game->back->bpp / 8));
	game->back->addr[i] = (char)(color & 0xFF);
	game->back->addr[i + 1] = (char)((color >> 8) & 0xFF);
	game->back->addr[i + 2] = (char)((color >> 16) & 0xFF);
}

void	draw_map(t_game *game)
{
	char	**map;
	int		color;
	int		x;
	int		y;

	y = 0;
	color = 0x0000FF;
	map = game->map->grid;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(game, x * BLOCK, y * BLOCK, BLOCK, color);
			x++;
		}
		y++;
	}
}

void	draw_square(t_game *game, int x, int y, int size, int color)
{
	float	i;

	i = 0;
	while (i++ < size)
		put_pixel(game, (x + i), y, color);
	i = 0;
	while (i++ < size)
		put_pixel(game, x, (y + i), color);
	i = 0;
	while (i++ < size)
		put_pixel(game, (x + size), (y + i), color);
	i = 0;
	while (i++ < size)
		put_pixel(game, (x + i), (y + size), color);
}

t_image	*get_wall_texture(t_game *game)
{
	t_raycast	*rc;

	rc = game->rc;
	if (rc->side == 0)
	{
		if (rc->ray_dir_x > 0)
			return (game->east_img);
		else
			return (game->west_img);
	}
	else
	{		
		if (rc->ray_dir_y > 0)
			return (game->south_img);
		else
			return (game->north_img);	
	}
}

void	draw_wall_segment(t_game *game, int x)
{
	int	y;
	t_raycast *rc;

	rc = game->rc;
	y = rc->draw_start;
	// printf("y: %d\n", y);
	while (y < rc->draw_end)
	{
		rc->tex_y = (int)rc->tex_pos & (TEXTUREHEIGHT - 1);
		rc->tex_pos += rc->step;
		rc->color = get_pixel(get_wall_texture(game), rc->tex_x, rc->tex_y);
		printf("here_is_draw_wall_segment\n");
		put_pixel(game, x, y, rc->color);
		y++;
	}
}
