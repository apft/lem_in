/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 18:50:00 by apion             #+#    #+#             */
/*   Updated: 2019/03/22 21:00:54 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "utils.h"
#include "float_pf.h"
#include "extract_arg.h"
#include "handlers.h"
#include "filter.h"

int		extract_int_conv(va_list ap, t_specs *specs, char *str)
{
	union u_value	value;

	value = (union u_value){0};
	if (specs->type & INT)
	{
		extract_arg_integer(ap, &value, specs->flags);
		return (handle_int_conv(&value, specs, str));
	}
	extract_arg_uinteger(ap, &value, specs->flags);
	return (handle_int_conv_u(&value, specs, str));
}

int		extract_char_conv(va_list ap, t_specs *specs, char *str)
{
	union u_value	value;

	value = (union u_value){0};
	if (specs->type & PERCENT)
		value.type_char = '%';
	else
		extract_arg_uinteger(ap, &value, MOD_HH);
	return (handle_char_conv(value.type_char, specs, str));
}

int		extract_str_conv(va_list ap, t_specs *specs, char *str)
{
	char	*value;

	value = extract_arg_str(ap);
	if (!value)
		value = NULL_STR;
	return (handle_str_conv(value, specs, str));
}

int		extract_pointer_conv(va_list ap, t_specs *specs, char *str)
{
	clear_flags(specs, MOD_HH | MOD_H | MOD_LL);
	specs->flags |= PREFIX | MOD_L;
	specs->type |= HEXA;
	return (extract_int_conv(ap, specs, str));
}

int		extract_float_conv(va_list ap, t_specs *specs, char *str)
{
	union u_double	value;

	value = (union u_double){0};
	extract_arg_double(ap, &value, specs->flags & MOD_LD);
	if (!(specs->flags & MOD_LD) && value.field.exp == FLOAT_EXP_MAX)
		return (handle_float_limit(&value, specs, str, 0));
	else if ((specs->flags & MOD_LD) && value.field_ld.exp == FLOAT_LD_EXP_MAX)
		return (handle_float_limit(&value, specs, str, specs->flags & MOD_LD));
	if (specs->type & (FLOAT_HEXA | FLOAT_HEXA_C))
		return (handle_float_conv_hex(&value, specs, str));
	return (handle_float_conv(&value, specs, str));
}
