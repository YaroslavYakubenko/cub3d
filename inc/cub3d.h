/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:37:39 by yyakuben          #+#    #+#             */
/*   Updated: 2025/02/20 18:44:23 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line_bonus.h"
# ifdef __APPLE__
#  include "../mlx/mlx.h"
#  include <OpenGL/gl.h>
#  include <AppKit/AppKit.h>
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_SPACE 49
# else
#  include "../minilibx_linux/mlx.h"
#  include <X11/X.h>
#  include <X11/keysym.h>
#  include <X11/Xlib.h>
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_ESC 65307
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_SPACE 32
# endif
# include <assert.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define KEY_PRESS_MASK (1L<<0) 
# define KEY_RELEASE_MASK (1L<<1) 
# define DESTROY 17

# define PLAYER_SPEED 5
# define ROTATION_SPEED 0.03
# define DISTANCE 10
# define FOV 1.047 //60 градусов, угол обзора камеры
# define PI 3.14159265358979323846

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define TEXTUREHEIGHT	512
# define TEXTUREWIDTH	512
# define BLOCK 128
# define DEBUG 0

enum	e_side
{
	_s_null,
	_s_north,
	_s_south,
	_s_west,
	_s_east
};

typedef	struct	s_raycast
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;
}	t_raycast;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_lenght;
	int		endian;
}	t_image;


typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	lef_rotate;
	bool	right_rotate;
	double	plane_x;
	double	plane_y;
	double	dir_x;
	double	dir_y;
}	t_player;

typedef struct s_map
{
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*floor;
	char		*ceiling;
	int			floor_color;
	int			ceiling_color;
	char		**grid;
	char		**liness;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_image		*back;
	t_image		*north_img;
	t_image		*south_img;
	t_image		*west_img;
	t_image		*east_img;
	t_map		*map;
	t_player	*player;
	float		*z_buffer;
	t_raycast	*rc;
}	t_game;

// typedef struct s_ray
// {
// 	float	ray_x;
// 	float	ray_y;
// 	float	ray_dir_x;
// 	float	ray_dir_y;
// 	float	side_dist_x;
// 	float	side_dist_y;
// 	int		step_x;
// 	int		step_y;
// 	int		side;
// }	t_ray;




char	**read_file(const char *file_name);
t_map	*parse_cub_file(const char *file_name);
void	free_resources(t_map *map);
void	load_all_textures(t_game *game);
// void	render_scene(t_game *game);

void	put_pixel(t_game *game, int x, int y, int color);
int		key_press(int keycode, t_game *game);
int		key_realese(int keycode, t_game *game);
void	move_player(t_game *game, float move_x, float move_y);
void	init_player(t_player *player, t_game *game);
int		draw_loop(t_game *game);
void	init_game(t_game *game);
void	clear_image(t_game *game);
void	draw_square(t_game *game, int x, int y, int size, int color);
void	draw_map(t_game *game);
int		exit_game(t_game *game);
void	free_game(t_game *game);
void	free_map(t_map *map, t_game *game);
bool	touch(t_game *game, float px, float py);
float	fixed_dist(t_game *game, double x1, double y1, double x2, double y2);
void	movement_player(t_game *game);
void	init_raycast(t_game *game);
void	draw_wall_segment(t_game *game, int x, int y);
void	calculate_texture_position(t_game *game);
void	calculate_wall_dimensions(t_game *game);
void	find_wall_hit(t_game *game);
void	calculate_ray_step(t_game *game);
void	calculate_ray_direction(t_game *game, int x);
int		get_pixel(t_image *texture, int x, int y);
void	floor_and_ceiling(t_game *game);
void	init_movement(t_game *game);

#endif