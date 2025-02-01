/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:32:09 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/31 11:05:00 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

void	calculate_texture_information(double ray_x, double ray_y, t_game *game)
{
	double	wallX;
	int		texX;

	if (game->dda_info.side == 0)
		wallX = game->camera.pos_y + game->dda_info.perpWallDist * ray_y;
	if (game->dda_info.side == 1)
		wallX = game->camera.pos_x + game->dda_info.perpWallDist * ray_x;
	wallX -= floor(wallX);
	//鏡面処理
	texX = (int)(wallX * (double)TEXWIDTH);
	game->texInfo.texX = texX;
	if (game->dda_info.side == 0 && ray_x > 0)
		game->texInfo.texX = TEXWIDTH - texX - 1;
	if (game->dda_info.side == 1 && ray_y> 0)
		game->texInfo.texX = TEXWIDTH - texX - 1;
}
