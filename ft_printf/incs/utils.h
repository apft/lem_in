/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 13:25:47 by apion             #+#    #+#             */
/*   Updated: 2019/03/25 17:27:41 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define BASE_DEC		"0123456789"
# define BASE_OCT		"01234567"
# define BASE_HEXA		"0123456789abcdef"
# define BASE_HEXA_C	"0123456789ABCDEF"
# define BASE_BIN		"01"

# define NULL_STR "(null)"

typedef struct	s_specs
{
	int		flags;
	int		type;
	int		precision;
	int		width_min;
	int		width_arg;
	int		width_prefix;
	int		width_suffix;
	int		width;
	int		is_neg;
}				t_specs;

union			u_value
{
	char				type_char;
	unsigned char		type_uchar;
	short				type_short;
	unsigned short		type_ushort;
	int					type_int;
	unsigned int		type_uint;
	long				type_long;
	unsigned long		type_ulong;
	long long			type_long_long;
	unsigned long long	type_ulong_long;
	void				*type_ptr;
};

enum			e_flags
{
	LEFT = 1,
	PLUS = 1 << 1,
	SPACE = 1 << 2,
	PREFIX = 1 << 3,
	PAD = 1 << 4,
	WIDTH = 1 << 5,
	PRECISION = 1 << 6,
	MOD_HH = 1 << 7,
	MOD_H = 1 << 8,
	MOD_L = 1 << 9,
	MOD_LL = 1 << 10,
	MOD_LD = 1 << 11,
	FLOAT_FORCE_POINT = 1 << 12,
	FLOAT_ROUND_TEN = 1 << 13
};

enum			e_type
{
	INT = 1,
	OCTAL = 1 << 1,
	UINT = 1 << 2,
	HEXA = 1 << 3,
	HEXA_C = 1 << 4,
	FLOAT = 1 << 5,
	FLOAT_C = 1 << 6,
	FLOAT_HEXA = 1 << 7,
	FLOAT_HEXA_C = 1 << 8,
	CHAR = 1 << 9,
	STRING = 1 << 10,
	POINTER = 1 << 11,
	PERCENT = 1 << 12,
	BIN = 1 << 13,
	BIN_C = 1 << 14
};

int				pf_strlen(const char *str);
int				pf_min(int a, int b);
int				pf_max(int a, int b);
int				pf_isdigit(char c);
char			*get_base(int type);

#endif
