/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 22:04:33 by yyakuben          #+#    #+#             */
/*   Updated: 2025/02/16 21:43:20 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycast_v2(t_game *game)
{
	game->rc->tex_x = 0;
	game->rc->tex_y = 0;
	game->rc->step = 0.0;
	game->rc->tex_pos = 0.0;
	game->rc->color = 0;
}

void	init_raycast(t_game *game)
{
	game->rc = malloc(sizeof(t_raycast));
	if (!game->rc)
		return ;
	game->rc->camera_x = 0.0;
	game->rc->ray_dir_x = 0.0;
	game->rc->ray_dir_y = 0.0;
	game->rc->map_x = 0;
	game->rc->map_y = 0;
	game->rc->side_dist_x = 0.0;
	game->rc->side_dist_y = 0.0;
	game->rc->delta_dist_x = 0.0;
	game->rc->delta_dist_y = 0.0;
	game->rc->step_x = 0;
	game->rc->step_y = 0;
	game->rc->hit = 0;
	game->rc->side = 0;
	game->rc->perp_wall_dist = 0.0;
	game->rc->line_height = 0;
	game->rc->draw_start = 0;
	game->rc->draw_end = 0;
	game->rc->wall_x = 0.0;
	init_raycast_v2(game);
}
