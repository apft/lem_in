/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:24:44 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/26 10:42:41 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "env.h"
#include "error.h"

static char	*get_room_name(t_list *node)
{
	return (((t_room *)node->content)->name);
}

static int	lst_to_array(t_env *env)
{
	(void)env;
	return (SUCCESS);
}

int			handle_tube(char *line, t_env *env, unsigned int *cmd_flag)
{
	if (*cmd_flag & BLK_ROOM)
	{
		*cmd_flag ^= BLK_ROOM | BLK_TUBE;
		if (lst_to_array(env) != SUCCESS)
			return (ERR_LST_TO_ARRAY_FAILED);
		// not good
		//ft_strarraymergesort(env->rooms_array, env->nb_room);
	}
	(void)line;
	get_room_name(env->map);
	return (SUCCESS);
}
