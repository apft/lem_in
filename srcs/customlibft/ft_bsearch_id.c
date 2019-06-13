/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsearch_id.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:36:56 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/29 13:36:50 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "customlibft.h"
#include <unistd.h>

ssize_t		ft_bsearch_id(void *ref, t_array_args *args, int (*cmp)())
{
	size_t		pivot;
	size_t		offset;
	int			result;

	offset = 0u;
	while (args->nb_elmt > 0)
	{
		pivot = args->nb_elmt >> 1;
		result = (*cmp)(ref, args->array + (pivot * args->size_elmt));
		if (result == 0)
			return (pivot + offset);
		if (result > 0)
		{
			args->array += (pivot + 1) * args->size_elmt;
			offset += pivot + 1;
			--args->nb_elmt;
		}
		args->nb_elmt >>= 1;
	}
	return (-1);
}
