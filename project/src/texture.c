/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:32:09 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/26 13:13:28 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"


// void	texture_init(t_game *game)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	while (x < TEXWIDTH)
// 	{
// 		y = 0;
// 		while (y < TEXHEIGHT)
// 		{
// 			game->texInfo.texture[0][TEXWIDTH * y + x] = 65536 * 192 * (x % 16
// 					&& y % 16);
// 			game->texInfo.texture[1][TEXWIDTH * y + x] = 128 + 256 * 128 + 65536
// 				* 128;
// 			y++;
// 		}
// 		x++;
// 	}
// }

void	calculate_texture_information(double rayX, double rayY, t_game *game)
{
	double	wallX;
	int		texX;

	game->texInfo.texNum = game->map[game->ddaInfo.mapX][game->ddaInfo.mapY]
		- 1;
	if (game->ddaInfo.side == 0)
		wallX = game->camera.pos_y + game->ddaInfo.perpWallDist * rayY;
	if (game->ddaInfo.side == 1)
		wallX = game->camera.pos_x + game->ddaInfo.perpWallDist * rayX;
	wallX -= floor(wallX);
	//鏡面処理
	texX = (int)(wallX * (double)TEXWIDTH);
	game->texInfo.texX = texX;
	if (game->ddaInfo.side == 0 && rayX > 0)
		game->texInfo.texX = TEXWIDTH - texX - 1;
	if (game->ddaInfo.side == 1 && rayY > 0)
		game->texInfo.texX = TEXWIDTH - texX - 1;
}
