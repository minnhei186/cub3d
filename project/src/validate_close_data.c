/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_close_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:05:29 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/07 13:12:17 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

char	get_cell(const char *row, int j)
{
	int	len;

	len = ft_strlen(row);
	if (j < len)
		return (row[j]);
	else
		return (' ');
}

static int	is_floor_or_player(char c)
{
	return ((c == '0') || (c == 'N') || (c == 'S') || (c == 'E') || (c == 'W'));
}

static int	check_adjacent(t_map_data *map_data, int i, int j)
{
	char	up;
	char	down;
	char	left;
	char	right;

	up = get_cell(map_data->map[i - 1], j);
	down = get_cell(map_data->map[i + 1], j);
	left = get_cell(map_data->map[i], j - 1);
	right = get_cell(map_data->map[i], j + 1);
	return ((up != ' ') && (down != ' ') && (left != ' ') && (right != ' '));
}

void	validate_map_closed(t_map_data *map_data)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < map_data->map_height)
	{
		j = 0;
		while (j < map_data->map_width)
		{
			c = get_cell(map_data->map[i], j);
			if (is_floor_or_player(c))
			{
				if (i == 0 || i == map_data->map_height - 1 || j == 0
					|| j == map_data->map_width - 1)
					fatal_error_exit(1, "not close map_data");
				if (!check_adjacent(map_data, i, j))
					fatal_error_exit(1, "not close map_data");
			}
			j++;
		}
		i++;
	}
}
