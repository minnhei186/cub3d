/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 03:18:11 by nkannan           #+#    #+#             */
/*   Updated: 2025/01/29 15:59:55 by nkannan          ###   ########.fr       */
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

static int	parse_config_line_inner(t_config_data *data)
{
	char	**split;

	if (data->map_started)
	{
		ft_printf("Error: Found additional data after map lines.\n");
		free(data->line);
		return (1);
	}
	split = ft_split(data->line + data->pos, ' ');
	if (!split)
	{
		free(data->line);
		return (1);
	}
	if (parse_texture_or_color(data->m, split, data->tex_count, &data->pos))
	{
		free_split(split);
		free(data->line);
		return (1);
	}
	free_split(split);
	return (0);
}

int	handle_config_line(t_map_data *m, char *line, int pos, int map_started,
		int *tex_count)
{
	t_config_data	data;

	data.m = m;
	data.line = line;
	data.pos = pos;
	data.map_started = map_started;
	data.tex_count = tex_count;
	return (parse_config_line_inner(&data));
}

static int	handle_map_line_inner(t_map_line_data *data)
{
	if (*data->tex_count < 4)
	{
		ft_printf("Error: Texture paths must be set before map data.\n");
		free(data->line);
		return (1);
	}
	if (add_map_line(data->map_data, data->line) == -1)
	{
		free(data->line);
		return (1);
	}
	return (0);
}

static int	handle_map_line(t_map_data *map_data, char *line, int *tex_count)
{
	t_map_line_data	data;

	data.map_data = map_data;
	data.line = line;
	data.tex_count = tex_count;
	return (handle_map_line_inner(&data));
}

typedef struct s_process_line_data
{
	t_map_data	*map_data;
	char		*line;
	int			*map_started;
	int			*texture_count;
	int			pos;
}				t_process_line_data;

static int	process_line_inner(t_process_line_data *data)
{
	if (line_starts_with_texture_or_color(&data->line[data->pos]))
	{
		if (handle_config_line(data->map_data, data->line, data->pos,
				*data->map_started, data->texture_count))
			return (1);
	}
	else if (is_map_line(data->line, data->pos))
	{
		if (handle_map_line(data->map_data, data->line, data->texture_count))
			return (1);
		*data->map_started = 1;
	}
	return (0);
}

int	process_line(t_map_data *map_data, char *line, int *map_started,
		int *texture_count, int pos)
{
	t_process_line_data	data;

	data.map_data = map_data;
	data.line = line;
	data.map_started = map_started;
	data.texture_count = texture_count;
	data.pos = pos;
	return (process_line_inner(&data));
}

int	parse_map(int fd, t_map_data *map_data)
{
	char	*line;
	int		texture_count;
	int		map_started;
	int		pos;

	texture_count = 0;
	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		pos = 0;
		remove_comment(line, 0);
		skip_whitespace(line, &pos);
		if (!line[pos])
		{
			free(line);
			continue ;
		}
		if (process_line(map_data, line, &map_started, &texture_count, pos))
			return (free(line), 1);
		free(line);
	}
	return (0);
}
