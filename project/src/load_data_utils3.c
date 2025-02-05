/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 03:11:28 by nkannan           #+#    #+#             */
/*   Updated: 2025/02/05 10:14:40 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wall.h"

static int	handle_player(t_map_data *map_data, char *trimmed, int j)
{
	if (map_data->player_found)
	{
		fatal_error_exit(1, "More than one player start found.");
		return (-1);
	}
	map_data->player_dir = trimmed[j];
	map_data->player_x = j;
	map_data->player_y = map_data->map_height - 1;
	map_data->player_found = 1;
	trimmed[j] = '0';
	return (0);
}

static int	allocate_and_store_map_line(t_map_data *map_data, char *trimmed)
{
	int	len;

	map_data->map_height++;
	map_data->map = ft_realloc_double_ptr(
			(void **)map_data->map, sizeof(char *) * (map_data->map_height + 1));
	if (!map_data->map)
	{
		free(trimmed);
		return (-1);
	}
	map_data->map[map_data->map_height - 1] = trimmed;
	len = ft_strlen(trimmed);
	if (len > map_data->map_width)
		map_data->map_width = len;
	return (0);
}

int	add_map_line(t_map_data *map_data, const char *line)
{
	char	*trimmed;
	int		j;

	trimmed = ft_strtrim(line, " \n");
	if (!trimmed)
		return (-1);
	if (!validate_map_line(trimmed))
	{
		free(trimmed);
		fatal_error_exit(1, "Map line contains invalid characters");
	}
	if (allocate_and_store_map_line(map_data, trimmed) < 0)
		return (-1);
	j = 0;
	while (trimmed[j])
	{
		if (is_player_char(trimmed[j]))
		{
			if (handle_player(map_data, trimmed, j) < 0)
				return (-1);
		}
		j++;
	}
	return (0);
}