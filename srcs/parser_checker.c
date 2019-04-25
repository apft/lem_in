/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:24:44 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/25 18:24:21 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "parser.h"

static int	get_room_name(t_list *node)
{
	return (((t_room *)node->content)->name);
}

static int	lst_to_array(t_env *env)
{
	return (SUCCESS);
}

static int	handle_tube(char *line, t_env *env, unsigned int *cmd_flag)
{
	if (*cmd_flag & BLK_ROOM)
	{
		*cmd_flag ^= BLK_ROOM | BLK_TUBE;
		if (lst_to_array(env) != SUCCESS)
			return (ERR_LST_TO_ARRAY_FAILED);
		// not good
		ft_strarraymergesort(env->rooms_array, env->nb_room);
	}
	return (SUCCESS);
}

int			handle_room_or_tube(char *line, t_env *env, unsigned int *cmd_flag)
{
	if (ft_strchr(line, '-'))
		return (handle_tube(line, env, cmd_flag));
	else
		return (handle_room(line, env, cmd_flag));
}
