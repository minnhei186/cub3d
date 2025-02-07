/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:46:27 by nkannan           #+#    #+#             */
/*   Updated: 2025/02/07 13:09:41 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wall.h"

void	use_data_init(t_use_data *use_data)
{
	int	i;
	int	j;

	use_data->map = NULL;
	use_data->map_width = 0;
	use_data->map_height = 0;
	use_data->floor_color = 0;
	use_data->ceilling_color = 0;
	use_data->player_x = 0.0;
	use_data->player_y = 0.0;
	use_data->player_dir_x = 0.0;
	use_data->player_dir_y = 0.0;
	use_data->player_plane_x = 0.0;
	use_data->player_plane_y = 0.0;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < TEXWIDTH * TEXHEIGHT)
		{
			use_data->texture[i][j] = 0;
			j++;
		}
		i++;
	}
}

static void	allocate_map(t_use_data *data, const t_map_data *map_data)
{
	int	y;
	int	x;

	data->map = (int **)malloc(sizeof(int *) * map_data->map_height);
	if (!data->map)
		fatal_error_exit(1, "error: malloc failed");
	y = -1;
	while (++y < map_data->map_height)
	{
		data->map[y] = (int *)malloc(sizeof(int) * map_data->map_width);
		if (!data->map[y])
			fatal_error_exit(1, "error: malloc failed");
		x = -1;
		while (++x < map_data->map_width)
			data->map[y][x] = (map_data->map[y][x] == '1');
	}
}

static void	conversion_dir(t_use_data *use_data, const t_map_data *map_data)
{
	if (map_data->player_dir == 'N')
		north_direction(use_data);
	else if (map_data->player_dir == 'S')
		south_direction(use_data);
	else if (map_data->player_dir == 'W')
		west_direction(use_data);
	else if (map_data->player_dir == 'E')
		east_direction(use_data);
}

static void	set_player(t_use_data *use_data, const t_map_data *map_data)
{
	use_data->player_x = (double)map_data->player_x + 0.5;
	use_data->player_y = (double)map_data->player_y + 0.5;
	conversion_dir(use_data, map_data);
}

void	translate_data(void **mlx, t_use_data *data, const t_map_data *map)
{
	*mlx = mlx_init();
	if (!*mlx)
		fatal_error_exit(1, "error: *mlx_init failed");
	set_player(data, map);
	load_texture(*mlx, data->texture[0], map->north_texture);
	load_texture(*mlx, data->texture[1], map->south_texture);
	load_texture(*mlx, data->texture[2], map->west_texture);
	load_texture(*mlx, data->texture[3], map->east_texture);
	data->map_width = map->map_width;
	data->map_height = map->map_height;
	data->floor_color = map->floor_color;
	data->ceilling_color = map->ceilling_color;
	allocate_map(data, map);
}
