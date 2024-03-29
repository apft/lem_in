/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:19:48 by apion             #+#    #+#             */
/*   Updated: 2019/06/14 11:17:25 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "room.h"
#include "path.h"
#include "cleaner.h"
#include "error.h"
#include <stdlib.h>

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

int			compute_sum_path_lengths(t_room *start, t_room *current, t_env *env,
						int *lengths)
{
	(void)start;
	(void)env;
	if (!is_closed_path(current))
		return (loop_continue);
	*lengths += compute_path_length(current);
	return (loop_success);
}

static int	add_path_to_array(t_room *start, t_room *current, t_env *env,
						int *index)
{
	int		length;

	(void)start;
	if (!is_closed_path(current))
		return (loop_continue);
	env->paths_array[*index] = (t_path *)malloc(sizeof(t_path));
	if (!env->paths_array[*index])
	{
		free_ptr_array_to_index((void ***)&env->paths_array, *index);
		return (errno);
	}
	length = compute_path_length(current);
	*env->paths_array[*index] = (t_path){current, current, current, length, 0,
		0};
	++(*index);
	return (loop_success);
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
