/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:55:01 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/06 16:58:07 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

int	has_cub_extention(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 4, ".cub", 4) == 0);
}

int	is_valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ')
		return (1);
	return (0);
}

int	validate_map_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_valid_map_char(line[i]))
			return (0);
		i++;
	}
	return (1);


}

void	validate_map_data_integrity(t_map_data *map_data)
{
	if (!map_data->north_texture || !map_data->south_texture
		|| !map_data->west_texture || !map_data->east_texture)
	{
		fatal_error_exit(1, "Missing one or more texture paths (NO, SO, WE, EA).");
	}

	if (map_data->floor_color == (unsigned int)-1
		|| map_data->ceilling_color == (unsigned int)-1)
	{
		fatal_error_exit(1, "Missing floor or ceiling color (F or C).");
	}


	if (map_data->map_height == 0)
		fatal_error_exit(1, "No map data found.");

	if (!map_data->player_found)
		fatal_error_exit(1, "No player found in map data.");

	if (map_data->map_height < 3 || map_data->map_width < 3)
		fatal_error_exit(1, "Map is too small to be enclosed.");

	validate_map_closed((t_map_data *)map_data);
}

