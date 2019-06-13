/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int_conv_short.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 18:57:52 by apion             #+#    #+#             */
/*   Updated: 2019/02/12 23:56:09 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "filter.h"
#include "filler.h"

static int		get_size(short value, char *base)
{
	int		size;
	int		b;

	b = pf_strlen(base);
	size = 1;
	while (value /= b)
		size++;
	return (size);
}

static void		fill_str(short value, char *base, char *str, t_specs *specs)
{
	int		b;
	int		i;
	int		j;

	b = pf_strlen(base);
	i = 0;
	i += filler(str, specs, FILL_START);
	j = specs->width_arg;
	while (j--)
	{
		*(str + i + j) = *(base + (specs->is_neg ? -(value % b) : value % b));
		value /= b;
	}
	i += specs->width_arg;
	filler(str + i, specs, i);
}

int				handle_int_conv_short(short value, t_specs *specs, char *str)
{
	char	*base;

	base = get_base(specs->type);
	specs->is_neg = value < 0;
	specs->width_arg = get_size(value, base);
	if (!value && (specs->flags & PREFIX) && (specs->type & (HEXA | HEXA_C)))
		specs->flags ^= PREFIX;
	if (!value && (specs->flags & PRECISION) && !specs->precision)
		specs->width_arg -= 1;
	filter_specs(specs);
	if (str)
		fill_str(value, base, str, specs);
	return (1);
}
