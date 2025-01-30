/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:32:09 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/29 13:47:30 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"


void calculate_texture_information(double rayX, double rayY, t_game *game)
{
    double  wallX;
    int     texX;

    // 1. side == 0 (垂直壁) なら y座標で計算、side == 1 (水平壁) なら x座標で計算
    if (game->ddaInfo.side == 0)
        wallX = game->camera.pos_y + game->ddaInfo.perpWallDist * rayY;
    else // side == 1
        wallX = game->camera.pos_x + game->ddaInfo.perpWallDist * rayX;

    // 2. 小数部分だけ取り出し (0.0 <= wallX < 1.0 が理想)
    wallX -= floor(wallX);

    // 3. 浮動小数点誤差で 1.0 を超えたり負になったりしないようクリップ
    // if (wallX < 0.0)
    //     wallX = 0.0;
    // if (wallX >= 1.0 - eps)
    //     wallX = 1.0 - eps;
	
	// ★修正: 浮動小数点誤差で -0.0001 や 1.000001 等になる可能性を排除
    if (wallX < 0.0)
        wallX = 0.0; 
    if (wallX > 1.0)
        wallX = 1.0;


    // 4. テクスチャ X座標を計算
    texX = (int)(wallX * (double)TEXWIDTH);
	
	// // 5. % 演算で万一の範囲外アクセスを防ぎ、負値なら補正
    // texX = texX % TEXWIDTH;
    // if (texX < 0)
    //     texX += TEXWIDTH;
	
	// ★修正: texX を [0, TEXWIDTH-1] に収める (オーバーフロー防止)
    if (texX < 0)
        texX = 0;
    else if (texX >= TEXWIDTH)
        texX = TEXWIDTH - 1;

    

    // // 6. “鏡面処理” (左右反転) - 壁の向き次第で調整
    // if (game->ddaInfo.side == 0 && rayX > 0)
    //     texX = TEXWIDTH - texX - 1;
    // if (game->ddaInfo.side == 1 && rayY > 0)
    //     texX = TEXWIDTH - texX - 1;
	
	// ★修正: flip 条件を好みで見直し
    //   side=0 && rayX>0 → EAST向きの時にテクスチャ左右反転
    //   side=1 && rayY>0 → SOUTH向きの時にテクスチャ左右反転 (例)
    if (game->ddaInfo.side == 0 && rayX > 0)
        texX = TEXWIDTH - texX - 1;
    else if (game->ddaInfo.side == 1 && rayY > 0)
        texX = TEXWIDTH - texX - 1;

    // 7. 計算結果を格納
    game->texInfo.texX = texX;
}

//mk01
//void calculate_texture_information(double rayX, double rayY, t_game *game)
//{
//    double  wallX;
//    int     texX;
//
//
//    if (game->ddaInfo.side == 0)
//        wallX = game->camera.pos_y + game->ddaInfo.perpWallDist * rayY;
//    else // side == 1
//        wallX = game->camera.pos_x + game->ddaInfo.perpWallDist * rayX;
//
//    // 小数部分だけ取り出す (0.0 <= wallX < 1.0)
//    wallX -= floor(wallX);
//
//    // テクスチャ X座標の計算
//    texX = (int)(wallX * TEXWIDTH);
//
//    // 負値なら補正 (通常は負値にならないはずですが、念のため)
//    texX = texX % TEXWIDTH;
//    if (texX < 0)
//        texX += TEXWIDTH;
//
//    // “鏡面処理” (左右反転) - 好みに応じて条件を変更
//    if (game->ddaInfo.side == 0 && rayX > 0)
//        texX = TEXWIDTH - texX - 1;
//    if (game->ddaInfo.side == 1 && rayY > 0)
//        texX = TEXWIDTH - texX - 1;
//
//    // 計算結果を格納
//    game->texInfo.texX = texX;
//}

//mk00
// void	calculate_texture_information(double rayX, double rayY, t_game *game)
// {
// 	double	wallX;
// 	int		texX;

// 	game->texInfo.texNum = game->map[game->ddaInfo.mapX][game->ddaInfo.mapY]
// 		- 1;
// 	if (game->ddaInfo.side == 0)
// 		wallX = game->camera.pos_y + game->ddaInfo.perpWallDist * rayY;
// 	if (game->ddaInfo.side == 1)
// 		wallX = game->camera.pos_x + game->ddaInfo.perpWallDist * rayX;
// 	wallX -= floor(wallX);
// 	//鏡面処理
// 	texX = (int)(wallX * (double)TEXWIDTH);
// 	game->texInfo.texX = texX;
// 	if (game->ddaInfo.side == 0 && rayX > 0)
// 		game->texInfo.texX = TEXWIDTH - texX - 1;
// 	if (game->ddaInfo.side == 1 && rayY > 0)
// 		game->texInfo.texX = TEXWIDTH - texX - 1;
// }
