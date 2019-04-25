/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 14:01:05 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/01 18:44:04 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		*ft_memdup(const void *src, size_t size)
{
	void	*dst;

	if (!(dst = ft_memalloc(size + 1)))
		return (NULL);
	if (!ft_memcpy(dst, src, size))
		return (NULL);
	return (dst);
}
