/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int_conv_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 18:57:52 by apion             #+#    #+#             */
/*   Updated: 2019/02/13 00:31:59 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "filter.h"
#include "filler.h"

static int		get_length(char value, char *base)
{
	int		length;
	int		base_length;

	base_length = pf_strlen(base);
	length = 1;
	while (value /= base_length)
		length++;
	return (length);
}

static void		fill_str(char value, char *base, char *str, t_specs *specs)
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

int				handle_int_conv_char(char value, t_specs *specs, char *str)
{
	char	*base;

	base = get_base(specs->type);
	specs->is_neg = value < 0;
	specs->width_arg = get_length(value, base);
	if (!value && (specs->flags & PREFIX) && (specs->type & (HEXA | HEXA_C)))
		specs->flags ^= PREFIX;
	if (!value && (specs->flags & PRECISION) && !specs->precision)
		specs->width_arg -= 1;
	filter_specs(specs);
	if (str)
		fill_str(value, base, str, specs);
	return (1);
}
