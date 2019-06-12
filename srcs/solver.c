/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:43:55 by apion             #+#    #+#             */
/*   Updated: 2019/06/12 16:21:35 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bfs.h"
#include "path_utils.h"
#include "cleaner.h"
#include "augmenting_path.h"
#include "error.h"
#include "output.h"
#include "tests.h"

#define MAX_FLOW_REACHED 42

static int	set_room_dst(t_room *start, t_room *current, t_env *env)
{
	int		i;

	(void)start;
	i = 1;
	if (!is_closed_path(current))
		return (LOOP_CONTINUE);
	while (current != env->end)
	{
		current->dst = i;
		++i;
		current = current->next;
	}
	return (LOOP_SUCCESS);
}

static void	initialize(t_env *env, t_queue *queue)
{
	int		i;

	i = 0;
	while (i < env->nb_rooms)
	{
		env->rooms_array[i]->visited = VISITED_EMPTY;
		env->rooms_array[i]->from_junction = (void *)0;
		env->rooms_array[i]->from = (void *)0;
		env->rooms_array[i]->cost[0] = COST_INF;
		env->rooms_array[i]->cost[1] = COST_INF;
		++i;
	}
	env->start->cost[0] = 0;
	*queue = (t_queue){0, 0};
	enqueue(queue, (void *)env->start);
	apply_foreach_room_linked_to_ref(env->start, env, 0, &set_room_dst);
}

static int	compute_max_stream(int *max_stream, t_env *env)
{
	int		status;

	status = fill_paths_array(env, NO_UPDATE_LINKS);
	if (status != SUCCESS)
		return (status);
	*max_stream = env->paths_array[env->nb_paths - 1]->nb_ants_stream;
	free_ptr_array_to_index((void ***)&env->paths_array, env->nb_paths);
	return (status);
}

static int	has_augmenting_path(t_env *env)
{
	t_queue	queue;
	int		max_stream;
	int		status;

	initialize(env, &queue);
	bfs_max_flow(env, &queue);
	if (external_cost(env->end) == COST_INF)
		return (ERROR);
	save_augmenting_path(env);
	status = compute_max_stream(&max_stream, env);
	if (status != SUCCESS)
		return (status);
	if (max_stream >= env->nb_ants)
	{
		if (env->nb_paths > 1)
			reset_to_previous_augmenting_path(env);
		return (MAX_FLOW_REACHED);
	}
	return (SUCCESS);
}

int			solver(t_env *env)
{
	while (has_augmenting_path(env) == SUCCESS)
	{
		test_flow(env);
	}
	if (!env->nb_paths)
		return (ERR_NO_PATH_FOUND);
	return (SUCCESS);
}
