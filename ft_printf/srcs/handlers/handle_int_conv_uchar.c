/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int_conv_uchar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 19:00:17 by apion             #+#    #+#             */
/*   Updated: 2019/04/11 11:14:53 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "is_type.h"
#include "filter.h"
#include "filler.h"

static int		get_size(unsigned char value, char *base)
{
	int		size;
	int		b;

	b = pf_strlen(base);
	size = 1;
	while (value /= b)
		size++;
	return (size);
}

static void		fill_str(unsigned char value, char *base, char *str,
							t_specs *specs)
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
		*(str + i + j) = *(base + value % b);
		value /= b;
	}
	i += specs->width_arg;
	filler(str + i, specs, i);
}

int				handle_int_conv_uchar(unsigned char value, t_specs *specs,
							char *str)
{
	char			*base;

	base = get_base(specs->type);
	specs->width_arg = get_size(value, base);
	if (!value && (specs->flags & PREFIX)
			&& is_hexa_or_bin_conversion(specs->type))
		specs->flags ^= PREFIX;
	if (!value && (((specs->flags & PRECISION) && !specs->precision)
				|| ((specs->type & OCTAL) && (specs->flags & PREFIX))))
		specs->width_arg = 0;
	filter_specs(specs);
	if (str)
		fill_str(value, base, str, specs);
	return (1);
}
