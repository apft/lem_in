/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int_conv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 22:48:35 by apion             #+#    #+#             */
/*   Updated: 2019/02/13 14:38:54 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "handlers.h"

int		handle_int_conv(union u_value *value, t_specs *specs, char *str)
{
	if (specs->flags & MOD_HH)
		return (handle_int_conv_char(value->type_char, specs, str));
	if (specs->flags & MOD_H)
		return (handle_int_conv_short(value->type_short, specs, str));
	if (specs->flags & MOD_L)
		return (handle_int_conv_long(value->type_long, specs, str));
	if (specs->flags & MOD_LL)
		return (handle_int_conv_long_long(value->type_long_long, specs, str));
	return (handle_int_conv_int(value->type_int, specs, str));
}

int		handle_int_conv_u(union u_value *value, t_specs *specs, char *str)
{
	if (specs->flags & MOD_HH)
		return (handle_int_conv_uchar(value->type_uchar, specs, str));
	if (specs->flags & MOD_H)
		return (handle_int_conv_ushort(value->type_ushort, specs, str));
	if (specs->flags & MOD_L)
		return (handle_int_conv_ulong(value->type_ulong, specs, str));
	if (specs->flags & MOD_LL)
		return (handle_int_conv_ulong_long(value->type_ulong_long, specs, str));
	return (handle_int_conv_uint(value->type_uint, specs, str));
}
