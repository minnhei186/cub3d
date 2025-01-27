/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:22:38 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/25 17:45:47 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

double	ft_abs(double a)
{
	if (a >= 0)
		return (a);
	else
		return (-a);
}

void	calculate_start_ddaInfo(double rayX, double rayY, double posX,
		double posY, t_ddaInfo *ddaInfo)
{

	ddaInfo->mapX = (int)posX;
	ddaInfo->mapY = (int)posY;
	
	ddaInfo->deltaDistX = ft_abs(1 / rayX);
	ddaInfo->deltaDistY = ft_abs(1 / rayY);
	
	if (rayX < 0) 
	{
		ddaInfo->stepX = -1;
		ddaInfo->sideDistX = (posX - (ddaInfo->mapX)) * (ddaInfo->deltaDistX);
	}
	else 
	{
		ddaInfo->stepX = 1;
		ddaInfo->sideDistX = (1.0 + (ddaInfo->mapX) - posX)
			* (ddaInfo->deltaDistX);
	}
	if (rayY < 0) 
	{
		ddaInfo->stepY = -1;
		ddaInfo->sideDistY = (posY - (ddaInfo->mapY)) * (ddaInfo->deltaDistY);
	}
	else 
	{
		ddaInfo->stepY = 1;
		ddaInfo->sideDistY = (1.0 + (ddaInfo->mapY) - posY)
			* (ddaInfo->deltaDistY);
	}
}

void	calculate_dda_algo(int **map, t_ddaInfo *ddaInfo)
{
	int	hit;

	hit = 0;
	while (hit != 1)
	{
		// x軸の辺が最短なのでdeltaDistXで更新
		if ((ddaInfo->sideDistX) < (ddaInfo->sideDistY))
		{
			(ddaInfo->sideDistX) += (ddaInfo->deltaDistX);
			(ddaInfo->mapX) += (ddaInfo->stepX);
			(ddaInfo->side) = 0;
		}
		// y軸の辺が最短なのでdeltaDistYで更新
		else
		{
			(ddaInfo->sideDistY) += (ddaInfo->deltaDistY);
			(ddaInfo->mapY) += (ddaInfo->stepY);
			(ddaInfo->side) = 1;
		}
		//壁に衝突したかどうか
		//変更　modified access order
		if (map[ddaInfo->mapX][ddaInfo->mapY] == 1)
			hit = 1;
	}
}

void	calculate_perp_hight(t_ddaInfo *ddaInfo)
{
	if (ddaInfo->side == 0)
		ddaInfo->perpWallDist = (ddaInfo->sideDistX - (ddaInfo->deltaDistX));
	else
		ddaInfo->perpWallDist = (ddaInfo->sideDistY - (ddaInfo->deltaDistY));
}
