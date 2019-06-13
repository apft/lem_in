/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_pf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:01:06 by apion             #+#    #+#             */
/*   Updated: 2019/03/25 11:45:14 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOAT_PF_H
# define FLOAT_PF_H

# define FLOAT_DEFAULT_PRECISION 6

# define FLOAT_SIZE_SIGN 1
# define FLOAT_SIZE_EXP 11
# define FLOAT_SIZE_FRAC 52

# define FLOAT_EXP_BIAS 1023
# define FLOAT_EXP_MAX 2047

# define FLOAT_LD_SIZE_SIGN 1
# define FLOAT_LD_SIZE_EXP 15
# define FLOAT_LD_INTEGER_PART 1
# define FLOAT_LD_SIZE_FRAC 63

# define FLOAT_LD_EXP_BIAS 16383
# define FLOAT_LD_EXP_MAX 32767

# define FLOAT_MASK_RIGHT 0b1111UL
# define FLOAT_MASK_LEFT (0b1111UL << 60)

# include "utils.h"
# include "bigint.h"

typedef union			u_double
{
	double				type_dbl;
	unsigned long		type_long;
	struct
	{
		unsigned long	frac:FLOAT_SIZE_FRAC;
		unsigned int	exp:FLOAT_SIZE_EXP;
		unsigned int	sign:FLOAT_SIZE_SIGN;
	}					field;

	long double			type_long_dbl;
	unsigned long long	type_ll;
	struct
	{
		unsigned long	frac:FLOAT_LD_SIZE_FRAC;
		unsigned int	int_part:FLOAT_LD_INTEGER_PART;
		unsigned int	exp:FLOAT_LD_SIZE_EXP;
		unsigned int	sign:FLOAT_LD_SIZE_SIGN;
	}					field_ld;
}						t_float;

typedef struct			s_field
{
	unsigned long	frac;
	unsigned int	exp_unbiased;
	int				exp;
	unsigned int	implicit_bit;
	unsigned int	sign;
}						t_field;

typedef struct			s_frac
{
	t_bigint	*numerator;
	t_bigint	*denominator;
}						t_frac;

void					float_extract_fields(t_field *fields, t_float *value,
								int is_long_dbl);
int						float_compute_pow_ten(union u_double *value,
								int is_long_dbl);

int						get_quotient_and_substract(
								t_bigint *numerator, t_bigint *denominator);
void					generate_bigints_num_den(
								union u_double *value, int pow_ten,
								t_frac frac, int is_long_dbl);

int						float_fill_floor_part(char *str, int pow_ten,
								int is_round_ten, t_frac frac);
int						float_fill_decimal_part(char *str, int pow_ten,
								int precision, t_frac frac);
void					float_fill_after(char *str, int start,
								int decimal_length, t_specs *specs);
int						float_fill_pref_radix(t_field *fields, char *base,
								char *str, t_specs *specs);
int						float_fill_exp(t_field *fields,
								char *str, t_specs *specs);

int						float_will_round_to_ten(union u_double *value,
								int pow_ten, int precisior, int is_long_dbl);
void					float_apply_rounding_if_needed(char *str, int pow_ten,
								int precision, t_frac frac);

#endif
