/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:52:17 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/14 14:56:27 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

//__attribute__((destructor))
//static void destructor() {
//	system("leaks -q Wall");
//}

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
		calculate_texture_information(rayX, rayY, game);
		draw(pixel, game);
		pixel++;
	}
	mlx_put_image_to_window(game->wall.mlx, game->wall.win, game->wall.img, 0,
		0);
	return (0);
}


void map_data_init(t_map_data *map_data)
{
	map_data->north_texture=NULL;
	map_data->south_texture=NULL;
	map_data->west_texture=NULL;
	map_data->east_texture=NULL;

	map_data->map=NULL;
	map_data->map_width=0;
	map_data->map_height=0;

	map_data->floor_color=0;
	map_data->ceilling_color=0;
	
	map_data->map = ft_calloc(1, sizeof(char *)); //NULL止めよう
}

////このコピー元のデータを示すようにしよう
//void copy_data(t_game *game,t_map_data *map_data)
//{
//	if(map_data->map!=NULL)
//		game->map=map_data->map;
//
//	game->texInfo.floor_color=map_data.floor_color;
//	game->texInfo.ceilling_color=map_data.ceilling_color;
//
//
//	//texture
//	//map_dataの方にテクスチャーの情報を入れておく。
//	//char ではなくunsigend int で値として持っておこう。
//	//
//
//
//}
	




int	main(void)
{
	t_game	game;
	t_map_data map_data;

	map_data_init(&map_data);
	get_data(&map_data,"./map.cub");

	game_init(&game);
	//copy_data(game,map);
	mlx_loop_hook(game.wall.mlx, game_loop, &game);
	mlx_loop(game.wall.mlx);
	return (EXIT_SUCCESS);
}
