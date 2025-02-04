/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 01:19:38 by nkannan           #+#    #+#             */
/*   Updated: 2025/02/05 08:26:18 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wall.h"

static void	set_texture(char **dst, char *src, int *count)
{
	free(*dst);
	*dst = ft_strtrim(src, " \n\t\r");
	(*count)++;
}

static void	set_color(unsigned int *dst, char *src)
{
	*dst = get_color(src);
}

int	parse_texture_or_color(t_map_data *m, char **sp, int *tc)
{
	if (!sp[0] || !sp[1])
		return (0);
	if (!ft_strncmp(sp[0], "NO", 2))
		set_texture(&m->north_texture, sp[1], tc);
	else if (!ft_strncmp(sp[0], "SO", 2))
		set_texture(&m->south_texture, sp[1], tc);
	else if (!ft_strncmp(sp[0], "WE", 2))
		set_texture(&m->west_texture, sp[1], tc);
	else if (!ft_strncmp(sp[0], "EA", 2))
		set_texture(&m->east_texture, sp[1], tc);
	else if (!ft_strncmp(sp[0], "F", 1))
		set_color(&m->floor_color, sp[1]);
	else if (!ft_strncmp(sp[0], "C", 1))
		set_color(&m->ceilling_color, sp[1]);
	return (0);
}

//ファイルを開いてパース
void	get_data(t_map_data *map_data, const char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		fatal_error_exit(1,"error opening file");
	if (parse_map(fd, map_data))
	{
		close(fd);
		fatal_error_exit(1,"invalid data faile");
	}
	close(fd);
}
