/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atois.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 18:57:09 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/28 21:28:19 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int		ft_atois(const char *str, int *nb)
{
	int			neg;
	int			res;
	int			ret;

	neg = 1;
	res = 0;
	ret = 0;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		neg = (*str++ == '-') ? -1 : 1;
	while (ft_isdigit(*str))
	{
		if (!ret)
			ret = ft_check_int_overflow_multi(res, 10);
		res *= 10;
		if (!ret)
			ret = ft_check_int_overflow_add(res, *str - '0');
		res += (*str - '0');
		++str;
	}
	if (!ret)
		ret = ft_check_int_overflow_multi(res, neg);
	*nb = neg * res;
	return (((neg == -1) && (res == INT_MIN)) ? 0 : ret);
}
