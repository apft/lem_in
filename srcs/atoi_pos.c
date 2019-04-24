/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:38:01 by apion             #+#    #+#             */
/*   Updated: 2019/04/24 16:40:37 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef INT_MIN
# define INT_MIN 0xffffffff
#endif

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
	int		sign;

	*n = 0;
	sign = 1;
	jump_spaces(str);
	if (!**str)
		return (0);
	if (**str == '+' || **str == '-')
		sign = *((*str)++) == '-' ? -1 : 1;
	if (!**str || (**str && !ft_isdigit(**str)))
		return (0);
	while (ft_isdigit(**str))
	{
		*n = 10 * (*n) + (*((*str)++) - '0');
		if ((*n < 0 && *n != INT_MIN) || (sign > 0 && *n == INT_MIN))
			return (0);
	}
	if (!**str || !(jump_spaces(str) && !**str))
		return (0);
	*n *= sign;
	return (1);
}
