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

#include <stdlib.h>
#include "parser.h"
#include "env.h"
#include "error.h"

static char	*get_room_name(t_list *node)
{
	return (((t_room *)node->content)->name);
}

static int	lst_to_array(t_env *env)
{
	t_list		*map;
	int			i;

	env->rooms_array = (t_room **)malloc(sizeof(t_room *) * env->nb_room);
	if (!env->rooms_array)
		return (errno);
	map = env->map;
	i = 0;
	while (map)
	{
		env->rooms_array[i] = (t_room *)(map->content);
		++i;
		map = map->next;
	}
	return (SUCCESS);
}

int			array_room_merge_sort(t_room **array, size_t array_size);
int			handle_tube(char *line, t_env *env, unsigned int *cmd_flag)
{
	if (*cmd_flag & BLK_ROOM)
	{
		*cmd_flag ^= BLK_ROOM | BLK_TUBE;
		if (lst_to_array(env) != SUCCESS)
			return (errno);
		array_room_merge_sort(env->rooms_array, env->nb_room);
	}
	(void)line;
	get_room_name(env->map);
	return (SUCCESS);
}
