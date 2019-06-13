/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 11:35:55 by apion             #+#    #+#             */
/*   Updated: 2019/03/08 11:42:51 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

void	bigint_copy(t_bigint *dest, t_bigint *src)
{
	int		i;

	i = BIGINT_N_BLOCKS + 1;
	while (i--)
		dest->blocks[i] = src->blocks[i];
	dest->length = src->length;
}
