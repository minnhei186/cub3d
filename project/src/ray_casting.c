/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:22:38 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/11 16:53:51 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

static void	caluculate_step_direct(double ray_x, double ray_y, t_game *game)
{
	if (ray_x < 0)
	{
		game->dda_info.step_x = -1;
		game->dda_info.side_dist_x = (game->camera.pos_x - (game->dda_info.map_x))
			* (game->dda_info.delta_dist_x);
	}
	else
	{
		game->dda_info.step_x = 1;
		game->dda_info.side_dist_x = (1.0 + (game->dda_info.map_x)
				- game->camera.pos_x) * (game->dda_info.delta_dist_x);
	}
	if (ray_y < 0)
	{
		game->dda_info.step_y = -1;
		game->dda_info.side_dist_y = (game->camera.pos_y - (game->dda_info.map_y))
			* (game->dda_info.delta_dist_y);
	}
	else
	{
		game->dda_info.step_y = 1;
		game->dda_info.side_dist_y = (1.0 + (game->dda_info.map_y)
				- game->camera.pos_y) * (game->dda_info.delta_dist_y);
	}
}

void	calculate_start_dda_info(double ray_x, double ray_y, t_game *game)
{
	game->dda_info.map_x = (int)game->camera.pos_x;
	game->dda_info.map_y = (int)game->camera.pos_y;
	game->dda_info.delta_dist_x = ft_abs(1 / ray_x);
	game->dda_info.delta_dist_y = ft_abs(1 / ray_y);
	caluculate_step_direct(ray_x, ray_y, game);
}

void	calculate_dda_algo(int **map, t_dda_info *dda_info)
{
	int	hit;

	hit = 0;
	while (hit != 1)
	{
		if ((dda_info->side_dist_x) < (dda_info->side_dist_y))
		{
			(dda_info->side_dist_x) += (dda_info->delta_dist_x);
			(dda_info->map_x) += (dda_info->step_x);
			(dda_info->side) = 0;
		}
		else
		{
			(dda_info->side_dist_y) += (dda_info->delta_dist_y);
			(dda_info->map_y) += (dda_info->step_y);
			(dda_info->side) = 1;
		}
		if (map[dda_info->map_x][dda_info->map_y] == 1)
			hit = 1;
	}
}

void	calculate_perp_hight(t_dda_info *dda_info)
{
	if (dda_info->side == 0)
		dda_info->perp_wall_dist = (dda_info->side_dist_x - (dda_info->delta_dist_x));
	else
		dda_info->perp_wall_dist = (dda_info->side_dist_y - (dda_info->delta_dist_y));
}
