/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:14:31 by apion             #+#    #+#             */
/*   Updated: 2019/05/01 13:08:00 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"
#include "output.h"
#include "ft_printf.h"
#include "bfs.h"
#include "tube.h"

int			check_map(t_env *env)
{
	env->end->dst_min_to_start = bfs(env);
	if (env->end->dst_min_to_start < 1)
		return (ERR_NO_PATH_FROM_START_TO_END);
	return (SUCCESS);
}

static void	compute_nb_neighbour(t_room *room, int **matrix, int size)
{
	while (size--)
		if (matrix[room->id][size])
			room->nb_neighbour += 1;
}

static void	remove_self_loop_and_compute_nb_neighbour(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->nb_room)
	{
		env->matrix[i][i] = 0;
		compute_nb_neighbour(env->rooms_array[i], env->matrix, env->nb_room);
		++i;
	}
}

void		matrix_filter(t_env *env)
{
	remove_self_loop_and_compute_nb_neighbour(env);
	bfs_remove_dead_end_path(env);
	remove_oriented_tubes_back_to_start_or_from_end(env);
}
