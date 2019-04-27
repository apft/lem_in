/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:24:44 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/27 18:15:36 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"
int		ft_nchar(char *str, char c);

static char	*get_room_name(t_list *node)
{
	return (((t_room *)node->content)->name);
}

int			handle_tube(char *line, t_env *env)
{
	(void)line;
	(void)cmd_flag;
	if (ft_nchar(line, '-') != 1)
		return (ERR_INVALID_TUBE_DEFINITION);
	get_room_name(env->map);
	return (SUCCESS);
}
