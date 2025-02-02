/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:34:44 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/29 03:37:14 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wall.h"

unsigned int	get_color(char *line, int *i)
{
	unsigned int (r), g, b, color_count = 0;
	r = ft_atoi(line + *i);
	color_count++;
	while (ft_isdigit(line[*i]))
		(*i)++;
	if (line[*i] == ',')
		(*i)++;
	else
		return (0);
	g = ft_atoi(line + *i);
	color_count++;
	while (ft_isdigit(line[*i]))
		(*i)++;
	if (line[*i] == ',')
		(*i)++;
	else
		return (0);
	b = ft_atoi(line + *i);
	color_count++;
	while (ft_isdigit(line[*i]))
		(*i)++;
	if (color_count != 3)
		return (0);
	return (r << 16 | g << 8 | b);
}

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

void	free_map_data(t_map_data *map_data)
{
	if (map_data->north_texture)
		free(map_data->north_texture);
	if (map_data->south_texture)
		free(map_data->south_texture);
	if (map_data->west_texture)
		free(map_data->west_texture);
	if (map_data->east_texture)
		free(map_data->east_texture);
	if (map_data->map)
		free_split(map_data->map);
	free(map_data);
}

// マップ関連の文字か判定
int	is_map_char(char c)
{
	int		result;
	char	*result_str;

	if (c == '0' || c == '1' || c == ' ')
	{
		result = 1;
		result_str = "true";
	}
	else
	{
		result = 0;
		result_str = "false";
	}
	ft_printf("DEBUG: is_map_char checking '%c': %s\n", c, result_str);
	return (result);
}

// プレイヤーの開始位置を示す文字かどうかを判定
int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}
