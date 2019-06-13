/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_limit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 11:47:16 by apion             #+#    #+#             */
/*   Updated: 2019/03/22 17:31:21 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

int		bigint_is_null(t_bigint *a)
{
	if (bigint_is_overflow(a) || bigint_is_underflow(a))
		return (0);
	if (a->length != 1 || a->blocks[0] != 0)
		return (0);
	return (1);
}

int		bigint_is_overflow(t_bigint *a)
{
	return (a->blocks[BIGINT_N_BLOCKS] == BIGINT_OVERFLOW);
}

int		bigint_is_underflow(t_bigint *a)
{
	return (a->blocks[BIGINT_N_BLOCKS] == BIGINT_UNDERFLOW);
}
