/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:37:39 by yyakuben          #+#    #+#             */
/*   Updated: 2024/12/01 18:22:57 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx_linux/mlx.h"
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line_bonus.h"
# include <X11/X.h>
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

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_SPACE 32
# define KEY_PRESS KeyPress
# define KEY_RELEASE KeyRelease

# define KEY_PRESS_MASK KeyPressMask
# define KEY_RELEASE_MASK KeyReleaseMask

# define PLAYER_SPEED 0.03
# define ROTATION_SPEED 0.025

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
}	t_player;

typedef struct s_map
{
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	int			floor_color;
	int			ceiling_color;
	char		**grid;
	t_player	player;
}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	*map;
}	t_game;




char	**read_file(const char *file_name);
t_map	*parse_cub_file(const char *file_name);
void	free_map(t_map *map);
int		find_player(t_map *map);
int		handle_input(int keycode, t_game *game);
int		key_handle_wrappper(int keycode, void *param);
void	free_resources(t_map *map);
void	free_map(t_map *map);
void	render_scene(t_game *game);

#endif