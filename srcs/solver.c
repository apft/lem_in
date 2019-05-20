/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:43:55 by apion             #+#    #+#             */
/*   Updated: 2019/05/20 15:34:22 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "customlibft.h"
#include "error.h"

static void	clear_queue(t_queue *queue)
{
	while (dequeue(queue) || queue->head)
		;
}

static int save_path_and_clear_queue(t_room *end, t_queue *queue)
{
	t_room	*current;

	current = end;
	while (current->parent)
	{
		current->flag |= FL_CLOSE_PATH;
		current->parent->next = current;
		current = current->parent;
	}
	clear_queue(queue);
	return (SUCCESS);
}

static int	bfs_max_flow(t_env *env, t_room *start)
{
	t_queue	queue;
	t_room	*current;
	int		i;

	queue = (t_queue){0, 0};
	enqueue(&queue, (void *)start);
	start->visited = 1;
	while (queue.head)
	{
		current = (t_room *)dequeue(&queue);
		if (current == env->end)
			return (save_path_and_clear_queue(current, &queue));
		i = 0;
		while (i < env->nb_room)
		{
			if (env->matrix[current->id][i] && !env->rooms_array[i]->visited
					&& !(current == start && (env->rooms_array[i]->flag & FL_CLOSE_PATH)))
			{
				env->rooms_array[i]->visited = 1;
				if ((env->rooms_array[i]->flag & FL_CLOSE_PATH)
					&& bfs_max_flow(env, env->rooms_array[i]->parent) == SUCCESS)
				{
					env->rooms_array[i]->parent = current;
					current->next = env->rooms_array[i];
					return (save_path_and_clear_queue(current, &queue));
				}
				env->rooms_array[i]->parent = current;
				enqueue(&queue, (void *)env->rooms_array[i]);
			}
			++i;
		}
	}
	return (ERROR);
}

static int	has_augmenting_path(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->nb_room)
		env->rooms_array[i++]->visited = 0;
	return (bfs_max_flow(env, env->start));
}

int		solver(t_env *env)
{
	while (has_augmenting_path(env) == SUCCESS)
		;
	return (SUCCESS);
}
