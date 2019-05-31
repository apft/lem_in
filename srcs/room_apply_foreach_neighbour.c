/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_apply_foreach_neighbour.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:34:42 by apion             #+#    #+#             */
/*   Updated: 2019/05/31 12:35:42 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	has_oriented_tube_between_rooms(int id_room_a, int id_room_b,
					t_env *env)
{
	return (env->matrix[id_room_a][id_room_b]);
}

void		apply_foreach_room_linked_to_ref(t_room *ref, t_env *env,
					void *data, void (*fct)())
{
	t_room	*neighbour;
	int		i;

	i = 0;
	while (i < env->nb_room)
	{
		if (has_oriented_tube_between_rooms(ref->id, i, env))
		{
			neighbour = env->rooms_array[i];
			fct(ref, neighbour, env, data);
		}
		++i;
	}
}
