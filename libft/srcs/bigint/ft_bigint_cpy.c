/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigint_cpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:44:01 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/19 10:06:32 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bigint		*ft_bigint_cpy(t_bigint *dest, const t_bigint *src)
{
	size_t		i;

	i = 0;
	while (i < src->length)
	{
		dest->blocks[i] = src->blocks[i];
		i++;
	}
	dest->length = src->length;
	return (dest);
}
