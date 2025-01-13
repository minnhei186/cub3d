/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:52:29 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/13 14:13:25 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"


//system call error 0
//custum error 1

void system_error(char *error_msg)
{
	perror(error_msg);
	exit(EXIT_FAILURE);
}

void custum_error(char *error_msg)
{
	write(1,error_msg,ft_strlen(error_msg));
	write(1,"\n",1);
	exit(EXIT_FAILURE);
}
	
	

void fatal_error_exit(int error_status,char *error_msg)
{
	if(error_status==0)
		system_error(error_msg);
	else if (error_status==1)
		 custum_error(error_msg);
}


