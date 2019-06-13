/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str_conv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 18:57:52 by apion             #+#    #+#             */
/*   Updated: 2019/03/15 21:50:44 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "filter.h"
#include "filler.h"

static void		fill_str(char *value, char *str, t_specs *specs)
{
	int		i;
	int		j;

	i = 0;
	i += filler(str, specs, FILL_START);
	j = 0;
	if (specs->flags & PRECISION)
	{
		while (j < specs->precision && *(value + j))
			*(str + i++) = *(value + j++);
	}
	else
	{
		while (*(value + j))
			*(str + i++) = *(value + j++);
	}
	filler(str + i, specs, i);
}

int				handle_str_conv(char *value, t_specs *specs, char *str)
{
	if (!(specs->flags & PRECISION) || specs->precision)
		specs->width_arg += pf_strlen(value);
	filter_specs(specs);
	if (str)
		fill_str(value, str, specs);
	return (1);
}
