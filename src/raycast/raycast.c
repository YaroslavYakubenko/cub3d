/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:51:06 by yyakuben          #+#    #+#             */
/*   Updated: 2025/03/04 16:59:07 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_direction_calculate(t_game *game, int x)
{
	double camera_x = 2 * x / (double)SCREEN_WIDTH - 1; // a normalized value from -1 (left of the screen) to +1 (right of the screen).
	game->rc->ray_dir_x = game->player->dir_x + game->player->plane_x
		* camera_x; // x for each ray of each pixel
	game->rc->ray_dir_y = game->player->dir_y + game->player->plane_y
		* camera_x; // y for each ray of each pixel
	game->rc->map_x = (int)game->player->x; //player position in int
	game->rc->map_y = (int)game->player->y; //player position in int
	game->rc->delta_dist_x = fabs(1 / game->rc->ray_dir_x); // Distance the ray must travel in world space to cross one full tile in the X direction.
	game->rc->delta_dist_y = fabs(1 / game->rc->ray_dir_y); // distance to travel whole grid
}

void	calculate_step_and_dist(t_game *game)
{
	if (game->rc->ray_dir_x < 0) // if left
	{
		game->rc->step_x = -1; // step - from one grid cell to another 
		game->rc->side_dist_x = (game->player->x - game->rc->map_x)
			* game->rc->delta_dist_x; // how far the ray is from the first vertical and horizontal grid lines  // to the left edge of the tile
	}
	else
	{
		game->rc->step_x = 1; // right
		game->rc->side_dist_x = (game->rc->map_x + 1.0 - game->player->x)
			* game->rc->delta_dist_x; //Distance from the player's current position to the first vertical grid line the ray will cross.
	}
	if (game->rc->ray_dir_y < 0) //if down
	{
		game->rc->step_y = -1;
		game->rc->side_dist_y = (game->player->y - game->rc->map_y)
			* game->rc->delta_dist_y; // Distance to the top edge of the tile
	}
	else
	{
		game->rc->step_y = 1; //up
		game->rc->side_dist_y = (game->rc->map_y + 1.0 - game->player->y)
			* game->rc->delta_dist_y; // Distance to the bottom edge of the tile
	}
}

void	set_ray_steps(t_game *game)
{
	game->rc->hit = 0;
	while (game->rc->hit == 0)
	{
		if (game->rc->side_dist_x < game->rc->side_dist_y) // the ray will move to the next vertical grid line.
		{
			game->rc->side_dist_x += game->rc->delta_dist_x; // tracking how far ray moves across the grid
			game->rc->map_x += game->rc->step_x; // update player position (not for real)
			game->rc->side = 0; // wall was hit on a vertical line
		}
		else // the ray will move to the next horizontal grid line.
		{
			game->rc->side_dist_y += game->rc->delta_dist_y; // tracking how far ray moves across the grid
			game->rc->map_y += game->rc->step_y; // move in map cells
			game->rc->side = 1; // wall was hit on a horisontal line
		}
		if (game->map->grid[game->rc->map_x][game->rc->map_y] > '0') // if it's not 0 then it's a wall
			game->rc->hit = 1; // flag to hit the wall
	}
}

void	calculate_wall_parameters(t_game *game)
{
	if (game->rc->side == 0) // if Hits a vertical wall (X-direction)
		game->rc->perp_wall_dist = (game->rc->map_x - game->player->x + (1
					- game->rc->step_x) / 2) / game->rc->ray_dir_x + 0.0001; // 0.0001 for this pixel between walls // calc against fish eye
	else // if Hits a horizontal wall (Y-direction)
		game->rc->perp_wall_dist = (game->rc->map_y - game->player->y + (1
					- game->rc->step_y) / 2) / game->rc->ray_dir_y + 0.0001;
	// (1 - step_x) / 2 adjusts the calculation depending on whether the ray is stepping left (-1) or right (+1).
	//  Why do we divide by raydir_x or raydir_y?
	// Since the ray isn’t always moving perfectly along an axis, dividing by the direction ensures a true perpendicular distance, eliminating distortion.
	game->rc->line_height = (int)(SCREEN_HEIGHT / game->rc->perp_wall_dist); // The closer the wall (perp_wall_dist is small), the taller the wall appears.
	game->rc->draw_start = -game->rc->line_height / 2 + SCREEN_HEIGHT / 2; // (Top Pixel of the Wall)
	if (game->rc->draw_start < 0)
		game->rc->draw_start = 0; // (prevents rendering outside the screen)
	game->rc->draw_end = game->rc->line_height / 2 + SCREEN_HEIGHT / 2;
	if (game->rc->draw_end >= SCREEN_HEIGHT)
		game->rc->draw_end = SCREEN_HEIGHT - 1; // so it doesn’t exceed screen bounds.
}

void	calculate_texture_coordinates(t_game *game)
{
	if (game->rc->side == 0) // vertical wall
		game->rc->wall_x = game->player->y + game->rc->perp_wall_dist
			* game->rc->ray_dir_y; // x-coor is on the grid so counting on y
	else
		game->rc->wall_x = game->player->x + game->rc->perp_wall_dist
			* game->rc->ray_dir_x; // y-coor is on the grid so counting on x
	game->rc->wall_x -= floor(game->rc->wall_x); // We only care about the fractional part (0 to 1), which tells us where along the wall the hit occurred.
	game->rc->tex_x = (int)(game->rc->wall_x * (double)TEXTUREWIDTH); // Textures have a fixed width (e.g., 64 pixels). Since wall_x is a fraction between 0 and 1, we multiply it by TEXWIDTH to get the pixel column from the texture.
	if (game->rc->side == 0 && game->rc->ray_dir_x > 0) // If the ray hit a vertical wall (side == 0) and was moving right (raydir_x > 0), 
		game->rc->tex_x = TEXTUREWIDTH - game->rc->tex_x - 1; // flip the texture.
	if (game->rc->side == 1 && game->rc->ray_dir_y < 0) // horizontal wall and was moving up
		game->rc->tex_x = TEXTUREWIDTH - game->rc->tex_x - 1; // flip the texture.
	// The step variable tells us how much to move in the texture for each pixel.
	game->rc->step = 1.0 * TEXTUREHEIGHT / game->rc->line_height;
	// This formula finds where to start sampling from the texture.
	game->rc->tex_pos = (game->rc->draw_start - SCREEN_HEIGHT / 2
			+ game->rc->line_height / 2) * game->rc->step;
}
