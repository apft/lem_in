/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:38:01 by apion             #+#    #+#             */
/*   Updated: 2019/04/26 21:03:44 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "atoi_pos.h"
#include "libft.h"
#include "error.h"

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
	int		is_neg;

	tmp = 0;
	is_neg = 0;
	str += jump_spaces(str);
	if (!*str)
		return (ERR_ATOI_EMPTY);
	if (ft_issign(*str))
		is_neg = *str++ == '-' ? 1 : 0;
	if (!*str || (*str && !ft_isdigit(*str)))
		return (ERR_ATOI_NO_DIGITS);
	while (ft_isdigit(*str))
	{
		tmp = 10 * tmp + *str++ - '0';
		if (tmp > INT_MAX)
			return (ERR_ATOI_OVERFLOW);
	}
	if (!is_valid_part_after_nb(str, context))
		return (ERR_ATOI_INVALID_CHAR);
	if (is_neg && tmp)
		return (ERR_ATOI_NEG);
	*n = tmp;
	return (SUCCESS);
}
