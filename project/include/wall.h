/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:08:37 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/03 13:54:30 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 
#include "get_next_line.h"
#include "ft_printf.h"
#include "mlx.h"
#include <stdio.h>
#include <math.h>


//mlx
#define WIDTH 1280
#define HEIGHT 720

//texture
#define TEXWIDTH 64
#define TEXHEIGHT 64


//rayInfo
#define PLAYERX 5.5
#define PLAYERY 5.5

#define INITDIRX 0
#define INITDIRY -1

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
	double pos_x;           
    	double pos_y;           

    	double dir_x;           
    	double dir_y;           

    	double plane_x;         
    	double plane_y;         

    	double step;            
	

}t_camera;


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

    int		texture[TEXWIDTH*TEXHEIGHT];
    int         worldMap[10][10]; 
    

} t_game;






//init
void wall_init(t_game *game);
void camera_init(t_game *game);
void worldMap_init(t_game *game);
void texture_init(t_game *game);


//dda
void calculate_start_ddaInfo(double rayX,double rayY,double posX,double posY,t_ddaInfo *ddaInfo);
void calculate_dda_algo(int wordMap[10][10],t_ddaInfo *ddaInfo);
void calculate_perp_hight(t_ddaInfo *ddaInfo);


//draw
void my_pixel_put(int x,int y,int color,t_wall *wall);
void clear_window(t_wall *wall);
void drawWorld(int pixel,int drawStart,int drawEnd,t_wall *wall);
void draw(int pixel,double perpWallDist,t_wall *wall);

//event
int	key_press(int keycode, t_game *game);
int 	key_release(int keycode, t_game *game);
int 	close_window(t_game *game);
void	readKeys(t_game *game);
void 	update_player(t_game *game);

//move
void move_forward(t_game *game);
void move_back(t_game *game);
void move_right(t_game *game);
void move_left(t_game *game);


