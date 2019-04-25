/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:17:47 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/01 15:38:08 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcdup(const void *src, int c, size_t size, size_t *dst_size)
{
	size_t	i;
	void	*dst;

	i = 0;
	while ((i < size) && (((const unsigned char *)src)[i] != (unsigned char)c))
		i++;
	dst = ft_memdup(src, i);
	*dst_size = i;
	return (dst);
}
