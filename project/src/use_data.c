/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:46:27 by nkannan           #+#    #+#             */
/*   Updated: 2025/01/31 10:47:09 by hosokawa         ###   ########.fr       */
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

static void	load_texture(void *mlx, int *texture, char *path)
{
	void	*img;
	char	*addr;

	int (bpp), size_line, endian;
	int (x), y;
	img = mlx_xpm_file_to_image(mlx, path, &x, &y);
	if (!img || x != TEXWIDTH || y != TEXHEIGHT)
		fatal_error_exit(1, "error: invalid texture");
	addr = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	if (!addr)
		fatal_error_exit(1, "error: mlx_get_data_addr failed");
	y = -1;
	while (++y < TEXHEIGHT)
	{
		x = -1;
		while (++x < TEXWIDTH)
			texture[y * TEXWIDTH + x] = *(unsigned int *)(addr + (y * size_line
						+ x * (bpp / 8)));
	}
	mlx_destroy_image(mlx, img);
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

static void	set_player_dir(t_use_data *data, char dir)
{
	int	index;

	double (dir_x)[4] = {0.0, 0.0, -1.0, 1.0};
	double (dir_y)[4] = {-1.0, 1.0, 0.0, 0.0};
	double (plane_x)[4] = {0.66, -0.66, 0.0, 0.0};
	double (plane_y)[4] = {0.0, 0.0, -0.66, 0.66};
	if (dir == 'N')
		index = 0;
	else if (dir == 'S')
		index = 1;
	else if (dir == 'W')
		index = 2;
	else
		index = 3;
	data->player_dir_x = dir_x[index];
	data->player_dir_y = dir_y[index];
	data->player_plane_x = plane_x[index];
	data->player_plane_y = plane_y[index];
}

void	translate_data(t_use_data *data, const t_map_data *map)
{
	void	*mlx;

	mlx = mlx_init();
	if (!mlx)
		fatal_error_exit(1, "error: mlx_init failed");
	use_data_init(data);
	data->player_x = (double)map->player_x + 0.5;
	data->player_y = (double)map->player_y + 0.5;
	set_player_dir(data, map->player_dir);
	load_texture(mlx, data->texture[0], map->north_texture);
	load_texture(mlx, data->texture[1], map->south_texture);
	load_texture(mlx, data->texture[2], map->west_texture);
	load_texture(mlx, data->texture[3], map->east_texture);
	data->map_width = map->map_width;
	data->map_height = map->map_height;
	data->floor_color = map->floor_color;
	data->ceilling_color = map->ceilling_color;
	allocate_map(data, map);
}
