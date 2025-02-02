/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 09:39:19 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/02 10:19:29 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

static void	check_image(t_img_data *data)
{
	if (!data->img || data->width != TEXWIDTH || data->height != TEXHEIGHT)
		fatal_error_exit(1, "error: invalid texture");
}

static void	check_address(t_img_data *data)
{
	if (!data->addr)
		fatal_error_exit(1, "error: mlx_get_data_addr failed");
}

static void	fill_texture_data(int *texture, t_img_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			texture[y * data->width + x] = *(unsigned int *)(data->addr + (y
						* data->size_line + x * (data->bpp / 8)));
			x++;
		}
		y++;
	}
}

void	load_texture(void *mlx, int *texture, char *path)
{
	t_img_data	data;

	data.img = mlx_xpm_file_to_image(mlx, path, &data.width, &data.height);
	check_image(&data);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.size_line,
			&data.endian);
	check_address(&data);
	fill_texture_data(texture, &data);
	mlx_destroy_image(mlx, data.img);
}
