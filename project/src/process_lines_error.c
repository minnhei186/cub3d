/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_lines_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:54:26 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/09 16:44:42 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

void	encountered_empty_error(char *line)
{
	free(line);
	fatal_error_exit(1, "Empty line within map data");
}

 int	handle_empty_line(t_parse_data *data, char *trimmed, char *line,
		int *encountered_empty)
{
	if (trimmed[0] == '\0')
	{
		if (*(data->map_started))
			*encountered_empty = 1;
		free(trimmed);
		free(line);
		return (1);
	}
	return (0);
}
