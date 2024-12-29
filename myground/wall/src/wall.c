/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:52:17 by hosokawa          #+#    #+#             */
/*   Updated: 2024/12/28 16:16:29 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"


int main(void)
{
	t_wall wall;
	t_rayInfo rayInfo;
	int worldMap[10][10];
	int pixel;
	
	
	//マップの情報を作成
	worldMap_init(worldMap);
	//mlxを初期化
	wall_init(&wall);
	//光線情報を初期化
	rayInfo_init(&rayInfo);

	pixel=0;
	while(pixel<WIDTH)
	{
		//光線を定義
		double camera;
		double rayX;
		double rayY;

		camera=2.0*(double)pixel/(double)WIDTH-1.0;		

		rayX=rayInfo.dirX+(rayInfo.planeX*camera);
		rayY=rayInfo.dirY+(rayInfo.planeY*camera);

		//光線を動かす
		
		//初期値を求める
		//DDAアルゴリズムに必要な情報を初期化
		t_ddaInfo ddaInfo;
		calculate_start_ddaInfo(rayX,rayY,rayInfo.posX,rayInfo.posY,&ddaInfo);

		//DDAをスタート
		int hit=0;
		while(hit!=1)
		{
			
			//x軸の辺が最短なのでdeltaDistXで更新
			if((ddaInfo.sideDistX)<(ddaInfo.sideDistY))
			{
				(ddaInfo.sideDistX)+=(ddaInfo.deltaDistX);
				(ddaInfo.mapX)+=(ddaInfo.stepX);
				(ddaInfo.side)=0;
			}
			//y軸の辺が最短なのでdeltaDistYで更新
			else
			{
				(ddaInfo.sideDistY)+=(ddaInfo.deltaDistY);
				(ddaInfo.mapY)+=(ddaInfo.stepY);
				(ddaInfo.side)=1;
			}
			//壁に衝突したかどうか
			if(worldMap[ddaInfo.mapX][ddaInfo.mapY]==1)
				hit=1;
		}

		//壁まで垂直距離を算出
		if(ddaInfo.side==0)
			ddaInfo.perpWallDist=(ddaInfo.sideDistX-(ddaInfo.deltaDistX));
		else
			ddaInfo.perpWallDist=(ddaInfo.sideDistY-(ddaInfo.deltaDistY));

		//壁までの垂直距離から壁の高さを算出
		int lineHeight;
		int h;
		int drawStart;
		int drawEnd;

		h=HEIGHT;
		lineHeight=(int)(1/(ddaInfo.perpWallDist)*h);
		//プレイヤーの視点を真ん中にして上面と底面の位置を算出
		drawStart=-lineHeight/2+h/2;
		if(drawStart<0)
			drawStart=0;
		drawEnd=lineHeight/2+h/2;
		if(drawEnd>=h)
			drawEnd=h-1;
		
		//描画
		drawWorld(pixel,drawStart,drawEnd,&wall);
		pixel++;
	}

	mlx_put_image_to_window(wall.mlx,wall.win,wall.img,0,0);
	mlx_loop(wall.mlx);

	return EXIT_SUCCESS;
}



//	mlx_put_image_to_window(wall.mlx,wall.win,wall.img,0,0);
//	mlx_loop(wall.mlx);



	




