/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:08:37 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/11 17:07:34 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALL_H
# define WALL_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <X11/keysym.h>
# include <errno.h>
# include <math.h>
# include <stdio.h>

// mlx
# define WIDTH 1280
# define HEIGHT 720

// texture
# define TEXWIDTH 50
# define TEXHEIGHT 50

// rayInfo
# define PLAYERX 1.5
# define PLAYERY 1.5

// draw_wall
# define WEST_INDEX 3
# define EAST_INDEX 2
# define SOUTH_INDEX 1
# define NORTH_INDEX 0

// event
# define ESC_KEY 53

# define INITPLANEX -0.66
# define INITPLANEY 0.66

// mlx

typedef struct s_wall
{
	void			*mlx;
	void			*win;
	void			*img;

	char			*addr_pt;
	int				bpp;
	int				size_line;
	int				endian;

	int				key_up;
	int				key_down;
	int				key_left;
	int				key_right;
	int				key_left_rotate;
	int				key_right_rotate;

}					t_wall;

// load_data

typedef struct s_img_data
{
	void			*img;
	char			*addr;
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	int				height;
}					t_img_data;

typedef struct s_map_data
{
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	char			**map;
	int				map_width;
	int				map_height;

	unsigned int	floor_color;
	unsigned int	ceilling_color;

	int				player_x;
	int				player_y;
	char			player_dir;
	int				player_found;
}					t_map_data;

typedef struct s_use_data
{
	int				texture[4][TEXWIDTH * TEXHEIGHT];
	int				**map;

	int				map_width;
	int				map_height;

	unsigned int	floor_color;
	unsigned int	ceilling_color;

	double			player_x;
	double			player_y;

	double			player_dir_x;
	double			player_dir_y;

	double			player_plane_x;
	double			player_plane_y;
}					t_use_data;

// game
typedef struct s_camera
{
	double			pos_x;
	double			pos_y;

	double			dir_x;
	double			dir_y;

	double			plane_x;
	double			plane_y;

	double			step;

}					t_camera;

typedef struct s_dda_info
{
	int				map_x;
	int				map_y;

	double			side_dist_x;
	double			side_dist_y;

	double			delta_dist_x;
	double			delta_dist_y;

	double			perp_wall_dist;
	int				step_x;
	int				step_y;

	int				hit;
	int				side;
}					t_dda_info;

typedef struct s_tex_info
{
	int				tex_x;
	int				(*texture)[TEXWIDTH * TEXHEIGHT];
	unsigned int	floor_color;
	unsigned int	ceilling_color;

}					t_tex_info;

typedef struct s_game
{
	t_wall			wall;
	t_camera		camera;
	t_dda_info		dda_info;
	t_tex_info		tex_info;

	int				**map;
	int				map_height;
	int				map_width;
	int				world_map[10][10];

}					t_game;

typedef struct s_draw
{
	int				draw_start;
	int				draw_end;
	int				line_height;

	double			step;
	double			tex_pos;
}					t_draw;

typedef struct s_parse_data
{
	t_map_data		*map_data;
	int				*map_started;
	int				*texture_count;
}					t_parse_data;

// validation_utils
char				get_cell(const char *row, int j);

// validation
int					has_cub_extention(const char *filename);
void				validate_map_closed(t_map_data *map_data);
int					validate_map_line(const char *line);
void				validate_map_data_integrity(t_map_data *map_data);

// free
void				free_all_resources(t_game *game);
void				free_map_data(t_map_data *map_data);

// parse_map_utils_error
void				empty_row_error(char *trimmed);
void				invalid_char_error(char *trimmed);

// parse_map_utils.c
int					handle_map_line(t_parse_data *d, char *line);

// utils

double				ft_abs(double a);
void				*ft_realloc_double_ptr(void **ptr, size_t size);

// error
void				fatal_error_exit(int error_status, char *error_msg);

// --- load_data関連の関数プロトタイプ ---
void				get_data(t_map_data *map_data, const char *filepath);
int					parse_map(int fd, t_map_data *map_data);
int					parse_texture_or_color(t_map_data *m, char *id, char *value,
						int *tc);
int					line_starts_with_texture_or_color(const char *line);
int					add_map_line(t_map_data *map_data, const char *line);

// --- load_data_utils関連の関数プロトタイプ ---
unsigned int		get_color(char *line);
void				free_split(char **split);
void				free_map_data(t_map_data *map_data);
int					is_map_char(char c);
int					is_player_char(char c);
void				skip_whitespace(const char *line, int *i);
void				remove_comment(char *line, int start_index);
int					is_map_line(const char *line, int i);

// process_line_error.c
int					check_trimmed(char *trimmed, int *map_started);
int					check_map_line_end(t_parse_data *d, char *line, int pos);

// process_lines_error.c
void				encountered_empty_error(char *line);
int					handle_empty_line(t_parse_data *data, char *trimmed,
						char *line, int *encountered_empty);
int					process_line_wrapper(t_parse_data *data,
						int *encountered_empty, char *line);

// parser_line.c
int					process_line(t_parse_data *d, char *line);
int					process_lines(int fd, t_parse_data *data);

// map_data
void				map_data_init(t_map_data *map_data);

// set_direction
void				north_direction(t_use_data *use_data);
void				south_direction(t_use_data *use_data);
void				west_direction(t_use_data *use_data);
void				east_direction(t_use_data *use_data);

// use_data
void				use_data_init(t_use_data *use_data);
void				translate_data(void **mlx, t_use_data *use_data,
						const t_map_data *map_data);

// load_texture_for_use_data
void				load_texture(void *mlx, int *texture, char *path);

// copy_data

void				copy_data(t_game *game, t_use_data *use_data);

// init
void				wall_init(t_game *game);
void				camera_init(t_game *game);
void				ddaInfo_init(t_game *game);
void				worldMap_init(t_game *game);
void				texInfo_init(t_game *game);
void				game_init(t_game *game);

// dda
void				calculate_start_dda_info(double ray_x, double ray_y,
						t_game *game);
void				calculate_dda_algo(int **map, t_dda_info *dda_info);
void				calculate_perp_hight(t_dda_info *dda_info);

// draw_info
void				init_draw_info(t_draw *draw);
void				get_draw_wall_info(t_draw *draw, double perp_wall_dist);
void				get_draw_texture_info(t_draw *draw);

// draw
void				my_pixel_put(int x, int y, int color, t_wall *wall);
void				clear_window(t_wall *wall);
void				draw_world(int pixel, t_draw *draw, t_game *game);
void				draw(int pixel, t_game *game);

// event
int					key_press(int keycode, t_game *game);
int					key_release(int keycode, t_game *game);
int					close_window(t_game *game);
void				read_keys(t_game *game);
void				update_player(t_game *game);

// move
void				move_forward(t_game *game);
void				move_back(t_game *game);
void				move_right(t_game *game);
void				move_left(t_game *game);
void				rotate_right(t_game *game);
void				rotate_left(t_game *game);

// texture
void				texture_init(t_game *game);
void				calculate_texture_information(double ray_x, double ray_y,
						t_game *game);

#endif
