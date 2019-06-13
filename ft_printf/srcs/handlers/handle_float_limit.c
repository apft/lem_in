/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_float_limit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:40:55 by apion             #+#    #+#             */
/*   Updated: 2019/03/22 22:04:47 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "float_pf.h"
#include "handlers.h"
#include "filter.h"

#define FLOAT_LIMIT_INF "inf"
#define FLOAT_LIMIT_NAN "nan"

#define FLOAT_LIMIT_INF_C "INF"
#define FLOAT_LIMIT_NAN_C "NAN"

static void	set_value(char *dst, char *src)
{
	int		i;

	i = 0;
	while (*(src + i))
	{
		*(dst + i) = *(src + i);
		++i;
	}
	*(dst + i) = 0;
}

static int	handle_nan(t_specs *specs, char *str)
{
	char	nan[4];

	if (specs->type & (FLOAT_C | FLOAT_HEXA_C))
		set_value(nan, FLOAT_LIMIT_NAN_C);
	else
		set_value(nan, FLOAT_LIMIT_NAN);
	clear_flags(specs, PLUS | SPACE);
	return (handle_str_conv(nan, specs, str));
}

static int	handle_dbl(union u_double *value, t_specs *specs, char *str)
{
	char	inf[4];

	if (specs->type & (FLOAT_C | FLOAT_HEXA_C))
		set_value(inf, FLOAT_LIMIT_INF_C);
	else
		set_value(inf, FLOAT_LIMIT_INF);
	if (!value->field.frac)
	{
		specs->is_neg = value->field.sign;
		return (handle_str_conv(inf, specs, str));
	}
	return (handle_nan(specs, str));
}

static int	handle_long_dbl(union u_double *value, t_specs *specs, char *str)
{
	char	inf[4];

	if (specs->type & (FLOAT_C | FLOAT_HEXA_C))
		set_value(inf, FLOAT_LIMIT_INF_C);
	else
		set_value(inf, FLOAT_LIMIT_INF);
	if (value->field_ld.int_part && !value->field_ld.frac)
	{
		specs->is_neg = value->field_ld.sign;
		return (handle_str_conv(inf, specs, str));
	}
	return (handle_nan(specs, str));
}

int			handle_float_limit(union u_double *value, t_specs *specs, char *str,
							int flag)
{
	specs->type |= STRING;
	specs->precision = 0;
	clear_flags(specs, PRECISION | PAD);
	if (flag & MOD_LD)
		return (handle_long_dbl(value, specs, str));
	return (handle_dbl(value, specs, str));
}
