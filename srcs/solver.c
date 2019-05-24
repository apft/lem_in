/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:43:55 by apion             #+#    #+#             */
/*   Updated: 2019/05/24 13:58:41 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "env.h"
#include "customlibft.h"
#include "error.h"
#include "output.h"
#include "ft_printf.h"

static int	is_closed_path(t_room *room)
{
	return (room->flag & FL_CLOSE_PATH);
}

static int	is_junction(t_room *room)
{
	return ((long)room->from_junction);
}

static int	has_oriented_tube_between_rooms(int id_room_a, int id_room_b, t_env *env)
{
	return (env->matrix[id_room_a][id_room_b]);
}

static int	is_room_already_visited(t_room *room)
{
	return (room->visited);
}

static void	apply_foreach_room_linked_to_ref(t_room *ref, t_env *env, void *data, void (*fct)())
{
	t_room	*neighbour;
	int		i;

	i = 0;
	while (i < env->nb_room)
	{
		if (has_oriented_tube_between_rooms(ref->id, i, env))
		{
			neighbour = env->rooms_array[i];
			fct(ref, neighbour, env, data);
		}
		++i;
	}
}

static void	open_path(t_room **room_from)
{
	t_room	*current;
	t_room	*next;

	current = (*room_from)->from;
	if (!current->from)
		return ;
	while (!is_junction(current))
	{
		current->flag ^= FL_CLOSE_PATH;
		next = current->next;
		current->next = 0;
		current = next;
	}
	current->dst = current->from_junction->dst + 1;
	*room_from = current->from_junction;
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
		current->next = next;
		if (current != env->end)
		{
			if (!is_closed_path(current))
				current->flag |= FL_CLOSE_PATH;
			else
				open_path(&current);
		}
		next = current;
		current = current->from;
	}
	return (SUCCESS);
}

static int	is_linked_on_same_path(t_room *room_a, t_room *room_b)
{
	if (!is_closed_path(room_a) || !is_closed_path(room_b))
		return (0);
	return (room_a->next == room_b || room_b->next == room_a);
}

static void	search_for_valid_neighbour(t_room *current, t_room *neighbour, t_env *env, t_queue *queue)
{
	if (is_room_already_visited(neighbour) && neighbour->next != current)
		return ;
	if (current == env->start && is_closed_path(neighbour))
		return ;
	if (is_closed_path(current))
	{
		if (neighbour == current->next)
			return ;
		if (is_linked_on_same_path(current, current->from))
		{
			if (neighbour == current->next)
				return ;
		}
		else if (is_junction(current))
		{
			if (neighbour->next != current)
				return ;
		}
		else
		{
			if (current->next == neighbour)
				return ;
		}
	}
	else
	{
		if (is_closed_path(neighbour) && neighbour->from == env->start)
			return ;
	}
	ft_printf("%s%s(%s) ", is_closed_path(neighbour) ? "^" : "", neighbour->name, neighbour->from ? neighbour->from->name : ".");
	if (neighbour != env->end)
		neighbour->visited = 1;
	neighbour->from = current;
	if (!is_closed_path(neighbour))
		neighbour->dst = neighbour->from->dst + 1;
	if (is_closed_path(neighbour) && !is_linked_on_same_path(current, neighbour))
		neighbour->from_junction = current;
	enqueue(queue, (void *)neighbour);
}

static void	bfs_max_flow(t_env *env, t_queue *queue)
{
	t_room	*current;

	while (queue->head)
	{
		current = (t_room *)dequeue(queue);
		if (current->dst >= env->end->dst)
			continue ;
		ft_printf("%s(%s)%s->{", current->name, current->from ? current->from->name : ".", is_junction(current) ? "*" : "");
		apply_foreach_room_linked_to_ref(current, env, queue, &search_for_valid_neighbour);
		ft_printf("} > ");
	}
}

static void	reset_from_path(t_room *from, t_room *current, t_env *env)
{
	if (!is_closed_path(current))
		return ;
	while (current != env->end)
	{
		current->from = from;
		from = current;
		current = current->next;
	}
}

static void	initialize(t_env *env, t_queue *queue)
{
	int		i;

	i = 0;
	while (i < env->nb_room)
	{
		env->rooms_array[i]->visited = 0;
		env->rooms_array[i]->from_junction = 0;
		++i;
	}
	*queue = (t_queue){0, 0};
	enqueue(queue, (void *)env->start);
	env->end->dst = INT_MAX;
	env->start->visited = 1;
	apply_foreach_room_linked_to_ref(env->start, env, (void *)0, &reset_from_path);
}

static int	has_augmenting_path(t_env *env)
{
	t_queue	queue;

	initialize(env, &queue);
	bfs_max_flow(env, &queue);
	if (env->end->dst == INT_MAX)
		return (ERROR);
	save_path(env);
	return (SUCCESS);
}

int		solver(t_env *env)
{
	int	i;

	i = 0;
	while (has_augmenting_path(env) == SUCCESS)
	{
		ft_printf("\n");
		ft_printf("Loop %d:\n", i++);
		print_paths(env);
	}
	ft_printf("\n");
	return (SUCCESS);
}
