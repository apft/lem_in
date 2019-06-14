/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:51:36 by apion             #+#    #+#             */
/*   Updated: 2019/06/14 11:08:21 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "solver.h"
#include "dead_end.h"
#include "tube.h"
#include "customlibft.h"
#include "error.h"

static int	initialize(t_env *env, t_queue *queue)
{
	int		i;
	int		status;

	i = 0;
	while (i < env->nb_rooms)
		env->rooms_array[i++]->visited = 0;
	*queue = (t_queue){0, 0};
	status = enqueue(queue, (void *)env->start);
	if (status != SUCCESS)
		return (status);
	env->start->visited = 1;
	return (SUCCESS);
}

int			bfs_remove_dead_end_path(t_env *env)
{
	int		status;
	t_queue	queue;
	t_room	*current;

	status = initialize(env, &queue);
	if (status != SUCCESS)
		return (status);
	while (queue.head)
	{
		current = (t_room *)dequeue(&queue);
		if (!current)
			return (ERR_NULL_POINTER);
		apply_foreach_room_linked_to_ref(current, env,
			&queue, &search_for_dead_end);
	}
	return (SUCCESS);
}

int			bfs_max_flow(t_env *env, t_queue *queue)
{
	t_room	*current;
	int		status;

	while (queue->head)
	{
		current = (t_room *)dequeue(queue);
		if (!current)
			return (ERR_NULL_POINTER);
		current->visited = VISITED_AS_CURRENT;
		status = apply_foreach_room_linked_to_ref(current, env,
					queue, &search_for_valid_neighbour);
		if (status != SUCCESS)
			return (status);
	}
	return (SUCCESS);
}
