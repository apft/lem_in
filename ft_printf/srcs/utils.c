/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 10:24:24 by apion             #+#    #+#             */
/*   Updated: 2019/03/22 19:05:08 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int		pf_strlen(const char *str)
{
	int		i;

	i = 0;
	while (*(str + i))
		++i;
	return (i);
}

int		pf_min(int a, int b)
{
	return (a < b ? a : b);
}

int		pf_max(int a, int b)
{
	return (a < b ? b : a);
}

int		pf_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

char	*get_base(int type)
{
	if (type & OCTAL)
		return (BASE_OCT);
	else if (type & (HEXA | FLOAT_HEXA))
		return (BASE_HEXA);
	else if (type & (HEXA_C | FLOAT_HEXA_C))
		return (BASE_HEXA_C);
	else if (type & (BIN | BIN_C))
		return (BASE_BIN);
	else
		return (BASE_DEC);
}
