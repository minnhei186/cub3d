/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:52:29 by hosokawa          #+#    #+#             */
/*   Updated: 2025/02/05 10:43:23 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

// system call error 0
// custum error 1

static void	print_error_prefix(void)
{
	write(STDERR_FILENO, "Error\n", 6);
}

void	system_error(char *error_msg)
{
	print_error_prefix();
	perror(error_msg);
	exit(EXIT_FAILURE);
}

void	custum_error(char *error_msg)
{
	print_error_prefix();
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void	fatal_error_exit(int error_status, char *error_msg)
{
	if (error_status == 0)
		system_error(error_msg);
	else if (error_status == 1)
		custum_error(error_msg);
}
