/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:30:57 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/14 15:14:01 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

//// テクスチャの読み込み
//static void	load_texture(t_game *game, char *path, int tex_num)
//{
//	char	abs_path[1024];
//	void	*img_ptr;
//	int		width;
//	int		height;
//	char	*addr_pt;
//	int		bpp;
//	int		size_line;
//	int		endian;
//
//	// realpath()で絶対パスを取得
//	if (!realpath(path, abs_path))
//	{
//		ft_printf("Error: realpath failed: %s\n", strerror(errno));
//		exit(1);
//	}
//
//	// XPMファイルを読み込み
//	img_ptr = mlx_xpm_file_to_image(game->wall.mlx, abs_path, &width, &height);
//	if (!img_ptr)
//	{
//		ft_printf("Error: Failed to load XPM image: %s\n", abs_path);
//		exit(1);
//	}
//
//	// 画像データ取得
//	addr_pt = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
//	if (!addr_pt)
//	{
//		ft_printf("Error: mlx_get_data_addr failed.\n");
//		mlx_destroy_image(game->wall.mlx, img_ptr);
//		exit(1);
//	}
//
//	// 画像ピクセルをテクスチャ配列にコピー
//	for (int y = 0; y < height; y++)
//	{
//		for (int x = 0; x < width; x++)
//		{
//			game->texInfo.texture[tex_num][TEXWIDTH * y + x]
//				= *(unsigned int *)(addr_pt + (y * size_line) + (x * (bpp / 8)));
//		}
//	}
//
//	// 使い終わった画像を破棄
//	mlx_destroy_image(game->wall.mlx, img_ptr);
//}
