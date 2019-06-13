/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:02:09 by apion             #+#    #+#             */
/*   Updated: 2019/03/25 12:45:14 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "float_pf.h"
#include "utils.h"

static int	float_compute_pow_ten_long_dbl(long double n)
{
	int		pow_ten;

	pow_ten = 0;
	if (!n)
		return (pow_ten);
	if (n < 0)
		n *= -1;
	if (n >= 10.0)
	{
		while (n >= 10.0)
		{
			n /= 10;
			++pow_ten;
		}
	}
	else if (n < 1.0)
	{
		while (n < 1.0)
		{
			n *= 10;
			--pow_ten;
		}
	}
	return (pow_ten);
}

static int	float_compute_pow_ten_dbl(double n)
{
	return (float_compute_pow_ten_long_dbl((long double)n));
}

int			float_compute_pow_ten(union u_double *value, int is_long_dbl)
{
	if (is_long_dbl)
		return (float_compute_pow_ten_long_dbl(value->type_long_dbl));
	return (float_compute_pow_ten_dbl(value->type_dbl));
}

static int	get_exp_subnormal(t_field *fields, int is_long_dbl)
{
	unsigned long	n;
	unsigned long	mask;
	int				offset;

	n = fields->frac << (is_long_dbl ? 3 : 12);
	mask = FLOAT_MASK_LEFT;
	offset = 0;
	while (!(n & (mask >> (4 * offset))))
		++offset;
	offset += 1;
	return (4 * offset);
}

void		float_extract_fields(t_field *fields, t_float *value,
								int is_long_dbl)
{
	if (is_long_dbl)
	{
		fields->frac = value->field_ld.frac;
		fields->exp_unbiased = value->field_ld.exp;
		fields->implicit_bit = value->field_ld.int_part;
		fields->sign = value->field_ld.sign;
	}
	else
	{
		fields->frac = value->field.frac;
		fields->exp_unbiased = value->field.exp;
		fields->implicit_bit = !!fields->exp_unbiased;
		fields->sign = value->field.sign;
	}
	if (fields->exp_unbiased || fields->frac)
	{
		fields->exp = (fields->exp_unbiased ? fields->exp_unbiased : 1)
			- (is_long_dbl ? FLOAT_LD_EXP_BIAS : FLOAT_EXP_BIAS);
		if (is_long_dbl && fields->implicit_bit)
			fields->exp -= 3;
		if (fields->exp_unbiased == 0 && fields->frac != 0)
			fields->exp -= get_exp_subnormal(fields, is_long_dbl);
	}
	else
		fields->exp = 0;
}
