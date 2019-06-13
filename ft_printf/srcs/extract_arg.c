/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 22:57:53 by apion             #+#    #+#             */
/*   Updated: 2019/03/18 15:08:34 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "utils.h"
#include "float_pf.h"

void	extract_arg_integer(va_list ap, union u_value *value, int flag)
{
	if (flag & MOD_L)
		value->type_long = va_arg(ap, long);
	else if (flag & MOD_LL)
		value->type_long_long = va_arg(ap, long long);
	else
		value->type_int = va_arg(ap, int);
}

void	extract_arg_uinteger(va_list ap, union u_value *value, int flag)
{
	if (flag & MOD_L)
		value->type_ulong = va_arg(ap, unsigned long);
	else if (flag & MOD_LL)
		value->type_ulong_long = va_arg(ap, unsigned long long);
	else
		value->type_uint = va_arg(ap, unsigned int);
}

char	*extract_arg_str(va_list ap)
{
	char	*str;

	str = (char *)va_arg(ap, void *);
	return (str);
}

void	extract_arg_double(va_list ap, union u_double *value, int flag)
{
	if (flag & MOD_LD)
		value->type_long_dbl = va_arg(ap, long double);
	else
		value->type_dbl = va_arg(ap, double);
}
