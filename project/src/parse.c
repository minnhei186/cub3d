/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 01:19:38 by nkannan           #+#    #+#             */
/*   Updated: 2025/01/13 02:23:18 by nkannan          ###   ########.fr       */
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

	if (!path) // pathがNULLの場合のエラー処理を追加
	{
		ft_printf("Error: Texture path is NULL.\n");
		exit(1);
	}

	ft_printf("Loading texture %d from '%s'\n", tex_num, path);

	img_ptr = mlx_xpm_file_to_image(game->wall.mlx, path, &width, &height);

	if (!img_ptr)
	{
		ft_printf("Error loading texture '%s': ", path);
		perror("");  // perrorでOSのエラーメッセージを表示
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

// マップ関連の文字か判定
static int is_map_char(char c)
{
    // マップデータとして有効な文字のみを許可
    int result = (c == '0' || c == '1' || c == ' ');
    ft_printf("DEBUG: is_map_char checking '%c': %s\n", c, result ? "true" : "false");
    return result;
}

// プレイヤーの開始位置を示す文字かどうかを判定
static int is_player_char(char c)
{
    return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}


// map.cubのパース (二段階ロード)
static int	parse_map(int fd, t_game *game, t_map_data *map_data)
{
	char	*line;
	char	**split;
	int		i;
	int		map_start;
    int     line_num = 0;
    int		split_count;
	int		texture_path_set;
	char	*temp;


	map_start = 0;
	texture_path_set = 0; //初期化
    // map_data の初期化
	map_data->north_texture = NULL;
	map_data->south_texture = NULL;
	map_data->west_texture = NULL;
	map_data->east_texture = NULL;
    map_data->map_width = 0;
    map_data->map_height = 0;


	map_data->map = ft_calloc(1, sizeof(char *)); //マップデータの前にメモリ確保
	if (!map_data->map)
		return (1);
	while ((line = get_next_line(fd)))
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		line_num++;
        ft_printf("Line %d: %s map_start: %d\n", line_num, line, map_start); // 行の内容と行数を表示

		// マップデータの開始を検出（最初の数字の1が現れた時）
		if (line[i] && (is_map_char(line[i]) || is_player_char(line[i])) && line[i] != ' ' && !ft_strncmp(&line[i], "1", 1))  // マップは必ず1で始まる
		{
            ft_printf("DEBUG: Checking map char '%c' at position %d (texture_path_set: %d)\n", 
                     line[i], i, texture_path_set);
            // テクスチャパスが全て設定されているか確認
            if (texture_path_set != 4)
            {
                ft_printf("Error: Texture paths must be set before map data.\n");
                ft_printf("DEBUG: Current texture paths:\n");
                ft_printf("  NO: %s\n", map_data->north_texture ? map_data->north_texture : "NOT SET");
                ft_printf("  SO: %s\n", map_data->south_texture ? map_data->south_texture : "NOT SET");
                ft_printf("  WE: %s\n", map_data->west_texture ? map_data->west_texture : "NOT SET");
                ft_printf("  EA: %s\n", map_data->east_texture ? map_data->east_texture : "NOT SET");
                return (1);
            }
            map_start = 1;

            map_data->map_height++;

            temp = ft_strtrim(line, " \n");
            if (!temp)
                return (free(line),1);


            map_data->map = ft_realloc_double_ptr((void **)map_data->map, sizeof(char *) * (map_data->map_height + 1));

            if (!map_data->map)
                return (free(line),free(temp), 1);
            map_data->map[map_data->map_height - 1] = temp;



            int len = ft_strlen(map_data->map[map_data->map_height - 1]);
            if (len > map_data->map_width)
                map_data->map_width = len;



		}
		else if (line[i] && line[i] != '\n')
		{
		    int comment_start = -1;
            for (int j = 0; line[i + j] != '\0'; j++)
            {
                if (line[i + j] == '#')
                {
                    comment_start = j; //コメント開始位置を保存
                    break;
                }
            }
            if (comment_start != -1)
            {
                line[i + comment_start] = '\0'; //コメント部分を'\0'で終端
            }




            split = ft_split(line + i, ' ');
			if (!split)
                return (free(line), 1); // エラー処理


            split_count = 0;
            while (split && split[split_count])
                split_count++;
            ft_printf("split count: %d\n", split_count);


            for (int j = 0; split && split[j]; j++)
            {
                ft_printf("split[%d]: %s\n", j, split[j]);
            }


			if (split && split[0] && split[1] && !map_start)  // map_startがfalseの時のみテクスチャを処理
			{
				if (!ft_strncmp(split[0], "NO", 2))
                {
                    if (map_data->north_texture)
                        free(map_data->north_texture);
                    map_data->north_texture = ft_strtrim(split[1], " \n\t\r");
                    ft_printf("NO texture (in map_data): %s\n", map_data->north_texture);
                    texture_path_set++;
                    ft_printf("Texture paths set: %d\n", texture_path_set);
                }
				else if (!ft_strncmp(split[0], "SO", 2))
                {
                    map_data->south_texture = ft_strtrim(split[1], " \n\t\r");
					ft_printf("SO texture (in map_data): %s\n", map_data->south_texture);
                    texture_path_set++;
                    ft_printf("Texture paths set: %d\n", texture_path_set);
                }
				else if (!ft_strncmp(split[0], "WE", 2))
                {
                    map_data->west_texture = ft_strtrim(split[1], " \n\t\r");
					ft_printf("WE texture (in map_data): %s\n", map_data->west_texture);
                    texture_path_set++;
                    ft_printf("Texture paths set: %d\n", texture_path_set);
                }
				else if (!ft_strncmp(split[0], "EA", 2))
                {
                    map_data->east_texture = ft_strtrim(split[1], " \n\t\r");
                    ft_printf("EA texture (in map_data): %s\n", map_data->east_texture);
                    texture_path_set++;
                    ft_printf("Texture paths set: %d\n", texture_path_set);
                }
				else if (!ft_strncmp(split[0], "F", 1))
                {
					game->texInfo.floor_color = get_color(split[1], &i); //修正
                    ft_printf("Floor color: %X\n", game->texInfo.floor_color);
                }
				else if (!ft_strncmp(split[0], "C", 1))
					{
                        game->texInfo.ceilling_color = get_color(split[1], &i); //修正
                    	ft_printf("Ceilling color: %X\n", game->texInfo.ceilling_color);

                    }
			}
			free_split(split);
		}

        free(line); //free(line)の位置を修正

	}

    ft_printf("Total lines read: %d\n", line_num);
    //全てのテクスチャパスが設定されているかチェック
    if (texture_path_set != 4)
    {
        ft_printf("Error: Not all texture paths were set.\n");
        return (1);
    }


    //マップの高さと幅が0以上であることを確認する
    if(map_data->map_height <= 0 || map_data->map_width <= 0)
        return (1);



	return (0);
}

