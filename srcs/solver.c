/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:43:55 by apion             #+#    #+#             */
/*   Updated: 2019/06/14 11:19:59 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bfs.h"
#include "path.h"
#include "cleaner.h"
#include "augmenting_path.h"
#include "error.h"
#include "output.h"

#define MAX_FLOW_REACHED 42

static int	set_room_dst(t_room *start, t_room *current, t_env *env)
{
	int		i;

	(void)start;
	i = 1;
	if (!is_closed_path(current))
		return (loop_continue);
	while (current != env->end)
	{
		current->dst = i;
		++i;
		current = current->next;
	}
	return (loop_success);
}

static int	initialize(t_env *env, t_queue *queue)
{
	int		i;
	int		status;

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
	status = enqueue(queue, (void *)env->start);
	if (status != SUCCESS)
		return (status);
	apply_foreach_room_linked_to_ref(env->start, env, 0, &set_room_dst);
	return (SUCCESS);
}

void		compute_nb_lines(t_env *env)
{
	int		sum_path_lengths;

	sum_path_lengths = 0;
	apply_foreach_room_linked_to_ref(env->start, env, &sum_path_lengths,
		&compute_sum_path_lengths);
	env->nb_lines = ((sum_path_lengths + env->nb_ants) / env->nb_paths) - 1;
	env->nb_lines += !!((sum_path_lengths + env->nb_ants) % env->nb_paths);
}

static int	has_augmenting_path(t_env *env)
{
	t_queue	queue;
	int		prev_nb_lines;
	int		status;

	if ((status = initialize(env, &queue)) != SUCCESS)
		return (status);
	if ((status = bfs_max_flow(env, &queue)) != SUCCESS)
		return (status);
	if (external_cost(env->end) == COST_INF)
		return (ERROR);
	save_augmenting_path(env);
	if (env->nb_paths == 1)
		prev_nb_lines = INT_MAX;
	else
		prev_nb_lines = env->nb_lines;
	compute_nb_lines(env);
	if (prev_nb_lines <= env->nb_lines)
	{
		if (env->nb_paths > 1)
			reset_to_previous_augmenting_path(env);
		env->nb_lines = prev_nb_lines;
		return (MAX_FLOW_REACHED);
	}
	return (SUCCESS);
}

int			solver(t_env *env)
{
	while (has_augmenting_path(env) == SUCCESS)
		;
	if (!env->nb_paths)
		return (err_env_no_path_from_start_to_end);
	return (SUCCESS);
}
