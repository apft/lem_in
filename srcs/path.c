/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:19:48 by apion             #+#    #+#             */
/*   Updated: 2019/06/11 11:57:39 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "room.h"
#include "path.h"
#include "error.h"
#include <stdlib.h>

static void	free_unfully_malloced_paths_array(t_path ***matrix, int index)
{
	while (index--)
		free((*matrix)[index]);
	free(*matrix);
	*matrix = NULL;
}

static int	compute_path_length(t_room *current)
{
	int		length;

	length = 0;
	while (current)
	{
		current = current->next;
		++length;
	}
	return (length);
}

static int	add_path_to_array(t_room *start, t_room *current, t_env *env,
								int *index)
{
	int		length;

	(void)start;
	if (!is_closed_path(current))
		return (LOOP_CONTINUE);
	env->paths_array[*index] = (t_path *)malloc(sizeof(t_path));
	if (!env->paths_array[*index])
	{
		free_unfully_malloced_paths_array(&env->paths_array, *index);
		return (errno);
	}
	length = compute_path_length(current);
	*env->paths_array[*index] = (t_path){current, current, current, length, 0,
											0};
	++(*index);
	return (LOOP_SUCCESS);
}

int			create_paths_array(t_env *env, int nb_path)
{
	int		status;
	int		i;

	env->paths_array = (t_path **)malloc(sizeof(t_path *) * nb_path);
	if (!env->paths_array)
		return (errno);
	i = 0;
	status = apply_foreach_room_linked_to_ref(env->start, env, &i,
			&add_path_to_array);
	if (status != SUCCESS)
		return (status);
	return (SUCCESS);
}
