/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:09:43 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/01 09:56:52 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

void	wall_init(t_game *game)
{
	game->wall.mlx = mlx_init();
	if (game->wall.mlx == NULL)
		fatal_error_exit(1, "error:mlx_init_error");
	game->wall.win = mlx_new_window(game->wall.mlx, WIDTH, HEIGHT,
			"wall wall!");
	if (game->wall.win == NULL)
		fatal_error_exit(1, "error:mlx_new_window_error");
	game->wall.img = mlx_new_image(game->wall.mlx, WIDTH, HEIGHT);
	if (game->wall.img == NULL)
		fatal_error_exit(1, "error:mlx_new_image_error");
	game->wall.addr_pt = mlx_get_data_addr(game->wall.img, &(game->wall.bpp),
			&(game->wall.size_line), &(game->wall.endian));
	if (game->wall.addr_pt == NULL)
		fatal_error_exit(1, "error:mlx_get_data_addr_error");
	game->wall.key_up = 0;
	game->wall.key_down = 0;
	game->wall.key_left = 0;
	game->wall.key_right = 0;
}

// reverse_fit
void	camera_init(t_game *game)
{
	game->camera.pos_x = PLAYERY;
	game->camera.pos_y = PLAYERX;
	game->camera.dir_x = INITDIRX;
	game->camera.dir_y = INITDIRY;
	game->camera.plane_x = INITPLANEX;
	game->camera.plane_y = INITPLANEY;
	game->camera.step = 0.1;
}

void	dda_info_init(t_game *game)
{
	game->dda_info.mapX = 0;
	game->dda_info.mapY = 0;
	game->dda_info.sideDistX = 0;
	game->dda_info.sideDistY = 0;
	game->dda_info.deltaDistX = 0;
	game->dda_info.deltaDistY = 0;
	game->dda_info.perpWallDist = 0;
	game->dda_info.stepX = 0;
	game->dda_info.stepY = 0;
	game->dda_info.hit = 0;
	game->dda_info.side = 0;
}

void	tex_info_init(t_game *game)
{
	game->tex_info.tex_x = 0;
	game->tex_info.floor_color = 0;
	game->tex_info.ceilling_color = 0;
	game->tex_info.texture = NULL;
}

void	game_init(t_game *game)
{
	wall_init(game);
	camera_init(game);
	dda_info_init(game);
	tex_info_init(game);
	game->map = NULL;
	read_keys(game);
}
