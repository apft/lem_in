/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:43:55 by apion             #+#    #+#             */
/*   Updated: 2019/06/07 12:39:58 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "customlibft.h"
#include "path_utils.h"
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

static void	open_path(t_room **current, t_room **next)
{
	t_room	*room_boundary;
	t_room	*from;

	//ft_printf("open_path\n");
	room_boundary = *current;
	*current = room_boundary->next;
	room_boundary->next = *next;
	room_boundary->from = *next;
	from = room_boundary;
	//print_room(room_boundary, "\n");
	//print_room(*current, "\t\t");
	while (!is_junction(*current))
	{
		(*current)->flag ^= FL_CLOSE_PATH;
		*next = (*current)->next;
		(*current)->next = 0;
		(*current)->from = from;
		from = *current;
		//print_room(*current, "\n");
		*current = *next;
		//print_room(*current, "\t\t");
	}
	room_boundary = *current;
	*current = room_boundary->from_junction;
	room_boundary->from = from;
	*next = room_boundary;
	//print_room(room_boundary, "\n");
	//print_room(*current, "\n");
}

static int	save_path(t_env *env)
{
	t_room	*current;
	t_room	*from;
	t_room	*next;

	//ft_printf("save_path\n");
	current = env->end;
	next = 0;
	from = 0;
	while (current->from)
	{
		//print_room(current, "\t\t");
		from = current->from;
		if (!is_closed_path(current))
		{
			if (current != env->end)
				current->flag |= FL_CLOSE_PATH;
			current->next = next;
			current->from = next;
			next = current;
			//print_room(current, "\n");
			current = from;
		}
		else
			open_path(&current, &next);
	}
	//print_room(current, "\t\t");
	current->next = next;
	current->from = next;
	//print_room(current, "\n");
	return (SUCCESS);
}

static void	close_path(t_room **current, t_room **from)
{
	t_room	*room_boundary;
	t_room	*next;

	//ft_printf("close_path\n");
	room_boundary = *current;
	*current = room_boundary->from;
	room_boundary->from = *from;
	next = room_boundary;
	//print_room(room_boundary, "\n");
	//print_room(*current, "\t\t");
	while (!is_closed_path(*current))
	{
		(*current)->flag |= FL_CLOSE_PATH;
		*from = (*current)->from;
		(*current)->next = next;
		(*current)->from = next;
		next = *current;
		//print_room(*current, "\n");
		*current = *from;
		//print_room(*current, "\t\t");
	}
	room_boundary = *current;
	*current = room_boundary->next;
	room_boundary->next = next;
	*from = room_boundary;
	//print_room(room_boundary, "\n");
	//print_room(*current, "\n");
}

static int	unsave_path(t_env *env)
{
	t_room	*current;
	t_room	*from;
	t_room	*next;

	//ft_printf("\nunsave_path\n");
	current = env->start;
	next = 0;
	from = 0;
	while (current->next)
	{
		//print_room(current, "\t\t");
		next = current->next;
		if (!is_junction(current))
		{
			if (current != env->start)
				current->flag ^= FL_CLOSE_PATH;
			current->next = 0;
			current->from = from;
			from = current;
			//print_room(current, "\n");
			current = next;
		}
		else
			close_path(&current, &from);
	}
	//print_room(current, "\t\t");
	current->next = 0;
	current->from = from;
	//print_room(current, "\n");
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
	return (SUCCESS);
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

static void	free_array_path(t_path ***array_path, size_t size)
{
	while (size--)
		free((*array_path)[size]);
	free(*array_path);
	*array_path = 0;
}

static int	max_stream(t_env *env)
{
	int		max_stream;

	fill_paths_array(env, NO_UPDATE_LINKS);
	max_stream = env->paths_array[env->nb_paths - 1]->nb_ants_stream;
	free_array_path(&env->paths_array, env->nb_paths);
	return (max_stream);
}

static int	has_augmenting_path(t_env *env)
{
	t_queue	queue;

	initialize(env, &queue);
	bfs_max_flow(env, &queue);
	if (env->end->cost[0] == COST_INF)
		return (ERROR);
	save_path(env);
	++(env->nb_paths);
	if (max_stream(env) >= env->nb_ants)
	{
		unsave_path(env);
		--(env->nb_paths);
		return (MAX_FLOW_REACHED);
	}
	return (SUCCESS);
}

int		solver(t_env *env)
{
	while (has_augmenting_path(env) == SUCCESS)
		;
	if (!env->nb_paths)
		return (ERR_NO_PATH_FOUND);
	return (SUCCESS);
}
