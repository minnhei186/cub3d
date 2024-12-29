/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:09:43 by hosokawa          #+#    #+#             */
/*   Updated: 2024/12/29 13:43:17 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

void wall_init(t_game *game)
{
    game->wall.mlx = mlx_init();
    game->wall.win = mlx_new_window(game->wall.mlx, WIDTH, HEIGHT, "wall wall!");
    game->wall.img = mlx_new_image(game->wall.mlx, WIDTH, HEIGHT);
    game->wall.addr_pt = mlx_get_data_addr(game->wall.img, &(game->wall.bpp),
                                           &(game->wall.size_line), &(game->wall.endian));

    game->wall.key_up = 0;
    game->wall.key_down = 0;
    game->wall.key_left = 0;
    game->wall.key_right = 0;
}

void camera_init(t_game *game)
{
    game->camera.pos_x = PLAYERX;
    game->camera.pos_y = PLAYERY;
    game->camera.dir_x = INITDIRX;
    game->camera.dir_y = INITDIRY;
    game->camera.plane_x = INITPLANEX;
    game->camera.plane_y = INITPLANEY;
    game->camera.step = 0.1; // デフォルトの移動速度を設定
    
}

void worldMap_init(t_game *game)
{
    int i = 0, j = 0;

    while (i < 10)
    {
        j = 0;
        while (j < 10)
        {
            if (i == 0 || i == 9 || j == 0 || j == 9)
                game->worldMap[i][j] = 1;
            else
                game->worldMap[i][j] = 0;

            ft_printf("%i", game->worldMap[i][j]);
            j++;
        }
        ft_printf("\n");
        i++;
    }
}

//void wall_init(t_wall *wall)
//{
//	wall->mlx=mlx_init();
//	wall->win=mlx_new_window(wall->mlx,WIDTH,HEIGHT,"wall wall!");
//	wall->img=mlx_new_image(wall->mlx,WIDTH,HEIGHT);
//	wall->addr_pt=mlx_get_data_addr(wall->img,&(wall->bpp),&(wall->size_line),&(wall->endian));
//
//	wall->key_up=0;
//	wall->key_down=0;
//	wall->key_left=0;
//	wall->key_right=0;
//	
//}
//
//
//void rayInfo_init(t_rayInfo *rayInfo)
//{
//	rayInfo->posX=PLAYERX;
//	rayInfo->posY=PLAYERY;
//	rayInfo->dirX=INITDIRX;
//	rayInfo->dirY=INITDIRY;
//	rayInfo->planeX=INITPLANEX;
//	rayInfo->planeY=INITPLANEY;
//	rayInfo->time=0;
//	rayInfo->oldTime=0;
//}
//
//void worldMap_init(int worldMap[10][10])
//{
//	int i;
//	int j;
//
//	//正方形の空間 10*10
//	i=0;
//	while(i<10)
//	{
//		j=0;
//		while(j<10)
//		{
//			if(i==0||i==9)
//				worldMap[i][j]=1;
//			else if(j==0||j==9)
//				worldMap[i][j]=1;
//			else
//				worldMap[i][j]=0;
//			ft_printf("%i",worldMap[i][j]);
//			j++;
//		}
//		ft_printf("\n");
//		i++;
//	}
//}
//
//
