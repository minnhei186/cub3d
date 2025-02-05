/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:34:44 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/05 10:56:03 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wall.h"

void	free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	is_map_char(char c)
{
	int	result;

	if (c == '0' || c == '1' || c == ' ')
	{
		result = 1;
	}
	else
	{
		result = 0;
	}
	return (result);
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}
