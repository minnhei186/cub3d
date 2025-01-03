/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:32:09 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/03 13:55:08 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"


//TEXWIDTH
//TEXHEIGHT
//テクスチャを一つ定義してみよう
void texture_init(t_game *game)
{
	int x;
	int y;

	x=0;
	y=0;
	while(x<TEXWIDTH)
	{
		y=0;
		while(y<TEXHEIGHT)
		{
			game->texture[TEXWIDTH*y+x]=65536 * 192 * (x % 16 && y % 16); 
			y++;
		}
			x++;
	}
}

			

