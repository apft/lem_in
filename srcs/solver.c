/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:43:55 by apion             #+#    #+#             */
/*   Updated: 2019/06/05 10:59:55 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "customlibft.h"
#include "error.h"
#include "output.h"
#include "ft_printf.h"

static int	set_room_dst(t_room *start, t_room *current, t_env *env)
{
	int		i;

	(void)start;
	i = 1;
	if (!is_closed_path(current))
		return (SUCCESS);
	while (current != env->end)
	{
		current->dst = i;
		++i;
		current = current->next;
	}
	return (SUCCESS);
}

static void	open_path(t_room **room_from, t_room *first_next)
{
	t_room	*current;
	t_room	*next;

	current = (*room_from)->next;
	(*room_from)->next = first_next;
	while (!is_junction(current))
	{
		current->flag ^= FL_CLOSE_PATH;
		next = current->next;
		current->next = 0;
		current = next;
	}
	*room_from = current->from_junction;
	if (is_closed_path(*room_from))
		open_path(room_from, current);
	(*room_from)->next = current;
	(*room_from)->flag |= FL_CLOSE_PATH;
}

static int	save_path(t_env *env)
{
	t_room	*current;
	t_room	*next;

	current = env->end;
	next = 0;
	while (current->from)
	{
		if (current != env->end)
		{
			if (!is_closed_path(current))
			{
				current->flag |= FL_CLOSE_PATH;
				current->next = next;
			}
			else
				open_path(&current, next);
		}
		else
			current->next = next;
		next = current;
		current = current->from;
	}
	return (SUCCESS);
}

static int	closed_room_seen_from_ext_only(t_room *current)
{
	if (!is_closed_path(current))
		return (0);
	return (current->from_junction && (internal_cost(current) == COST_INF));
}

static int	closed_room_seen_from_int_only(t_room *current)
{
	if (!is_closed_path(current))
		return (0);
	return (!is_junction(current));
}

static int	search_for_valid_neighbour(t_room *current, t_room *neighbour, t_env *env, t_queue *queue)
{
	if (neighbour == current->from)
		return (SUCCESS);
	if (current == env->start && is_closed_path(neighbour))
		return (SUCCESS);
	if (is_closed_path(neighbour) && !is_linked_on_same_path(current, neighbour))
	{
		if (is_junction(neighbour) && neighbour->from_junction == current)
			return (SUCCESS);
	}
	if (is_closed_path(current))
	{
		if (neighbour == current->next)
			return (SUCCESS);
		if (closed_room_seen_from_ext_only(current))
		{
			if (!is_linked_on_same_path(current, neighbour))
				return (SUCCESS);
			if (internal_cost(neighbour) <= (external_cost(current) - 1))
				return (SUCCESS);
			neighbour->cost[1] = (external_cost(current) - 1);
		}
		else if (closed_room_seen_from_int_only(current))
		{
			if (is_linked_on_same_path(current, neighbour))
			{
				if (internal_cost(neighbour) <= (internal_cost(current) - 1))
					return (SUCCESS);
				neighbour->cost[1] = (internal_cost(current) - 1);
			}
			else
			{
				if (external_cost(neighbour) <= (internal_cost(current) + 1))
					return (SUCCESS);
				if (neighbour->visited == VISITED_EMPTY && is_closed_path(neighbour) && neighbour->dst > (external_cost(current) + 1))
					return (SUCCESS);
				if (neighbour->visited != VISITED_EMPTY && is_closed_path(neighbour) && neighbour->dst >= (external_cost(current) + 1))
					return (SUCCESS);
				neighbour->cost[0] = internal_cost(current) + 1;
			}
		}
		else
		{
			if (is_linked_on_same_path(current, neighbour))
			{
				if (internal_cost(neighbour) <= (ft_min(external_cost(current), internal_cost(current)) - 1))
					return (SUCCESS);
				 neighbour->cost[1] = (ft_min(external_cost(current), internal_cost(current)) - 1);
			}
			else
			{
				if (external_cost(neighbour) <= (internal_cost(current) + 1))
					return (SUCCESS);
				if (internal_cost(neighbour) <= (internal_cost(current) + 1))
					return (SUCCESS);
				if (neighbour->visited == VISITED_EMPTY && is_closed_path(neighbour) && neighbour->dst > (external_cost(current) + 1))
					return (SUCCESS);
				if (neighbour->visited != VISITED_EMPTY && is_closed_path(neighbour) && neighbour->dst >= (external_cost(current) + 1))
					return (SUCCESS);
				neighbour->cost[0] = internal_cost(current) + 1;
			}
		}
	}
	else
	{
		if (is_closed_path(neighbour) && env->matrix[env->start->id][neighbour->id])
			return (SUCCESS);
		if (external_cost(neighbour) <= (external_cost(current) + 1))
			return (SUCCESS);
		if (internal_cost(neighbour) <= (external_cost(current) + 1))
			return (SUCCESS);
		if (neighbour->visited == VISITED_EMPTY && is_closed_path(neighbour) && neighbour->dst > (external_cost(current) + 1))
			return (SUCCESS);
		if (neighbour->visited != VISITED_EMPTY && is_closed_path(neighbour) && neighbour->dst >= (external_cost(current) + 1))
			return (SUCCESS);
		neighbour->cost[0] = (external_cost(current) + 1);
	}
	if (is_closed_path(neighbour) && !is_linked_on_same_path(current, neighbour))
		neighbour->from_junction = current;
//	print_room(neighbour, " ");
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
	return (SUCCESS);
}

#include <stdlib.h>
static void	bfs_max_flow(t_env *env, t_queue *queue)
{
	t_room	*current;

	while (queue->head)
	{
		current = (t_room *)dequeue(queue);
//		print_room(current, "->{");
		current->visited = VISITED_AS_CURRENT;
		apply_foreach_room_linked_to_ref(current, env, queue, &search_for_valid_neighbour);
//		ft_printf("}\n");
		if (internal_cost(current) < 0 || external_cost(current) < 0)
		{
//			ft_printf("error");
			exit(1);
		}
	}
}

static void	initialize(t_env *env, t_queue *queue)
{
	int		i;

	i = 0;
	while (i < env->nb_room)
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

static int	has_augmenting_path(t_env *env)
{
	t_queue	queue;

	initialize(env, &queue);
	bfs_max_flow(env, &queue);
	if (env->end->cost[0] == COST_INF)
		return (ERROR);
	save_path(env);
	return (SUCCESS);
}

int		solver(t_env *env)
{
	int		flow;

	flow = 0;
	while (has_augmenting_path(env) == SUCCESS)
	{
		flow += env->end->cost[0] - 1;
		ft_printf("\n");
		ft_printf("Loop %d:\n", env->nb_path);
		print_paths(env);
		++(env->nb_path);
	}
	ft_printf("\n\nflow= %d\n", flow);
	if (!env->nb_path)
		return (ERR_NO_PATH_FOUND);
	return (SUCCESS);
}