// game構造体へのデータコピー
static void	copy_map_data_to_game(t_game *game, t_map_data *map_data)
{
	int	i;
	int	j;
    int player_set = 0;


    if (map_data->north_texture)
	    load_texture(game, map_data->north_texture, 0);
    if (map_data->south_texture)
	    load_texture(game, map_data->south_texture, 1);
    if (map_data->west_texture)
	    load_texture(game, map_data->west_texture, 2);
    if (map_data->east_texture)
	    load_texture(game, map_data->east_texture, 3);





    i = 0;
	while (i < map_data->map_height && i < 10)
	{
		j = 0;
		while (j < map_data->map_width && j < 10)
		{
            if (j < (int)ft_strlen(map_data->map[i]))
            {


                if (map_data->map[i][j] == '1')
                    game->worldMap[i][j] = 1;
                else if (map_data->map[i][j] == '0' || map_data->map[i][j] == ' ')
                    game->worldMap[i][j] = 0;
                else if (map_data->map[i][j] == 'N' || map_data->map[i][j] == 'S' ||
                         map_data->map[i][j] == 'W' || map_data->map[i][j] == 'E')
                {

                    if (player_set) //既にプレイヤーが設定されている場合はエラー
                    {
                        ft_printf("Error: Multiple player starting positions defined.\n");
                        exit(1);

                    }
                    game->worldMap[i][j] = 0; //プレイヤーの初期位置は床とする
                    game->camera.pos_x = j + 0.5;
                    game->camera.pos_y = i + 0.5;
                    if (map_data->map[i][j] == 'N')
                    {
                        game->camera.dir_x = 0;
                        game->camera.dir_y = -1;
                        game->camera.plane_x = 0.66;
                        game->camera.plane_y = 0;

                    }
                    else if (map_data->map[i][j] == 'S')
                    {
                        game->camera.dir_x = 0;
                        game->camera.dir_y = 1;
                        game->camera.plane_x = -0.66;
                        game->camera.plane_y = 0;


                    }

                     else if (map_data->map[i][j] == 'E')
                    {
                        game->camera.dir_x = 1;
                        game->camera.dir_y = 0;
                        game->camera.plane_x = 0;
                        game->camera.plane_y = 0.66;


                    }
                    else if (map_data->map[i][j] == 'W')
                    {
                        game->camera.dir_x = -1;
                        game->camera.dir_y = 0;
                        game->camera.plane_x = 0;
                        game->camera.plane_y = -0.66;


                    }

                    player_set++;
                }

				else // 有効な文字ではない場合はエラーとする
                {
					ft_printf("Error: Invalid character in map: '%c'\n", map_data->map[i][j]);
					exit(1);

                }

            }
            else
                game->worldMap[i][j] = 0; //範囲外の値を0で埋める

			j++;

		}

        // マップデータの残りの部分を空白で埋める
        while (j < 10)
        {
            game->worldMap[i][j] = 0;
            j++;
        }

		i++;

	}
	game->map_width = map_data->map_width; //マップの幅と高さを設定
	game->map_height = map_data->map_height;

	ft_printf("map width: %d, map height: %d\n", game->map_width,
			game->map_height); //マップ幅、高さ表示


    //プレイヤーが設定されていない場合はエラー
    if (!player_set)
    {

        ft_printf("Error: No player starting position defined.\n");
        exit(1);
    }
}

int	get_data(t_game *game, char *filepath)
{
	int			fd;
	t_map_data	*map_data;

	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		ft_printf("Current working directory: %s\n", cwd);
	}

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
