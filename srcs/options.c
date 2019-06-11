/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:30:32 by jkettani          #+#    #+#             */
/*   Updated: 2019/06/11 10:36:12 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options.h"
#include "env.h"
#include "error.h"

t_option	g_option[] =
{
	{'e', OP_ERR},
	{'d', OP_DEBUG}
};

static int	update_flag(char c, t_uint *options)
{
	size_t	size;

	size = sizeof(g_option) / sizeof(t_option);
	while (size--)
	{
		if (g_option[size].c == c)
		{
			*options |= g_option[size].flag;
			return (SUCCESS);
		}
	}
	return (ERR_INVALID_OPTION);
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
