/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:32:09 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/13 01:57:10 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wall.h"


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

void calculate_texture_information(double rayX, double rayY, t_game *game)
{
	double wallX;
	int texX;

	// game->texInfo.texNum = game->worldMap[game->ddaInfo.mapX][game->ddaInfo.mapY] - 1;
    game->texInfo.texNum = game->worldMap[game->ddaInfo.mapY][game->ddaInfo.mapX];
    if(game->texInfo.texNum <= 0) //範囲外参照回避のため
        game->texInfo.texNum = 0;

	if (game->ddaInfo.side == 0)
		wallX = game->camera.pos_y + game->ddaInfo.perpWallDist * rayY;
	else
		wallX = game->camera.pos_x + game->ddaInfo.perpWallDist * rayX;
	wallX -= floor((wallX));

    texX = (int)(wallX * (double)TEXWIDTH);
	if (game->ddaInfo.side == 0 && rayX > 0)
		texX = TEXWIDTH - texX - 1;
	if (game->ddaInfo.side == 1 && rayY < 0)
		texX = TEXWIDTH - texX - 1;
    game->texInfo.texX = texX;

}
