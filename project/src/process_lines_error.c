/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_lines_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:54:26 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/09 17:06:47 by hosokawa         ###   ########.fr       */
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

int	process_line_wrapper(t_parse_data *data, int *encountered_empty, char *line)
{
	char	*trimmed;
	int		ret;

	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
		fatal_error_exit(1, "Memory allocation error");
	if (handle_empty_line(data, trimmed, line, encountered_empty))
		return (0);
	free(trimmed);
	if (*encountered_empty)
		encountered_empty_error(line);
	ret = process_line(data, line);
	free(line);
	return (ret);
}
