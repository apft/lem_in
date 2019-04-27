/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:24:44 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/26 22:09:05 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"

static char	*get_room_name(t_list *node)
{
	return (((t_room *)node->content)->name);
}

int			handle_tube(char *line, t_env *env, unsigned int *cmd_flag)
{
	(void)line;
	get_room_name(env->map);
	return (SUCCESS);
}
