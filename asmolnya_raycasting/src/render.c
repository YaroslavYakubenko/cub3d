#include "../includes/game.h"

void	ray_direction_calculate(t_game *game, int x)
{
	double camera_x = 2 * x / (double)WIDTH - 1; // a normalized value from -1 (left of the screen) to +1 (right of the screen).
	game->rc.raydir_x = game->player.dir_x + game->player.plane_x
		* camera_x; // x for each ray of each pixel
	game->rc.raydir_y = game->player.dir_y + game->player.plane_y
		* camera_x; // y for each ray of each pixel
	game->rc.map_x = (int)game->player.pos_x; //player position in int
	game->rc.map_y = (int)game->player.pos_y; //player position in int
	game->rc.delta_dist_x = fabs(1 / game->rc.raydir_x); // Distance the ray must travel in world space to cross one full tile in the X direction.
	game->rc.delta_dist_y = fabs(1 / game->rc.raydir_y); // distance to travel whole grid
}

void	calculate_step_and_dist(t_game *game)
{
	if (game->rc.raydir_x < 0) // if left
	{
		game->rc.step_x = -1; // step - from one grid cell to another 
		game->rc.side_dist_x = (game->player.pos_x - game->rc.map_x)
			* game->rc.delta_dist_x; // how far the ray is from the first vertical and horizontal grid lines  // to the left edge of the tile
	}
	else
	{
		game->rc.step_x = 1; // right
		game->rc.side_dist_x = (game->rc.map_x + 1.0 - game->player.pos_x)
			* game->rc.delta_dist_x; //Distance from the player's current position to the first vertical grid line the ray will cross.
	}
	if (game->rc.raydir_y < 0) //if down
	{
		game->rc.step_y = -1;
		game->rc.side_dist_y = (game->player.pos_y - game->rc.map_y)
			* game->rc.delta_dist_y; // Distance to the top edge of the tile
	}
	else
	{
		game->rc.step_y = 1; //up
		game->rc.side_dist_y = (game->rc.map_y + 1.0 - game->player.pos_y)
			* game->rc.delta_dist_y; // Distance to the bottom edge of the tile
	}
}

void	set_ray_steps(t_game *game) // find if this particular ray hits a wall
{
	game->rc.hit = 0;
	while (game->rc.hit == 0)
	{
		if (game->rc.side_dist_x < game->rc.side_dist_y) // the ray will move to the next vertical grid line.
		{
			game->rc.side_dist_x += game->rc.delta_dist_x; // tracking how far ray moves across the grid
			game->rc.map_x += game->rc.step_x; // update player position (not for real)
			game->rc.side = 0; // wall was hit on a vertical line
		}
		else // the ray will move to the next horizontal grid line.
		{
			game->rc.side_dist_y += game->rc.delta_dist_y; // tracking how far ray moves across the grid
			game->rc.map_y += game->rc.step_y; // move in map cells
			game->rc.side = 1; // wall was hit on a horisontal line
		}
		if (game->map->map[game->rc.map_x][game->rc.map_y] > '0') // if it's not 0 then it's a wall
			game->rc.hit = 1; // flag to hit the wall
	}
}

void	calculate_wall_parameters(t_game *game)
{
	if (game->rc.side == 0) // if Hits a vertical wall (X-direction)
		game->rc.perp_wall_dist = (game->rc.map_x - game->player.pos_x + (1
					- game->rc.step_x) / 2) / game->rc.raydir_x + 0.0001; // 0.0001 for this pixel between walls // calc against fish eye
	else // if Hits a horizontal wall (Y-direction)
		game->rc.perp_wall_dist = (game->rc.map_y - game->player.pos_y + (1
					- game->rc.step_y) / 2) / game->rc.raydir_y + 0.0001;
	// (1 - step_x) / 2 adjusts the calculation depending on whether the ray is stepping left (-1) or right (+1).
	//  Why do we divide by raydir_x or raydir_y?
	// Since the ray isn’t always moving perfectly along an axis, dividing by the direction ensures a true perpendicular distance, eliminating distortion.
	game->rc.line_height = (int)(HEIGHT / game->rc.perp_wall_dist); // The closer the wall (perp_wall_dist is small), the taller the wall appears.
	game->rc.draw_start = -game->rc.line_height / 2 + HEIGHT / 2; // (Top Pixel of the Wall)
	if (game->rc.draw_start < 0)
		game->rc.draw_start = 0; // (prevents rendering outside the screen)
	game->rc.draw_end = game->rc.line_height / 2 + HEIGHT / 2;
	if (game->rc.draw_end >= HEIGHT)
		game->rc.draw_end = HEIGHT - 1; // so it doesn’t exceed screen bounds.
}

