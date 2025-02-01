/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_data_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:43:39 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/31 10:44:12 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

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
