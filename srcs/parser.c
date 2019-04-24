/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:57:48 by apion             #+#    #+#             */
/*   Updated: 2019/04/24 16:19:03 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"
#include "env.h"
#include "error.h"

static int	get_number_ants(t_env *env)
{
	char	*line;
	int		len;
	int		eol_had_newline;

	len = get_next_line(STDIN_FILEN0, &line, &eol_had_newline);
	if (len == GNL_ERROR)
		return (ERR_READ);
	t_env->ants = 0;
	return (0);
}


int		parser(t_env *env)
{
	char	*line;
	int		len;
	int		eol_had_newline;

	if (get_number_ants(env) < 0)
		return (ERR_ANTS);
	while ((len = get_next_line(STDIN_FILEN0, &line, &eol_had_newline)) >= 0)
	{
	}
	return (0);
}
