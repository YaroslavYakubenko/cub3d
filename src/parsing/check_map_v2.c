/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:26:51 by yyakuben          #+#    #+#             */
/*   Updated: 2025/03/08 17:25:46 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_first_syms(char *line) //????????????
{
	int res;

	res = 0;
	if (ft_strncmp(line, "NO ", 3) == 0)
		res = 1;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		res = 1;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		res = 1;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		res = 1;
	else if (ft_strncmp(line, "F ", 2) == 0)
		res = 1;
	else if (ft_strncmp(line, "C ", 2) == 0)
		res = 1;
	else if (line[0] == '\n'
		|| line[0] == '\t' || line[0] == ' ')
		res = 1;
	return (res);
}

