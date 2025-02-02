/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 10:09:46 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/02 10:12:15 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

void	north_direction(t_use_data *use_data)
{
	use_data->player_dir_x = 0.0;
	use_data->player_dir_y = -1.0;
	use_data->player_plane_x = 0.66;
	use_data->player_plane_y = 0.0;
}

void	south_direction(t_use_data *use_data)
{
	use_data->player_dir_x = 0.0;
	use_data->player_dir_y = 1.0;
	use_data->player_plane_x = -0.66;
	use_data->player_plane_y = 0.0;
}

void	west_direction(t_use_data *use_data)
{
	use_data->player_dir_x = -1.0;
	use_data->player_dir_y = 0.0;
	use_data->player_plane_x = 0.0;
	use_data->player_plane_y = -0.66;
}

void	east_direction(t_use_data *use_data)
{
	use_data->player_dir_x = 1.0;
	use_data->player_dir_y = 0.0;
	use_data->player_plane_x = 0.0;
	use_data->player_plane_y = 0.66;
}
