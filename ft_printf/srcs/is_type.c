/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:45:53 by apion             #+#    #+#             */
/*   Updated: 2019/03/28 10:49:10 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int		is_numeric_conversion(unsigned int type)
{
	return (type & (INT | OCTAL | UINT | HEXA | HEXA_C));
}

int		is_signed_conversion(unsigned int type)
{
	return (type & (INT | FLOAT | FLOAT_C | FLOAT_HEXA | FLOAT_HEXA_C));
}

int		is_hexa_or_bin_conversion(unsigned int type)
{
	return (type & (HEXA | HEXA_C | FLOAT_HEXA | FLOAT_HEXA_C | BIN));
}

int		is_float_conversion(unsigned int type)
{
	return (type & (FLOAT | FLOAT_C | FLOAT_HEXA | FLOAT_HEXA_C));
}

int		is_type(t_specs *specs, unsigned int type)
{
	return (specs->type & type);
}
