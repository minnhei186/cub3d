/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:55:01 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/04 12:37:01 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

int	has_cub_extention(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	//セグフォ注意
	return (ft_strncmp(filename + len - 4, ".cub",4) == 0);
}


int	is_valid_map_char(char c)
{
	if (c == '0' || c == '1' ||
		c == 'N' || c == 'S' || c == 'E' || c == 'W' ||
		c == ' ')
		return (1);
	return (0);
}

int	validate_map_line(const char *line)
{
	int	i = 0;

	while (line[i])
	{
		if (!is_valid_map_char(line[i]))
			return (0);
		i++;
	}
	return (1);
}



//void	validate_texture_and_color(t_map_data *map_data)
//{
//	if (!map_data->north_texture || !map_data->south_texture)
//	{
//		if(!map_data->west_texture || !map_data->east_texture)
//			fatal_error_exit(1, "need 4 direction texture_path");
//	}
//	if (map_data->floor_color == -1 || map_data->ceilling_color == -1)
//		fatal_error_exit(1, "Error: Floor and ceiling colors must be set.");
//}
//
