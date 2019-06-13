/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:19:35 by apion             #+#    #+#             */
/*   Updated: 2019/03/20 15:23:59 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

static unsigned int	compute_substraction(unsigned long alpha,
						unsigned long beta, unsigned long *carry, int no_carry)
{
	unsigned int	result;

	if (no_carry)
	{
		result = (unsigned int)(alpha - beta - *carry);
		*carry = 0;
	}
	else
	{
		result = (unsigned int)(
				(1UL << BIGINT_SIZE_BLOCK) + alpha - beta - *carry);
		*carry = 1;
	}
	return (result);
}

static void			sub_and_shrink_length(t_bigint *result,
											t_bigint *a, t_bigint *b)
{
	unsigned int	i;
	int				n_null_block;
	unsigned long	alpha;
	unsigned long	beta;
	unsigned long	carry;

	n_null_block = 0;
	carry = 0;
	i = 0;
	while (i < a->length)
	{
		alpha = (unsigned long)a->blocks[i];
		beta = (unsigned long)b->blocks[i];
		if (alpha >= beta + carry)
			result->blocks[i] = compute_substraction(alpha, beta, &carry, 1);
		else
			result->blocks[i] = compute_substraction(alpha, beta, &carry, 0);
		n_null_block = (result->blocks[i] == 0 && i) ? n_null_block + 1 : 0;
		++i;
	}
	result->length -= n_null_block;
}

void				bigint_sub_int(t_bigint *result, t_bigint *a,
						unsigned int n)
{
	t_bigint	b;

	bigint_init_int(&b, n);
	bigint_sub(result, a, &b);
}

void				bigint_sub(t_bigint *result, t_bigint *a, t_bigint *b)
{
	t_bigint		temp;

	if (bigint_is_underflow(a) || bigint_is_underflow(b)
			|| bigint_cmp(a, b) < 0)
		result->blocks[BIGINT_N_BLOCKS] = BIGINT_UNDERFLOW;
	else
	{
		bigint_init_null(&temp);
		temp.length = a->length;
		sub_and_shrink_length(&temp, a, b);
		bigint_copy(result, &temp);
	}
}
