/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:54:10 by yyakuben          #+#    #+#             */
/*   Updated: 2025/02/16 22:20:29 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_ray_direction(t_game *game, int x)
{
	t_raycast	*rc;

	rc = game->rc;
	rc->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	rc->ray_dir_x = game->player->dir_x + game->player->plane_x * rc->camera_x;
	rc->ray_dir_y = game->player->dir_y + game->player->plane_y * rc->camera_x;
	// printf("player_x: %f\nplayer_y: %f\n", game->player->x, game->player->y);
	rc->map_x = (int)game->player->x;
	rc->map_y = (int)game->player->y;
	// printf("map_y: %d\nmap_x: %d\n", rc->map_y, rc->map_x);
	rc->delta_dist_x = fabs(1 / rc->ray_dir_x);
	rc->delta_dist_y = fabs(1 / rc->ray_dir_y);
}

void	calculate_ray_step(t_game *game)
{
	t_raycast *rc;
	
	rc = game->rc;
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (game->player->x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - game->player->x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (game->player->y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (game->player->y + 1.0 - game->player->y) * rc->delta_dist_y;
	}
}

void	find_wall_hit(t_game *game)
{
	t_raycast *rc;
	
	rc = game->rc;
	rc->hit = 0;
	while (rc->hit == 0)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		// printf("map_y: %d\nmap_x: %d\n", rc->map_y, rc->map_x);
		// printf("game->map_y: %d\ngame->map_x: %d\n", game->rc->map_y, game->rc->map_x);
		if (game->map->grid[rc->map_y][rc->map_x])
			rc->hit = 1;
	}
}

void	calculate_wall_dimensions(t_game *game)
{
	t_raycast *rc;

	rc = game->rc;
	if (rc->side == 0)
		rc->perp_wall_dist = (rc->map_x - game->player->x + (1 - rc->step_x)
		/ 2) / rc->ray_dir_x;
	else
		rc->perp_wall_dist = (rc->map_y - game->player->y + (1 - rc->step_y)
		/ 2) / rc->ray_dir_y;
	rc->line_height = (int)(SCREEN_HEIGHT / rc->perp_wall_dist);
	rc->draw_start = -rc->line_height / 2 + SCREEN_HEIGHT / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + SCREEN_HEIGHT / 2;
	if (rc->draw_end >= SCREEN_HEIGHT)
		rc->draw_end = SCREEN_HEIGHT - 1;
}

void	calculate_texture_position(t_game *game)
{
	t_raycast *rc;

	rc = game->rc;
	if (rc->side == 0)
		rc->wall_x = game->player->y + rc->perp_wall_dist * rc->ray_dir_y;
	else
		rc->wall_x = game->player->x + rc->perp_wall_dist * rc->ray_dir_x;
	rc->wall_x = floor(rc->wall_x);
	rc->tex_x = (int)(rc->wall_x * (double)TEXTUREHEIGHT);
	if (rc->side == 0 && rc->ray_dir_x > 0)
		rc->tex_x = TEXTUREHEIGHT - rc->tex_x - 1;
	if (rc->side == 1 && rc->ray_dir_y < 0)
		rc->tex_x = TEXTUREHEIGHT - rc->tex_x - 1;
	rc->step = 1.0 * TEXTUREHEIGHT / rc->line_height;
	rc->tex_pos = (rc->draw_start - SCREEN_HEIGHT / 2 + rc->line_height / 2
		* rc->step);
}


