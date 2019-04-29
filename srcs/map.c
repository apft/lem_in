/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:14:31 by apion             #+#    #+#             */
/*   Updated: 2019/04/29 17:05:46 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"

static int	has_tube_from_start_and_to_end(t_env *env)
{
	int		i;
	int		from_start;
	int		to_end;

	if (!env->rooms_array)
		return (ERR_EMPTY_MAP);
	i = 0;
	from_start = 0;
	to_end = 0;
	while (i < env->nb_room && (!from_start || !to_end))
	{
		if (!from_start && env->matrix[env->start->id][i])
			from_start = 1;
		if (!to_end && env->matrix[i][env->end->id])
			to_end = 1;
		++i;
	}
	return (from_start && to_end);
}

int			check_map(t_env *env)
{
	if (!has_tube_from_start_and_to_end(env))
		return (ERR_NO_TUBE_FROM_START_AND_TO_END);
	return (SUCCESS);
}

void		matrix_filter(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->nb_room)
	{
		env->matrix[i][i] = 0;
		env->matrix[i][env->start->id] = 0;
		env->matrix[env->end->id][i] = 0;
		++i;
	}
}
