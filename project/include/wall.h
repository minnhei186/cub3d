/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:08:37 by hosokawa          #+#    #+#             */
/*   Updated: 2024/12/29 13:37:47 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 
#include "get_next_line.h"
#include "ft_printf.h"
#include "mlx.h"


//mlx
#define WIDTH 1280
#define HEIGHT 720


//rayInfo
#define PLAYERX 5.5
#define PLAYERY 5.5

#define INITDIRX 1
#define INITDIRY 0

#define INITPLANEX -0.66
#define INITPLANEY 0.66




typedef struct s_wall
{
	void *mlx;
	void *win;
	void *img;

	char *addr_pt;
	int bpp;
	int size_line;
	int endian;

	int key_up;
    	int key_down;
    	int key_left;
    	int key_right;
}t_wall;

typedef struct s_camera
{
	double pos_x;           // プレイヤーの位置X
    	double pos_y;           // プレイヤーの位置Y

    	double dir_x;           // 視線方向ベクトルX
    	double dir_y;           // 視線方向ベクトルY

    	double plane_x;         // カメラ平面ベクトルX
    	double plane_y;         // カメラ平面ベクトルY

    	double step;            // 移動速度
	

}t_camera;

//typedef struct s_rayInfo
//{
//	double posX;
//	double posY;
//
//	double dirX;
//	double dirY;
//
//	double planeX;
//	double planeY;
//
//	double time;
//	double oldTime;
//}t_rayInfo;

typedef struct s_ddaInfo
{
	int mapX;
	int mapY;

	double sideDistX;
	double sideDistY;

	double deltaDistX;
	double deltaDistY;

	double perpWallDist;
	int stepX;
	int stepY;

	int hit;
	int side;
}t_ddaInfo;

typedef struct s_game
{
    t_wall      wall;      
    t_camera    camera;    
    int         worldMap[10][10]; 

} t_game;






void wall_init(t_game *game);
void camera_init(t_game *game);
void worldMap_init(t_game *game);

void calculate_start_ddaInfo(double rayX,double rayY,double posX,double posY,t_ddaInfo *ddaInfo);
void calculate_dda_algo(int wordMap[10][10],t_ddaInfo *ddaInfo);
void calculate_perp_hight(t_ddaInfo *ddaInfo);


void my_pixel_put(int x,int y,int color,t_wall *wall);
void drawWorld(int pixel,int drawStart,int drawEnd,t_wall *wall);
void draw(int pixel,double perpWallDist,t_wall *wall);

//event
int	key_press(int keycode, t_game *game);
int 	key_release(int keycode, t_game *game);
int 	close_window(t_game *game);
void	readKeys(t_game *game);
void 	update_player(t_game *game);



