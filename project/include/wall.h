/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:08:37 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/13 15:14:26 by hosokawa         ###   ########.fr       */
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

typedef struct s_texInfo
{
	int texNum;
	int texX;

	int texture[2][TEXWIDTH*TEXHEIGHT];
}t_texInfo;


typedef struct s_game
{
    t_wall      wall;      
    t_camera    camera;    
    t_ddaInfo  	ddaInfo;
    t_texInfo   texInfo;

    int         worldMap[10][10]; 
    

} t_game;


typedef struct s_draw
{
	int drawStart;
	int drawEnd;
	int lineHeight;

	double step;
	double texPos;
}t_draw;




//error
void fatal_error_exit(int error_status,char *error_msg);

//init
void wall_init(t_game *game);
void camera_init(t_game *game);
void ddaInfo_init(t_game *game);
void worldMap_init(t_game *game);
void texInfo_init(t_game *game);
void game_init(t_game *game);

//dda
void calculate_start_ddaInfo(double rayX,double rayY,double posX,double posY,t_ddaInfo *ddaInfo);
void calculate_dda_algo(int wordMap[10][10],t_ddaInfo *ddaInfo);
void calculate_perp_hight(t_ddaInfo *ddaInfo);

//draw_info
void init_draw_info(t_draw *draw);
void get_draw_wall_info(t_draw *draw,double perpWallDist);
void get_draw_texture_info(t_draw *draw);


//draw
void my_pixel_put(int x,int y,int color,t_wall *wall);
void clear_window(t_wall *wall);
void drawWorld(int pixel,t_draw *draw,t_game *game);
void draw(int pixel,t_game *game);

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

//texture
void texture_init(t_game *game);
void calculate_texture_information(double rayX,double rayY,t_game *game);

