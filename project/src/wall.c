/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:52:17 by hosokawa          #+#    #+#             */
/*   Updated: 2024/12/29 13:42:11 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

int	game_loop(t_game *game)
{
	int		pixel;
	double	camera;
	double	rayX;
	double	rayY;

	// プレイヤーの動きや視点を更新
	update_player(game);
	// 再描画処理
	pixel = 0;
	while (pixel < WIDTH)
	{
		t_ddaInfo ddaInfo;

		camera = 2.0 * (double)pixel / (double)WIDTH - 1.0;
		rayX = game->camera.dir_x + (game->camera.plane_x * camera);
		rayY = game->camera.dir_y + (game->camera.plane_y * camera);
		calculate_start_ddaInfo(rayX, rayY, game->camera.pos_x,
			game->camera.pos_y, &ddaInfo);
		calculate_dda_algo(game->worldMap, &ddaInfo);
		calculate_perp_hight(&ddaInfo);
		draw(pixel, ddaInfo.perpWallDist, &game->wall);//ここら辺は直接gameでもいいな
		pixel++;
	}
	// 更新した画像をウィンドウに出力
	mlx_put_image_to_window(game->wall.mlx, game->wall.win, game->wall.img, 0,0);
	return (0);
}

int	main(void)
{
	t_game	game;

	wall_init(&game);
	camera_init(&game);
	worldMap_init(&game);
	readKeys(&game);
	mlx_loop_hook(game.wall.mlx, game_loop, &game);
	mlx_loop(game.wall.mlx);
	return (EXIT_SUCCESS);
}

// int main(void)
//{
//	t_wall wall;
//	t_rayInfo rayInfo;
//	int worldMap[10][10];
//	int pixel;
//
//
//	worldMap_init(worldMap);
//	wall_init(&wall);
//	rayInfo_init(&rayInfo);
//
//	readKeys(&wall);
//	pixel=0;
//	while(pixel<WIDTH)
//	{
//		double camera;
//		double rayX;
//		double rayY;
//
//		camera=2.0*(double)pixel/(double)WIDTH-1.0;
//
//		rayX=rayInfo.dirX+(rayInfo.planeX*camera);
//		rayY=rayInfo.dirY+(rayInfo.planeY*camera);
//
//		t_ddaInfo ddaInfo;
//		calculate_start_ddaInfo(rayX,rayY,rayInfo.posX,rayInfo.posY,&ddaInfo);
//		calculate_dda_algo(worldMap,&ddaInfo);
//		calculate_perp_hight(&ddaInfo);
//		draw(pixel,ddaInfo.perpWallDist,&wall);
//		pixel++;
//	}
//
//	update_player(&wall);
//
//	mlx_put_image_to_window(wall.mlx,wall.win,wall.img,0,0);
//	mlx_loop(wall.mlx);
//
//	return (EXIT_SUCCESS);
//}
