/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:55:06 by nkannan           #+#    #+#             */
/*   Updated: 2025/02/05 10:57:30 by hosokawa         ###   ########.fr       */
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
			if (handle_player(map_data, trimmed, j) < 0)
				return (-1);
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

// int	line_starts_with_texture_or_color(const char *line)
//{
//	if (!ft_strncmp(line, "NO", 2))
//		return (1);
//	if (!ft_strncmp(line, "SO", 2))
//		return (1);
//	if (!ft_strncmp(line, "WE", 2))
//		return (1);
//	if (!ft_strncmp(line, "EA", 2))
//		return (1);
//	if (!ft_strncmp(line, "F", 1))
//		return (1);
//	if (!ft_strncmp(line, "C", 1))
//		return (1);
//	return (0);
//}
//
// static int	ft_isspace(int c)
//{
//	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'
//		|| c == '\v')
//		return (1);
//	return (0);
//}
//
// static int	parse_config_line(t_parse_data *d, char *line)
//{
//	int		i;
//	int		j;
//	char	*id;
//	char	*value;
//
//	if (*(d->map_started))
//	{
//		fatal_error_exit(1, "Additional data after map.");
//		return (1);
//	}
//	i = 0;
//	skip_whitespace(line, &i);
//	j = i;
//	while (line[j] && !ft_isspace(line[j]))
//		j++;
//	id = ft_substr(line, i, j - i);
//	skip_whitespace(line, &j);
//	value = ft_substr(line, j, ft_strlen(line + j));
//	if (!id || !*id || !value || !*value)
//	{
//		free(id);
//		free(value);
//		fatal_error_exit(1, "Invalid texture/color line");
//	}
//	parse_texture_or_color(d->map_data, id, value, d->texture_count);
//	free(id);
//	free(value);
//	return (0);
//}
//
// static int	handle_map_line(t_parse_data *d, char *line)
//{
//	if (*(d->texture_count) < 4)
//	{
//		fatal_error_exit(1,
//			"Textures must be set before map or need 4 textures");
//		return (1);
//	}
//	if (add_map_line(d->map_data, line) < 0)
//		return (1);
//	*(d->map_started) = 1;
//	return (0);
//}
//
// static int	process_line(t_parse_data *d, char *line)
//{
//	int	pos;
//
//	pos = 0;
//	remove_comment(line, 0);
//	skip_whitespace(line, &pos);
//	if (!line[pos])
//		return (0);
//	if (line_starts_with_texture_or_color(&line[pos]))
//	{
//		if (parse_config_line(d, line + pos))
//			return (1);
//	}
//	else if (is_map_line(line, pos))
//	{
//		if (handle_map_line(d, line))
//			return (1);
//	}
//	return (0);
//}
//
// int	process_lines(int fd, t_parse_data *data)
//{
//	char	*line;
//	int		ret;
//
//	line = get_next_line(fd);
//	while (line)
//	{
//		ret = process_line(data, line);
//		free(line);
//		if (ret)
//			return (1);
//		line = get_next_line(fd);
//	}
//	return (0);
//}
