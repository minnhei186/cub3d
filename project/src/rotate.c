/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:19:54 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/01 09:22:44 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

#define MOVESPEED 0.1
#define ROTSPEED 0.01

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->camera.dir_x;
	old_plane_x = game->camera.plane_x;
	game->camera.dir_x = game->camera.dir_x * cos(-ROTSPEED)
		- game->camera.dir_y * sin(-ROTSPEED);
	game->camera.dir_y = old_dir_x * sin(-ROTSPEED) + game->camera.dir_y
		* cos(-ROTSPEED);
	game->camera.plane_x = game->camera.plane_x * cos(-ROTSPEED)
		- game->camera.plane_y * sin(-ROTSPEED);
	game->camera.plane_y = old_plane_x * sin(-ROTSPEED) + game->camera.plane_y
		* cos(-ROTSPEED);
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->camera.dir_x;
	old_plane_x = game->camera.plane_x;
	game->camera.dir_x = game->camera.dir_x * cos(ROTSPEED) - game->camera.dir_y
		* sin(ROTSPEED);
	game->camera.dir_y = old_dir_x * sin(ROTSPEED) + game->camera.dir_y
		* cos(ROTSPEED);
	game->camera.plane_x = game->camera.plane_x * cos(ROTSPEED)
		- game->camera.plane_y * sin(ROTSPEED);
	game->camera.plane_y = old_plane_x * sin(ROTSPEED) + game->camera.plane_y
		* cos(ROTSPEED);
}
