/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:57:48 by apion             #+#    #+#             */
/*   Updated: 2019/04/24 18:20:25 by apion            ###   ########.fr       */
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
	int		status;

	len = get_next_line(STDIN_FILEN0, &line, &eol_had_newline);
	if (len == GNL_ERROR)
		return (ERR_READ);
	status = atoi_pos(line, &(env->nb_ants));
	if (status == SUCCESS)
		if (list_line_add_first(&env->map, line))
			return (errno);
	return (status);
}


int		parser(t_env *env)
{
	char	*line;
	int		len;
	int		eol_had_newline;
	int		status;

	if ((status = get_number_ants(env)) != SUCCESS)
		return (status);
	while ((len = get_next_line(STDIN_FILEN0, &line, &eol_had_newline)) >= 0)
	{
		list_add_first(&env->map, line);
	}
	if (!eol_had_newline)
		return (ERR_EOF_NO_NEWLINE)
	if (len == GNL_ERROR)
		return (errno);
	return (SUCCESS);
}
