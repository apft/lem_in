/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:38:01 by apion             #+#    #+#             */
/*   Updated: 2019/04/26 10:13:48 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atoi_pos.h"
#include "libft.h"
#include "error.h"

static int	jump_spaces(char *str)
{
	int		has_jumped;

	has_jumped = 0;
	while (ft_isspace(*str) && (has_jumped = 1))
		++str;
	return (has_jumped);
}

static int	is_valid_part_after_nb(char *str, unsigned int context)
{
	return (((context == ATOI_NBR_AND_SPACES_ONLY) && jump_spaces(str) && !*str)
			|| ((context == ATOI_NBR_IN_STR) && ft_isspace(*str)));
}

int			atoi_pos(char *str, int *n, unsigned int context)
{
	*n = 0;
	jump_spaces(str);
	if (!*str)
		return (ERR_ATOI_EMPTY);
	if (*str == '-')
		return (ERR_ATOI_NEG);
	if (*str == '+')
		++str;
	if (!*str || (*str && !ft_isdigit(*str)))
		return (ERR_ATOI_NO_DIGITS);
	while (ft_isdigit(*str))
	{
		*n = 10 * (*n) + *str++ - '0';
		if (*n < 0)
			return (ERR_ATOI_OVERFLOW);
	}
	if (!*str || !is_valid_part_after_nb(str, context))
		return (ERR_ATOI_INVALID_CHAR);
	return (SUCCESS);
}
