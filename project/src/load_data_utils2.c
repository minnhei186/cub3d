/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 03:05:15 by nkannan           #+#    #+#             */
/*   Updated: 2025/01/29 03:12:03 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wall.h"

void	skip_whitespace(const char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

void	remove_comment(char *line, int start_index)
{
	int	j;

	j = 0;
	while (line[start_index + j] != '\0')
	{
		if (line[start_index + j] == '#')
		{
			line[start_index + j] = '\0';
			break ;
		}
		j++;
	}
}

int	is_map_line(const char *line, int i)
{
	return (line[i] && (is_map_char(line[i]) || is_player_char(line[i])));
}
