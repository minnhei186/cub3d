/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 12:28:05 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/11 15:47:01 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == 126 || keycode == 13) 
		game->wall.key_up = 1;
	if (keycode == 125 || keycode == 1) 
		game->wall.key_down = 1;
	if (keycode == 124 || keycode == 2) 
		game->wall.key_right = 1;
	if (keycode == 123 || keycode == 0) 
		game->wall.key_left = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 126 || keycode == 13) 
		game->wall.key_up = 0;
	if (keycode == 125 || keycode == 1) 
		game->wall.key_down = 0;
	if (keycode == 124 || keycode == 2) 
		game->wall.key_right = 0;
	if (keycode == 123 || keycode == 0) 
		game->wall.key_left = 0;
	return (0);
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->wall.mlx, game->wall.win);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

void	readKeys(t_game *game)
{
	
	mlx_hook(game->wall.win, 2, 1L << 0, (int (*)())key_press, game);
	
	mlx_hook(game->wall.win, 3, 1L << 1, (int (*)())key_release, game);
	
	mlx_hook(game->wall.win, 17, 0L, (int (*)())close_window, game);
}

void	update_player(t_game *game)
{
	if (game->wall.key_up)
	{
		move_forward(game);
	}
	if (game->wall.key_down)
	{
		move_back(game);
	}
	if (game->wall.key_left)
	{
		move_left(game);
	}
	if (game->wall.key_right)
	{
		move_right(game);
	}
}
