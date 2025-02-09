/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:23:24 by dhosokaw          #+#    #+#             */
/*   Updated: 2025/02/09 18:38:57 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/select.h>
# include <unistd.h>
# include <stdint.h>

char	*get_next_line(int fd);

int		gnl_strlen(char *str);
char	*gnl_strchr(char *str, char find_c);
char	*gnl_strjoin(char *left_str, char *right_str);
void	*gnl_calloc(size_t count, size_t size);
char	*gnl_double_free(char **pt_1, char **pt_2);

#endif
