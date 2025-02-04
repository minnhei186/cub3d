/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:45:17 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/05 08:37:12 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

/* skip_whitespace.c */
static int	color_skip_whitespace(char *s, int i)
{
	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'
			|| s[i] == '\r'))
		i++;
	return (i);
}

/* parse_channel.c */
static int	parse_channel(char *line, int *i, char *err_msg)
{
	int	val;

	if (!ft_isdigit(line[*i]) && line[*i] != '-' && line[*i] != '+')
		fatal_error_exit(1, err_msg);
	val = ft_atoi(line + *i);
	while (line[*i] && (ft_isdigit(line[*i]) || line[*i] == '-'
			|| line[*i] == '+'))
		(*i)++;
	return (val);
}

/* check_char.c */
static void	check_char(char *line, int *i, char expected, char *err_msg)
{
	*i = color_skip_whitespace(line, *i);
	if (line[*i] != expected)
		fatal_error_exit(1, err_msg);
	(*i)++;
}

/* check_end.c */
static void	check_end(char *line, int i)
{
	i = color_skip_whitespace(line, i);
	if (line[i] != '\0')
		fatal_error_exit(1, "Blue channel の後に余分な文字があります。");
}

/* get_color.c */
unsigned int	get_color(char *line)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = color_skip_whitespace(line, 0);
	r = parse_channel(line, &i, "Red channel: 数字が見つかりません。");
	i = color_skip_whitespace(line, i);
	check_char(line, &i, ',', "Red channel の後にカンマがありません。");
	i = color_skip_whitespace(line, i);
	g = parse_channel(line, &i, "Green channel: 数字が見つかりません。");
	i = color_skip_whitespace(line, i);
	check_char(line, &i, ',', "Green channel の後にカンマがありません。");
	i = color_skip_whitespace(line, i);
	b = parse_channel(line, &i, "Blue channel: 数字が見つかりません。");
	check_end(line, i);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		fatal_error_exit(1, "色の値は 0～255 の範囲でなければなりません。");
	return ((r << 16) | (g << 8) | b);
}

// /*
// 	Parse a color channel value from the given line.
// 	The function advances the index past the digits.
// */
// static int	parse_color_channel(char *line, int *i)
// {
// 	int	value;

// 	value = ft_atoi(line + *i);
// 	while (ft_isdigit(line[*i]))
// 		(*i)++;
// 	return (value);
// }

// /*
// 	Check that the current character is a comma.
// 	If so, advance the index; otherwise, exit with an error.
// */
// static void	expect_comma(char *line, int *i, char *err_msg)
// {
// 	if (line[*i] == ',')
// 		(*i)++;
// 	else
// 		fatal_error_exit(1, err_msg);
// }

// /*
// 	Parse and return a color value from the given line.
// 	The format is expected as: R,G,B where R, G, B are integers.
// 	If any value is out of the 0-255 range or the format is invalid,
// 	an error is triggered.
// */
// unsigned int	get_color(char *line, int *i)
// {
// 	int	r;
// 	int	g;
// 	int	b;

// 	r = parse_color_channel(line, i);
// 	expect_comma(line, i,
//"Error: Invalid color format (missing comma after R)");
// 	g = parse_color_channel(line, i);
// 	expect_comma(line, i,
//"Error: Invalid color format (missing comma after G)");
// 	b = parse_color_channel(line, i);
// 	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
// 		fatal_error_exit(1,
//			"Error: Color values must be in range 0-255");
// 	return ((r << 16) | (g << 8) | b);
// }
