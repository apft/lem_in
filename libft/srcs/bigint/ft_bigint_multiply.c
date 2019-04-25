/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigint_multiply.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:46:20 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/19 10:08:27 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bigint		*ft_bigint_multiply(const t_bigint *bigint1,
									const t_bigint *bigint2, t_bigint *result)
{
	const t_bigint	*large_nb;
	const t_bigint	*small_nb;
	t_bigint		bigint_tmp;
	size_t			i;
	int				shift;

	i = 0;
	shift = 0;
	ft_bigint_order(bigint1, bigint2, &small_nb, &large_nb);
	while (i < small_nb->length)
	{
		bigint_tmp = (t_bigint){0, {0}};
		ft_bigint_cpy(&bigint_tmp, large_nb);
		ft_bigint_multiply_uint(&bigint_tmp, small_nb->blocks[i]);
		ft_bigint_shiftleft(&bigint_tmp, shift * BIGINT_BLOCK_SIZE);
		ft_bigint_add(result, &bigint_tmp, result);
		++i;
		++shift;
	}
	return (result);
}
