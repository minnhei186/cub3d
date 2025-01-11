/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:39:05 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/11 14:39:06 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

void my_pixel_put(int x,int y,int color,t_wall *wall)
{
	char *position;

	position=wall->addr_pt+(y*wall->size_line+x*(wall->bpp/8));
	*(unsigned int *)position=color;
}

void clear_window(t_wall *wall)
{
    int x, y;
    unsigned int background_color = 0x000000; // 黒

    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            my_pixel_put(x, y, background_color, wall);
        }
    }
}

void drawWorld(int pixel,int drawStart,int drawEnd,double texPos,double step, t_game *game)
{
	int i;
//	unsigned int red_color = 0xFF0000; 
	unsigned int blue_color=0x0000FF;
	unsigned int green_color=0x00FF00;
	unsigned int tex_color;
	int texY;



	i=0;
	while(i<drawStart)
	{
		my_pixel_put(pixel,i,blue_color,&game->wall);
		i++;
	}
	while(i<drawEnd)
	{
		texY=(int)texPos&(TEXHEIGHT-1);
		texPos+=step;
		if(game->ddaInfo.side==0)
			tex_color=game->texInfo.texture[0][TEXHEIGHT*texY+game->texInfo.texX];
		else
			tex_color=game->texInfo.texture[1][TEXHEIGHT*texY+game->texInfo.texX];


		my_pixel_put(pixel,i,tex_color,&game->wall);
		i++;
	}
	while(i<HEIGHT)
	{
		my_pixel_put(pixel,i,green_color,&game->wall);
		i++;
	}

}


void draw(int pixel,t_game *game)
{
		int lineHeight;
		int h;
		int drawStart;
		int drawEnd;



		h=HEIGHT;
		lineHeight=(int)(1/(game->ddaInfo.perpWallDist)*h);

		//プレイヤーの視点を真ん中にして上面と底面の位置を算出
		drawStart=-lineHeight/2+h/2;
		if(drawStart<0)
			drawStart=0;
		drawEnd=lineHeight/2+h/2;
		if(drawEnd>=h)
			drawEnd=h-1;

		//texture
		double step;
		double texPos;
		
		step=1.0*TEXHEIGHT/lineHeight;
		texPos=(drawStart-h/2+lineHeight/2)*step;

		//描画
		drawWorld(pixel,drawStart,drawEnd,texPos,step,game);
}


