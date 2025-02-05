/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:42:22 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/05 10:43:29 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

static int	color_skip_ws(char *s, int i)
{
	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'
			|| s[i] == '\r'))
		i++;
	return (i);
}

static int	parse_channel(char *line, int *i, char *msg)
{
	char	buf[16];
	int		bi;

	bi = 0;
	*i = color_skip_ws(line, *i);
	while (line[*i] && line[*i] != ',')
	{
		if (ft_isdigit(line[*i]))
		{
			if (bi < 15)
				buf[bi++] = line[*i];
			else
				fatal_error_exit(1, "Number too long.");
		}
		else if (!(line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n'
				|| line[*i] == '\r'))
			fatal_error_exit(1, msg);
		(*i)++;
	}
	buf[bi] = '\0';
	if (bi == 0)
		fatal_error_exit(1, msg);
	return (ft_atoi(buf));
}

static void	check_comma(char *line, int *i, char *msg)
{
	if (line[*i] != ',')
		fatal_error_exit(1, msg);
	(*i)++;
}

unsigned int	get_color(char *line)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	r = parse_channel(line, &i, "Invalid R channel");
	check_comma(line, &i, "Missing comma after R");
	g = parse_channel(line, &i, "Invalid G channel");
	check_comma(line, &i, "Missing comma after G");
	b = parse_channel(line, &i, "Invalid B channel");
	i = color_skip_ws(line, i);
	if (line[i])
		fatal_error_exit(1, "Extra characters after B channel");
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		fatal_error_exit(1, "Color must be in [0..255]");
	return ((r << 16) | (g << 8) | b);
}
