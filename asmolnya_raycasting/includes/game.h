#ifndef GAME_H
#define GAME_H

#include "../../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define DEBUG 0

#define WIDTH 1280
#define HEIGHT 720

#define W 119
#define A 97
#define S 115
#define D 100

#define PI 3.14159265359

#define BLOCK 64
#define LEFT 65361
#define RIGHT 65363

typedef struct s_map
{
	// t_dataList			*data;
	char				**map;
	int					start_map;
	int					height;
	int					width;
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	// char				*floor;
	// char				*ceiling;
	unsigned int		color_floor;
	unsigned int		color_ceiling;
}						t_map;

typedef struct s_player
{
    float x;
    float y;
    float angle;

    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;

    bool left_rotate;
    bool right_rotate;

    char				direction;
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
} t_player;

typedef struct s_raycast
{
	// double				camera_x;
	double				raydir_x;
	double				raydir_y;
	int					map_x;
	int					map_y;
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				perp_wall_dist;
	int					step_x;
	int					step_y;
	int					hit;
	int					side;
	int					line_height;
	int					draw_start;
	int					draw_end;
	double				wall_x;
	double				step;
	double				tex_pos;
	int					tex_x;
	int					tex_y;
	int					color;
}						t_raycast;

typedef struct s_game
{
    void *mlx;
    void *win;
    void *img;

    char *data;
    int bpp;
    int size_line;
    int endian;
    t_player player;
    t_map *map; 
    t_raycast rc; // allocate memory
} t_game;

void init_player(t_player *player);
int key_press(int keycode, t_player *player);
int key_release(int keycode, t_player *player);
void move_player(t_player *player);
char **get_map(void);
void	init_position_charactor(t_game *game);

#endif
