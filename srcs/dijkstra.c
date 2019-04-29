/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:17:28 by apion             #+#    #+#             */
/*   Updated: 2019/04/29 18:38:00 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <limits.h>

static t_room	*get_neighbour_with_shortest_path(t_room *current, t_env *env)
{
	t_room	*neighour_min;
	t_room	*neighbour;
	int		dst;
	int		i;

	neighour_min = 0;
	dst = INT_MAX;
	i = 0;
	while (i < env->nb_room)
	{
		if (env->matrix[current->id][i])
		{
			neighbour = env->rooms_array[i];
			if (neighbour->dst_min_to_start < dst)
			{
				dst = neighbour->dst_min_to_start;
				neighour_min = neighbour;
			}
		}
		++i;
	}
	return (neighour_min);
}

void		dijkstra(t_env *env)
{
	t_room	*current;
	t_room	*next;
	int		i;
	int		has_neighbour;

	(void)has_neighbour;
	env->start->dst_min_to_start = 0;
	current = env->start;
	while (current != env->end)
	{
		i = 0;
		while (i < env->nb_room)
		{
			if (env->matrix[current->id][i])
			{
				next = env->rooms_array[i];
				if ((current->dst_min_to_start + 1) < next->dst_min_to_start)
					next->dst_min_to_start = current->dst_min_to_start + 1;
			}
			++i;
		}
		current = get_neighbour_with_shortest_path(current, env);
	}
}
