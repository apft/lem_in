/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigint_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 22:32:10 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/18 12:24:07 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Add `bigint1' and `bigint2' and store the sum in `result'.
** Return a pointer to `result'.
*/

t_bigint		*ft_bigint_add(const t_bigint *bigint1, const t_bigint *bigint2,
							t_bigint *result)
{
	t_ulint			sum;
	t_ulint			carry;
	size_t			i;
	size_t			max_len;

	sum = 0UL;
	carry = 0UL;
	i = 0;
	max_len = (size_t)ft_max(bigint1->length, bigint2->length);
	while (i < max_len)
	{
		sum = carry + (t_ulint)bigint1->blocks[i]
					+ (t_ulint)bigint2->blocks[i];
		result->blocks[i] = (t_uint)(sum & 0xFFFFFFFFUL);
		carry = sum >> BIGINT_BLOCK_SIZE;
		i++;
	}
	if (carry && (i < BIGINT_SIZE))
		result->blocks[i] = (t_uint)(carry & 0xFFFFFFFFUL);
	result->length = (carry) ? max_len + 1 : max_len;
	return (result);
}
