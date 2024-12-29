/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:39:05 by hosokawa          #+#    #+#             */
/*   Updated: 2024/12/28 15:44:28 by hosokawa         ###   ########.fr       */
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


