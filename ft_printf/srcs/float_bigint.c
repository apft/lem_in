/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_bigint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 08:54:19 by apion             #+#    #+#             */
/*   Updated: 2019/03/18 16:50:43 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "float_pf.h"
#include "bigint.h"

static void	extract_mantissa(t_bigint *numerator, unsigned long frac,
							int implicit_bit, int flag)
{
	t_bigint	bigint_implicit_bit;

	bigint_init_null(numerator);
	numerator->blocks[0] = (unsigned int)(frac & BIGINT_MASK_BLOCK);
	numerator->blocks[1] = (unsigned int)(frac >> BIGINT_SIZE_BLOCK);
	if (numerator->blocks[1])
		numerator->length += 1;
	if (implicit_bit)
	{
		bigint_init_int(&bigint_implicit_bit, 1);
		if (flag & MOD_LD)
			bigint_shift_left_self(&bigint_implicit_bit, FLOAT_LD_SIZE_FRAC);
		else
			bigint_shift_left_self(&bigint_implicit_bit, FLOAT_SIZE_FRAC);
		bigint_add(numerator, numerator, &bigint_implicit_bit);
	}
}

static void	generate_bigint_pow_ten(t_bigint *bigint_pow_ten, int pow_ten)
{
	bigint_init_int(bigint_pow_ten, 1);
	if (pow_ten < 0)
		pow_ten *= -1;
	while (pow_ten--)
		bigint_mult_int(bigint_pow_ten, bigint_pow_ten, 10);
}

int			get_quotient_and_substract(t_bigint *numerator,
										t_bigint *denominator)
{
	int			quotient;
	t_bigint	result_tmp;

	if (bigint_cmp(numerator, denominator) < 0)
		return (0);
	quotient = 5;
	bigint_init_null(&result_tmp);
	bigint_mult_int(&result_tmp, denominator, quotient);
	while (bigint_cmp(&result_tmp, numerator) < 0 && quotient++)
		bigint_add(&result_tmp, &result_tmp, denominator);
	while (bigint_cmp(&result_tmp, numerator) > 0 && quotient--)
		bigint_sub(&result_tmp, &result_tmp, denominator);
	bigint_sub(numerator, numerator, &result_tmp);
	return (quotient);
}

void		generate_bigints_num_den(union u_double *value, int pow_ten,
							t_frac frac, int flag)
{
	unsigned long	mantissa;
	unsigned int	exp_unbiased;
	int				exp;
	t_bigint		bigint_pow_ten;
	int				implicit_bit;

	mantissa = (flag & MOD_LD) ? value->field_ld.frac : value->field.frac;
	exp_unbiased = (flag & MOD_LD) ? value->field_ld.exp : value->field.exp;
	implicit_bit = (flag & MOD_LD) ? value->field_ld.int_part : !!exp_unbiased;
	extract_mantissa(frac.numerator, mantissa, implicit_bit, flag);
	bigint_init_int(frac.denominator, 1);
	exp = (exp_unbiased ? exp_unbiased : 1)
		- ((flag & MOD_LD) ? FLOAT_LD_EXP_BIAS + FLOAT_LD_SIZE_FRAC
				: FLOAT_EXP_BIAS + FLOAT_SIZE_FRAC);
	if (exp >= 0)
		bigint_shift_left_self(frac.numerator, exp);
	else
		bigint_shift_left_self(frac.denominator, -exp);
	generate_bigint_pow_ten(&bigint_pow_ten, pow_ten);
	if (pow_ten > 0)
		bigint_mult(frac.denominator, frac.denominator, &bigint_pow_ten);
	else if (pow_ten < 0)
		bigint_mult(frac.numerator, frac.numerator, &bigint_pow_ten);
}
