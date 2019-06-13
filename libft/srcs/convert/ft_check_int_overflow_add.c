/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_int_overflow_add.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 19:27:58 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/28 20:25:55 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int		ft_check_int_overflow_add(int nb1, int nb2)
{
	if (nb2 > 0 && (nb1 > INT_MAX - nb2))
		return (1);
	if (nb2 < 0 && (nb1 < INT_MIN - nb2))
		return (-1);
	return (0);
}
