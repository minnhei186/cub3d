/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:48:55 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/31 11:24:10 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

#define MOVESPEED 0.1
#define ROTSPEED 0.01

void	move_forward(t_game *game)
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;

	pos_x = game->camera.pos_x;
	pos_y = game->camera.pos_y;
	dir_x = game->camera.dir_x;
	dir_y = game->camera.dir_y;
	if (game->map[(int)(pos_x + dir_x * MOVESPEED)][(int)pos_y] != 1)
		game->camera.pos_x += dir_x * MOVESPEED;
	if (game->map[(int)pos_x][(int)(pos_y + dir_y * MOVESPEED)] != 1)
		game->camera.pos_y += dir_y * MOVESPEED;
}

void	move_back(t_game *game)
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;

	pos_x = game->camera.pos_x;
	pos_y = game->camera.pos_y;
	dir_x = game->camera.dir_x;
	dir_y = game->camera.dir_y;
	if (game->map[(int)(pos_x - dir_x * MOVESPEED)][(int)pos_y] != 1)
	{
		game->camera.pos_x -= dir_x * MOVESPEED;
	}
	if (game->map[(int)pos_x][(int)(pos_y - dir_y * MOVESPEED)] != 1)
	{
		game->camera.pos_y -= dir_y * MOVESPEED;
	}
}

void	move_right(t_game *game)
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;

	pos_x = game->camera.pos_x;
	pos_y = game->camera.pos_y;
	dir_x = game->camera.dir_x;
	dir_y = game->camera.dir_y;
	if (game->map[(int)(pos_x + dir_y * MOVESPEED)][(int)pos_y] != 1)
		game->camera.pos_x += dir_y * MOVESPEED;
	if (game->map[(int)pos_x][(int)(pos_y - dir_x * MOVESPEED)] != 1)
		game->camera.pos_y -= dir_x * MOVESPEED;
}

void	move_left(t_game *game)
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;

	pos_x = game->camera.pos_x;
	pos_y = game->camera.pos_y;
	dir_x = game->camera.dir_x;
	dir_y = game->camera.dir_y;
	if (game->map[(int)(pos_x - dir_y * MOVESPEED)][(int)pos_y] != 1)
		game->camera.pos_x -= dir_y * MOVESPEED;
	if (game->map[(int)pos_x][(int)(pos_y + dir_x * MOVESPEED)] != 1)
		game->camera.pos_y += dir_x * MOVESPEED;
}
