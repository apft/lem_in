/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigint_divide.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 12:04:39 by jkettani          #+#    #+#             */
/*   Updated: 2019/06/14 11:40:51 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Assuming  0 <= dividend / divisor < 10, give the result of the integer
** division of dividend by divisor.
*/

int				ft_bigint_divide(const t_bigint *dividend,
											const t_bigint *divisor)
{
	int				res;
	t_bigint		bigint_tmp;

	res = 5;
	bigint_tmp = (t_bigint){0, {0}};
	ft_bigint_multiply_uint(ft_bigint_cpy(&bigint_tmp, divisor), res);
	if (ft_bigint_comp(dividend, &bigint_tmp) > 0)
	{
		while (ft_bigint_comp(dividend, ft_bigint_add(&bigint_tmp, divisor,
				&bigint_tmp)) > 0)
			++res;
		return (!ft_bigint_comp(dividend, &bigint_tmp) ? res + 1 : res);
	}
	if (ft_bigint_comp(dividend, &bigint_tmp) < 0)
	{
		while (ft_bigint_comp(dividend, ft_bigint_subst(&bigint_tmp, divisor,
				&bigint_tmp)) < 0)
			--res;
		return (res - 1);
	}
	return (res);
}
