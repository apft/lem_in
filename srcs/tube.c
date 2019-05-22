/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:16:03 by apion             #+#    #+#             */
/*   Updated: 2019/05/22 10:20:33 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		is_dead_end(t_env *env, int index, int index_parent)
{
	int		i;

	i = 0;
	while (i < env->nb_room)
	{
		if (i != index_parent && env->matrix[index][i])
			return (0);
		++i;
	}
	return (1);
}

void	remove_oriented_tube_between_rooms(t_env *env,
				t_room *room_a, t_room *room_b)
{
	if (env->matrix[room_a->id][room_b->id])
	{
		env->matrix[room_a->id][room_b->id] = 0;
		room_a->nb_neighbour -= 1;
	}
}

void	remove_tube_between_rooms(t_env *env, t_room *room_a, t_room *room_b)
{
	remove_oriented_tube_between_rooms(env, room_a, room_b);
	remove_oriented_tube_between_rooms(env, room_b, room_a);
}

void	remove_oriented_tubes_back_to_start_or_from_end(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->nb_room)
	{
		remove_oriented_tube_between_rooms(env, env->rooms_array[i], env->start);
		remove_oriented_tube_between_rooms(env, env->end, env->rooms_array[i]);
		++i;
	}
}

void	remove_dead_end_path(t_room *dead_end, t_env *env)
{
	t_room	*from;

	from = dead_end->from;
	while (dead_end && from)
	{
		remove_tube_between_rooms(env, dead_end, from);
		if (from->nb_neighbour == 1)
		{
			dead_end = from;
			from = dead_end->from;
		}
		else
			return ;
	}
}
