/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 01:29:14 by nkannan           #+#    #+#             */
/*   Updated: 2025/01/13 01:29:38 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wall.h"

void    *ft_realloc_double_ptr(void **ptr, size_t size)
{
    void **new_ptr;
    size_t i;

    if (!ptr)
        return ft_calloc(1, size);
    if (!size)
        return (free(ptr), NULL);
    new_ptr = ft_calloc(1, size);
    if (!new_ptr)
        return NULL;
    i = 0;
    while (ptr[i] && i < size / sizeof(void *) - 1)
    {
        new_ptr[i] = ptr[i];
        i++;
    }

    free(ptr);

    return new_ptr;


}
