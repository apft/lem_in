/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_filler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 10:58:40 by apion             #+#    #+#             */
/*   Updated: 2019/04/11 11:15:13 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "float_pf.h"
#include "filler.h"

int		float_fill_pref_radix(t_field *fields, char *b, char *str,
							t_specs *specs)
{
	int				i;
	int				is_long_dbl;
	unsigned int	integer;

	is_long_dbl = specs->flags & MOD_LD;
	i = filler(str, specs, FILL_START);
	if (fields->exp_unbiased || (!fields->exp_unbiased && !fields->frac))
	{
		if (is_long_dbl)
			integer = (unsigned int)(fields->frac >> 60)
				| (fields->implicit_bit << 3);
		else
			integer = fields->implicit_bit;
		*(str + i++) = is_long_dbl ? *(b + integer) : (char)('0' + integer);
	}
	else
	{
		fields->frac <<= 1 - fields->exp
			- (is_long_dbl ? FLOAT_LD_EXP_BIAS : FLOAT_EXP_BIAS);
		*(str + i++) = *(b + (unsigned int)(fields->frac >> 52));
	}
	if (specs->precision || (specs->flags & FLOAT_FORCE_POINT))
		*(str + i++) = '.';
	return (i);
}

int		float_fill_exp(t_field *fields, char *str, t_specs *specs)
{
	int		exp;
	int		i;
	int		j;

	exp = fields->exp;
	i = 0;
	*(str + i++) = (specs->type & FLOAT_HEXA) ? 'p' : 'P';
	*(str + i++) = (exp < 0) ? '-' : '+';
	if (!fields->exp_unbiased || !exp)
		*(str + i) = '0';
	j = specs->width_suffix - 2;
	while (exp && j--)
	{
		*(str + i + j) = '0' + (exp < 0 ? -(exp % 10) : exp % 10);
		exp /= 10;
	}
	return (i + specs->width_suffix - 2);
}

int		float_fill_floor_part(char *str, int pow_ten, int is_round_ten,
									t_frac frac)
{
	int		i;
	int		digit;

	i = 0;
	if (pow_ten < 0 && !is_round_ten)
	{
		*(str + i++) = '0';
		return (i);
	}
	while (i <= pow_ten)
	{
		digit = get_quotient_and_substract(frac.numerator, frac.denominator);
		*(str + i++) = '0' + (char)digit;
		bigint_mult_int(frac.numerator, frac.numerator, 10);
	}
	return (i);
}

int		float_fill_decimal_part(char *str, int pow_ten, int precision,
									t_frac frac)
{
	int		i;
	int		digit;

	i = 0;
	if (pow_ten < 0)
		while (i < precision && ++pow_ten)
			*(str + i++) = '0';
	while (i < precision && !bigint_is_null(frac.numerator))
	{
		digit = get_quotient_and_substract(frac.numerator, frac.denominator);
		*(str + i++) = '0' + (char)digit;
		bigint_mult_int(frac.numerator, frac.numerator, 10);
	}
	return (i);
}

void	float_fill_after(char *str, int start, int decimal_length,
									t_specs *specs)
{
	int		i;

	i = start;
	i += fill_char(str + i, '0', specs->precision + decimal_length - i);
	fill_char(str + i, ' ', specs->width - i);
}
