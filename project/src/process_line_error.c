/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:47:01 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/09 15:51:48 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

int	check_trimmed(char *trimmed, int *map_started)
{
	if (!trimmed)
		fatal_error_exit(1, "Memory allocation error");
	if (trimmed[0] == '\0')
	{
		free(trimmed);
		if (*map_started)
			fatal_error_exit(1, "Empty line within map data");
		return (1);
	}
	return (0);
}

int	check_map_line_end(t_parse_data *d, char *line, int pos)
{
	if (!line[pos])
	{
		if (*(d->map_started))
			fatal_error_exit(1, "Empty line within map data");
		return (1);
	}
	return (0);
}
