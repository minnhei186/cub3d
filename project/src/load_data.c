
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

//utils
static void	skip_whitespace(const char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

static void	remove_comment(char *line, int start_index)
{
	int	j;

	j = 0;
	while (line[start_index + j] != '\0')
	{
		if (line[start_index + j] == '#')
		{
			line[start_index + j] = '\0';
			break ;
		}
		j++;
	}
}

static int	is_map_line(const char *line, int i)
{
	return (line[i] && (is_map_char(line[i]) || is_player_char(line[i])));
}

//マップ行追加
static int	add_map_line(t_map_data *map_data, const char *line)
{
	char	*trimmed;
	int		len;
	int j;

	trimmed = ft_strtrim(line, " \n");
	if (!trimmed)
		return (-1);
	map_data->map_height++;
	map_data->map = ft_realloc_double_ptr((void **)map_data->map, sizeof(char *)
			* (map_data->map_height + 1));
	if (!map_data->map)
	{
		free(trimmed);
		return (-1);
	}
	map_data->map[map_data->map_height - 1] = trimmed;
	{
		len = ft_strlen(trimmed);
		if (len > map_data->map_width)
			map_data->map_width = len;
	}

	// ▼ プレイヤー文字(N, S, E, W)を探して、見つけたら座標と向きを記録
	j = 0;
	while (trimmed[j])
	{
		if (is_player_char(trimmed[j]))  // 例: 'N','S','E','W'を判定
		{
			// すでにプレイヤーが見つかっている場合はエラーにするなどの処理も可能
			if (map_data->player_found)
			{
				ft_printf("Error: More than one player start found.\n");
				return (-1); // 必要に応じて処理を分岐
			}
			map_data->player_dir = trimmed[j];
			map_data->player_x = j;
			map_data->player_y = map_data->map_height - 1;
			map_data->player_found = 1;

			// マップ上ではプレイヤー位置を'0'などに置き換えることが多い
			// （後で移動可能床として扱うため）
			trimmed[j] = '0';
		}
		j++;
	}

	return (0);
}

// テクスチャ・色設定用サブ関数
static void	set_texture(char **dst, char *src, int *count)
{
	free(*dst);
	*dst = ft_strtrim(src, " \n\t\r");
	(*count)++;
}

static void	set_color(unsigned int *dst, char *src, int *col_idx)
{
	*dst = get_color(src, col_idx);
}

// テクスチャ or 色パース
static int	parse_texture_or_color(t_map_data *m, char **sp, int *tc, int *ci)
{
	if (!sp[0] || !sp[1])
		return (0);
	if (!ft_strncmp(sp[0], "NO", 2))
		set_texture(&m->north_texture, sp[1], tc);
	else if (!ft_strncmp(sp[0], "SO", 2))
		set_texture(&m->south_texture, sp[1], tc);
	else if (!ft_strncmp(sp[0], "WE", 2))
		set_texture(&m->west_texture, sp[1], tc);
	else if (!ft_strncmp(sp[0], "EA", 2))
		set_texture(&m->east_texture, sp[1], tc);
	else if (!ft_strncmp(sp[0], "F", 1))
		set_color(&m->floor_color, sp[1], ci);
	else if (!ft_strncmp(sp[0], "C", 1))
		set_color(&m->ceilling_color, sp[1], ci);
	return (0);
}

// マップ行/設定行の処理
static int	handle_map_line(t_map_data *map_data, char *line, int *tex_count)
{
	if (*tex_count < 4)
	{
		ft_printf("Error: Texture paths must be set before map data.\n");
		free(line);
		return (1);
	}
	if (add_map_line(map_data, line) == -1)
	{
		free(line);
		return (1);
	}
	return (0);
}

static int	handle_config_line(t_map_data *m, char *line, int pos,
		int map_started, int *tex_count)
{
	char	**split;

	if (map_started)
	{
		ft_printf("Error: Found additional data after map lines.\n");
		free(line);
		return (1);
	}
	split = ft_split(line + pos, ' ');
	if (!split)
	{
		free(line);
		return (1);
	}
	if (parse_texture_or_color(m, split, tex_count, &pos))
	{
		free_split(split);
		free(line);
		return (1);
	}
	free_split(split);
	return (0);
}

static int	line_starts_with_texture_or_color(const char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		return (1);
	if (!ft_strncmp(line, "SO", 2))
		return (1);
	if (!ft_strncmp(line, "WE", 2))
		return (1);
	if (!ft_strncmp(line, "EA", 2))
		return (1);
	if (!ft_strncmp(line, "F", 1))
		return (1);
	if (!ft_strncmp(line, "C", 1))
		return (1);
	return (0);
}

//メインのパース関数
int	parse_map(int fd, t_map_data *map_data)
{
	char	*line;
	int		texture_count;
	int		map_started;
	int		pos;

	texture_count = 0;
	map_started = 0;
	while ((line = get_next_line(fd)))
	{
		pos = 0;
		remove_comment(line, 0);
		skip_whitespace(line, &pos);
		if (!line[pos])
		{
			free(line);
			continue ;
		}
		if (line_starts_with_texture_or_color(&line[pos]))
		{
			if (map_started)
			{
				ft_printf("Error: Found additional data after map lines.\n");
				free(line);
				return (1);
			}
			if (handle_config_line(map_data, line, pos, map_started,
					&texture_count))
				return (1);
		}
		else if (is_map_line(line, pos))
		{
			if (handle_map_line(map_data, line, &texture_count))
				return (1);
			map_started = 1;
		}
		free(line);
	}
	return (0);
}
//ファイルを開いてパース
int	get_data(t_map_data *map_data, const char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	if (parse_map(fd, map_data))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
