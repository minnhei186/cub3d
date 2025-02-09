/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 12:28:05 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/09 18:59:08 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		close_window(game);
	if (keycode == XK_w)
		game->wall.key_up = 1;
	if (keycode == XK_s)
		game->wall.key_down = 1;
	if (keycode == XK_d)
		game->wall.key_right = 1;
	if (keycode == XK_a)
		game->wall.key_left = 1;
	if (keycode == XK_Left)
		game->wall.key_left_rotate = 1;
	if (keycode == XK_Right)
		game->wall.key_right_rotate = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->wall.key_up = 0;
	if (keycode == XK_s)
		game->wall.key_down = 0;
	if (keycode == XK_d)
		game->wall.key_right = 0;
	if (keycode == XK_a)
		game->wall.key_left = 0;
	if (keycode == XK_Left)
		game->wall.key_left_rotate = 0;
	if (keycode == XK_Right)
		game->wall.key_right_rotate = 0;
	return (0);
}

int	close_window(t_game *game)
{
	free_all_resources(game);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

void	read_keys(t_game *game)
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
	if (game->wall.key_left_rotate)
	{
		rotate_left(game);
	}
	if (game->wall.key_right_rotate)
	{
		rotate_right(game);
	}
}
