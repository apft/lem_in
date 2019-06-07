/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:08:05 by jkettani          #+#    #+#             */
/*   Updated: 2019/06/07 12:35:01 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_utils.h"
#include "generic_merge_sort.h"
#include "error.h"

static void	compute_streams(t_env *env)
{
	int		i;
	int		j;

	i = 0;
	while (i < env->nb_paths)
	{
		j = i;
		while (j--)
			env->paths_array[i]->nb_ants_stream += env->paths_array[i]->length
				- env->paths_array[j]->length + 1;
		++i;
	}
}

static int	cmp_array_lengths(t_path **elm1, t_path **elm2)
{
	return ((*elm1)->length - (*elm2)->length);
}

static int	sort_paths_array(t_env *env)
{
	t_array_args	args;
	int				status;

	args = (t_array_args){env->paths_array, sizeof(t_path *), env->nb_paths,
				&cmp_array_lengths};
	status = array_merge_sort(&args);
	if (status != SUCCESS)
		return (status);
	return (SUCCESS);
}

static void	update_paths_links(t_env *env)
{
	int		i;
	t_room	*current;
	t_room	*from;

	i = 0;
	while (i < env->nb_paths)
	{
		from = env->start;
		current = env->paths_array[i]->front;
		while (current != env->end)
		{
			current->from = from;
			from = current;
			current = current->next;
		}
		++i;
	}
}

int			fill_paths_array(t_env *env, int update_links)
{
	int		status;

	status = create_paths_array(env, env->nb_paths);
	if (status != SUCCESS)
		return (status);
	status = sort_paths_array(env);
	if (status != SUCCESS)
		return (status);
	compute_streams(env);
	if (update_links)
		update_paths_links(env);
	return (SUCCESS);
}
