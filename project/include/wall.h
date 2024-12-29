/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:08:37 by hosokawa          #+#    #+#             */
/*   Updated: 2024/12/29 11:43:48 by hosokawa         ###   ########.fr       */
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
}t_wall;

typedef struct s_camera
{
	float camera_x;
	float camera_y;

	float camera_direct_x;
	float camera_direct_y;

	float step;
}t_camera;

typedef struct s_rayInfo
{
	double posX;
	double posY;

	double dirX;
	double dirY;

	double planeX;
	double planeY;

	double time;
	double oldTime;
}t_rayInfo;

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






void wall_init(t_wall *wall);
void rayInfo_init(t_rayInfo *rayInfo);
void worldMap_init(int worldMap[10][10]);

void calculate_start_ddaInfo(double rayX,double rayY,double posX,double posY,t_ddaInfo *ddaInfo);
void calculate_dda_algo(int wordMap[10][10],t_ddaInfo *ddaInfo);
void calculate_perp_hight(t_ddaInfo *ddaInfo);


void my_pixel_put(int x,int y,int color,t_wall *wall);
void drawWorld(int pixel,int drawStart,int drawEnd,t_wall *wall);
void draw(int pixel,double perpWallDist,t_wall *wall);



