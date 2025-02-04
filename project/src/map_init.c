/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:38:51 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/04 11:24:24 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

void	map_data_init(t_map_data *map_data)
{
	map_data->north_texture = NULL;
	map_data->south_texture = NULL;
	map_data->west_texture = NULL;
	map_data->east_texture = NULL;
	map_data->map = NULL;
	map_data->map_width = 0;
	map_data->map_height = 0;
	map_data->floor_color = -1;
	map_data->ceilling_color = -1;
	map_data->map = ft_calloc(1, sizeof(char *));
	if (map_data->map == NULL)
		fatal_error_exit(0, "map_data_malloc_error");
}
