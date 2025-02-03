/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 10:39:44 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/03 12:47:36 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

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
}

void	free_all_resources(t_game *game)
{
	int	i;

	if (game->wall.img)
		mlx_destroy_image(game->wall.mlx, game->wall.img);
	if (game->wall.win)
		mlx_destroy_window(game->wall.mlx, game->wall.win);
	if (game->map)
	{
		i = 0;
		while (i < game->map_height)
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
		game->map = NULL;
	}
}
