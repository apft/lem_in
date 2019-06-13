/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:58:42 by apion             #+#    #+#             */
/*   Updated: 2019/03/22 17:18:21 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

static int	is_shift_overflow(unsigned int block_id, unsigned int is_aligned)
{
	if (!is_aligned && block_id > BIGINT_N_BLOCKS)
		return (1);
	if (is_aligned && block_id > BIGINT_N_BLOCKS)
		return (1);
	return (0);
}

void		bigint_shift_left_self(t_bigint *result, unsigned int shift)
{
	bigint_shift_left(result, result, shift);
}

void		bigint_shift_left(t_bigint *result, t_bigint *input,
								unsigned int shift)
{
	unsigned int	offset;
	unsigned int	mod;
	unsigned int	carry;
	unsigned int	i;

	offset = shift / BIGINT_SIZE_BLOCK;
	mod = shift % BIGINT_SIZE_BLOCK;
	i = input->length;
	if (is_shift_overflow(i + offset, mod))
		result->blocks[BIGINT_N_BLOCKS] = BIGINT_OVERFLOW;
	else
	{
		result->length = i + offset;
		while (i--)
		{
			carry = mod ? input->blocks[i] >> (BIGINT_SIZE_BLOCK - mod) : 0;
			result->blocks[i + offset + 1] += carry;
			result->blocks[i + offset] = input->blocks[i] << mod;
			if ((i + offset + !!carry) >= input->length)
				result->length += 1;
		}
		while (offset--)
			result->blocks[offset] = 0;
	}
}
