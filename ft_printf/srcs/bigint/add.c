/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:03:40 by apion             #+#    #+#             */
/*   Updated: 2019/03/08 13:10:50 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

static int	sum_and_propagate_carry(t_bigint *result, t_bigint *a, t_bigint *b)
{
	unsigned int	i;
	unsigned long	carry;
	unsigned long	sum;

	i = 0;
	carry = 0UL;
	while (i < result->length)
	{
		sum = carry;
		sum += (unsigned long)(a->blocks[i]) + (unsigned long)(b->blocks[i]);
		carry = sum >> BIGINT_SIZE_BLOCK;
		result->blocks[i] = sum & BIGINT_MASK_BLOCK;
		++i;
	}
	return (carry ? 1 : 0);
}

void		bigint_add(t_bigint *result, t_bigint *a, t_bigint *b)
{
	if (bigint_is_overflow(a) || bigint_is_overflow(b))
		result->blocks[BIGINT_N_BLOCKS] = BIGINT_OVERFLOW;
	else
	{
		result->length = (a->length < b->length) ? b->length : a->length;
		if (sum_and_propagate_carry(result, a, b))
		{
			if (result->length < BIGINT_N_BLOCKS)
			{
				result->blocks[result->length] = 1;
				result->length += 1;
			}
			else
				result->blocks[BIGINT_N_BLOCKS] = BIGINT_OVERFLOW;
		}
	}
}

void		bigint_add_int(t_bigint *result, t_bigint *a, unsigned int n)
{
	t_bigint	b;

	bigint_init_int(&b, n);
	bigint_add(result, a, &b);
}
