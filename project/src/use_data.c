/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:46:27 by nkannan           #+#    #+#             */
/*   Updated: 2025/01/17 10:59:44 by hosokawa         ###   ########.fr       */
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

static void	load_texture(int *texture_dest, char *texture_path)
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
	int		i;
	int		j;
	void	*mlx;

	mlx = mlx_init();
	if (!mlx)
		fatal_error_exit(1, "error: mlx_init failed in load_texture");
	img = mlx_xpm_file_to_image(mlx, texture_path, &width, &height);
	if (!img || width != TEXWIDTH || height != TEXHEIGHT)
		fatal_error_exit(1, "error: invalid texture file or dimensions");
	addr = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	if (!addr)
		fatal_error_exit(1, "error: mlx_get_data_addr failed");
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			texture_dest[i * width + j] = *(unsigned int *)(addr + (i
						* size_line + j * (bpp / 8)));
			j++;
		}
		i++;
	}
	mlx_destroy_image(mlx, img);
}

static void	allocate_map(t_use_data *use_data, const t_map_data *map_data)
{
	int	i;
	int	j;

	use_data->map = (int **)malloc(sizeof(int *) * map_data->map_height);
	if (!use_data->map)
		fatal_error_exit(1, "error: malloc failed for map");
	i = 0;
	while (i < map_data->map_height)
	{
		use_data->map[i] = (int *)malloc(sizeof(int) * map_data->map_width);
		if (!use_data->map[i])
			fatal_error_exit(1, "error: malloc failed for map row");
		j = 0;
		while (j < map_data->map_width)
		{
			if (map_data->map[i][j] == '1')
				use_data->map[i][j] = 1;
			else
				use_data->map[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	translate_data(t_use_data *use_data, const t_map_data *map_data)
{
	use_data_init(use_data);
	load_texture(use_data->texture[0], map_data->north_texture);
	load_texture(use_data->texture[1], map_data->south_texture);
	load_texture(use_data->texture[2], map_data->west_texture);
	load_texture(use_data->texture[3], map_data->east_texture);
	use_data->map_width = map_data->map_width;
	use_data->map_height = map_data->map_height;
	use_data->floor_color = map_data->floor_color;
	use_data->ceilling_color = map_data->ceilling_color;
	allocate_map(use_data, map_data);
}
