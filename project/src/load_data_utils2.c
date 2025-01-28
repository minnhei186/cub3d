/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 03:05:15 by nkannan           #+#    #+#             */
/*   Updated: 2025/01/29 03:08:36 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wall.h"

void	skip_whitespace(const char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

void	remove_comment(char *line, int start_index)
{
	int	j;

	j = 0;
	while (line[start_index + j] != '\0')
	{
		if (line[start_index + j] == '#')
		{
			line[start_index + j] = '\0';
			break ;
		}
		j++;
	}
}

int	is_map_line(const char *line, int i)
{
	return (line[i] && (is_map_char(line[i]) || is_player_char(line[i])));
}


static int	handle_player(t_map_data *map_data, char *trimmed, int j)
{
	if (map_data->player_found)
	{
		ft_printf("Error: More than one player start found.\n");
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
	int len;

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
