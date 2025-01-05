/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:52:17 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/05 13:46:39 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

int	game_loop(t_game *game)
{
	int		pixel;
	double	camera;
	double	rayX;
	double	rayY;

	update_player(game);
	clear_window(&game->wall);
	pixel = 0;
	while (pixel < WIDTH)
	{

		camera = 2.0 * (double)pixel / (double)WIDTH - 1.0;
		rayX = game->camera.dir_x + (game->camera.plane_x * camera);
		rayY = game->camera.dir_y + (game->camera.plane_y * camera);
		calculate_start_ddaInfo(rayX, rayY, game->camera.pos_x,
			game->camera.pos_y, &game->ddaInfo);
		calculate_dda_algo(game->worldMap, &game->ddaInfo);
		calculate_perp_hight(&game->ddaInfo);
		draw(pixel,game);
		pixel++;
	}
	mlx_put_image_to_window(game->wall.mlx, game->wall.win, game->wall.img, 0,0);
	return (0);
}

int	main(void)
{
	t_game	game;

	wall_init(&game);
	camera_init(&game);
	ddaInfo_init(&game);
	worldMap_init(&game);
	readKeys(&game);
	mlx_loop_hook(game.wall.mlx, game_loop, &game);
	mlx_loop(game.wall.mlx);
	return (EXIT_SUCCESS);
}

