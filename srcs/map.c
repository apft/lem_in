/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:14:31 by apion             #+#    #+#             */
/*   Updated: 2019/06/12 16:40:31 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "env.h"
#include "error.h"
#include "bfs.h"
#include "tube.h"
#include "room.h"

static void	remove_self_loop(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->nb_rooms)
	{
		env->matrix[i][i] = 0;
		++i;
	}
}

void		matrix_filter(t_env *env)
{
	remove_self_loop(env);
	bfs_remove_dead_end_path(env);
	remove_oriented_tubes_back_to_start_or_from_end(env);
}

int			start_directly_linked_to_end(t_env *env)
{
	int		j;
	int		index_start;

	j = 0;
	index_start = env->start->id;
	while (j < env->nb_rooms)
	{
		if (j == env->end->id)
		{
			if (env->matrix[index_start][j])
			{
				env->start->flag |= FL_DIRECT_TO_END;
				return (1);
			}
		}
		++j;
	}
	return (0);
}
