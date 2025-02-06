/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:39:05 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/06 17:43:44 by hosokawa         ###   ########.fr       */
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
	int				x;
	int				y;

	y = 0;
	background_color = 0x000000;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_pixel_put(x, y, background_color, wall);
			x++;
		}
		y++;
	}
}

unsigned int	get_wall_color(t_game *game, int tex_y)
{
	unsigned int	tex_color;

	if (tex_y < 0)
		tex_y = 0;
	else if (tex_y >= TEXHEIGHT)
		tex_y = TEXHEIGHT - 1;
	if (game->dda_info.side == 0)
	{
		if (game->dda_info.stepX > 0)
			tex_color = game->tex_info.texture[SOUTH_INDEX][TEXWIDTH * tex_y
				+ game->tex_info.tex_x];
		else
			tex_color = game->tex_info.texture[NORTH_INDEX][TEXWIDTH * tex_y
				+ game->tex_info.tex_x];
	}
	else
	{
		if (game->dda_info.stepY > 0)
			tex_color = game->tex_info.texture[WEST_INDEX][TEXWIDTH * tex_y
				+ game->tex_info.tex_x];
		else
			tex_color = game->tex_info.texture[EAST_INDEX][TEXWIDTH * tex_y
				+ game->tex_info.tex_x];
	}
	return (tex_color);
}

void	draw_world(int pixel, t_draw *draw, t_game *game)
{
	int				i;
	unsigned int	tex_color;
	int				tex_y;

	i = 0;
	while (i < draw->drawStart)
	{
		my_pixel_put(pixel, i, game->tex_info.ceilling_color, &game->wall);
		i++;
	}
	while (i < draw->drawEnd)
	{
		tex_y = (int)(draw->texPos);
		tex_color = get_wall_color(game, tex_y);
		draw->texPos += draw->step;
		if ((tex_color & 0xFF000000) == 0)
			my_pixel_put(pixel, i, tex_color, &game->wall);
		i++;
	}
	while (i < HEIGHT)
	{
		my_pixel_put(pixel, i, game->tex_info.floor_color, &game->wall);
		i++;
	}
}

void	draw(int pixel, t_game *game)
{
	t_draw	draw;

	init_draw_info(&draw);
	get_draw_wall_info(&draw, game->dda_info.perpWallDist);
	get_draw_texture_info(&draw);
	draw_world(pixel, &draw, game);
}

//
// while (i < draw->drawEnd)
//	{
//		tex_y = (int)(draw->texPos);
//		if (tex_y < 0)
//			tex_y = 0;
//		else if (tex_y >= TEXHEIGHT)
//			tex_y = TEXHEIGHT - 1;
//		draw->texPos += draw->step;
//		tex_color = get_wall_color(game, tex_y);
//
