/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 11:25:14 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/03 11:18:08 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wall.h"

void	copy_data(t_game *game, t_use_data *use_data)
{
	game->tex_info.texture = use_data->texture;
	game->map = use_data->map;
	game->map_height = use_data->map_height;
	game->map_width = use_data->map_width;
	game->tex_info.floor_color = use_data->floor_color;
	game->tex_info.ceilling_color = use_data->ceilling_color;
	game->camera.pos_x = use_data->player_y;
	game->camera.pos_y = use_data->player_x;
	game->camera.dir_x = use_data->player_dir_y;
	game->camera.dir_y = use_data->player_dir_x;
	game->camera.plane_x = use_data->player_plane_y;
	game->camera.plane_y = use_data->player_plane_x;
}
