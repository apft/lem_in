/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 12:24:36 by apion             #+#    #+#             */
/*   Updated: 2019/03/01 19:39:18 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

long	bigint_cmp(t_bigint *a, t_bigint *b)
{
	unsigned int	block;
	long			diff;

	if (a->length < b->length)
		return (-1);
	if (a->length > b->length)
		return (1);
	block = a->length;
	while (block--)
	{
		diff = (long)a->blocks[block] - (long)b->blocks[block];
		if (diff)
			return (diff);
	}
	return (0);
}
