/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_int_overflow_multi.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 19:28:47 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/28 21:12:08 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

int		ft_check_int_overflow_multi(int nb1, int nb2)
{
	int res;

	if (!nb1 || !nb2)
		return (0);
	res = nb1 * nb2;
	if (nb1 == res / nb2)
		return (0);
	else
		return (1);
}
