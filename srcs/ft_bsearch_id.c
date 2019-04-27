/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsearch_id.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:36:56 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/27 20:45:59 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "room.h"

int		ft_bsearch_id(void *ref, t_room **array, size_t array_size, int (*cmp)())
{
	int		pivot;
	int		result;

	pivot = array_size >> 1;
	while (array_size > 0)
	{
		result = (*cmp)(ref, array[pivot]);
		if (result == 0)
			return (pivot);
		if (result > 0)
		{
			++pivot;
			--array_size;
		}
		array_size >>= 1;
		if (result > 0)
			pivot = pivot + (array_size >> 1);
		else
			pivot = pivot - (array_size >> 1);
	}
	return (-1);
}
