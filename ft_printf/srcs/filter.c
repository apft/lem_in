/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 11:37:13 by apion             #+#    #+#             */
/*   Updated: 2019/03/28 10:49:11 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "is_type.h"

void		clear_flags(t_specs *specs, int flags)
{
	if (specs->flags & flags)
		specs->flags &= ~flags;
}

static int	compute_width_float_hexa(t_specs *specs)
{
	specs->width_arg = specs->width_prefix + 1
		+ (specs->precision || (specs->flags & FLOAT_FORCE_POINT) ? 1 : 0)
		+ specs->precision + specs->width_suffix;
	return (pf_max(specs->width_min, specs->width_arg));
}

static int	compute_width_float(t_specs *specs)
{
	if (is_type(specs, FLOAT_HEXA | FLOAT_HEXA_C))
		return (compute_width_float_hexa(specs));
	return (pf_max(specs->width_min, specs->width_prefix + specs->width_arg));
}

static int	compute_width(t_specs *specs)
{
	int		width_print;

	if (specs->is_neg || specs->flags & (PLUS | SPACE))
		specs->width_prefix += 1;
	if (specs->flags & PREFIX)
		specs->width_prefix += 1;
	if ((specs->flags & PREFIX) && is_hexa_or_bin_conversion(specs->type))
		specs->width_prefix += 1;
	if (is_type(specs, OCTAL) && (specs->flags & PREFIX)
			&& (!specs->width_arg || ((specs->flags & PRECISION)
					&& specs->width_arg < specs->precision)))
	{
		clear_flags(specs, PREFIX);
		specs->width_prefix = 0;
	}
	if (is_float_conversion(specs->type) && !is_type(specs, STRING))
		return (compute_width_float(specs));
	width_print = specs->width_prefix;
	if (is_type(specs, STRING) && (specs->flags & PRECISION))
		width_print += pf_min(specs->precision, specs->width_arg);
	else
		width_print += pf_max(specs->precision, specs->width_arg);
	return (pf_max(specs->width_min, width_print));
}

void		filter_specs(t_specs *specs)
{
	if (is_type(specs, INT | UINT | CHAR | STRING | PERCENT))
		clear_flags(specs, PREFIX);
	if (((specs->flags & PAD) && (specs->flags & LEFT))
		|| (is_numeric_conversion(specs->type) && (specs->flags & PRECISION)))
		clear_flags(specs, PAD);
	if (!is_signed_conversion(specs->type))
		clear_flags(specs, PLUS | SPACE);
	if (specs->flags & PLUS)
		clear_flags(specs, SPACE);
	if (specs->is_neg)
		clear_flags(specs, SPACE | PLUS);
	if (is_type(specs, OCTAL) && (specs->flags & PREFIX) && !specs->precision)
	{
		specs->flags |= PRECISION;
		specs->precision = 1;
	}
	if (is_type(specs, CHAR | PERCENT))
	{
		clear_flags(specs, PRECISION);
		specs->precision = 0;
	}
	specs->width = compute_width(specs);
}
