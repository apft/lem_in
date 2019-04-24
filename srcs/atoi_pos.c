/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:38:01 by apion             #+#    #+#             */
/*   Updated: 2019/04/24 17:38:38 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	jump_spaces(char **str)
{
	int		has_jumped;

	has_jumped = 0;
	while (ft_isspace(**str) && (has_jumped = 1))
		++(*str);
	return (has_jumped);
}

int			atoi_pos(char **str, int *n)
{
	*n = 0;
	jump_spaces(str);
	if (!**str)
		return (ERR_ATOI_EMPTY);
	if (**str == '-')
		return (ERR_ATOI_NEG);
	if (**str == '+')
		++(*str);
	if (!**str || (**str && !ft_isdigit(**str)))
		return (ERR_ATOI_EMPTY);
	while (ft_isdigit(**str))
	{
		*n = 10 * (*n) + (*((*str)++) - '0');
		if (*n < 0)
			return (ERR_ATOI_OVERFLOW);
	}
	if (!**str || !(jump_spaces(str) && !**str))
		return (ERR_ATOI_INVALID_CHAR);
	return (SUCCESS);
}
