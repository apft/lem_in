/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:38:01 by apion             #+#    #+#             */
/*   Updated: 2019/06/14 10:47:49 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atoi_pos.h"
#include "libft.h"
#include "error.h"

#define ATOI_MAX_POS	((long)0x7fffffff)
#define ATOI_MAX_NEG	((long)0x80000000)

static int	jump_spaces(char *str)
{
	int		i;

	i = 0;
	while (ft_isspace(*(str + i)))
		++i;
	return (i);
}

static int	is_valid_part_after_nb(char *str, unsigned int context)
{
	if (!*str)
		return (1);
	if ((context == ATOI_NBR_AND_SPACES_ONLY) && !*(str + jump_spaces(str)))
		return (1);
	if ((context == ATOI_NBR_IN_STR) && ft_isspace(*str))
		return (1);
	return (0);
}

int			atoi_pos(char *str, int *n, unsigned int context)
{
	long	tmp;
	int		sign;

	tmp = 0;
	sign = 1;
	str += jump_spaces(str);
	if (!*str)
		return (ERR_ATOI_EMPTY);
	if (ft_issign(*str))
		sign = *str++ == '-' ? -1 : 1;
	if (!*str || (*str && !ft_isdigit(*str)))
		return (ERR_ATOI_NO_DIGITS);
	while (ft_isdigit(*str))
	{
		tmp = 10 * tmp + *str++ - '0';
		if ((sign > 0 && tmp > ATOI_MAX_POS)
			|| (sign < 0 && tmp > ATOI_MAX_NEG))
			return (ERR_ATOI_OVERFLOW);
	}
	if (!is_valid_part_after_nb(str, context))
		return (ERR_ATOI_INVALID_CHAR);
	*n = (int)(sign * tmp);
	return (SUCCESS);
}
