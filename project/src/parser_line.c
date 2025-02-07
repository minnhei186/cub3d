/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:54:22 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/07 13:12:50 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

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

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'
		|| c == '\v')
		return (1);
	return (0);
}

static int	parse_config_line(t_parse_data *d, char *line)
{
	int		i;
	int		start;
	char	*id;
	char	*value;

	if (*(d->map_started))
		fatal_error_exit(1, "Additional data after map.");
	i = 0;
	skip_whitespace(line, &i);
	start = i;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	id = ft_substr(line, start, i - start);
	skip_whitespace(line, &i);
	value = ft_substr(line, i, ft_strlen(line + i));
	if (!id || !*id || !value || !*value)
		fatal_error_exit(1, "Invalid texture/color line");
	parse_texture_or_color(d->map_data, id, value, d->texture_count);
	free(id);
	free(value);
	return (0);
}

static int	process_line(t_parse_data *d, char *line)
{
	char	*trimmed;
	int		pos;

	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
		fatal_error_exit(1, "Memory allocation error");
	if (trimmed[0] == '\0')
	{
		free(trimmed);
		if (*(d->map_started))
			fatal_error_exit(1, "Empty line within map data");
		return (0);
	}
	free(trimmed);
	pos = 0;
	remove_comment(line, 0);
	skip_whitespace(line, &pos);
	if (!line[pos])
	{
		if (*(d->map_started))
			fatal_error_exit(1, "Empty line within map data");
		return (0);
	}
	if (line_starts_with_texture_or_color(&line[pos]))
	{
		if (*(d->map_started))
			fatal_error_exit(1, "Configuration after map start");
		if (parse_config_line(d, line + pos))
			return (1);
	}
	else if (is_map_line(line, pos))
	{
		if (handle_map_line(d, line))
			return (1);
	}
	return (0);
}

int	process_lines(int fd, t_parse_data *data)
{
	char	*line;

	int ret, empty_line_detected;
	empty_line_detected = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!empty_line_detected && *(data->map_started) && line[0] == '\n')
			empty_line_detected = 1;
		ret = process_line(data, line);
		free(line);
		if (ret)
			return (1);
		line = get_next_line(fd);
	}
	if (empty_line_detected)
		fatal_error_exit(1, "Empty line within map data");
	return (0);
}
