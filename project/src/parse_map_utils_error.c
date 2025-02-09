/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:36:49 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/09 15:37:07 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

void	empty_row_error(char *trimmed)
{
	free(trimmed);
	fatal_error_exit(1, "Empty map row found");
}

void	invalid_char_error(char *trimmed)
{
	free(trimmed);
	fatal_error_exit(1, "Map line contains invalid characters");
}
