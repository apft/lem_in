/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsearch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:36:56 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/25 18:11:48 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_bsearch(void *ref, void *array, size_t array_size, int (*cmp)())
{
	void	*pivot;
	int		result;

	while (array_size > 0)
	{
		pivot = array + (array_size >> 1);
		result = (*cmp)(ref, pivot);
		if (result == 0)
			return (pivot);
		if (result > 0)
		{
			array = pivot + 1;	
			--array_size;
		}
		array_size >>= 1;
	}
	return (NULL);
}
