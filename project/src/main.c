/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:52:17 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/09 17:28:13 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

int	game_loop(t_game *game)
{
	int		pixel;
	double	camera;
	double	ray_x;
	double	ray_y;

	update_player(game);
	clear_window(&game->wall);
	pixel = 0;
	while (pixel < WIDTH)
	{
		camera = 2.0 * (double)pixel / (double)WIDTH - 1.0;
		ray_x = game->camera.dir_x + (game->camera.plane_x * camera);
		ray_y = game->camera.dir_y + (game->camera.plane_y * camera);
		calculate_start_dda_info(ray_x, ray_y, game);
		calculate_dda_algo(game->map, &game->dda_info);
		calculate_perp_hight(&game->dda_info);
		calculate_texture_information(ray_x, ray_y, game);
		draw(pixel, game);
		pixel++;
	}
	mlx_put_image_to_window(game->wall.mlx, game->wall.win, game->wall.img, 0,
		0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_map_data	map_data;
	t_use_data	use_data;
	void		*mlx;

	if (argc != 2)
		fatal_error_exit(1, "Need one .cub file argument");
	if (!has_cub_extention(argv[1]))
		fatal_error_exit(1, "Not a .cub file");
	map_data_init(&map_data);
	get_data(&map_data, argv[1]);
	validate_map_data_integrity(&map_data);
	use_data_init(&use_data);
	translate_data(&mlx, &use_data, &map_data);
	free_map_data(&map_data);
	game_init(&game);
	copy_data(&game, &use_data);
	mlx_loop_hook(game.wall.mlx, game_loop, &game);
	mlx_loop(game.wall.mlx);
	return (EXIT_SUCCESS);
}
