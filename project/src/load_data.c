/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 01:19:38 by nkannan           #+#    #+#             */
/*   Updated: 2025/02/05 10:43:36 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wall.h"

static void	set_texture(char **dst, char *src, int *count)
{
	free(*dst);
	*dst = ft_strtrim(src, " \t\r\n");
	(*count)++;
}

static void	set_color(unsigned int *dst, char *src)
{
	*dst = get_color(src);
}

int	parse_texture_or_color(t_map_data *m, char *id, char *value, int *tc)
{
	if (!ft_strncmp(id, "NO", 3))
		set_texture(&m->north_texture, value, tc);
	else if (!ft_strncmp(id, "SO", 3))
		set_texture(&m->south_texture, value, tc);
	else if (!ft_strncmp(id, "WE", 3))
		set_texture(&m->west_texture, value, tc);
	else if (!ft_strncmp(id, "EA", 3))
		set_texture(&m->east_texture, value, tc);
	else if (!ft_strncmp(id, "F", 2))
		set_color(&m->floor_color, value);
	else if (!ft_strncmp(id, "C", 2))
		set_color(&m->ceilling_color, value);
	return (0);
}

void	get_data(t_map_data *map_data, const char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		fatal_error_exit(0, "open");
	if (parse_map(fd, map_data))
	{
		close(fd);
		fatal_error_exit(1, "invalid data file");
	}
	close(fd);
}
