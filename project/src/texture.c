/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:32:09 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/11 16:53:27 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

void	calculate_texture_information(double ray_x, double ray_y, t_game *game)
{
	double	wall_x;
	int		tex_x;

	if (game->dda_info.side == 0)
		wall_x = game->camera.pos_y + game->dda_info.perp_wall_dist * ray_y;
	if (game->dda_info.side == 1)
		wall_x = game->camera.pos_x + game->dda_info.perp_wall_dist * ray_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)TEXWIDTH);
	game->tex_info.tex_x = tex_x;
	if (game->dda_info.side == 0 && ray_x > 0)
		game->tex_info.tex_x = TEXWIDTH - tex_x - 1;
	if (game->dda_info.side == 1 && ray_y > 0)
		game->tex_info.tex_x = TEXWIDTH - tex_x - 1;
}
