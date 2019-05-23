/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:43:55 by apion             #+#    #+#             */
/*   Updated: 2019/05/23 21:57:14 by apion            ###   ########.fr       */
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

static void	clear_queue(t_queue *queue)
{
	while (dequeue(queue) || queue->head)
		;
}

static void	open_path(t_room **room_from)
{
	t_room	*current;

	current = (*room_from)->from;
	if (!current->from)
		return ;
	while (is_closed_path(current->from))
	{
		current->flag ^= FL_CLOSE_PATH;
		current->next = 0;
		current = current->from;
	}
	current->dst = current->from->dst + 1;
	*room_from = current;
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

static int	has_oriented_tube_between_rooms(int id_room_a, int id_room_b, t_env *env)
{
	return (env->matrix[id_room_a][id_room_b]);
}

static int	is_room_already_visited(t_room *room)
{
	return (room->visited);
}

static int	is_from_start_and_closed(t_room *current, t_room *neighbour, t_env *env)
{
	return ((current == env->start && is_closed_path(neighbour))
			|| (is_closed_path(neighbour) && neighbour->from == env->start && !is_closed_path(current)));
}

static void	bfs_max_flow(t_env *env, t_queue *queue)
{
	t_room	*current;
	t_room	*neighbour;
	int		i;

	while (queue->head)
	{
		current = (t_room *)dequeue(queue);
		if (current->dst >= env->end->dst)
			continue ;
		ft_printf("%s->{", current->name);
		i = 0;
		while (i < env->nb_room)
		{
			if (has_oriented_tube_between_rooms(current->id, i, env)
					&& !is_room_already_visited(env->rooms_array[i]))
			{
				neighbour = env->rooms_array[i];
				if (neighbour != current->next && !is_from_start_and_closed(current, neighbour, env))
				{
					ft_printf("%s ", neighbour->name);
					if (neighbour != env->end)
						neighbour->visited = 1;
					neighbour->from = current;
					if (!is_closed_path(neighbour))
						neighbour->dst = neighbour->from->dst + 1;
					enqueue(queue, (void *)neighbour);
				}
			}
			++i;
		}
		ft_printf("} > ");
	}
}

static void	reset_from_path(t_env *env, t_room *current)
{
	t_room	*from;

	from = env->start;
	while (current != env->end)
	{
		current->from = from;
		from = current;
		current = current->next;
	}
}

static void	reset_from_paths(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->nb_room)
	{
		if (env->matrix[env->start->id][i] && (env->rooms_array[i]->flag & FL_CLOSE_PATH))
			reset_from_path(env, env->rooms_array[i]);
		++i;
	}
}

static int	has_augmenting_path(t_env *env)
{
	t_queue	queue;
	int		i;

	i = 0;
	while (i < env->nb_room)
		env->rooms_array[i++]->visited = 0;
	queue = (t_queue){0, 0};
	enqueue(&queue, (void *)env->start);
	env->end->dst = INT_MAX;
	env->start->visited = 1;
	reset_from_paths(env);
	bfs_max_flow(env, &queue);
	if (env->end->dst == INT_MAX)
		return (ERROR);
	save_path(env);
	clear_queue(&queue);
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
