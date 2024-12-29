/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:39:05 by hosokawa          #+#    #+#             */
/*   Updated: 2024/12/29 11:36:33 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

void my_pixel_put(int x,int y,int color,t_wall *wall)
{
	char *position;

	position=wall->addr_pt+(y*wall->size_line+x*(wall->bpp/8));
	*(unsigned int *)position=color;
}

void drawWorld(int pixel,int drawStart,int drawEnd,t_wall *wall)
{
	 unsigned int color = 0xFF0000; // 赤い壁

	while(drawStart<drawEnd)
	{
		my_pixel_put(pixel,drawStart,color,wall);
		drawStart++;
	}
}

void draw(int pixel,double perpWallDist,t_wall *wall)
{
		int lineHeight;
		int h;
		int drawStart;
		int drawEnd;

		h=HEIGHT;
		lineHeight=(int)(1/(perpWallDist)*h);

		//プレイヤーの視点を真ん中にして上面と底面の位置を算出
		drawStart=-lineHeight/2+h/2;
		if(drawStart<0)
			drawStart=0;
		drawEnd=lineHeight/2+h/2;
		if(drawEnd>=h)
			drawEnd=h-1;

		//描画
		drawWorld(pixel,drawStart,drawEnd,wall);
}


