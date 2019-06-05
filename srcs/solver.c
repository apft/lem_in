/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:43:55 by apion             #+#    #+#             */
/*   Updated: 2019/06/04 16:29:27 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "customlibft.h"
#include "error.h"
#include "output.h"
#include "ft_printf.h"

static void	set_room_dst(t_room *start, t_room *current, t_env *env, int *dst)
{
	int		i;

	(void)start;
	(void)dst;
	i = 1;
	if (!is_closed_path(current))
		return ;
	while (current != env->end)
	{
		current->dst = i;
		++i;
		current = current->next;
	}
}

static void	open_path(t_room **room_from, t_room *first_next)
{
	t_room	*current;
	t_room	*next;

	ft_printf("open_path\n");
	current = (*room_from)->next;
		print_room(current, "\n");
	(*room_from)->next = first_next;
	while (!is_junction(current))
	{
		current->flag ^= FL_CLOSE_PATH;
		next = current->next;
		current->next = 0;
		current = next;
		print_room(current, "\n");
	}
	*room_from = current->from_junction;
	current->from_junction = 0;
	print_room(*room_from, "\n");
	if (is_closed_path(*room_from))
	{
		ft_printf("open_path_rec\n");
		open_path(room_from, current);
	}
	else
		(*room_from)->next = current;
	(*room_from)->flag |= FL_CLOSE_PATH;
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

static int	closed_room_seen_from_ext_only(t_room *current)
{
	if (!is_closed_path(current))
		return (0);
	return (is_junction(current) && (internal_cost(current) == COST_INF));
}

static int	closed_room_seen_from_int_only(t_room *current)
{
	if (!is_closed_path(current))
		return (0);
	return (!is_junction(current));
}

static void	search_for_valid_neighbour(t_room *current, t_room *neighbour, t_env *env, t_queue *queue)
{
	if (neighbour == current->from)
		return ;
	if (neighbour == current->from_junction)
		return ;
	if (current == env->start && is_closed_path(neighbour))
		return ;
	//if (is_junction(neighbour) && !is_linked_on_same_path(current, neighbour))
//	if (is_junction(neighbour) && neighbour->from_junction == current)
//		return ;
	if (is_closed_path(current))
	{
		if (neighbour == current->next)
			return ;
		if (closed_room_seen_from_ext_only(current))
		{
			if (!is_linked_on_same_path(current, neighbour))
				return ;
			if (neighbour->visited == VISITED_AS_NEIGHBOUR)
				return ;
			if (internal_cost(neighbour) <= (external_cost(current) - 1))
				return ;
			neighbour->cost[1] = (external_cost(current) - 1);
		}
		else if (closed_room_seen_from_int_only(current))
		{
			if (is_linked_on_same_path(current, neighbour))
			{
				if (internal_cost(neighbour) <= (internal_cost(current) - 1))
					return ;
				if (neighbour->visited == VISITED_AS_NEIGHBOUR)
					return ;
				if (is_junction(neighbour) && external_cost(neighbour) <= (internal_cost(current) - 1))
					return ;
				neighbour->from_junction = 0;
				neighbour->cost[1] = (internal_cost(current) - 1);
			}
			else
			{
				if (external_cost(neighbour) <= (internal_cost(current) + 1))
					return ;
				if (neighbour->visited == VISITED_EMPTY && is_closed_path(neighbour) && neighbour->dst > (internal_cost(current) + 1))
					return ;
				if (neighbour->visited != VISITED_EMPTY && is_closed_path(neighbour) && neighbour->dst >= (internal_cost(current) + 1))
					return ;
				neighbour->cost[0] = internal_cost(current) + 1;
			}
		}
		else
		{
			if (is_linked_on_same_path(current, neighbour))
			{
				if (is_junction(current))
				{
					if (internal_cost(neighbour) <= (external_cost(current) - 1))
						return ;
					neighbour->cost[1] = external_cost(current) - 1;
				}
				else {
					if (internal_cost(neighbour) <= (internal_cost(current) - 1))
						return ;
					neighbour->cost[1] = internal_cost(current) - 1;
				}
				neighbour->from_junction = 0;
			}
			else
			{
				if (external_cost(neighbour) <= (internal_cost(current) + 1))
					return ;
				if (internal_cost(neighbour) <= (internal_cost(current) + 1))
					return ;
				if (neighbour->visited == VISITED_EMPTY && is_closed_path(neighbour) && neighbour->dst > (internal_cost(current) + 1))
					return ;
				if (neighbour->visited != VISITED_EMPTY && is_closed_path(neighbour) && neighbour->dst >= (internal_cost(current) + 1))
					return ;
				neighbour->cost[0] = internal_cost(current) + 1;
			}
		}
	}
	else
	{
		if (is_closed_path(neighbour) && env->matrix[env->start->id][neighbour->id])
			return ;
		if (external_cost(neighbour) <= (external_cost(current) + 1))
			return ;
		if (internal_cost(neighbour) <= (external_cost(current) + 1))
			return ;
		if (neighbour->visited == VISITED_EMPTY && is_closed_path(neighbour) && neighbour->dst > (external_cost(current) + 1))
			return ;
		if (neighbour->visited != VISITED_EMPTY && is_closed_path(neighbour) && neighbour->dst >= (external_cost(current) + 1))
			return ;
		neighbour->cost[0] = (external_cost(current) + 1);
	}
	if (is_closed_path(neighbour) && !is_linked_on_same_path(current, neighbour))
		neighbour->from_junction = current;
	print_room(neighbour, " ");
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
}

#include <stdlib.h>
static void	bfs_max_flow(t_env *env, t_queue *queue)
{
	t_room	*current;

	while (queue->head)
	{
		current = (t_room *)dequeue(queue);
		print_room(current, "->{");
		current->visited = VISITED_AS_CURRENT;
		apply_foreach_room_linked_to_ref(current, env, queue, &search_for_valid_neighbour);
		ft_printf("}\n");
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

static void	add_path_length(t_room *start, t_room *current, t_env *env, int *flow)
{
	(void)start;
	(void)env;
	if (!is_closed_path(current))
		return ;
	*flow += compute_path_length(current);
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
	if (!nb_path)
		return (ERR_NO_PATH_FOUND);
	return (SUCCESS);
}
