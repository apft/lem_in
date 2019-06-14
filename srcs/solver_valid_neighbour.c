/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_valid_neighbour.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:39:19 by apion             #+#    #+#             */
/*   Updated: 2019/06/14 11:20:29 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "tube.h"
#include "customlibft.h"

static int	check_neighbour_with_closed_current(t_room *current,
				t_room *neighbour)
{
	int		cost;

	if (neighbour == current->next)
		return (LOOP_CONTINUE);
	if (is_linked_on_same_path(current, neighbour))
	{
		cost = ft_min(external_cost(current), internal_cost(current)) - 1;
		if (internal_cost(neighbour) <= cost)
			return (LOOP_CONTINUE);
		neighbour->cost[1] = cost;
		if (internal_cost(neighbour) < external_cost(neighbour))
			neighbour->from_junction = 0;
	}
	else
	{
		if (is_closed_room_as_junction(current))
			return (LOOP_CONTINUE);
		cost = internal_cost(current) + 1;
		if (external_cost(neighbour) <= cost
			|| internal_cost(neighbour) <= cost
			|| (is_closed_path(neighbour) && (neighbour->dst > cost)))
			return (LOOP_CONTINUE);
		neighbour->cost[0] = cost;
	}
	return (SUCCESS);
}

static int	check_neighbour_with_open_current(t_room *current,
				t_room *neighbour, t_env *env)
{
	int		cost;

	cost = external_cost(current) + 1;
	if (is_closed_path(neighbour)
		&& has_oriented_tube_between_rooms(env->start, neighbour, env))
		return (LOOP_CONTINUE);
	if (external_cost(neighbour) <= cost || internal_cost(neighbour) <= cost)
		return (LOOP_CONTINUE);
	if (is_closed_path(neighbour))
	{
		if (neighbour->dst > cost)
			return (LOOP_CONTINUE);
	}
	neighbour->cost[0] = cost;
	return (SUCCESS);
}

static void	update_neighbour_froms(t_room *current, t_room *neighbour)
{
	if (is_closed_path(neighbour)
		&& !is_linked_on_same_path(current, neighbour))
		neighbour->from_junction = current;
	neighbour->from = current;
}

static int	add_neighbour_to_queue(t_room *neighbour, t_queue *queue)
{
	int		status;

	if (neighbour->visited == VISITED_EMPTY)
	{
		neighbour->visited = VISITED_AS_NEIGHBOUR;
		status = enqueue(queue, (void *)neighbour);
		if (status != SUCCESS)
			return (status);
	}
	else if (neighbour->visited == VISITED_AS_CURRENT)
	{
		neighbour->visited = VISITED_AS_NEIGHBOUR;
		status = prequeue(queue, (void *)neighbour);
		if (status != SUCCESS)
			return (status);
	}
	return (SUCCESS);
}

int			search_for_valid_neighbour(t_room *current, t_room *neighbour,
				t_env *env, t_queue *queue)
{
	int		status;

	if (neighbour == current->from || neighbour == current->from_junction)
		return (LOOP_CONTINUE);
	if (current == env->start && is_closed_path(neighbour))
		return (LOOP_CONTINUE);
	if (is_closed_path(current))
	{
		status = check_neighbour_with_closed_current(current, neighbour);
		if (status != SUCCESS)
			return (status);
	}
	else
	{
		status = check_neighbour_with_open_current(current, neighbour, env);
		if (status != SUCCESS)
			return (status);
	}
	update_neighbour_froms(current, neighbour);
	status = add_neighbour_to_queue(neighbour, queue);
	if (status != SUCCESS)
		return (status);
	return (LOOP_SUCCESS);
}
