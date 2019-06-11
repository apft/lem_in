/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:43:55 by apion             #+#    #+#             */
/*   Updated: 2019/06/11 15:01:42 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "customlibft.h"
#include "path_utils.h"
#include "augmented_path.h"
#include "cleaner.h"
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

static int	closed_room_as_junction(t_room *current)
{
	if (!is_closed_path(current))
		return (0);
	return (is_junction(current) && internal_cost(current) == COST_INF);
}

static int	search_for_valid_neighbour(t_room *current, t_room *neighbour, t_env *env, t_queue *queue)
{
	int		cost_current;

	if (neighbour == current->from)
		return (LOOP_CONTINUE);
	if (neighbour == current->from_junction)
		return (LOOP_CONTINUE);
	if (current == env->start && is_closed_path(neighbour))
		return (LOOP_CONTINUE);
	if (is_closed_path(current))
	{
		if (neighbour == current->next)
			return (LOOP_CONTINUE);
		if (is_linked_on_same_path(current, neighbour))
		{
			cost_current = ft_min(external_cost(current), internal_cost(current));
			if (internal_cost(neighbour) <= (cost_current - 1))
				return (LOOP_CONTINUE);
			neighbour->cost[1] = cost_current - 1;
			if (internal_cost(neighbour) < external_cost(neighbour))
				neighbour->from_junction = 0;
		}
		else
		{
			if (closed_room_as_junction(current))
				return (LOOP_CONTINUE);
			else
				cost_current = internal_cost(current);
			if (external_cost(neighbour) <= (cost_current + 1))
				return (LOOP_CONTINUE);
			if (internal_cost(neighbour) <= (cost_current + 1))
				return (LOOP_CONTINUE);
			if (is_closed_path(neighbour))
			{
				if (neighbour->dst > (cost_current + 1))
					return (LOOP_CONTINUE);
			}
			neighbour->cost[0] = cost_current + 1;
		}
	}
	else
	{
		if (is_closed_path(neighbour) && env->matrix[env->start->id][neighbour->id])
			return (LOOP_CONTINUE);
		if (external_cost(neighbour) <= (external_cost(current) + 1))
			return (LOOP_CONTINUE);
		if (internal_cost(neighbour) <= (external_cost(current) + 1))
			return (LOOP_CONTINUE);
		if (is_closed_path(neighbour))
		{
			if (neighbour->dst > (external_cost(current) + 1))
				return (LOOP_CONTINUE);
		}
		neighbour->cost[0] = (external_cost(current) + 1);
	}
	if (is_closed_path(neighbour) && !is_linked_on_same_path(current, neighbour))
		neighbour->from_junction = current;
	//print_room(neighbour, " ");
	neighbour->from = current;
	if (neighbour->visited == VISITED_EMPTY)
	{
		neighbour->visited = VISITED_AS_NEIGHBOUR;
		enqueue(queue, (void *)neighbour);
	}
	else if (neighbour->visited == VISITED_AS_CURRENT)
	{
		neighbour->visited = VISITED_AS_NEIGHBOUR;
		prequeue(queue, (void *)neighbour);
	}
	return (LOOP_SUCCESS);
}

#include <stdlib.h>
static void	bfs_max_flow(t_env *env, t_queue *queue)
{
	t_room	*current;

	while (queue->head)
	{
		current = (t_room *)dequeue(queue);
		//print_room(current, "->{");
		current->visited = VISITED_AS_CURRENT;
		apply_foreach_room_linked_to_ref(current, env, queue, &search_for_valid_neighbour);
		//ft_printf("}\n");
		test_cost(current);
	}
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

static int	has_augmented_path(t_env *env)
{
	t_queue	queue;
	int		max_stream;
	int		status;

	initialize(env, &queue);
	bfs_max_flow(env, &queue);
	if (env->end->cost[0] == COST_INF)
		return (ERROR);
	save_augmented_path(env);
	++(env->nb_paths);
	status = compute_max_stream(&max_stream, env);
	if (status != SUCCESS)
		return (status);
	if (max_stream >= env->nb_ants)
	{
		if (env->nb_paths > 1)
		{
			reset_to_previous_augmented_path(env);
			--(env->nb_paths);
		}
		return (MAX_FLOW_REACHED);
	}
	return (SUCCESS);
}

int		solver(t_env *env)
{
	while (has_augmented_path(env) == SUCCESS)
	{
		test_flow(env);
	}
	if (!env->nb_paths)
		return (ERR_NO_PATH_FOUND);
	return (SUCCESS);
}
