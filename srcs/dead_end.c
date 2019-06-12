/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 12:35:14 by apion             #+#    #+#             */
/*   Updated: 2019/06/12 12:40:32 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "tube.h"

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

int			is_dead_end(t_env *env, int index, int index_parent)
{
	int		i;

	i = 0;
	while (i < env->nb_rooms)
	{
		if (i != index_parent && env->matrix[index][i])
			return (0);
		++i;
	}
	return (1);
}

void		remove_dead_end_path(t_room *dead_end, t_env *env)
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
