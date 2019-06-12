/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:51:36 by apion             #+#    #+#             */
/*   Updated: 2019/06/12 16:40:21 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "solver.h"
#include "dead_end.h"
#include "tube.h"
#include "customlibft.h"
#include "error.h"
#include "tests.h"

static void	initialize(t_env *env, t_queue *queue)
{
	int		i;

	i = 0;
	while (i < env->nb_rooms)
		env->rooms_array[i++]->visited = 0;
	*queue = (t_queue){0, 0};
	enqueue(queue, (void *)env->start);
	env->start->visited = 1;
}

void		bfs_remove_dead_end_path(t_env *env)
{
	t_queue	queue;
	t_room	*current;

	initialize(env, &queue);
	while (queue.head)
	{
		current = (t_room *)dequeue(&queue);
		apply_foreach_room_linked_to_ref(current, env,
				&queue, &search_for_dead_end);
	}
}

void		bfs_max_flow(t_env *env, t_queue *queue)
{
	t_room	*current;

	while (queue->head)
	{
		current = (t_room *)dequeue(queue);
		current->visited = VISITED_AS_CURRENT;
		apply_foreach_room_linked_to_ref(current, env,
				queue, &search_for_valid_neighbour);
		test_cost(current);
	}
}
