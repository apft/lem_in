/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:43:55 by apion             #+#    #+#             */
/*   Updated: 2019/06/05 17:50:54 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "customlibft.h"
#include "error.h"
#include "output.h"
#include "ft_printf.h"

#define MAX_FLOW	0
#define MAX_FLOW_REACHED 42

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

static void	open_path(t_room **room_junction, t_room *next)
{
	t_room	*current;

	ft_printf("open_path\n");
	current = (*room_junction)->next;
	print_room(current, "\n");
	(*room_junction)->next = next;
	while (!is_junction(current))
	{
		current->flag ^= FL_CLOSE_PATH;
		next = current->next;
		current->next = 0;
		current = next;
		print_room(current, "\n");
	}
	*room_junction = current->from_junction;
	current->from_junction = 0;
	print_room(*room_junction, "\n");
	if (is_closed_path(*room_junction))
	{
		ft_printf("open_path_rec\n");
		open_path(room_junction, current);
	}
	else
		(*room_junction)->next = current;
	(*room_junction)->flag |= FL_CLOSE_PATH;
}

static int	save_path(t_env *env)
{
	t_room	*current;
	t_room	*next;

	ft_printf("save_path\n");
	current = env->end;
	next = 0;
	while (current->from)
	{
		print_room(current, "\n");
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

static int	closed_room_as_junction(t_room *current)
{
	if (!is_closed_path(current))
		return (0);
	return (is_junction(current) && (external_cost(current) < internal_cost(current)));
}

static int	search_for_valid_neighbour(t_room *current, t_room *neighbour, t_env *env, t_queue *queue)
{
	if (neighbour == current->from)
		return (SUCCESS);
	if (neighbour == current->from_junction)
		return (SUCCESS);
	if (current == env->start && is_closed_path(neighbour))
		return (SUCCESS);
	if (is_closed_path(current))
	{
		if (neighbour == current->next)
			return (SUCCESS);
		if (closed_room_as_junction(current))
		{
			if (!is_linked_on_same_path(current, neighbour))
				return (SUCCESS);
			if (internal_cost(neighbour) <= (external_cost(current) - 1))
				return (SUCCESS);
			if (is_junction(neighbour) && external_cost(neighbour) <= (external_cost(current) - 1))
				return (SUCCESS);
			neighbour->from_junction = 0;
			neighbour->cost[1] = (external_cost(current) - 1);
		}
		else
		{
			if (is_linked_on_same_path(current, neighbour))
			{
				if (internal_cost(neighbour) <= (internal_cost(current) - 1))
					return (SUCCESS);
				if (is_junction(neighbour) && external_cost(neighbour) <= (internal_cost(current) - 1))
					return (SUCCESS);
				neighbour->from_junction = 0;
				neighbour->cost[1] = (internal_cost(current) - 1);
			}
			else
			{
				if (external_cost(neighbour) <= (internal_cost(current) + 1))
					return (SUCCESS);
				if (internal_cost(neighbour) <= (internal_cost(current) + 1))
					return (SUCCESS);
				if (is_closed_path(neighbour))
				{
					if (neighbour->dst > (internal_cost(current) + 1))
						return (SUCCESS);
				}
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
		if (is_closed_path(neighbour))
		{
			if (neighbour->dst > (external_cost(current) + 1))
				return (SUCCESS);
		}
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
			ft_dprintf(2, "error: negative cost");
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
	if (MAX_FLOW && env->flow + external_cost(env->end) > env->nb_ants)
		return (MAX_FLOW_REACHED);
	save_path(env);
	return (SUCCESS);
}

static int      compute_path_length(t_room *current)
{
	int             length;

	length = 0;
	while (current)
	{
		current = current->next;
		++length;
	}
	return (length);
}

static int	add_path_length(t_room *start, t_room *current, t_env *env, int *flow)
{
	(void)start;
	(void)env;
	if (!is_closed_path(current))
		return (SUCCESS);
	*flow += compute_path_length(current);
	return (SUCCESS);
}

static int	compute_flow(t_env *env)
{
	int		flow;

	flow = 0;
	apply_foreach_room_linked_to_ref(env->start, env, &flow, &add_path_length);
	return (flow);
}

int		solver(t_env *env)
{
	int		flow;
	int		nb_path;
	int		flow_2;

	flow = 0;
	flow_2 = 0;
	nb_path = 0;
	while (has_augmenting_path(env) == SUCCESS)
	{
		flow = compute_flow(env);
		env->flow += external_cost(env->end);
		flow_2 += env->end->cost[0];
		ft_printf("\n\nnb_path= %d, flow= %d", nb_path, flow);
		ft_printf("Loop %d:\n", nb_path);
		print_paths(env);
		if (flow != flow_2)
		{
			ft_dprintf(2, "error: flow: %d, flow_2: %d, cost(end): %d\n", flow, flow_2, env->end->cost[0]);
			exit(2);
		}
		++nb_path;
	}
	ft_printf("\n\nnb_path= %d, flow= %d", nb_path, flow);
	env->nb_path = nb_path;
	if (!nb_path)
		return (ERR_NO_PATH_FOUND);
	return (SUCCESS);
}
