/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:55:06 by nkannan           #+#    #+#             */
/*   Updated: 2025/02/09 15:37:39 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

static int	handle_player(t_map_data *map_data, char *trimmed, int j)
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

static int	allocate_and_store_map_line(t_map_data *map_data, char *trimmed)
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

int	add_map_line(t_map_data *map_data, const char *line)
{
	char	*trimmed;
	int		j;

	trimmed = ft_strtrim(line, " \n");
	if (!trimmed)
		return (-1);
	if (trimmed[0] == '\0')
		empty_row_error(trimmed);
	if (!validate_map_line(trimmed))
		invalid_char_error(trimmed);
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

int	handle_map_line(t_parse_data *d, char *line)
{
	if (*(d->texture_count) < 4)
		fatal_error_exit(1,
			"Textures must be set before map or need 4 textures");
	if (add_map_line(d->map_data, line) < 0)
		return (1);
	*(d->map_started) = 1;
	return (0);
}
