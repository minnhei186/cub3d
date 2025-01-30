/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:39:05 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/29 14:10:08 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

void	my_pixel_put(int x, int y, int color, t_wall *wall)
{
	char	*position;

	position = wall->addr_pt + (y * wall->size_line + x * (wall->bpp / 8));
	*(unsigned int *)position = color;
}

void	clear_window(t_wall *wall)
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

void	drawWorld(int pixel, t_draw *draw, t_game *game)
{
	int				i;
	unsigned int	tex_color;
	int				texY;

	i = 0;
	while (i < draw->drawStart)
	{
		my_pixel_put(pixel, i, game->texInfo.ceilling_color, &game->wall);
		i++;
	}
	//高さと横が違う
	//修正地点
	//ここで南北東西のテクスチャーの割り当てを行う
	while (i < draw->drawEnd)
	{
		// texY = (int)draw->texPos & (TEXHEIGHT - 1); 修正
		//大幅に改善　テクスチャーの正い描画、しかし以前として移動した際に不適切な描画となる
		// texY = (int)draw->texPos % TEXHEIGHT;
		// if (texY < 0)
    	// texY += TEXHEIGHT;
		
		// ★修正: texYの範囲チェックを明示的に行う
		texY = (int)(draw->texPos);
		if (texY < 0)                   // 0未満なら0へ
			texY = 0;
		else if (texY >= TEXHEIGHT)     // 最大値を超えたらTEXHEIGHT-1へ
			texY = TEXHEIGHT - 1;
		
		draw->texPos += draw->step;
		// direct_index_need
		if (game->ddaInfo.side == 0)
		{
			if (game->ddaInfo.stepX > 0)
				tex_color = game->texInfo.texture[EAST_INDEX][TEXWIDTH * texY
					+ game->texInfo.texX];
			else
				tex_color = game->texInfo.texture[WEST_INDEX][TEXWIDTH * texY
					+ game->texInfo.texX];
		}
		else
		{
			if (game->ddaInfo.stepY > 0)
				tex_color = game->texInfo.texture[SOUTH_INDEX][TEXWIDTH * texY
					+ game->texInfo.texX];
			else
				tex_color = game->texInfo.texture[NORTH_INDEX][TEXWIDTH * texY
					+ game->texInfo.texX];
		}
		//	if (game->ddaInfo.side == 0)
		//		tex_color = game->texInfo.texture[0][TEXWIDTH * texY
		//			+ game->texInfo.texX];
		//	else
		//		tex_color = game->texInfo.texture[3][TEXWIDTH * texY
		//			+ game->texInfo.texX];
		if ((tex_color & 0xFF000000) == 0)//めっちゃ強引
			my_pixel_put(pixel, i, tex_color, &game->wall);
		i++;
	}
	while (i < HEIGHT)
	{
		my_pixel_put(pixel, i, game->texInfo.floor_color, &game->wall);
		i++;
	}
}

void	draw(int pixel, t_game *game)
{
	t_draw	draw;

	init_draw_info(&draw);
	get_draw_wall_info(&draw, game->ddaInfo.perpWallDist);
	get_draw_texture_info(&draw);
	drawWorld(pixel, &draw, game);
}
