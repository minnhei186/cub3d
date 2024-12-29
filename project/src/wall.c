/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:52:17 by hosokawa          #+#    #+#             */
/*   Updated: 2024/12/29 11:44:40 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"


int main(void)
{
	t_wall wall;
	t_rayInfo rayInfo;
	int worldMap[10][10];
	int pixel;
	
	
	worldMap_init(worldMap);
	wall_init(&wall);
	rayInfo_init(&rayInfo);

	pixel=0;
	while(pixel<WIDTH)
	{
		double camera;
		double rayX;
		double rayY;

		camera=2.0*(double)pixel/(double)WIDTH-1.0;		

		rayX=rayInfo.dirX+(rayInfo.planeX*camera);
		rayY=rayInfo.dirY+(rayInfo.planeY*camera);
	
		t_ddaInfo ddaInfo;
		calculate_start_ddaInfo(rayX,rayY,rayInfo.posX,rayInfo.posY,&ddaInfo);
		calculate_dda_algo(worldMap,&ddaInfo);	
		calculate_perp_hight(&ddaInfo);
		draw(pixel,ddaInfo.perpWallDist,&wall);
		pixel++;
	}

	mlx_put_image_to_window(wall.mlx,wall.win,wall.img,0,0);
	mlx_loop(wall.mlx);

	return EXIT_SUCCESS;
}






	




