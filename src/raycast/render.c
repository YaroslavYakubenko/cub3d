/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:54:23 by yyakuben          #+#    #+#             */
/*   Updated: 2025/03/04 17:44:16 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image	*get_texture_directions(t_game *game)
{
	if (game->rc->side == 0)
	{
		if (game->rc->ray_dir_x > 0)
			return (game->east_img);
		else
			return (game->west_img);
	}
	else
	{
		if (game->rc->ray_dir_y > 0)
			return (game->south_img);
		else
			return (game->north_img);
	}
}

int	get_texture_pixel(t_image *texture, int tex_x, int tex_y)
{
	int				offset;
	unsigned int	*pixel;

	if (!texture || !texture->addr || tex_x < 0 || tex_y < 0
		|| tex_x >= TEXTUREWIDTH || tex_y >= TEXTUREHEIGHT)
		return (0);
	offset = tex_y * (texture->line_lenght / (texture->bpp / 8)) + tex_x;
	pixel = (unsigned int *)(texture->addr + offset * (texture->bpp / 8));
	return (*pixel);
}

static void	render_walls(t_game *game, int x, int y)
{
	game->rc->tex_y = (int)game->rc->tex_pos & (TEXTUREHEIGHT - 1);
	game->rc->tex_pos += game->rc->step;
	game->rc->color = get_texture_pixel(get_texture_directions(game),
			game->rc->tex_x, game->rc->tex_y);
	my_mlx_pixel_put_v2(game->back, x, y, game->rc->color);
}

int	render(t_game *game)
{
	int	y;
	int	x;

	move_player(game);
	clear_image(game);
	floor_and_ceiling(game);
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		ray_direction_calculate(game, x);
		calculate_step_and_dist(game);
		set_ray_steps(game);
		calculate_wall_parameters(game);
		calculate_texture_coordinates(game);
		y = game->rc->draw_start - 1;
		while (++y < game->rc->draw_end)
		{
			render_walls(game, x, y);
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->back->img, 0, 0);
	return (0);
}
