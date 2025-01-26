/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:52:17 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/24 15:33:40 by hosokawa         ###   ########.fr       */
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
		calculate_dda_algo(game->map, &game->ddaInfo);
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


//void test(t_use_data *use_data)
//{
//	int i;
//	int j;
//
//	i=0;
//	while(i<TEXHEIGHT)
//	{
//		j=0;
//		while(j<TEXWIDTH)
//		{
//			printf("%i",use_data->texture[0][i+j]);
//			j++;
//		}
//		printf("\n");
//		i++;
//	}
//	return ;
//}



int	main(void)
{
	t_game	game;
	t_map_data map_data;
	t_use_data use_data;

	//ファイルからデータを読む混む
	map_data_init(&map_data);
	get_data(&map_data,"small_map.cub");	


	//望ましいデータ型に変換
	use_data_init(&use_data);	
	translate_data(&use_data,&map_data);


	//gameとデータを紐付ける
	game_init(&game);
	copy_data(&game,&use_data);

	//test
	int i;
	int j;

	i=0;
	while(i<use_data.map_height)
	{
		j=0;
		while(j<use_data.map_width)
		{
			printf("%i",use_data.map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	

	mlx_loop_hook(game.wall.mlx, game_loop, &game);
	mlx_loop(game.wall.mlx);
	return (EXIT_SUCCESS);
}




