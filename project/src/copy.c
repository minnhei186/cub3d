/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:25:14 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/17 12:01:58 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

void copy_data(t_game *game,t_use_data *use_data)
{
	// int i;

	// i=0;
	// while(i<4)
	// {
	// 	game->texInfo.texture[i]=use_data->texture[i];
	// 	i++;
	// }

	game->texInfo.texture=use_data->texture;
	game->map=use_data->map;

	game->texInfo.floor_color=use_data->floor_color;
	game->texInfo.ceilling_color=use_data->ceilling_color;
}



