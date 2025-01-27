/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:25:14 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/26 13:21:14 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

void copy_data(t_game *game,t_use_data *use_data)
{


	game->texInfo.texture=use_data->texture;
	game->map=use_data->map;

	game->texInfo.floor_color=use_data->floor_color;
	game->texInfo.ceilling_color=use_data->ceilling_color;
}



