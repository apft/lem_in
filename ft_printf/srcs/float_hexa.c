/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 19:43:34 by apion             #+#    #+#             */
/*   Updated: 2019/03/25 15:55:52 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "float_pf.h"

unsigned int	float_hexa_extract_byte(unsigned long n, int byte_index)
{
	return ((unsigned int)(((n << (4 * byte_index)) & FLOAT_MASK_LEFT) >> 60));
}

static int		round_floor_part_if_needed(t_field *fields, int base_length,
								char *base, char *str)
{
	unsigned long	n;
	int				round_to_even;
	int				index;

	n = fields->frac;
	round_to_even = ((int)(n >> 60) == base_length / 2) && (*str - '0') % 2;
	if (((int)(n >> 60) > base_length / 2) || round_to_even)
	{
		index = 1 + (*(str - 1) == '.');
		if (*(str - index) < *(base + base_length - 1))
			*(str - index) += 1;
		else
			*(str - index) = '1';
		return (1);
	}
	return (0);
}

int				float_hexa_round(t_field *fields, char *base, char *str,
								int precision)
{
	int		b;
	int		id;
	int		next;
	int		next_next;
	int		propagate;

	b = pf_strlen(base);
	if (!precision && round_floor_part_if_needed(fields, b, base, str))
		return (1);
	propagate = 1;
	while (propagate && precision--)
	{
		id = float_hexa_extract_byte(fields->frac, precision);
		next = float_hexa_extract_byte(fields->frac, precision + 1);
		next_next = float_hexa_extract_byte(fields->frac, precision + 2);
		if (next > (b / 2))
			id += 1;
		if (next == (b / 2) && next_next)
			id += 1;
		propagate = (id == b) ? 1 : 0;
		*(str--) = *(base + (id == b ? 0 : id));
		if (propagate && *str == '.')
			(*(str - 1))++;
	}
	return (1);
}
