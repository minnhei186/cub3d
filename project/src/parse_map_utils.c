/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:55:06 by nkannan           #+#    #+#             */
/*   Updated: 2025/02/05 10:43:42 by hosokawa         ###   ########.fr       */
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
	int		j;
	char	*id;
	char	*value;

	if (*(d->map_started))
	{
		fatal_error_exit(1, "Additional data after map.");
		return (1);
	}
	i = 0;
	skip_whitespace(line, &i);
	j = i;
	while (line[j] && !ft_isspace(line[j]))
		j++;
	id = ft_substr(line, i, j - i);
	skip_whitespace(line, &j);
	value = ft_substr(line, j, ft_strlen(line + j));
	if (!id || !*id || !value || !*value)
	{
		free(id);
		free(value);
		fatal_error_exit(1, "Invalid texture/color line");
	}
	parse_texture_or_color(d->map_data, id, value, d->texture_count);
	free(id);
	free(value);
	return (0);
}

static int	handle_map_line(t_parse_data *d, char *line)
{
	if (*(d->texture_count) < 4)
	{
		fatal_error_exit(1,
			"Textures must be set before map or need 4 textures");
		return (1);
	}
	if (add_map_line(d->map_data, line) < 0)
		return (1);
	*(d->map_started) = 1;
	return (0);
}

static int	process_line(t_parse_data *d, char *line)
{
	int	pos;

	pos = 0;
	remove_comment(line, 0);
	skip_whitespace(line, &pos);
	if (!line[pos])
		return (0);
	if (line_starts_with_texture_or_color(&line[pos]))
	{
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
	int		ret;

	line = get_next_line(fd);
	while (line)
	{
		ret = process_line(data, line);
		free(line);
		if (ret)
			return (1);
		line = get_next_line(fd);
	}
	return (0);
}
