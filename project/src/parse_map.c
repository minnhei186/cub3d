/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 03:18:11 by nkannan           #+#    #+#             */
/*   Updated: 2025/01/29 16:52:57 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wall.h"

int	parse_map(int fd, t_map_data *map_data)
{
	int				texture_count;
	int				map_started;
	t_parse_data	data;

	texture_count = 0;
	map_started = 0;
	data.map_data = map_data;
	data.map_started = &map_started;
	data.texture_count = &texture_count;
	return (process_lines(fd, &data));
}
