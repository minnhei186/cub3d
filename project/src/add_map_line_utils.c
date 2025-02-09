/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_map_line_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:46:27 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/09 14:55:24 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

int	handle_player(t_map_data *map_data, char *trimmed, int j)
{
	if (map_data->player_found)
		fatal_error_exit(1, "More than one player start found.");
	map_data->player_dir = trimmed[j];
	map_data->player_x = j;
	map_data->player_y = map_data->map_height - 1;
	map_data->player_found = 1;
	trimmed[j] = '0';
	return (0);
}

int	allocate_and_store_map_line(t_map_data *map_data, char *trimmed)
{
	int	len;

	map_data->map_height++;
	map_data->map = ft_realloc_double_ptr((void **)map_data->map, sizeof(char *)
			* (map_data->map_height + 1));
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

void	validate_trimmed(t_map_data *map_data, char *trimmed)
{
	(void)map_data;
	if (trimmed[0] == '\0')
	{
		free(trimmed);
		fatal_error_exit(1, "Empty map row found");
	}
	if (!validate_map_line(trimmed))
	{
		free(trimmed);
		fatal_error_exit(1, "Map line contains invalid characters");
	}
}

int	store_line(t_map_data *map_data, char *trimmed)
{
	if (allocate_and_store_map_line(map_data, trimmed) < 0)
		return (-1);
	return (0);
}

int	find_player(t_map_data *map_data, char *trimmed)
{
	int	j;

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
