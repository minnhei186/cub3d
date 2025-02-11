/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:31:32 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/11 17:01:07 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

void	init_draw_info(t_draw *draw)
{
	draw->draw_start = 0;
	draw->draw_end = 0;
	draw->line_height = 0;
	draw->step = 0;
	draw->tex_pos = 0;
}

void	get_draw_wall_info(t_draw *draw, double perp_wall_dist)
{
	int	h;

	h = HEIGHT;
	draw->line_height = (int)(1 / perp_wall_dist * h);
	draw->draw_start = -draw->line_height / 2 + h / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + h / 2;
	if (draw->draw_end >= h)
		draw->draw_end = h - 1;
}

void	get_draw_texture_info(t_draw *draw)
{
	int	h;

	h = HEIGHT;
	draw->step = 1.0 * TEXHEIGHT / (double)draw->line_height;
	draw->tex_pos = (draw->draw_start - h / 2 + draw->line_height / 2)
		* draw->step;
}
