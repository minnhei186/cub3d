/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:40:13 by hosokawa          #+#    #+#             */
/*   Updated: 2025/01/31 11:28:43 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

double	ft_abs(double a)
{
	if (a >= 0)
		return (a);
	else
		return (-a);
}

void	*ft_realloc_double_ptr(void **ptr, size_t size)
{
	void	**new_ptr;
	size_t	i;

	if (!ptr)
		return (ft_calloc(1, size));
	if (!size)
		return (free(ptr), NULL);
	new_ptr = ft_calloc(1, size);
	if (!new_ptr)
		return (NULL);
	i = 0;
	while (ptr[i] && i < size / sizeof(void *) - 1)
	{
		new_ptr[i] = ptr[i];
		i++;
	}
	free(ptr);
	return (new_ptr);
}
