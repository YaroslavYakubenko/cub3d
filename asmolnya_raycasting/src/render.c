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

int render(t_game *game)
{
	// int	y;
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		ray_direction_calculate(game, x);
		// calculate_step_and_dist(game);
		// set_ray_steps(game);
		// calculate_wall_parameters(game);
		// calculate_texture_coordinates(game);
		// y = game->rc.draw_start - 1;
		// while (++y < game->rc.draw_end)
		// {
		// 	render_walls(game, x, y);
		// }
	}
	return (0);
}