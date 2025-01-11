/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:31:32 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/11 15:46:15 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

void	init_draw_info(t_draw *draw)
{
	draw->drawStart = 0;
	draw->drawEnd = 0;
	draw->lineHeight = 0;
	draw->step = 0;
	draw->texPos = 0;
}

void	get_draw_wall_info(t_draw *draw, double perpWallDist)
{
	int	h;

	h = HEIGHT;
	draw->lineHeight = (int)(1 / (perpWallDist)*h);
	draw->drawStart = -draw->lineHeight / 2 + h / 2;
	if (draw->drawStart < 0)
		draw->drawStart = 0;
	draw->drawEnd = draw->lineHeight / 2 + h / 2;
	if (draw->drawEnd >= h)
		draw->drawEnd = h - 1;
}

void	get_draw_texture_info(t_draw *draw)
{
	int	h;

	h = HEIGHT;
	draw->step = 1.0 * TEXHEIGHT / draw->lineHeight;
	draw->texPos = (draw->drawStart - h / 2 + draw->lineHeight / 2)
		* draw->step;
}
