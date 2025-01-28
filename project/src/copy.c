/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:25:14 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/29 02:56:13 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wall.h"

void	copy_data(t_game *game, t_use_data *use_data)
{
	game->texInfo.texture = use_data->texture;
	game->map = use_data->map;
	game->texInfo.floor_color = use_data->floor_color;
	game->texInfo.ceilling_color = use_data->ceilling_color;
	game->camera.pos_x = use_data->player_y;
	game->camera.pos_y = use_data->player_x;
	game->camera.dir_x = use_data->player_dir_y;
	game->camera.dir_y = use_data->player_dir_x;
	game->camera.plane_x = use_data->player_plane_y;
	game->camera.plane_y = use_data->player_plane_x;
}
