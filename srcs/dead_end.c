/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 12:35:14 by apion             #+#    #+#             */
/*   Updated: 2019/06/14 11:08:43 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "tube.h"
#include "customlibft.h"

static int	nb_of_neighbours(t_room *room, t_env *env)
{
	int		nb_neighbours;
	int		i;

	nb_neighbours = 0;
	i = 0;
	while (i < env->nb_rooms)
	{
		nb_neighbours += env->matrix[room->id][i];
		++i;
	}
	return (nb_neighbours);
}

static int	is_dead_end(t_room *current, t_room *neighbour, t_env *env)
{
	int		i;

	i = 0;
	while (i < env->nb_rooms)
	{
		if (i != current->id
			&& has_oriented_tube_between_rooms_by_id(neighbour->id, i, env))
			return (0);
		++i;
	}
	return (1);
}

static void	remove_dead_end_path(t_room *dead_end, t_env *env)
{
	t_room	*from;

	from = dead_end->from;
	while (dead_end && from)
	{
		remove_tube_between_rooms(env, dead_end, from);
		if (nb_of_neighbours(from, env) == 1)
		{
			dead_end = from;
			from = dead_end->from;
		}
		else
			return ;
	}
}

int			search_for_dead_end(t_room *current, t_room *neighbour,
				t_env *env, t_queue *queue)
{
	int		status;

	if (neighbour->visited || neighbour == env->end)
		return (loop_continue);
	neighbour->visited = 1;
	neighbour->from = current;
	if (is_dead_end(current, neighbour, env))
		remove_dead_end_path(neighbour, env);
	else
	{
		status = enqueue(queue, (void *)neighbour);
		if (status != SUCCESS)
			return (status);
	}
	return (loop_success);
}
