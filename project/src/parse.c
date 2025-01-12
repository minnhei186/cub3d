/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 01:19:38 by nkannan           #+#    #+#             */
/*   Updated: 2025/01/13 01:49:46 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wall.h"

// 色情報の取得
static unsigned int	get_color(char *line, int *i)
{
	unsigned int r, g, b;
	int color_count; // 取得した色の数
	color_count = 0;
	r = ft_atoi(line + *i);
	color_count++; // rを取得
	while (ft_isdigit(line[*i]))
		(*i)++;
	if (line[*i] == ',')
		(*i)++; // ','をスキップ
	else
		return (0); // ','がない場合はエラー
	g = ft_atoi(line + *i);
	color_count++; // gを取得
	while (ft_isdigit(line[*i]))
		(*i)++;
	if (line[*i] == ',')
		(*i)++; // ','をスキップ
	else
		return (0); // ','がない場合はエラー
	b = ft_atoi(line + *i);
	color_count++; // bを取得
	while (ft_isdigit(line[*i]))
		(*i)++;
	if (color_count != 3)
		return (0); // 3つ揃っていない場合はエラー
	return (r << 16 | g << 8 | b);
}

// テクスチャの読み込み
static void	load_texture(t_game *game, char *path, int tex_num)
{
	void	*img_ptr;
	int		width;
	int		height;
	char	*addr_pt;
	int		bpp;
	int		size_line;
	int		endian;

	img_ptr = mlx_xpm_file_to_image(game->wall.mlx, path, &width, &height);
	if (!img_ptr)
	{
		ft_printf("Error : invalid texture path\n"); //適切なエラー処理を追加
		exit(1);
	}
	addr_pt = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			game->texInfo.texture[tex_num][TEXWIDTH * y
				+ x] = *(unsigned int *)(addr_pt + y * size_line + x * 4);
		}
	}
	mlx_destroy_image(game->wall.mlx, img_ptr);
}

//free split
void	free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

// マップデータの解放
void	free_map_data(t_map_data *map_data)
{
	if (map_data->north_texture)
		free(map_data->north_texture);
	if (map_data->south_texture)
		free(map_data->south_texture);
	if (map_data->west_texture)
		free(map_data->west_texture);
	if (map_data->east_texture)
		free(map_data->east_texture);
	if (map_data->map)
		free_split(map_data->map);
	free(map_data);
}

// map.cubのパース (二段階ロード)
static int	parse_map(int fd, t_game *game, t_map_data *map_data)
{
	char	*line;
	char	**split;
	int		i;
	int		map_start;
	char	*temp;
    int     line_num;
    int     split_count; // splitの要素数をカウントする変数


	line_num = 0;
	map_start = 0; //mapが始まったかどうか
	while ((line = get_next_line(fd)))
	{
		i = 0;
        line_num++;
		ft_printf("Line %d: %s map_start: %d\n", line_num, line,map_start); // 行の内容と行数を表示
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (map_start)
		{
			map_data->map_height++;
			temp = ft_strtrim(line, " \n");
			if (!temp)
				return (1);
            ft_printf("map[%d]: %s\n", map_data->map_height - 1, temp);
			map_data->map = ft_realloc_double_ptr((void **)map_data->map,
													sizeof(char *)
													* (map_data->map_height
														+ 1));
			if (!map_data->map)
				return (1);
			map_data->map[map_data->map_height - 1] = temp;
			//map_data->map[map_data->map_height] = NULL; //不要
		}
		else if (line[i] && line[i] != '\n')
		{
			split = ft_split(line + i, ' ');
			if (!split)
			{
				free(line);
				return (1); // エラー処理
			}

            split_count = 0;
            while (split[split_count])
                split_count++;
            ft_printf("split count: %d\n", split_count);


            for (int j = 0; split[j]; j++)
            {
                ft_printf("split[%d]: %s\n", j, split[j]);
            }
			if (split[0] && split[1]) //split[1]があるかどうかのチェックを追加
			{
				if (!ft_strncmp(split[0], "NO", 2))
                {
					map_data->north_texture = ft_strdup(split[1]);
                    ft_printf("NO texture: %s\n", map_data->north_texture);
                }
				else if (!ft_strncmp(split[0], "SO", 2))
                {
					map_data->south_texture = ft_strdup(split[1]);
					ft_printf("SO texture: %s\n", map_data->south_texture); //追加
                }
				else if (!ft_strncmp(split[0], "WE", 2))
                {
					map_data->west_texture = ft_strdup(split[1]);
					ft_printf("WE texture: %s\n", map_data->west_texture); //追加
                }
				else if (!ft_strncmp(split[0], "EA", 2))
                {
					map_data->east_texture = ft_strdup(split[1]);
                    ft_printf("EA texture: %s\n", map_data->east_texture);
                }
				else if (!ft_strncmp(split[0], "F", 1))
                {

					game->texInfo.floor_color = get_color(split[1], &i);
                    ft_printf("Floor color: %X\n", game->texInfo.floor_color);
                }
				else if (!ft_strncmp(split[0], "C", 1))
					{
                        game->texInfo.ceilling_color = get_color(split[1], &i);
                    	ft_printf("Ceilling color: %X\n", game->texInfo.ceilling_color); //追加

                    }
			}
			free_split(split);
		}
		else if (!map_start && line[i] == '\n')
		{
			map_start = 1; //改行のみの場合、次の行からマップが始まる
			map_data->map = ft_calloc(1, sizeof(char *)); //既にcalloc済みのため不要

            if (!map_data->map)
                return (1);


		}
		free(line);
	}

    ft_printf("Total lines read: %d\n", line_num); // 全体の行数を表示

	return (0);
}

// game構造体へのデータコピー
static void	copy_map_data_to_game(t_game *game, t_map_data *map_data)
{
	int i, j;
	load_texture(game, map_data->north_texture, 0);
	load_texture(game, map_data->south_texture, 1);
	load_texture(game, map_data->west_texture, 2);
	load_texture(game, map_data->east_texture, 3);
	// game->texInfo.floor_color = map_data->floor_color;
	// game->texInfo.ceilling_color = map_data->ceilling_color;
	//worldmapにコピー(仮実装、エラー処理など必要)
	i = 0;
	while (map_data->map[i])
	{
		j = 0;
		while (map_data->map[i][j] != '\0' && map_data->map[i][j] != '\n')
		{
			if (map_data->map[i][j] == '1')
				game->worldMap[i][j] = 1;
			else if (map_data->map[i][j] == '0')
				game->worldMap[i][j] = 0;
			else if (map_data->map[i][j] == 'N')
			{
				game->worldMap[i][j] = 0;
				game->camera.pos_x = j + 0.5;
				game->camera.pos_y = i + 0.5;
				game->camera.dir_x = 0;
				game->camera.dir_y = -1;
				game->camera.plane_x = 0.66;
				game->camera.plane_y = 0;
			}
			else
				game->worldMap[i][j] = 0; //他の文字はとりあえず0で埋める
			j++;
		}
		i++;
	}
	game->map_width = j; //マップの幅と高さを設定
	game->map_height = i;

	ft_printf("map width: %d, map height: %d\n", game->map_width,game->map_height); //マップ幅、高さ表示
}

int	get_data(t_game *game, char *filepath)
{
	int			fd;
	t_map_data	*map_data;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
    {
		perror("Error opening file"); // perrorで詳細なエラーを表示するように変更
		return (1); // エラー処理
	}
	ft_printf("fd: %d\n", fd); // fdの値を表示


    // map_data = (t_map_data *)ft_calloc(1,sizeof(t_map_data)); //不要
	map_data = ft_calloc(1, sizeof(t_map_data)); // map_dataのメモリ確保

    if (!map_data)
       return (1);


	if (parse_map(fd, game, map_data)) //パース処理を呼び出し
	{
		free_map_data(map_data);
		return (1);
	}

	copy_map_data_to_game(game, map_data); // game構造体へのデータコピー
	free_map_data(map_data);               // map_dataのメモリ解放
	close(fd);
	return (0);
}
