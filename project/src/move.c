/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:48:55 by hosokawa          #+#    #+#             */
/*   Updated: 2024/12/30 15:46:59 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

#define MOVESPEED 0.1

void move_forward(t_game *game)
{
	double pos_x;
	double pos_y;

	double dir_x;
	double dir_y;

	pos_x=game->camera.pos_x;
	pos_y=game->camera.pos_y;

	dir_x=game->camera.dir_x;
	dir_y=game->camera.dir_y;

	if(game->worldMap[(int)(pos_x+dir_x*MOVESPEED)][(int)pos_y]!=1)
		game->camera.pos_x+=dir_x*MOVESPEED;
	if(game->worldMap[(int)pos_x][(int)(pos_y+dir_y*MOVESPEED)]!=1)
		game->camera.pos_y+=dir_y*MOVESPEED;
}

void move_back(t_game *game)
{
	double pos_x;
	double pos_y;

	double dir_x;
	double dir_y;

	pos_x=game->camera.pos_x;
	pos_y=game->camera.pos_y;

	dir_x=game->camera.dir_x;
	dir_y=game->camera.dir_y;

	if(game->worldMap[(int)(pos_x-dir_x*MOVESPEED)][(int)pos_y]!=1)
	{
		game->camera.pos_x-=dir_x*MOVESPEED;
	}
	if(game->worldMap[(int)pos_x][(int)(pos_y-dir_y*MOVESPEED)]!=1)
	{
		game->camera.pos_y-=dir_y*MOVESPEED;
	}
}






