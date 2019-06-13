/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_round.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 12:24:38 by apion             #+#    #+#             */
/*   Updated: 2019/03/21 12:58:46 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "float_pf.h"

int			float_will_round_to_ten(union u_double *value, int pow_ten,
								int precision, int flag)
{
	t_bigint	numerator;
	t_bigint	denominator;
	int			i;
	int			digit;
	int			digit_after;

	generate_bigints_num_den(value, pow_ten,
			(t_frac){&numerator, &denominator}, flag);
	digit = get_quotient_and_substract(&numerator, &denominator);
	pow_ten *= (pow_ten < 0) ? -1 : 1;
	if (digit != 9)
		return (0);
	bigint_mult_int(&numerator, &numerator, 10);
	digit_after = get_quotient_and_substract(&numerator, &denominator);
	i = 0;
	while (digit_after == 9 && i < (pow_ten + precision)
			&& !bigint_is_null(&numerator))
	{
		bigint_mult_int(&numerator, &numerator, 10);
		digit_after = get_quotient_and_substract(&numerator, &denominator);
		++i;
	}
	return ((digit_after >= 5 && i == (pow_ten + precision))
			|| (digit_after > 5 && bigint_is_null(&numerator)));
}

static int	propagate_rounding(char *str, int limit, int is_integer_part,
							int *offset)
{
	int		propagate;
	int		i;

	propagate = 1;
	i = 0;
	while (i < limit && propagate)
	{
		if (*(str - i) == '9')
			*(str - i) = '0';
		else
		{
			*(str - i) += 1;
			propagate = 0;
		}
		++i;
	}
	if (is_integer_part && i == limit && propagate)
		*(str - i) = *(str - i) == '9' ? '0' : *(str - i) + 1;
	*offset = i;
	return (propagate);
}

static void	apply_rounding(int pow_ten, int precision, char *str)
{
	int		i;
	int		propagate;

	i = 0;
	propagate = 1;
	if (precision)
		propagate = propagate_rounding(str - i, precision, 0, &i);
	if (propagate)
	{
		if (*(str - i) == '.')
			propagate_rounding(str - i - 1, pow_ten, 1, &i);
		else
			propagate_rounding(str - i, pow_ten, 1, &i);
	}
}

static int	extract_next_non_null_digit(t_frac frac)
{
	int		digit;

	bigint_mult_int(frac.numerator, frac.numerator, 10);
	digit = get_quotient_and_substract(frac.numerator, frac.denominator);
	while (digit == 0 && !bigint_is_null(frac.numerator))
	{
		bigint_mult_int(frac.numerator, frac.numerator, 10);
		digit = get_quotient_and_substract(frac.numerator, frac.denominator);
	}
	return (digit);
}

void		float_apply_rounding_if_needed(char *str, int pow_ten,
											int precision, t_frac frac)
{
	int		digit_after;

	if (bigint_is_null(frac.numerator)
			|| (pow_ten < 0 && (precision + 1 + pow_ten) < 0))
		return ;
	digit_after = get_quotient_and_substract(frac.numerator, frac.denominator);
	if (digit_after > 5)
		apply_rounding(pow_ten, precision, str);
	else if (digit_after == 5)
	{
		digit_after = extract_next_non_null_digit(frac);
		if (digit_after)
			apply_rounding(pow_ten, precision, str);
		else
		{
			if (pf_isdigit(*str) && (*str % 2) == 1)
				apply_rounding(pow_ten, precision, str);
			else if (*str == '.' && (*(str - 1) % 2) == 1)
				apply_rounding(pow_ten, precision, str - 1);
		}
	}
}
