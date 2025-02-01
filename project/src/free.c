/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 10:39:44 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/01 10:43:17 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

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
