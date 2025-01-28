/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 03:18:11 by nkannan           #+#    #+#             */
/*   Updated: 2025/01/29 03:22:06 by nkannan          ###   ########.fr       */
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

int	handle_config_line(t_map_data *m, char *line, int pos, int map_started,
		int *tex_count)
{
	char	**split;

	if (map_started)
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
	if (parse_texture_or_color(m, split, tex_count, &pos))
	{
		free_split(split);
		free(line);
		return (1);
	}
	free_split(split);
	return (0);
}

static int	handle_map_line(t_map_data *map_data, char *line, int *tex_count)
{
	if (*tex_count < 4)
	{
		ft_printf("Error: Texture paths must be set before map data.\n");
		free(line);
		return (1);
	}
	if (add_map_line(map_data, line) == -1)
	{
		free(line);
		return (1);
	}
	return (0);
}

static int	process_line(t_map_data *map_data, char *line, int *map_started,
		int *texture_count, int pos)
{
	if (line_starts_with_texture_or_color(&line[pos]))
	{
		if (handle_config_line(map_data, line, pos, *map_started,
				texture_count))
			return (1);
	}
	else if (is_map_line(line, pos))
	{
		if (handle_map_line(map_data, line, texture_count))
			return (1);
		*map_started = 1;
	}
	return (0);
}

//メインのパース関数
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
