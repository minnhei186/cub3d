/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:55:06 by nkannan           #+#    #+#             */
/*   Updated: 2025/01/29 16:53:24 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wall.h"

int	line_starts_with_texture_or_color(const char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		return (1);
	if (!ft_strncmp(line, "SO", 2))
		return (1);
	if (!ft_strncmp(line, "WE", 2))
		return (1);
	if (!ft_strncmp(line, "EA", 2))
		return (1);
	if (!ft_strncmp(line, "F", 1))
		return (1);
	if (!ft_strncmp(line, "C", 1))
		return (1);
	return (0);
}

static int	handle_config_line(t_parse_data *data, char *line, int pos)
{
	char	**split;

	if (*data->map_started)
	{
		ft_printf("Error: Found additional data after map lines.\n");
		free(line);
		return (1);
	}
	split = ft_split(line + pos, ' ');
	if (!split)
	{
		free(line);
		return (1);
	}
	if (parse_texture_or_color(data->map_data, split, data->texture_count,
			&pos))
	{
		free_split(split);
		free(line);
		return (1);
	}
	free_split(split);
	return (0);
}

static int	handle_map_line(t_parse_data *data, char *line)
{
	if (*data->texture_count < 4)
	{
		ft_printf("Error: Texture paths must be set before map data.\n");
		free(line);
		return (1);
	}
	if (add_map_line(data->map_data, line) == -1)
	{
		free(line);
		return (1);
	}
	return (0);
}

static int	process_line(t_parse_data *data, char *line, int pos)
{
	if (line_starts_with_texture_or_color(&line[pos]))
	{
		if (handle_config_line(data, line, pos))
			return (1);
	}
	else if (is_map_line(line, pos))
	{
		if (handle_map_line(data, line))
			return (1);
		*data->map_started = 1;
	}
	return (0);
}

int	process_lines(int fd, t_parse_data *data)
{
	char	*line;
	int		pos;

	line = get_next_line(fd);
	while (line)
	{
		pos = 0;
		remove_comment(line, 0);
		skip_whitespace(line, &pos);
		if (!line[pos])
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (process_line(data, line, pos))
			return (free(line), 1);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
