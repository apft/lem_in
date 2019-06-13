/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:00:42 by apion             #+#    #+#             */
/*   Updated: 2019/03/26 11:32:52 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "extractor.h"
#include "handlers.h"

#define VALID_CHAR "%-+ #0*.123456789hlLdiouxXfFcspaAbB{y"

t_parser	g_parser[] =
{
	{'d', INT, &extract_int_conv},
	{'i', INT, &extract_int_conv},
	{'o', OCTAL, &extract_int_conv},
	{'u', UINT, &extract_int_conv},
	{'x', HEXA, &extract_int_conv},
	{'X', HEXA_C, &extract_int_conv},
	{'f', FLOAT, &extract_float_conv},
	{'F', FLOAT_C, &extract_float_conv},
	{'a', FLOAT_HEXA, &extract_float_conv},
	{'A', FLOAT_HEXA_C, &extract_float_conv},
	{'c', CHAR, &extract_char_conv},
	{'s', STRING, &extract_str_conv},
	{'p', POINTER, &extract_pointer_conv},
	{'%', PERCENT, &extract_char_conv},
	{'b', BIN, &extract_int_conv},
	{'B', BIN_C, &extract_int_conv},
	{'y', STRING, &clear_screen}
};

static int	parse_nbr(const char **str, va_list ap)
{
	int		n;

	n = 0;
	if (**str == '*')
		return (va_arg(ap, int));
	while (**str >= '0' && **str <= '9')
		n = 10 * n + (*((*str)++) - '0');
	--(*str);
	return (n);
}

static void	parse_width(const char **f, t_specs *specs, va_list ap)
{
	int		width;
	int		is_from_asterisk;

	specs->flags |= WIDTH;
	is_from_asterisk = (**f == '*');
	width = parse_nbr(f, ap);
	if (width >= 0)
		specs->width_min = width;
	else
	{
		if (is_from_asterisk)
		{
			specs->flags |= LEFT;
			specs->width_min = -width;
		}
		else
			specs->width_min = 0;
	}
}

static void	parse_precision(const char **f, t_specs *specs, va_list ap)
{
	int		precision;

	++(*f);
	precision = parse_nbr(f, ap);
	if (precision >= 0)
	{
		specs->flags |= PRECISION;
		specs->precision = precision;
	}
	else
		specs->precision = 0;
}

static int	parse_type(const char **f, t_specs *specs, va_list ap, char *str)
{
	int		i;
	int		size;
	int		is_valid;

	i = 0;
	is_valid = 0;
	while (!is_valid && VALID_CHAR[i])
		if (**f == VALID_CHAR[i++])
			is_valid = 1;
	if (!is_valid)
		return (handle_char_conv(**f, specs, str));
	if (**f == '{')
		return (apply_effect(f, specs, str));
	i = 0;
	size = sizeof(g_parser) / sizeof(t_parser);
	while (i < size)
	{
		if (**f == g_parser[i].type && (specs->type = g_parser[i].flag))
			return (g_parser[i].f(ap, specs, str));
		++i;
	}
	return (0);
}

int			parse_specs(const char **f, t_specs *specs, va_list ap, char *str)
{
	++(*f);
	while (**f && !parse_type(f, specs, ap, str))
	{
		specs->flags |= (**f == '-') ? LEFT : 0;
		specs->flags |= (**f == '+') ? PLUS : 0;
		specs->flags |= (**f == ' ') ? SPACE : 0;
		specs->flags |= (**f == '#') ? PREFIX : 0;
		specs->flags |= (**f == '0') ? PAD : 0;
		specs->flags |= (**f == 'h' && *((*f) + 1) == 'h') ? MOD_HH : 0;
		specs->flags |= (!(specs->flags & MOD_HH)
				&& **f == 'h' && *((*f) + 1) != 'h') ? MOD_H : 0;
		specs->flags |= (**f == 'l' && *((*f) + 1) == 'l') ? MOD_LL : 0;
		specs->flags |= (!(specs->flags & MOD_LL)
				&& **f == 'l' && *((*f) + 1) != 'l') ? MOD_L : 0;
		specs->flags |= (**f == 'L') ? MOD_LD : 0;
		if (**f == '*' || (**f >= '1' && **f <= '9'))
			parse_width(f, specs, ap);
		if (**f == '.')
			parse_precision(f, specs, ap);
		if (**f)
			++(*f);
	}
	return (1);
}
