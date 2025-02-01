/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:22:38 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/31 11:52:36 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

static void	caluculate_step_direct(double ray_x, double ray_y, t_game *game)
{
	if (ray_x < 0)
	{
		game->dda_info.stepX = -1;
		game->dda_info.sideDistX = (game->camera.pos_x - (game->dda_info.mapX))
			* (game->dda_info.deltaDistX);
	}
	else
	{
		game->dda_info.stepX = 1;
		game->dda_info.sideDistX = (1.0 + (game->dda_info.mapX)
				- game->camera.pos_x) * (game->dda_info.deltaDistX);
	}
	if (ray_y < 0)
	{
		game->dda_info.stepY = -1;
		game->dda_info.sideDistY = (game->camera.pos_y - (game->dda_info.mapY))
			* (game->dda_info.deltaDistY);
	}
	else
	{
		game->dda_info.stepY = 1;
		game->dda_info.sideDistY = (1.0 + (game->dda_info.mapY)
				- game->camera.pos_y) * (game->dda_info.deltaDistY);
	}
}

void	calculate_start_dda_info(double ray_x, double ray_y, t_game *game)
{
	game->dda_info.mapX = (int)game->camera.pos_x;
	game->dda_info.mapY = (int)game->camera.pos_y;
	game->dda_info.deltaDistX = ft_abs(1 / ray_x);
	game->dda_info.deltaDistY = ft_abs(1 / ray_y);
	caluculate_step_direct(ray_x, ray_y, game);
}

void	calculate_dda_algo(int **map, t_dda_info *dda_info)
{
	int	hit;

	hit = 0;
	while (hit != 1)
	{
		if ((dda_info->sideDistX) < (dda_info->sideDistY))
		{
			(dda_info->sideDistX) += (dda_info->deltaDistX);
			(dda_info->mapX) += (dda_info->stepX);
			(dda_info->side) = 0;
		}
		else
		{
			(dda_info->sideDistY) += (dda_info->deltaDistY);
			(dda_info->mapY) += (dda_info->stepY);
			(dda_info->side) = 1;
		}
		if (map[dda_info->mapX][dda_info->mapY] == 1)
			hit = 1;
	}
}

void	calculate_perp_hight(t_dda_info *dda_info)
{
	if (dda_info->side == 0)
		dda_info->perpWallDist = (dda_info->sideDistX - (dda_info->deltaDistX));
	else
		dda_info->perpWallDist = (dda_info->sideDistY - (dda_info->deltaDistY));
}
