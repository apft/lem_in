/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:14:31 by apion             #+#    #+#             */
/*   Updated: 2019/06/07 14:25:05 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "env.h"
#include "error.h"
#include "bfs.h"
#include "tube.h"

int			check_map(t_env *env)
{
	(void)env;
	env->end->dst = bfs(env);
	if (env->end->dst < 1)
		return (ERR_ENV_NO_PATH_FROM_START_TO_END);
	return (SUCCESS);
}

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