void	calculate_texture_coordinates(t_game *game)
{
	if (game->rc.side == 0) // vertical wall
		game->rc.wall_x = game->player.pos_y + game->rc.perp_wall_dist
			* game->rc.raydir_y; // x-coor is on the grid so counting on y
	else
		game->rc.wall_x = game->player.pos_x + game->rc.perp_wall_dist
			* game->rc.raydir_x; // y-coor is on the grid so counting on x
	game->rc.wall_x -= floor(game->rc.wall_x); // We only care about the fractional part (0 to 1), which tells us where along the wall the hit occurred.
	game->rc.tex_x = (int)(game->rc.wall_x * (double)TEXWIDTH); // Textures have a fixed width (e.g., 64 pixels). Since wall_x is a fraction between 0 and 1, we multiply it by TEXWIDTH to get the pixel column from the texture.
	if (game->rc.side == 0 && game->rc.raydir_x > 0) // If the ray hit a vertical wall (side == 0) and was moving right (raydir_x > 0), 
		game->rc.tex_x = TEXWIDTH - game->rc.tex_x - 1; // flip the texture.
	if (game->rc.side == 1 && game->rc.raydir_y < 0) // horizontal wall and was moving up
		game->rc.tex_x = TEXWIDTH - game->rc.tex_x - 1; // flip the texture.
	// The step variable tells us how much to move in the texture for each pixel.
	game->rc.step = 1.0 * TEXHEIGHT / game->rc.line_height;
	// This formula finds where to start sampling from the texture.
	game->rc.tex_pos = (game->rc.draw_start - HEIGHT / 2
			+ game->rc.line_height / 2) * game->rc.step;
}

t_image	*get_texture_directions(t_game *game)
{
	if (game->rc.side == 0)
	{
		if (game->rc.raydir_x > 0)
			return (game->so_img);
		else
			return (game->no_img);
	}
	else
	{
		if (game->rc.raydir_y > 0)
			return (game->ea_img);
		else
			return (game->we_img);
	}
}

int	get_texture_pixel(t_image *texture, int tex_x, int tex_y)
{
	int				offset;
	unsigned int	*pixel;

	if (!texture || !texture->addr || tex_x < 0 || tex_y < 0
		|| tex_x >= TEXWIDTH || tex_y >= TEXHEIGHT)
		return (0);
	offset = tex_y * (texture->line_length / (texture->bits_per_pixel / 8))
		+ tex_x;
	pixel = (unsigned int *)(texture->addr + offset * (texture->bits_per_pixel
				/ 8));
	return (*pixel);
}

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	// MAYBE CHANGE floor and ceiling here

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}



static void	render_walls(t_game *game, int x, int y)
{
	game->rc.tex_y = (int)game->rc.tex_pos & (TEXHEIGHT - 1);
	game->rc.tex_pos += game->rc.step;
	game->rc.color = get_texture_pixel(get_texture_directions(game),
			game->rc.tex_x, game->rc.tex_y);
	my_mlx_pixel_put(game->back, x, y, game->rc.color);
}

int render(t_game *game)
{
	int	y;
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		ray_direction_calculate(game, x);
		calculate_step_and_dist(game);
		set_ray_steps(game);
		calculate_wall_parameters(game);
		calculate_texture_coordinates(game);
		y = game->rc.draw_start - 1;
		while (++y < game->rc.draw_end)
		{
			render_walls(game, x, y);
		}
	}
	move_player(&game->player);
	// printf("RENDER HERE\n");
	mlx_put_image_to_window(game->mlx, game->win, game->back->img, 0, 0);
	return (0);
}