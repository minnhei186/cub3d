/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:22:38 by hosokawa          #+#    #+#             */
/*   Updated: 2024/12/28 16:07:50 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

double ft_abs(double a)
{
	if(a>=0)
		return a;
	else 
		return -a;
}

void calculate_start_ddaInfo(double rayX,double rayY,double posX,double posY,t_ddaInfo *ddaInfo)
{
	//現在地のセル	
	ddaInfo->mapX=(int)posX;
	ddaInfo->mapY=(int)posY;

	//deltaX,deltaY　ある辺から次の辺までの距離
	ddaInfo->deltaDistX=ft_abs(1/rayX);
	ddaInfo->deltaDistY=ft_abs(1/rayY);

	//ddaInfo->sideDistX,sizeDistY 初期位置から次の辺までの距離
	if(rayX<0)//負
	{
		ddaInfo->stepX=-1;
		ddaInfo->sideDistX=(posX-(ddaInfo->mapX))*(ddaInfo->deltaDistX);
	}
	else //正
	{
		ddaInfo->stepX=1;
		ddaInfo->sideDistX=(1.0+(ddaInfo->mapX)-posX)*(ddaInfo->deltaDistX);
	}

	if(rayY<0)//負
	{
		ddaInfo->stepY=-1;
		ddaInfo->sideDistY=(posY-(ddaInfo->mapY))*(ddaInfo->deltaDistY);
	}
	else //正
	{
		ddaInfo->stepY=1;
		ddaInfo->sideDistY=(1.0+(ddaInfo->mapY)-posY)*(ddaInfo->deltaDistY);
	}
}





	
