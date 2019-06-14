/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:16:03 by apion             #+#    #+#             */
/*   Updated: 2019/06/14 11:21:15 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		has_oriented_tube_between_rooms_by_id(int id_room_a, int id_room_b,
			t_env *env)
{
	return (env->matrix[id_room_a][id_room_b]);
}

int		has_oriented_tube_between_rooms(t_room *room_a, t_room *room_b,
			t_env *env)
{
	return (has_oriented_tube_between_rooms_by_id(room_a->id, room_b->id, env));
}

void	remove_oriented_tube_between_rooms(t_env *env, t_room *room_a,
			t_room *room_b)
{
	if (has_oriented_tube_between_rooms(room_a, room_b, env))
		env->matrix[room_a->id][room_b->id] = 0;
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
	while (i < env->nb_rooms)
	{
		remove_oriented_tube_between_rooms(env, env->rooms_array[i],
			env->start);
		remove_oriented_tube_between_rooms(env, env->end, env->rooms_array[i]);
		++i;
	}
}
