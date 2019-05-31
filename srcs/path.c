/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:19:48 by apion             #+#    #+#             */
/*   Updated: 2019/05/31 17:06:13 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"
#include "bakery.h"
#include "error.h"

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

static void	sort_array_path(t_env *env, int nb_path)
{
}

static int	add_path_to_array(t_room *start, t_room *current, t_env *env, int *index)
{
	int		length;

	if (!is_closed_path(current))
		return ;
	env->paths_array[*index] = (t_path *)malloc(sizeof(*path));
	if (!env->paths_array[*index])
		return (free_unfully_malloced_matrix_and_return(env->paths_array, *index));
	length = compute_path_length(current);
	*env->paths_array[*index] = (t_path){current, current, current, length};
	++(*index);
}

static int	create_path_array(t_env *env, int nb_path)
{
	int		status;
	int		i;

	env->paths_array = (t_path **)malloc(sizeof(t_path *) * nb_path);
	if (!env->paths_array)
		return (errno);
	i = 0;
	status = apply_foreach_room_linked_to_ref(env->start, env, &i, &add_path_to_array);
	if (status != SUCCESS)
		return (status);
	return (SUCCESS);
}

int			fill_path_array(t_env *env)
{
	int		status;

	status = create_path_array(env, env->nb_path);
	if (status != SUCCESS)
		return (status);
	sort_array_path(env, env->nb_path);
}
