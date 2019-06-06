/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bakery.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:47:01 by apion             #+#    #+#             */
/*   Updated: 2019/06/06 10:56:05 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"
#include "parser.h"
#include "error.h"
#include "libft.h"

/*
** can also be called "factory"
*/

void	free_unfully_malloced_matrix(int ***matrix, int index)
{
	while (index--)
		free((*matrix)[index]);
	free(*matrix);
	*matrix = NULL;
}


static int	lst_to_array(t_env *env)
{
	t_list		*map;
	int			i;

	env->rooms_array = (t_room **)malloc(sizeof(t_room *) * env->nb_rooms);
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

static int	create_adjacency_matrix(t_env *env)
{
	int		i;

	env->matrix = (int **)malloc(sizeof(int *) * env->nb_rooms);
	if (!env->matrix)
		return (errno);
	i = 0;
	while (i < env->nb_rooms)
	{
		(env->matrix)[i] = (int *)ft_memalloc(sizeof(int) * env->nb_rooms);
		if (!(env->matrix)[i])
		{
			free_unfully_malloced_matrix(&(env->matrix), i);
			return (errno);
		}
		++i;
	}
	return (SUCCESS);
}

int			bake_environment(t_env *env, unsigned int *cmd_flag)
{
	*cmd_flag ^= BLK_ROOM | BLK_TUBE;
	if (!env->map)
		return (ERR_EMPTY_MAP);
	if (!env->start)
		return (ERR_EMPTY_START);
	if (!env->end)
		return (ERR_EMPTY_END);
	if (lst_to_array(env) != SUCCESS)
		return (errno);
	if (array_room_merge_sort(env->rooms_array, env->nb_rooms) != SUCCESS)
		return (errno);
	if (create_adjacency_matrix(env) != SUCCESS)
		return (errno);
	return (SUCCESS);
}
