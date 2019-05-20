/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:51:36 by apion             #+#    #+#             */
/*   Updated: 2019/05/20 14:49:12 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "customlibft.h"
#include "tube.h"
#include "error.h"

static void	clear_queue(t_queue *queue)
{
	while (dequeue(queue) || queue->head)
		;
}

static int	rewind_dst_to_start_and_clear_queue(t_room *current, t_queue *queue)
{
	int		i;

	i = 0;
	while (current->parent)
	{
		++i;
		current = current->parent;
	}
	clear_queue(queue);
	return (i);
}

static void	initialize(t_env *env, t_queue *queue)
{
	int		i;

	i = 0;
	while (i < env->nb_room)
		env->rooms_array[i++]->visited = 0;
	*queue = (t_queue){0, 0};
	enqueue(queue, (void *)env->start);
	env->start->visited = 1;
}

int			bfs(t_env *env)
{
	t_queue	queue;
	t_room	*current;
	int		i;

	initialize(env, &queue);
	while (queue.head)
	{
		current = (t_room *)dequeue(&queue);
		if (current == env->end)
			return (rewind_dst_to_start_and_clear_queue(env->end, &queue));
		i = 0;
		while (i < env->nb_room)
		{
			if (env->matrix[current->id][i] && !env->rooms_array[i]->visited)
			{
				env->rooms_array[i]->visited = 1;
				env->rooms_array[i]->parent = current;
				enqueue(&queue, (void *)env->rooms_array[i]);
			}
			++i;
		}
	}
	return (-1);
}

void		bfs_remove_dead_end_path(t_env *env)
{
	t_queue	queue;
	t_room	*current;
	int		i;

	initialize(env, &queue);
	while (queue.head)
	{
		current = (t_room *)dequeue(&queue);
		i = 0;
		while (i < env->nb_room)
		{
			if (env->matrix[current->id][i])
			{
				if (!env->rooms_array[i]->visited && env->rooms_array[i] != env->end)
				{
					env->rooms_array[i]->visited = 1;
					env->rooms_array[i]->parent = current;
					if (is_dead_end(env, i, current->id))
						remove_dead_end_path(env->rooms_array[i], env);
					else
						enqueue(&queue, (void *)env->rooms_array[i]);
				}
			}
			++i;
		}
	}
}
