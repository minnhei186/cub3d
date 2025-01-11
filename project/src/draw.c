/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:39:05 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/11 15:44:09 by hosokawa         ###   ########.fr       */
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
	unsigned int	blue_color;
	unsigned int	green_color;
	unsigned int	tex_color;
	int				texY;

	//	unsigned int red_color = 0xFF0000;
	blue_color = 0x0000FF;
	green_color = 0x00FF00;
	i = 0;
	while (i < draw->drawStart)
	{
		my_pixel_put(pixel, i, blue_color, &game->wall);
		i++;
	}
	while (i < draw->drawEnd)
	{
		texY = (int)draw->texPos & (TEXHEIGHT - 1);
		draw->texPos += draw->step;
		if (game->ddaInfo.side == 0)
			tex_color = game->texInfo.texture[0][TEXHEIGHT * texY
				+ game->texInfo.texX];
		else
			tex_color = game->texInfo.texture[1][TEXHEIGHT * texY
				+ game->texInfo.texX];
		my_pixel_put(pixel, i, tex_color, &game->wall);
		i++;
	}
	while (i < HEIGHT)
	{
		my_pixel_put(pixel, i, green_color, &game->wall);
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
