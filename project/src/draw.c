/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:39:05 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/01 09:44:56 by hosokawa         ###   ########.fr       */
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
	unsigned int	background_color;

	int x, y;
	background_color = 0x000000;
	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			my_pixel_put(x, y, background_color, wall);
		}
	}
}

unsigned int	get_wall_color(t_game *game, int texY)
{
	unsigned int	tex_color;

	if (texY < 0)
		texY = 0;
	else if (texY >= TEXHEIGHT)
		texY = TEXHEIGHT - 1;
	if (game->dda_info.side == 0)
	{
		if (game->dda_info.stepX > 0)
			tex_color = game->texInfo.texture[EAST_INDEX][TEXWIDTH * texY
				+ game->texInfo.texX];
		else
			tex_color = game->texInfo.texture[WEST_INDEX][TEXWIDTH * texY
				+ game->texInfo.texX];
	}
	else
	{
		if (game->dda_info.stepY > 0)
			tex_color = game->texInfo.texture[SOUTH_INDEX][TEXWIDTH * texY
				+ game->texInfo.texX];
		else
			tex_color = game->texInfo.texture[NORTH_INDEX][TEXWIDTH * texY
				+ game->texInfo.texX];
	}
	return (tex_color);
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
	while (i < draw->drawEnd)
	{
		texY = (int)(draw->texPos);
		tex_color = get_wall_color(game, texY);
		draw->texPos += draw->step;
		if ((tex_color & 0xFF000000) == 0)
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
	get_draw_wall_info(&draw, game->dda_info.perpWallDist);
	get_draw_texture_info(&draw);
	drawWorld(pixel, &draw, game);
}

//
// while (i < draw->drawEnd)
//	{
//		texY = (int)(draw->texPos);
//		if (texY < 0)
//			texY = 0;
//		else if (texY >= TEXHEIGHT)
//			texY = TEXHEIGHT - 1;
//		draw->texPos += draw->step;
//		tex_color = get_wall_color(game, texY);
//
