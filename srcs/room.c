/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:59:01 by apion             #+#    #+#             */
/*   Updated: 2019/06/11 18:16:28 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "customlibft.h"

int		external_cost(t_room *room)
{
	return (room->cost[0]);
}

int		internal_cost(t_room *room)
{
	return (room->cost[1]);
}

int		get_room_id_by_name(char *str, t_env *env, int (*cmp)())
{
	t_array_args	array_args;

	array_args = (t_array_args)
			{env->rooms_array, sizeof(t_room *), env->nb_rooms};
	return (ft_bsearch_id(str, &array_args, cmp));
}

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
