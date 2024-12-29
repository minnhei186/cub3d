/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 12:28:05 by hosokawa          #+#    #+#             */
/*   Updated: 2024/12/29 13:45:57 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"


int key_press(int keycode, t_game *game)
{
    if (keycode == 126 || keycode == 13) // 上矢印 or 'W'
        game->wall.key_up = 1;
    if (keycode == 125 || keycode == 1) // 下矢印 or 'S'
        game->wall.key_down = 1;
    if (keycode == 124 || keycode == 2) // 右矢印 or 'D'
        game->wall.key_right = 1;
    if (keycode == 123 || keycode == 0) // 左矢印 or 'A'
        game->wall.key_left = 1;
    return (0);
}

int key_release(int keycode, t_game *game)
{
    if (keycode == 126 || keycode == 13) // 上矢印 or 'W'
        game->wall.key_up = 0;
    if (keycode == 125 || keycode == 1) // 下矢印 or 'S'
        game->wall.key_down = 0;
    if (keycode == 124 || keycode == 2) // 右矢印 or 'D'
        game->wall.key_right = 0;
    if (keycode == 123 || keycode == 0) // 左矢印 or 'A'
        game->wall.key_left = 0;
    return (0);
}

int close_window(t_game *game)
{
    mlx_destroy_window(game->wall.mlx, game->wall.win);
    exit(EXIT_SUCCESS);
    return (EXIT_SUCCESS);
}

void readKeys(t_game *game)
{
    // 押下
    mlx_hook(game->wall.win, 2, 1L << 0, (int (*)())key_press, game);
    // 解放
    mlx_hook(game->wall.win, 3, 1L << 1, (int (*)())key_release, game);
    // ウィンドウの削除
    mlx_hook(game->wall.win, 17, 0L, (int (*)())close_window, game);
}

void update_player(t_game *game)
{
    if (game->wall.key_up)
        ft_printf("Moving forward\n");
    if (game->wall.key_down)
        ft_printf("Moving backward\n");
    if (game->wall.key_left)
        ft_printf("Rotating left\n");
    if (game->wall.key_right)
        ft_printf("Rotating right\n");
}


