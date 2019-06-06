/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_apply_foreach_neighbour.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:34:42 by apion             #+#    #+#             */
/*   Updated: 2019/06/06 10:56:05 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"

static int	has_oriented_tube_between_rooms(int id_room_a, int id_room_b,
					t_env *env)
{
	return (env->matrix[id_room_a][id_room_b]);
}

int			apply_foreach_room_linked_to_ref(t_room *ref, t_env *env,
					void *data, int (*fct)())
{
	t_room	*neighbour;
	int		status;
	int		i;

	i = 0;
	while (i < env->nb_rooms)
	{
		if (has_oriented_tube_between_rooms(ref->id, i, env))
		{
			neighbour = env->rooms_array[i];
			if (data)
				status = fct(ref, neighbour, env, data);
			else
				status = fct(ref, neighbour, env);
			if (status != SUCCESS)
				return (status);
		}
		++i;
	}
	return (SUCCESS);
}
