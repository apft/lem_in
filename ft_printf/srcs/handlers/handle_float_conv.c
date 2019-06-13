/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_float_conv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 17:50:11 by apion             #+#    #+#             */
/*   Updated: 2019/04/24 20:09:26 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "float_pf.h"
#include "handlers.h"
#include "bigint.h"
#include "filler.h"
#include "filter.h"

static void	fill_str(union u_double *value, char *str, t_specs *specs)
{
	t_bigint	numerator;
	t_bigint	denominator;
	int			pow_ten;
	int			i;
	int			decimal_length;

	pow_ten = float_compute_pow_ten(value, specs->flags & MOD_LD);
	generate_bigints_num_den(value, pow_ten,
			(t_frac){&numerator, &denominator}, specs->flags & MOD_LD);
	i = filler(str, specs, FILL_START);
	if ((specs->flags & FLOAT_ROUND_TEN) && pow_ten >= -1)
		*(str + i++) = '1';
	i += float_fill_floor_part(str + i, pow_ten, specs->flags & FLOAT_ROUND_TEN,
			(t_frac){&numerator, &denominator});
	if (specs->precision || (specs->flags & FLOAT_FORCE_POINT))
		*(str + i++) = '.';
	decimal_length = i;
	i += float_fill_decimal_part(str + i, pow_ten, specs->precision,
								(t_frac){&numerator, &denominator});
	float_apply_rounding_if_needed(str + i - 1, pow_ten, specs->precision,
								(t_frac){&numerator, &denominator});
	float_fill_after(str, i, decimal_length, specs);
}

static int	compute_width_arg_float(union u_double *value, t_specs *specs)
{
	int		width_arg;
	int		pow_ten;

	width_arg = 1;
	pow_ten = float_compute_pow_ten(value, specs->flags & MOD_LD);
	if (pow_ten > 0)
		width_arg += pow_ten;
	if (pow_ten >= -1 && float_will_round_to_ten(value, pow_ten,
									specs->precision, specs->flags & MOD_LD))
	{
		specs->flags |= FLOAT_ROUND_TEN;
		width_arg += (pow_ten >= 0) ? 1 : 0;
	}
	if ((specs->flags & PRECISION)
			&& (specs->precision || (specs->flags & FLOAT_FORCE_POINT)))
		width_arg += 1;
	width_arg += specs->precision;
	return (width_arg);
}

int			handle_float_conv(union u_double *value, t_specs *specs, char *str)
{
	if (specs->flags & MOD_LD)
		specs->is_neg = value->field_ld.sign;
	else
		specs->is_neg = value->field.sign;
	if (!(specs->flags & PRECISION))
	{
		specs->flags |= PRECISION;
		specs->precision = FLOAT_DEFAULT_PRECISION;
	}
	if (specs->flags & PREFIX)
	{
		specs->flags ^= PREFIX;
		specs->flags |= FLOAT_FORCE_POINT;
	}
	specs->width_arg = compute_width_arg_float(value, specs);
	filter_specs(specs);
	if (str)
		fill_str(value, str, specs);
	return (1);
}
