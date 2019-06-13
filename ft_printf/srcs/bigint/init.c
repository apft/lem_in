/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 17:01:19 by apion             #+#    #+#             */
/*   Updated: 2019/02/17 13:00:20 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

void	bigint_init_null(t_bigint *a)
{
	int		i;

	a->length = 1;
	i = 0;
	while (i < BIGINT_N_BLOCKS + 1)
		a->blocks[i++] = 0;
}

void	bigint_init_int(t_bigint *a, unsigned int n)
{
	bigint_init_null(a);
	a->blocks[0] = n;
}
