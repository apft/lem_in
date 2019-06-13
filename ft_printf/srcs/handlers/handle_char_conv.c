/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char_conv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 18:57:52 by apion             #+#    #+#             */
/*   Updated: 2019/02/12 23:51:01 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "filter.h"
#include "filler.h"

static void	fill_str(unsigned char value, char *str, t_specs *specs)
{
	int		i;

	i = 0;
	i += filler(str, specs, FILL_START);
	*(str + i++) = value;
	filler(str + i, specs, i);
}

int			handle_char_conv(unsigned char value, t_specs *specs, char *str)
{
	specs->width_arg = 1;
	filter_specs(specs);
	if (str)
		fill_str(value, str, specs);
	return (1);
}
