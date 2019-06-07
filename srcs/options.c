/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:30:32 by jkettani          #+#    #+#             */
/*   Updated: 2019/06/07 16:19:00 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options.h"
#include "env.h"
#include "error.h"

static int	update_flag(char c, t_uint *options)
{
	if (c == 'e')
		*options |= OP_ERR;
	else if (c == 'd')
		*options |= OP_DEBUG;
	else
		return (ERR_INVALID_OPTION);
	return (SUCCESS);
}

int			get_options(int ac, char **av, t_env *env)
{
	int			i;
	int			j;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			if (!av[i][1])
				return (ERR_INVALID_OPTION);
			j = 0;
			while (av[i][++j])
				if (update_flag(av[i][j], &env->options))
					return (ERR_INVALID_OPTION);
		}
		else
			return (ERR_INVALID_OPTION);
		++i;
	}
	return (SUCCESS);
}
