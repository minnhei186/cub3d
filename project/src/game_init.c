/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:09:43 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/06 09:09:52 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

void	wall_init(t_game *game)
{
	game->wall.mlx = mlx_init();
	game->wall.win = mlx_new_window(game->wall.mlx, WIDTH, HEIGHT,
			"wall wall!");
	game->wall.img = mlx_new_image(game->wall.mlx, WIDTH, HEIGHT);
	game->wall.addr_pt = mlx_get_data_addr(game->wall.img, &(game->wall.bpp),
			&(game->wall.size_line), &(game->wall.endian));
	game->wall.key_up = 0;
	game->wall.key_down = 0;
	game->wall.key_left = 0;
	game->wall.key_right = 0;
}

void	camera_init(t_game *game)
{
	game->camera.pos_x = PLAYERX;
	game->camera.pos_y = PLAYERY;
	game->camera.dir_x = INITDIRX;
	game->camera.dir_y = INITDIRY;
	game->camera.plane_x = INITPLANEX;
	game->camera.plane_y = INITPLANEY;
	game->camera.step = 0.1; // デフォルトの移動速度を設定
}

void	ddaInfo_init(t_game *game)
{
	game->ddaInfo.mapX = 0;
	game->ddaInfo.mapY = 0;
	game->ddaInfo.sideDistX = 0;
	game->ddaInfo.sideDistY = 0;
	game->ddaInfo.deltaDistX = 0;
	game->ddaInfo.deltaDistY = 0;
	game->ddaInfo.perpWallDist = 0;
	game->ddaInfo.stepX = 0;
	game->ddaInfo.stepY = 0;
	game->ddaInfo.hit = 0;
	game->ddaInfo.side = 0;
}

void texInfo_init(t_game *game)
{
	game->texInfo.texNum=0;
	game->texInfo.texX=0;

	texture_init(game);
}


void	worldMap_init(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if (i == 0 || i == 9 || j == 0 || j == 9)
				game->worldMap[i][j] = 1;
			else
				game->worldMap[i][j] = 0;
//			ft_printf("%i", game->worldMap[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}

	game->worldMap[1][5]=1;
	game->worldMap[2][5]=1;
	game->worldMap[3][5]=1;
	game->worldMap[4][5]=1;
	
}
